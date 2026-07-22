#pragma once

#if !defined(BIGDEC_USE_CUSTOM_ALLOC)
#define BIGDEC_ALLOC(x) malloc(x)
#define BIGDEC_FREE(x) free(x)
#endif

#define BIGDEC_SQRT_THRESHOLD 1000
#define BIGDEC_E_TAYLOR_THRESHOLD 1000
#define BIGDEC_E_TAYLOR_THRESHOLD_STRING "1000"
#define BIGDEC_E_BROTHERS_THRESHOLD 1000
#define BIGDEC_E_BROTHERS_THRESHOLD_STRING "1000"
#define BIGDEC_GUARD_THRESHOLD 10
#define BIGDEC_LN_THRESHOLD 10000
#define BIGDEC_LN_THRESHOLD_STRING "10000"

#include "bigInteger.h"

#ifdef __cplusplus
extern "C" {
#endif

struct BigDec_ {
  BigInt * value;
  int scale;
};

typedef struct BigDec_ BigDec;
void BigDec_init(BigDec * b);
void BigDec_init_from_string(BigDec *, char *);
void BigDec_set_from_string(BigDec *, char *);
void BigDec_copy(BigDec *, BigDec *);
void BigDec_destroy(BigDec * b);
void BigDec_reduce_scale_and_round(BigDec * b, int);
void BigDec_reduce_scale_and_cut(BigDec * b, int);
void BigDec_reduce_scale(BigDec *);
char * BigDec_to_string(BigDec *);
void BigDec_increase_scale(BigDec *, int);
void BigDec_decrease_scale_and_round(BigDec *, int);
int BigDec_cmp(BigDec *, BigDec *);
void BigDec_add(BigDec *, BigDec *, BigDec *, int);
void BigDec_subtract(BigDec *, BigDec *, BigDec *, int);
void BigDec_multiply(BigDec *, BigDec *, BigDec *, int);
void BigDec_multiply_prec(BigDec *, BigDec *, BigDec *, int);
void BigDec_divide(BigDec *, BigDec *, BigDec *, int);
void BigDec_power_int(BigDec *, BigDec *, int, int);
void BigDec_sqrt(BigDec *, BigDec *, int);
void BigDec_e_taylor_and_brothers(BigDec *, BigDec *, int);
void BigDec_ln_atanh(BigDec *, BigDec *, int);

#if defined(BIGDEC_IMPL) || defined(MPA_IMPL)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void BigDec_init(BigDec * b) {
  b->value = (BigInt *) BIGDEC_ALLOC(1 * sizeof(BigInt));
  BigInt_init(b->value);
  b->scale = 0;
}

void BigDec_set_from_string(BigDec * z, char * s) {
  BigInt b;
  int len = strlen(s);
  char * new_s = (char *) BIGDEC_ALLOC((len + 1) * sizeof(char));
  int i, j = 0;
  int flag = 0;
  int scale = 0;
  int is_negative = 0;
  
  if (s[0] == '-') {
    is_negative = 1;
    s = s + 1;
  }
  
  for (i = 0; i < len - is_negative; i++) {
    if (s[i] == '.') {
      flag = 1;
      continue;
    }
    if (flag) {
      scale++;
    }
    new_s[j] = s[i];
    j++;
  }
  
  new_s[j] = 0;
  /* printf("BigDec str is %s, scale is %d, is negative: %d\n", new_s, scale, is_negative); */
  BigInt_init_from_string(&b, new_s);
  BigInt_copy(z->value, &b);
  z->scale = scale;
  if (is_negative) {
    z->value->sign = -1;
  }
  BigDec_reduce_scale(z);
  BigInt_destroy(&b);
  BIGDEC_FREE(new_s);
}

