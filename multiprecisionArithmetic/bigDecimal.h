#pragma once

#if !defined(BIGDEC_USE_CUSTOM_ALLOC)
#define BIGDEC_ALLOC(x) malloc(x)
#define BIGDEC_FREE(x) free(x)
#endif

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
void BigDec_destroy(BigDec * b);
void BigDec_reduce_scale(BigDec *);
char * BigDec_to_string(BigDec *);
void BigDec_increase_scale(BigDec *, int);
int BigDec_cmp(BigDec *, BigDec *);
void BigDec_add(BigDec *, BigDec *, BigDec *);
void BigDec_subtract(BigDec *, BigDec *, BigDec *);
void BigDec_multiply(BigDec *, BigDec *, BigDec *);
void BigDec_divide(BigDec *, BigDec *, BigDec *, int);

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
  
  BigInt_remove_leading_zeroes(b->value);

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
    return ;
  }
  
  BigInt_set_from_int(&base, 10);
  
  BigInt_power(&temp, &base, removed);
  
  BigInt_divide_s(b->value, b->value, &temp);
  
  /* BigInt_print(b->value);
  
  printf("\n"); */
  
  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);
}

char * BigDec_to_string(BigDec * b) {
  int i, j, isNegative = 0, hasDot = 0, scale = b->scale;
  int allocChar;
  char * str;
  BigInt out1, out2, base, temp;
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);
  
  BigInt_remove_leading_zeroes(b->value);

  BigInt_set_from_limb(&base, BIGINT_BASE, 10);

  for (i = 0; i < b->value->internalSize; i++) {
    BigInt_base_multiply(&out2, &out1, &base, 10);
    BigInt_set_from_limb(&temp, b->value->internalRepresentation[b->value->internalSize - 1 - i], 10);
    BigInt_base_add(&out1, &out2, &temp, 10);
  }
  
  if (b->scale > 0) {
    hasDot = 1;
  }
  
  if (b->value->sign == -1) {
    isNegative = 1;
  }
  
  allocChar = BigInt_max_int(out1.internalSize, b->scale + 1) + isNegative + hasDot + 1;
  
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
  
  return str;
}

void BigDec_increase_scale(BigDec * b, int scale) {
  BigInt b10, temp;
  BigInt_init(&temp);
  BigInt_init_from_int(&b10, 10);
  
  BigInt_power(&temp, &b10, scale);
  
  BigInt_multiply_s(b->value, b->value, &temp);
  
  /* BigInt_print(b->value);
  
  printf("\n"); */
  
  BigInt_destroy(&temp);
  BigInt_destroy(&b10);
}

int BigDec_cmp(BigDec * a, BigDec * b) {
  int max_scale, result;
  
  max_scale = BigInt_max_int(a->scale, b->scale);
  
  BigDec_increase_scale(a, max_scale - a->scale);
  BigDec_increase_scale(b, max_scale - b->scale);
  
  result = BigInt_cmp(a->value, b->value);
  
  BigDec_reduce_scale(a);
  BigDec_reduce_scale(b);
  
  return result;
}

void BigDec_add(BigDec * sum, BigDec * addend1, BigDec * addend2) {
  int max_scale = BigInt_max_int(addend1->scale, addend2->scale);
  
  BigDec_increase_scale(addend1, max_scale - addend1->scale);
  BigDec_increase_scale(addend2, max_scale - addend2->scale);
  
  BigInt_add_s(sum->value, addend1->value, addend2->value);
  sum->scale = max_scale;
  
  BigDec_reduce_scale(addend1);
  BigDec_reduce_scale(addend2);
  BigDec_reduce_scale(sum);
}

void BigDec_subtract(BigDec * diff, BigDec * minuend, BigDec * subtrahend) {
  int max_scale = BigInt_max_int(minuend->scale, subtrahend->scale);
  
  BigDec_increase_scale(minuend, max_scale - minuend->scale);
  BigDec_increase_scale(subtrahend, max_scale - subtrahend->scale);
  
  BigInt_subtract_s(diff->value, minuend->value, subtrahend->value);
  diff->scale = max_scale;
  
  BigDec_reduce_scale(minuend);
  BigDec_reduce_scale(subtrahend);
  BigDec_reduce_scale(diff);
}

void BigDec_multiply(BigDec * product, BigDec * multiplicand, BigDec * multiplier) {
  int scale = multiplicand->scale + multiplier->scale;
  
  BigInt_multiply_s(product->value, multiplicand->value, multiplier->value);
  product->scale = scale;
  
  BigDec_reduce_scale(product);
}

void BigDec_divide(BigDec * quotient, BigDec * dividend, BigDec * divisor, int prec) {
  int scale = dividend->scale - divisor->scale;
  
  if (scale < 0) {
    prec = (scale * -1) + prec;
  }
  
  scale = scale + prec;
  
  BigDec_increase_scale(dividend, prec);
  
  BigInt_divide_s(quotient->value, dividend->value, divisor->value);
  quotient->scale = scale;
  
  BigDec_reduce_scale(dividend);
  BigDec_reduce_scale(quotient);
  
}

#endif

#ifdef __cplusplus
}
#endif
