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
void BigDec_destroy(BigDec * b);
void BigDec_reduce_scale(BigDec *);
void BigDec_increase_scale(BigDec *, int);
void BigDec_add(BigDec *, BigDec *, BigDec *);

#if defined(BIGDEC_IMPL) || defined(MPA_IMPL)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void BigDec_init(BigDec * b) {
  b->value = (BigInt *) BIGDEC_ALLOC(1 * sizeof(BigInt));
  BigInt_init(b->value);
  b->scale = 0;
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
  printf("BigDec str is %s, scale is %d, is negative: %d\n", new_s, scale, is_negative);
  b->value = (BigInt *) BIGDEC_ALLOC(1 * sizeof(BigInt));
  BigInt_init_from_string(b->value, new_s);
  b->scale = scale;
  if (is_negative) {
    b->value->sign = -1;
  }
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
  
  if (i >= out1.internalSize || b->scale < 0) {
    b->value->internalRepresentation[0] = 0;
    b->value->sign = 0;
    b->value->internalSize = 1;
    b->scale = 0;
    return ;
  }
  
  BigInt_set_from_int(&base, 10);
  
  BigInt_power(&temp, &base, removed);
  
  BigInt_divide_s(b->value, b->value, &temp);
  
  BigInt_print(b->value);
  
  printf("\n");
  
  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);
}

void BigDec_increase_scale(BigDec * b, int scale) {
  BigInt b10, temp;
  BigInt_init(&temp);
  BigInt_init_from_int(&b10, 10);
  
  BigInt_power(&temp, &b10, scale);
  
  BigInt_multiply_s(b->value, b->value, &temp);
  
  BigInt_print(b->value);
  
  printf("\n");
  
  BigInt_destroy(&temp);
  BigInt_destroy(&b10);
}

void BigDec_add(BigDec * sum, BigDec * addend1, BigDec * addend2) {
  int max_scale = BigInt_max_int(addend1->scale, addend2->scale);
  BigDec_reduce_scale(addend1);
  BigDec_reduce_scale(addend2);
  
  BigDec_increase_scale(addend1, max_scale - addend1->scale);
  BigDec_increase_scale(addend2, max_scale - addend2->scale);
  
  BigInt_add_u(sum->value, addend1->value, addend2->value);
  
  BigDec_reduce_scale(sum);
}

#endif

#ifdef __cplusplus
}
#endif