void BigDec_init_from_string(BigDec * b, char * s) {
  int len = strlen(s);
  char * new_s = (char *) BIGDEC_ALLOC((len + 1) * sizeof(char));
  int i, j = 0;
  int flag = 0;
  int scale = 0;
  int is_negative = 0;
  
  if (s[0] == '-') {
    is_negative = 1;
    s = s + 1;
  }
  
  for (i = 0; i < len - is_negative; i++) {
    if (s[i] == '.') {
      flag = 1;
      continue;
    }
    if (flag) {
      scale++;
    }
    new_s[j] = s[i];
    j++;
  }
  
  new_s[j] = 0;
  /* printf("BigDec str is %s, scale is %d, is negative: %d\n", new_s, scale, is_negative); */
  b->value = (BigInt *) BIGDEC_ALLOC(1 * sizeof(BigInt));
  BigInt_init_from_string(b->value, new_s);
  b->scale = scale;
  if (is_negative) {
    b->value->sign = -1;
  }
  BigDec_reduce_scale(b);
  BIGDEC_FREE(new_s);
}

void BigDec_copy(BigDec * dest, BigDec * src) {
  dest->scale = src->scale;
  BigInt_copy(dest->value, src->value);
}

void BigDec_destroy(BigDec * b) {
  BigInt_destroy(b->value);
  BIGDEC_FREE(b->value);
  b->scale = 0;
}

void BigDec_reduce_scale(BigDec * b) {
  int i, removed = 0;
  BigInt out1, out2, base, temp;
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);

  BigInt_set_from_limb(&base, BIGINT_BASE, 10);

  for (i = 0; i < b->value->internalSize; i++) {
    BigInt_base_multiply(&out2, &out1, &base, 10);
    BigInt_set_from_limb(&temp, b->value->internalRepresentation[b->value->internalSize - 1 - i], 10);
    BigInt_base_add(&out1, &out2, &temp, 10);
  }
  
  i = 0;
  while(i < out1.internalSize && out1.internalRepresentation[i] == 0 && b->scale > 0) {
    i++;
    removed++;
    b->scale = b->scale - 1;
  }
  
  if (i >= out1.internalSize) {
    b->value->internalRepresentation[0] = 0;
    b->value->sign = 0;
    b->value->internalSize = 1;
    b->scale = 0;
  } else {
    BigInt_set_from_int(&base, 10);
    BigInt_power(&temp, &base, removed);
    BigInt_divide_s(b->value, b->value, &temp);
  }
  
  /* BigInt_print(b->value);
  
  printf("\n"); */
  
  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);
}

void BigDec_reduce_scale_and_round(BigDec * b, int prec) {
  int i, removed = 0;
  BigInt out1, out2, base, temp;
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);

  BigInt_set_from_limb(&base, BIGINT_BASE, 10);

  for (i = 0; i < b->value->internalSize; i++) {
    BigInt_base_multiply(&out2, &out1, &base, 10);
    BigInt_set_from_limb(&temp, b->value->internalRepresentation[b->value->internalSize - 1 - i], 10);
    BigInt_base_add(&out1, &out2, &temp, 10);
  }
  
  i = 0;
  while(i < out1.internalSize && out1.internalRepresentation[i] == 0 && b->scale > 0) {
    i++;
    removed++;
    b->scale = b->scale - 1;
  }
  
  if (i >= out1.internalSize) {
    b->value->internalRepresentation[0] = 0;
    b->value->sign = 0;
    b->value->internalSize = 1;
    b->scale = 0;
  } else {
    BigInt_set_from_int(&base, 10);
    BigInt_power(&temp, &base, removed);
    BigInt_divide_s(b->value, b->value, &temp);
    /*  Rounding is still under testing */
    
    /* printf("Prec is %d, scale is %d\n",prec, b->scale); */
    
    if (b->scale > 0 && b->scale > prec) {
      if (out1.internalRepresentation[i] >= 5) {
        int s = b->value->sign;
        BigInt_set_from_int(&temp, 10);
        BigInt_divide_s(b->value, b->value, &temp);
        b->scale--;
        BigInt_set_from_int(&temp, 1);
        b->value->sign = 1;
        BigInt_add_s(b->value, b->value, &temp);
        b->value->sign = s;
      } else {
        BigInt_set_from_int(&temp, 10);
        BigInt_divide_s(b->value, b->value, &temp);
        b->scale--;
      }
    }
  }
  
  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);
}

