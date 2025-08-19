#pragma once

#include <stdlib.h>

#include "multiprecisionArithmetic.h"

#define BIGINT_BASE 32768
#define BIGINT_BASE_STRING "32768"
#define BIGINT_INTERNAL_SIZE_LIMIT 16

typedef struct {
  int * internalRepresentatiom;
  int internalSize;
} BigInt;

void BigInt_init (BigInt * b) {
  b->internalRepresentatiom = NULL;
  b->internalSize = 0;
}

void BigInt_init_from_string (BigInt * b, char * str) {
  int * tempArray = malloc((BIGINT_INTERNAL_SIZE_LIMIT) * sizeof(int));
  int i = 0;
  int x;
  // char tempDigits[7];
  char * tmp = NULL;
  char * rem = NULL;
  char * mul = NULL;
  char * str2 = malloc((strlen(str) + 1) * sizeof(char));
  int clearTemp = 1;
  // tempDigits[6] = 0;
  b->internalRepresentatiom = NULL;
  b->internalSize = 0;

  strcpy(str2, str);

  if (bigIntCmp(str2, BIGINT_BASE_STRING) < 0) {
    tempArray[i] = atoi(str2);
    i++;
    clearTemp = 0;
  } else {
    tmp = divide(str2, BIGINT_BASE_STRING);
    while(bigIntCmp(tmp, "0") > 0) {
      mul = multiply(tmp, BIGINT_BASE_STRING);
      rem = subtract(str2, mul);
      tempArray[i] = atoi(rem);
      i++;
      free(mul);
      free(rem);
      strcpy(str2, tmp);
      free(tmp);
      if (bigIntCmp(str2, BIGINT_BASE_STRING) < 0) {
        tempArray[i] = atoi(str2);
        i++;
        clearTemp = 0;
        break;
      } else {
        tmp = divide(str2, BIGINT_BASE_STRING);
      }
    }
  }
  
  b->internalRepresentatiom = malloc(i * sizeof(int));
  b->internalSize = i;
  for (x = 0; x < i; x++) {
    b->internalRepresentatiom[x] = tempArray[x];
  }

  if (clearTemp) {
    free(tmp);
  }
  free(str2);
  free(tempArray);
}


char * BigInt_to_string(BigInt * b) {
  int x;
  int len = b->internalSize;
  char * destbuf = malloc(1024 * sizeof(char));
  char * tmpProduct;
  char * tmpAdd;

  memset(destbuf, 0, 1024);
  itoa(b->internalRepresentatiom[len - 1], destbuf, 10);

  if (len == 0) {
    tmpAdd = malloc(2 * sizeof(char));
    tmpAdd[0] = '0';
    tmpAdd[1] = 0;
  } else if (len == 1) {
    tmpAdd = malloc((strlen(destbuf) + 1) * sizeof(char));
    strcpy(tmpAdd, destbuf);
  } else {
    for (x = len - 2; x >= 0; x--) {
      tmpProduct = multiply(destbuf, BIGINT_BASE_STRING);
      itoa(b->internalRepresentatiom[x], destbuf, 10);
      tmpAdd = add(tmpProduct, destbuf);
      free(tmpProduct);
      if (x != 0) {
        free(tmpAdd);
      }
    }
  }
  free(destbuf);
  return tmpAdd;
}

void BigInt_destroy(BigInt * b) {
  free(b->internalRepresentatiom);
  b->internalSize = 0;
}