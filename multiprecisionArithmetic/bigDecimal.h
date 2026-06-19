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
void BigDec_add(BigDec * sum, BigDec * addend1, BigDec * addend2);

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
  for (i = 0; i < len; i++) {
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
  printf("BigDec str is %s, scale is %d\n", new_s, scale);
  b->value = (BigInt *) BIGDEC_ALLOC(1 * sizeof(BigInt));
  BigInt_init_from_string(b->value, new_s);
  b->scale = scale;
  BIGDEC_FREE(new_s);
}

void BigDec_destroy(BigDec * b) {
  BigInt_destroy(b->value);
  BIGDEC_FREE(b->value);
  b->scale = 0;
}

void BigDec_add(BigDec * sum, BigDec * addend1, BigDec * addend2) {
  /* For now, we assume scale are the same */
  BigInt_add_t(sum->value, addend1->value, addend2->value);
}

#endif

#ifdef __cplusplus
}
#endif