void BigDec_reduce_scale_and_cut(BigDec * b, int prec) {
  int i, removed = 0;
  BigInt out1, out2, base, temp;
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);

  BigInt_set_from_limb(&base, BIGINT_BASE, 10);

  for (i = 0; i < b->value->internalSize; i++) {
    BigInt_base_multiply(&out2, &out1, &base, 10);
    BigInt_set_from_limb(&temp, b->value->internalRepresentation[b->value->internalSize - 1 - i], 10);
    BigInt_base_add(&out1, &out2, &temp, 10);
  }
  
  i = 0;
  while(i < out1.internalSize && out1.internalRepresentation[i] == 0 && b->scale > 0) {
    i++;
    removed++;
    b->scale = b->scale - 1;
  }
  
  if (i >= out1.internalSize) {
    b->value->internalRepresentation[0] = 0;
    b->value->sign = 0;
    b->value->internalSize = 1;
    b->scale = 0;
  } else {
    BigInt_set_from_int(&base, 10);
    BigInt_power(&temp, &base, removed);
    BigInt_divide_s(b->value, b->value, &temp);
    /*  Rounding is still under testing */
    
    /* printf("Prec is %d, scale is %d\n",prec, b->scale); */
    
    if (b->scale > 0 && b->scale > prec) {
      removed = b->scale - prec - 1;
      i += removed;
      BigInt_power(&temp, &base, removed);
      BigInt_divide_s(b->value, b->value, &temp);
      b->scale = b->scale - removed;
      if (out1.internalRepresentation[i] >= 5) {
        int s = b->value->sign;
        BigInt_set_from_int(&temp, 10);
        BigInt_divide_s(b->value, b->value, &temp);
        b->scale--;
        BigInt_set_from_int(&temp, 1);
        b->value->sign = 1;
        BigInt_add_s(b->value, b->value, &temp);
        b->value->sign = s;
        i++;
      } else {
        BigInt_set_from_int(&temp, 10);
        BigInt_divide_s(b->value, b->value, &temp);
        b->scale--;
      }
      
      /* printf("Scale is %d\n", b->scale); */
    }
  }
  
  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);
}

char * BigDec_to_string(BigDec * b) {
  BigDec c;
  int i, j, isNegative = 0, hasDot = 0, scale;
  int allocChar;
  char * str;
  BigInt out1, out2, base, temp;
  
  BigDec_init(&c);
  
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);
  
  BigDec_copy(&c, b);
  BigDec_reduce_scale(&c);
  
  scale = c.scale;

  BigInt_set_from_limb(&base, BIGINT_BASE, 10);

  for (i = 0; i < c.value->internalSize; i++) {
    BigInt_base_multiply(&out2, &out1, &base, 10);
    BigInt_set_from_limb(&temp, c.value->internalRepresentation[c.value->internalSize - 1 - i], 10);
    BigInt_base_add(&out1, &out2, &temp, 10);
  }
  
  if (c.scale > 0) {
    hasDot = 1;
  }
  
  if (c.value->sign == -1) {
    isNegative = 1;
  }
  
  allocChar = BigInt_max_int(out1.internalSize, c.scale + 1) + isNegative + hasDot + 1;
  
  /* printf("alloc: %d\n", allocChar); */
  
  str = (char *) BIGDEC_ALLOC(allocChar * sizeof(char));
  
  for (i = 0; i < allocChar; i++) {
    str[i] = '0';
  }
  
  if (isNegative) {
    str[0] = '-';
  }
  
  j = 0;
  
  for (i = allocChar - 2; i >= 0; i--) {
    if (hasDot && scale == 0) {
      str[i] = '.';
      scale--;
      continue;
    }
    if (j < out1.internalSize) {
      str[i] = out1.internalRepresentation[j] + '0';
      j++;
    }
    if (hasDot && scale > 0) {
      scale--;
    }
  }
  
  str[allocChar - 1] = 0;
  
  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);
  
  BigDec_destroy(&c);
  
  return str;
}

