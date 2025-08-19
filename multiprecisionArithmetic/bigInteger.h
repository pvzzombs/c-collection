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
  char * destbuf = malloc((5 * len + 1) * sizeof(char));
  char * tmpProduct;
  char * tmpAdd;

  memset(destbuf, 0, 5 * len + 1);
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
      strcpy(destbuf, tmpAdd);
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

void BigInt_add_impl(int * addend1, int * addend2, int * sum, int addend1Len, int addend2Len, int sumLen) {
  int i;
  int digitSum = 0, carry = 0;
  for (i = 0; i < addend2Len; i++) {
    int Addend1 = addend1[i];
    int Addend2 = addend2[i];
    digitSum = (Addend1 + Addend2 + carry) % BIGINT_BASE;
    carry = (Addend1 + Addend2 + carry) / BIGINT_BASE;
    sum[i] = digitSum;
  }
  for(; i < sumLen; i++) {
    int num = 0;
    if(i < addend1Len) {
      num = addend1[i];
    }
    digitSum = (num + carry) % BIGINT_BASE;
    carry = (num + carry) / BIGINT_BASE;
    sum[i] = digitSum;
  }
}

void BigInt_add(BigInt * addend1, BigInt * addend2, BigInt * sum) {
  if (sum->internalRepresentatiom != NULL) {
    free(sum->internalRepresentatiom);
    sum->internalRepresentatiom = NULL;
    sum->internalSize = 0;
  }
  if (addend1->internalSize > addend2->internalSize) {
    sum->internalRepresentatiom = malloc((addend1->internalSize + 1) * sizeof(int));
    sum->internalSize = addend1->internalSize + 1;
    BigInt_add_impl(addend1->internalRepresentatiom, addend2->internalRepresentatiom, sum->internalRepresentatiom, addend1->internalSize, addend2->internalSize, sum->internalSize);
  } else {
    sum->internalRepresentatiom = malloc((addend2->internalSize + 1) * sizeof(int));
    sum->internalSize = addend2->internalSize + 1;
    BigInt_add_impl(addend2->internalRepresentatiom, addend1->internalRepresentatiom, sum->internalRepresentatiom, addend2->internalSize, addend1->internalSize, sum->internalSize);
  }
  if (sum->internalRepresentatiom[sum->internalSize - 1] == 0) {
    sum->internalSize--;
  }
}