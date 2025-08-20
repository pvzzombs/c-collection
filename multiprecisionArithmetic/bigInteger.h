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
  int * tempArray = malloc((strlen(str) / 2 + 1) * sizeof(int));
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

int BigInt_cmp(BigInt * num1, BigInt * num2) {
  if (num1->internalSize < num2->internalSize) {
    return -1;
  } else if(num1->internalSize > num2->internalSize) {
    return 1;
  } else {
    int i;
    for (i = num1->internalSize - 1; i >= 0; i--) {
      if (num1->internalRepresentatiom[i] < num2->internalRepresentatiom[i]) {
        return -1;
      } else if (num1->internalRepresentatiom[i] > num2->internalRepresentatiom[i]) {
        return 1;
      }
    }
  }
  return 0;
}

void BigInt_remove_leading_zeroes(BigInt * b) {
  int bInternalSize = b->internalSize;
  int i;
  for (i = bInternalSize - 1; i >= 0; i--) {
    if (b->internalRepresentatiom[i] == 0) {
      b->internalSize--;
    } else {
      break;
    }
  }
  if (b->internalSize == 0) {
    if (bInternalSize > 0) {
      b->internalRepresentatiom[0] = 0;
      b->internalSize = 1;
    }
  }
}

void BigInt_add_leading_zero(BigInt * b) {
  int bSize = b->internalSize;
  int i;
  int * newInts = malloc((bSize + 1) * sizeof(int));
  for (i = 0; i < bSize; i++) {
    newInts[i] = b->internalRepresentatiom[i];
  }
  newInts[bSize] = 0;
  free(b->internalRepresentatiom);
  b->internalRepresentatiom = newInts;
  b->internalSize = bSize + 1;
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
  if (BigInt_cmp(addend1, addend2) < 0) {
    BigInt * temp = addend1;
    addend1 = addend2;
    addend2 = temp;
  }
  sum->internalRepresentatiom = malloc((addend1->internalSize + 1) * sizeof(int));
  sum->internalSize = addend1->internalSize + 1;
  BigInt_add_impl(addend1->internalRepresentatiom, addend2->internalRepresentatiom, sum->internalRepresentatiom, addend1->internalSize, addend2->internalSize, sum->internalSize);
  BigInt_remove_leading_zeroes(sum);
}

void BigInt_subtract_impl(int * minuend, int * subtrahend, int * difference, int minuendLen, int subtrahendLen, int differenceLen) {
  int i;
  int digitDifference = 0, borrow = 0;
  for (i = 0; i < subtrahendLen; i++) {
    int minuendDigit = minuend[i];
    int subtrahendDigit = subtrahend[i];
    int tempBorrow = borrow;

    if (minuendDigit - tempBorrow < subtrahendDigit) {
      minuendDigit += BIGINT_BASE;
      borrow = 1;
    } else {
      borrow = 0;
    }
    digitDifference = minuendDigit - tempBorrow - subtrahendDigit;
    difference[i] = digitDifference;
  }

  for (; i < minuendLen; i++) {
    int minuendDigit = minuend[i];
    int tempBorrow = borrow;
    if (minuendDigit - tempBorrow < 0) {
      minuendDigit += BIGINT_BASE;
      borrow = 1;
    } else {
      borrow = 0;
    }
    digitDifference = minuendDigit - tempBorrow - 0;
    difference[i] = digitDifference;
  }
}

void BigInt_subtract(BigInt * minuend, BigInt * subtrahend, BigInt * difference) {
  if (difference->internalRepresentatiom != NULL) {
    free(difference->internalRepresentatiom);
    difference->internalRepresentatiom = NULL;
    difference->internalSize = 0;
  }
  difference->internalRepresentatiom = malloc((minuend->internalSize) * sizeof(int));
  difference->internalSize = minuend->internalSize;
  BigInt_subtract_impl(minuend->internalRepresentatiom, subtrahend->internalRepresentatiom, difference->internalRepresentatiom, minuend->internalSize, subtrahend->internalSize, difference->internalSize);
  BigInt_remove_leading_zeroes(difference);
}

void BigInt_multiply_impl(int * multiplicand, int * multiplier, int * product, int multiplicandLen, int multiplierLen, int productLen) {
  int carryM;
  int carryA;
  int productDigit;
  int sumDigit;
  int pIndex = 0, pIndexTemp;
  int i, j;
  for (j = 0; j < multiplierLen; j++) {
    carryA = 0;
    carryM = 0;
    pIndexTemp = pIndex;
    for (i = 0; i < multiplicandLen; i++) {
      int m = multiplicand[i];
      int n = multiplier[j];
      int p = product[pIndex];
      productDigit = (m * n + carryM) % BIGINT_BASE;
      carryM = (m * n + carryM) / BIGINT_BASE;
      sumDigit = (productDigit + carryA + p) % BIGINT_BASE;
      carryA = (productDigit + carryA + p) / BIGINT_BASE;
      product[pIndex] = sumDigit;
      pIndex++;
    }

    for(; pIndex < productLen; pIndex++) {
      int p = product[pIndex];
      sumDigit = (carryM + carryA + p) % BIGINT_BASE;
      carryA = (carryM + carryA + p) / BIGINT_BASE;
      product[pIndex] = sumDigit;
      carryM = 0;
    }
    pIndex = pIndexTemp + 1;
  }
}