void BigDec_increase_scale(BigDec * b, int scale) {
  BigInt b10, temp;
  
  if (scale < 1) {
    return;
  }
  
  BigInt_init(&temp);
  BigInt_init_from_int(&b10, 10);
  
  BigInt_power(&temp, &b10, scale);
  
  BigInt_multiply_s(b->value, b->value, &temp);
  
  /* BigInt_print(b->value);
  
  printf("\n"); */
  b->scale = b->scale + scale;
  
  BigInt_destroy(&temp);
  BigInt_destroy(&b10);
}

void BigDec_decrease_scale_and_round(BigDec * b, int prec) {
  BigInt b10, temp;
  BigInt temp2, n;
  int p;
  
  if (prec < 0) {
    return;
  }
  
  if (b->scale > prec) {
    p = b->scale - prec - 1;
    BigInt_init(&temp);
    BigInt_init_from_int(&b10, 10);
    BigInt_init(&temp2);
    BigInt_init(&n);
    
    BigInt_power(&temp, &b10, p);
    
    BigInt_divide_s(b->value, b->value, &temp);
    
    b->scale = b->scale - p;
    
    BigInt_copy(&temp2, b->value);
    
    BigInt_set_from_int(&n, 10);
    
    BigInt_divide_s(&temp2, &temp2, &n);
    BigInt_multiply_s(&temp2, &temp2, &n);
    
    BigInt_subtract_s(&temp, b->value, &temp2);
    BigInt_set_from_int(&n, 5);
    
    if (BigInt_cmp(&temp, &n) >= 0) {
      BigInt_set_from_int(&n, 10);
      BigInt_divide_s(b->value, b->value, &n);
      BigInt_set_from_int(&n, 1);
      if (b->value->sign > 0) {
        BigInt_add_s(b->value, b->value, &n);
      } else if (b->value->sign < 0) {
        BigInt_subtract_s(b->value, b->value, &n);
      }
      b->scale--;
    } else {
      BigInt_set_from_int(&n, 10);
      BigInt_divide_s(b->value, b->value, &n);
      b->scale--;
    }
    
    BigInt_destroy(&temp);
    BigInt_destroy(&temp2);
    BigInt_destroy(&b10);
    BigInt_destroy(&n);
  }
  
  /* BigInt_print(b->value);
  
  printf("\n"); */
}

void BigDec_truncate(BigDec * dest, BigDec * src) {
  BigInt b10, temp;
  BigDec c;
    
  BigInt_init(&temp);
  BigInt_init_from_int(&b10, 10);
  BigDec_init(&c);
  
  BigDec_copy(&c, src);
  
  BigInt_power(&temp, &b10, c.scale);
  BigInt_divide_s(c.value, c.value, &temp);
  c.scale = 0;
  
  BigDec_copy(dest, &c);
  
  BigDec_destroy(&c);
  BigInt_destroy(&temp);
  BigInt_destroy(&b10);
}

int BigDec_cmp(BigDec * a, BigDec * b) {
  int max_scale, result, sc1, sc2;
  
  BigDec operand1, operand2;
  
  BigDec_init(&operand1);
  BigDec_init(&operand2);
  
  BigDec_copy(&operand1, a);
  BigDec_copy(&operand2, b);
  
  max_scale = BigInt_max_int(a->scale, b->scale);
  
  sc1 = max_scale - a->scale;
  sc2 = max_scale - b->scale;
  
  if (sc1 > 0) {
    BigDec_increase_scale(&operand1, sc1);
  }
  
  if (sc2 > 0) {
    BigDec_increase_scale(&operand2, sc2);
  }
  
  result = BigInt_cmp(operand1.value, operand2.value);
  
  BigDec_destroy(&operand1);
  BigDec_destroy(&operand2);
  
  return result;
}

void BigDec_add(BigDec * sum, BigDec * addend1, BigDec * addend2, int prec) {
  int max_scale = BigInt_max_int(addend1->scale, addend2->scale);
  int sc1, sc2;
  
  BigDec operand1, operand2;
  
  BigDec_init(&operand1);
  BigDec_init(&operand2);
  
  BigDec_copy(&operand1, addend1);
  BigDec_copy(&operand2, addend2);
  
  sc1 = max_scale - addend1->scale;
  sc2 = max_scale - addend2->scale;
  
  if (sc1 > 0) {
    BigDec_increase_scale(&operand1, sc1);
  }
  
  if (sc2 > 0) {
    BigDec_increase_scale(&operand2, sc2);
  }
  
  BigInt_add_s(sum->value, operand1.value, operand2.value);
  sum->scale = max_scale;
  
  BigDec_destroy(&operand1);
  BigDec_destroy(&operand2);
  
  BigDec_decrease_scale_and_round(sum, prec);
}

void BigDec_subtract(BigDec * diff, BigDec * minuend, BigDec * subtrahend, int prec) {
  int max_scale = BigInt_max_int(minuend->scale, subtrahend->scale);
  int sc1, sc2;
  
  BigDec operand1, operand2;
  
  BigDec_init(&operand1);
  BigDec_init(&operand2);
  
  BigDec_copy(&operand1, minuend);
  BigDec_copy(&operand2, subtrahend);
  
  sc1 = max_scale - minuend->scale;
  sc2 = max_scale - subtrahend->scale;
  
  if (sc1 > 0) {
    BigDec_increase_scale(&operand1, sc1);
  }
  
  if (sc2 > 0) {
    BigDec_increase_scale(&operand2, sc2);
  }
  
  BigInt_subtract_s(diff->value, operand1.value, operand2.value);
  diff->scale = max_scale;
  
  BigDec_destroy(&operand1);
  BigDec_destroy(&operand2);
  
  BigDec_decrease_scale_and_round(diff, prec);
}

void BigDec_multiply(BigDec * product, BigDec * multiplicand, BigDec * multiplier, int prec) {
  int scale = multiplicand->scale + multiplier->scale;
  
  BigInt_multiply_auto_s(product->value, multiplicand->value, multiplier->value);
  product->scale = scale;
  
  BigDec_decrease_scale_and_round(product, prec);
}

void BigDec_multiply_prec(BigDec * product, BigDec * multiplicand, BigDec * multiplier, int prec) {
  int scale = multiplicand->scale + multiplier->scale;
  
  BigInt_multiply_s(product->value, multiplicand->value, multiplier->value);
  product->scale = scale;
  
  BigDec_reduce_scale_and_cut(product, prec);
}

void BigDec_divide(BigDec * quotient, BigDec * dividend, BigDec * divisor, int prec) {
  int scale = dividend->scale - divisor->scale;
  int newPrec;
  
  BigDec operand1;
  
  BigDec_init(&operand1);
  
  BigDec_copy(&operand1, dividend);
  
  if (scale < 0) {
    newPrec = (scale * -1) + prec + 1;
  } else {
    newPrec = prec + 1;
  }
  
  scale = scale + newPrec;
  
  BigDec_increase_scale(&operand1, newPrec);
  
  BigInt_divide_s(quotient->value, operand1.value, divisor->value);
  quotient->scale = scale;
  
  BigDec_decrease_scale_and_round(quotient, prec);
  
  BigDec_destroy(&operand1);
}