void BigInt_multiply(BigInt * multiplicand, BigInt * multiplier, BigInt * product) {
  int i;
  if (product->internalRepresentatiom != NULL) {
    free(product->internalRepresentatiom);
    product->internalRepresentatiom = NULL;
    product->internalSize = 0;
  }
  if (BigInt_cmp(multiplicand, multiplier) < 0) {
    BigInt * temp = multiplicand;
    multiplicand = multiplier;
    multiplier = temp;
  }
  product->internalRepresentatiom = malloc((multiplicand->internalSize + multiplier->internalSize) * sizeof(int));
  product->internalSize = multiplicand->internalSize + multiplier->internalSize;
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentatiom[i] = 0;
  }
  BigInt_multiply_impl(multiplicand->internalRepresentatiom, multiplier->internalRepresentatiom, product->internalRepresentatiom, multiplicand->internalSize, multiplier->internalSize, product->internalSize);
  BigInt_remove_leading_zeroes(product);
}

int BigInt_internal_cmp(int * num1, int * num2, int num1Len, int num2Len) {
  if (num1Len < num2Len) {
    return -1;
  } else if (num1Len > num2Len) {
    return 1;
  } else {
    int i;
    for (i = num1Len - 1; i >= 0; i--) {
      if (num1[i] < num2[i]) {
        return -1;
      } else if (num1[i] > num2[i]) {
        return 1;
      }
    }
  }
  return 0;
}

int BigInt_internal_shift_towards_front_by_one(int * arr, int len){
  int i;
  for (i = len - 1; i > 0; i--) {
    arr[i] = arr[i - 1];
  }
}

void BigInt_divide_impl(int * dividend, int * divisor, int * quotient, int dividendLen, int divisorLen, int quotientLen) {
  int remainderLen = divisorLen + 1;
  int * remainder = malloc((remainderLen) * sizeof(int));
  int * tempHolder = malloc((remainderLen) * sizeof(int));
  int i, j;
  int qDigit1, qDigit2, dvsrDigit, qhat;
  int * qDigit = malloc(1 * sizeof(int));

  for (i = 0; i < remainderLen; i++) {
    remainder[remainderLen - i - 1] = dividend[dividendLen - i - 1];
  }

  for (i = 0; i < quotientLen; i++) {
    remainder[0] = dividend[quotientLen - i - 1];
    qDigit1 = remainder[remainderLen - 1];
    qDigit2 = remainder[remainderLen - 2];
    dvsrDigit = divisor[divisorLen - 1];
    qhat = (qDigit1 * BIGINT_BASE + qDigit2) / dvsrDigit;
    qhat = mininumInt(qhat, BIGINT_BASE - 1);

    qDigit[0] = qhat;
    for (j = 0; j < remainderLen; j++) {
      tempHolder[j] = 0;
    }
    BigInt_multiply_impl(divisor, qDigit, tempHolder, divisorLen, 1, remainderLen);
    while(BigInt_internal_cmp(remainder, tempHolder, remainderLen, remainderLen) < 0) {
      qDigit[0]--;
      for (j = 0; j < remainderLen; j++) {
        tempHolder[j] = 0;
      }
      BigInt_multiply_impl(divisor, qDigit, tempHolder, divisorLen, 1, remainderLen);
    }
    BigInt_subtract_impl(remainder, tempHolder, remainder, remainderLen, remainderLen, remainderLen);
    quotient[quotientLen - i - 1] = qDigit[0];
    BigInt_internal_shift_towards_front_by_one(remainder, remainderLen);
  }

  free(remainder);
  free(tempHolder);
  free(qDigit);
}

void BigInt_divide(BigInt * dividend, BigInt * divisor, BigInt * quotient) {
  int * d = malloc(1 * sizeof(int));
  int i;
  int * newDividend = NULL;
  int * newDivisor = NULL;
  if (quotient->internalRepresentatiom != NULL) {
    free(quotient->internalRepresentatiom);
    quotient->internalRepresentatiom = NULL;
    quotient->internalSize = 0;
  }
  BigInt_add_leading_zero(dividend);
  d[0] = BIGINT_BASE / (divisor->internalRepresentatiom[divisor->internalSize - 1] + 1);
  newDividend = malloc((dividend->internalSize) * sizeof(int));
  newDivisor = malloc((divisor->internalSize) * sizeof(int));
  for (i = 0; i < dividend->internalSize; i++) {
    newDividend[i] = 0;
  }
  for (i = 0; i < divisor->internalSize; i++) {
    newDivisor[i] = 0;
  }
  quotient->internalRepresentatiom = malloc((dividend->internalSize - divisor->internalSize) * sizeof(int));
  quotient->internalSize = dividend->internalSize - divisor->internalSize;
  BigInt_multiply_impl(dividend->internalRepresentatiom, d, newDividend, dividend->internalSize - 1, 1, dividend->internalSize);
  BigInt_multiply_impl(divisor->internalRepresentatiom, d, newDivisor, divisor->internalSize, 1, divisor->internalSize);
  BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentatiom, dividend->internalSize, divisor->internalSize, quotient->internalSize);
  BigInt_remove_leading_zeroes(quotient);

  free(newDividend);
  free(newDivisor);
  free(d);
}