void BigDec_power_int(BigDec * result, BigDec * base, int exponent, int prec) {
  BigDec basetemp;
  BigDec_init(&basetemp);
  BigDec_copy(&basetemp, base);
  BigInt_set_from_int(result->value, 1);
  result->scale = 0;
  while (exponent > 0) {
    if (exponent & 1) {
      BigDec_multiply(result, result, &basetemp, prec);
    }
    BigDec_multiply(&basetemp, &basetemp, &basetemp, prec);
    exponent = exponent >> 1;
  }
  BigDec_destroy(&basetemp);
}

void BigDec_sqrt(BigDec * dest, BigDec * src, int prec) {
  BigDec s;
  BigDec two;
  BigDec x;
  
  BigDec temp;
  
  int i = 0;
  
  BigDec_init(&s);
  BigDec_init_from_string(&two, "2");
  BigDec_init(&x);
  BigDec_init(&temp);
  
  BigDec_copy(&s, src);
  BigDec_divide(&x, &s, &two, prec);
  
  while (i < BIGDEC_SQRT_THRESHOLD) {
    BigDec_divide(&temp, &s, &x, prec);
    BigDec_add(&temp, &temp, &x, prec);
    BigDec_divide(&temp, &temp, &two, prec);
    
    if (BigDec_cmp(&x, &temp) == 0) {
      break;
    }
    
    BigDec_copy(&x, &temp);
    i++;
  }
  
  BigDec_copy(dest, &x);
  
  BigDec_destroy(&s);
  BigDec_destroy(&two);
  BigDec_destroy(&x);
  BigDec_destroy(&temp);
}
int BigDec_sqrt_with_bound(BigDec * dest, BigDec * src, BigDec * bound, int prec) {
  BigDec s;
  BigDec two;
  BigDec x;
  
  BigDec temp;
  
  int i = 0;
  int iter = 0;
  
  BigDec_init(&s);
  BigDec_init_from_string(&two, "2");
  BigDec_init(&x);
  BigDec_init(&temp);
  
  BigDec_copy(&s, src);
  BigDec_divide(&x, &s, &two, prec);
  
  while (i < BIGDEC_SQRT_THRESHOLD) {
    BigDec_divide(&temp, &s, &x, prec);
    BigDec_add(&temp, &temp, &x, prec);
    BigDec_divide(&temp, &temp, &two, prec);
    
    if (BigDec_cmp(&x, &temp) == 0) {
      BigDec_copy(&s, &temp);
      iter++;
      if (BigDec_cmp(&s, bound) <= 0) {
        break;
      }
    }
    
    BigDec_copy(&x, &temp);
    i++;
  }
  
  BigDec_copy(dest, &x);
  
  BigDec_destroy(&s);
  BigDec_destroy(&two);
  BigDec_destroy(&x);
  BigDec_destroy(&temp);
  
  return iter;
}

void BigDec_e_taylor(BigDec * dest, BigDec * x, int prec) {
  BigDec sum, term, n, oldSum, th, one;
  int new_prec = prec + BIGDEC_GUARD_THRESHOLD;
  
  BigDec_init_from_string(&sum, "1");
  BigDec_init_from_string(&term, "1");
  BigDec_init_from_string(&n, "1");
  BigDec_init(&oldSum);
  BigDec_init_from_string(&one, "1");
  BigDec_init_from_string(&th, BIGDEC_E_TAYLOR_THRESHOLD_STRING);
  
  
  while (BigDec_cmp(&n, &th) < 0) {
    BigDec_copy(&oldSum, &sum);
    BigDec_multiply(&term, &term, x, new_prec);
    BigDec_divide(&term, &term, &n, new_prec);
    BigDec_add(&sum, &sum, &term, new_prec);
    BigDec_add(&n, &n, &one, new_prec);
    
    if (BigDec_cmp(&sum, &oldSum) == 0) {
      /* printf("Iterations: %d\n", n.value->internalRepresentation[0]); */
      break;
    }
  }
  
  BigDec_decrease_scale_and_round(&sum, prec);
  BigDec_copy(dest, &sum);
  
  BigDec_destroy(&sum);
  BigDec_destroy(&term);
  BigDec_destroy(&n);
  BigDec_destroy(&oldSum);
  BigDec_destroy(&th);
  BigDec_destroy(&one);
}

void BigDec_e_brothers(BigDec * dest, int prec) {
  BigDec num, denom, terms, term, one, i, th, c;
  int new_prec = prec + BIGDEC_GUARD_THRESHOLD;
  
  BigDec_init_from_string(&num, "2");
  BigDec_init_from_string(&denom, "1");
  BigDec_init_from_string(&terms, "2");
  BigDec_init(&term);
  BigDec_init_from_string(&one, "1");
  BigDec_init(&i);
  BigDec_init_from_string(&th, BIGDEC_E_BROTHERS_THRESHOLD_STRING);
  BigDec_init(&c);
  int o = 0;
  
  while (BigDec_cmp(&i, &th) < 0) {
    BigDec_copy(&c, &terms);
    BigDec_multiply(&denom, &denom, &num, new_prec);
    BigDec_add(&num, &num, &one, new_prec);
    BigDec_multiply(&denom, &denom, &num, new_prec);
    BigDec_add(&num, &num, &one, new_prec);
    BigDec_divide(&term, &num, &denom, new_prec);
    BigDec_add(&terms, &terms, &term, new_prec);
    o++;
    
    if (BigDec_cmp(&c, &terms) == 0) {
      /* printf("Iterations: %d\n", o); */
      break;
    }
  }
  
  BigDec_decrease_scale_and_round(&terms, prec);
  BigDec_copy(dest, &terms);
  
  BigDec_destroy(&num);  
  BigDec_destroy(&denom);
  BigDec_destroy(&terms);
  BigDec_destroy(&term);
  BigDec_destroy(&one);
  BigDec_destroy(&i);
  BigDec_destroy(&th);
  BigDec_destroy(&c);
}

void BigDec_e_taylor_and_brothers(BigDec * dest, BigDec * src, int prec) {
  int new_prec = prec + BIGDEC_GUARD_THRESHOLD;
  BigDec intpart, decimalpart, e_int, e_dec, one;
  
  BigDec_init(&intpart);
  BigDec_init(&decimalpart);
  BigDec_init(&e_int);
  BigDec_init(&e_dec);
  BigDec_init_from_string(&one, "1");
  
  BigDec_truncate(&intpart, src);
  BigDec_subtract(&decimalpart, src, &intpart, new_prec);
  
  BigDec_e_taylor(&e_dec, &decimalpart, new_prec);
  BigDec_e_brothers(&e_int, new_prec);
  BigDec_power_int(&e_int, &e_int, intpart.value->internalRepresentation[0], new_prec);
  if (intpart.value->sign < 0) {
    BigDec_divide(&e_int, &one, &e_int, new_prec);
  }
  BigDec_multiply(dest, &e_int, &e_dec, new_prec);
  BigDec_decrease_scale_and_round(dest, prec);
  
  BigDec_destroy(&intpart);
  BigDec_destroy(&decimalpart);
  BigDec_destroy(&e_int);
  BigDec_destroy(&e_dec);
  BigDec_destroy(&one);
}

void BigDec_ln_slow(BigDec * dest, BigDec * src, int prec) {
  BigDec yn, x, e_yn, i, th, old, diff, one;
  int new_prec = prec + BIGDEC_GUARD_THRESHOLD, j = 0;
  
  BigDec_init(&yn);
  BigDec_init(&x);
  BigDec_init(&e_yn);
  BigDec_init(&i);
  BigDec_init_from_string(&th, BIGDEC_LN_THRESHOLD_STRING);
  BigDec_init(&old);
  BigDec_init(&diff);
  BigDec_init_from_string(&one, "1");
  
  BigDec_copy(&x, src);
  BigDec_copy(&yn, src);
  
  while(BigDec_cmp(&i, &th) < 0) {
    BigDec_copy(&old, &yn);
    BigDec_e_taylor_and_brothers(&e_yn, &yn, new_prec);
    BigDec_subtract(&diff, &x, &e_yn, new_prec);
    BigDec_divide(&diff, &diff, &e_yn, new_prec);
    BigDec_add(&diff, &diff, &yn, new_prec);
    BigDec_copy(&yn, &diff);
    
    j++;
    
    if (BigDec_cmp(&yn, &old) == 0) {
      /* printf("Ln iterations: %d\n", j); */
      break;
    }
    
    BigDec_add(&i, &i, &one, new_prec);
  }
  
  BigDec_decrease_scale_and_round(&yn, prec);
  BigDec_copy(dest, &yn);
  
  BigDec_destroy(&yn);
  BigDec_destroy(&x);
  BigDec_destroy(&e_yn);
  BigDec_destroy(&i);
  BigDec_destroy(&th);
  BigDec_destroy(&old);
  BigDec_destroy(&diff);
  BigDec_destroy(&one);
  
}

void BigDec_ln_atanh(BigDec * dest, BigDec * src, int prec) {
  BigDec z, one, two, new_z, num, denom, sum, temp, bound;
  int twos_count = 0, new_prec = prec + BIGDEC_GUARD_THRESHOLD, j = 0;
  
  BigDec_init(&z);
  BigDec_init(&new_z);
  BigDec_init_from_string(&one, "1");
  BigDec_init_from_string(&two, "2");
  BigDec_init(&num);
  BigDec_init(&denom);
  BigDec_init(&sum);
  BigDec_init(&temp);
  BigDec_init_from_string(&bound, "1.05");
  
  BigDec_copy(&z, src);
  
  /* while(BigDec_cmp(&z, &bound) > 0) {
    BigDec_sqrt(&z, &z, new_prec);
    twos_count++;
  } */
  twos_count = BigDec_sqrt_with_bound(&z, &z, &bound, new_prec);
  /* printf("two's count: %d\n", twos_count); */
  
  BigDec_subtract(&num, &z, &one, new_prec);
  BigDec_add(&denom, &z, &one, new_prec);
  BigDec_divide(&new_z, &num, &denom, new_prec);
  
  BigDec_copy(&num, &new_z);
  BigInt_set_from_int(denom.value, 1);
  denom.scale = 0;
  BigDec_copy(&sum, &new_z);
  
  while (j < BIGDEC_LN_THRESHOLD) {
    BigDec_copy(&temp, &sum);
    BigDec_multiply(&num, &num, &new_z, new_prec);
    BigDec_multiply(&num, &num, &new_z, new_prec);
    BigDec_add(&denom, &denom, &two, new_prec);
    BigDec_divide(&z, &num, &denom, new_prec);
    BigDec_add(&sum, &sum, &z, new_prec);
    
    j++;
    
    if (BigDec_cmp(&temp, &sum) == 0) {
      /* printf("Ln atanh iter: %d\n", j); */
      break;
    }
  }
  
  BigDec_multiply(&sum, &sum, &two, new_prec);
  BigDec_power_int(&two, &two, twos_count, new_prec);
  BigDec_multiply(&sum, &sum, &two, new_prec);
  
  BigDec_decrease_scale_and_round(&sum, prec);
  BigDec_copy(dest, &sum);
  
  BigDec_destroy(&z);
  BigDec_destroy(&new_z);
  BigDec_destroy(&one);
  BigDec_destroy(&two);
  BigDec_destroy(&num);
  BigDec_destroy(&denom);
  BigDec_destroy(&sum);
  BigDec_destroy(&temp);
  BigDec_destroy(&bound);
}

#endif

#ifdef __cplusplus
}
#endif
