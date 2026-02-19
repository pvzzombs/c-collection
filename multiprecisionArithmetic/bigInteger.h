#pragma once

#if defined(__STDC_VERSION__)
#include <stdint.h>
#if INTPTR_MAX == INT64_MAX
#define BIGINT_USE_64_BIT
#elif INTPTR_MAX == INT32_MAX
#define BIGINT_USE_32_BIT
#else
#define BIGINT_USE_16_BIT
#endif
#else
#if defined(_WIN64) || defined(__x86_64__)
#define BIGINT_USE_64_BIT
#elif defined(_WIN32)
#define BIGINT_USE_32_BIT
#else
#define BIGINT_USE_16_BIT
#endif
#endif

#if defined(BIGINT_USE_64_BIT)
#if defined(__STDC_VERSION__)
#define BIGINT_BASE 2147483648LL
#define BIGINT_BASE_STRING "2147483648"
#define BIGINT_BASE_DIGITS 9
#define BIGINT_BASE_10 1000000000LL
typedef int64_t BigInt_limb_t;
#else
#define BIGINT_BASE 2147483648L
#define BIGINT_BASE_STRING "2147483648"
#define BIGINT_BASE_DIGITS 9
#define BIGINT_BASE_10 1000000000L
typedef long BigInt_limb_t;
#endif

#elif defined(BIGINT_USE_32_BIT)

#define BIGINT_BASE 32768
#define BIGINT_BASE_STRING "32768"
#define BIGINT_BASE_DIGITS 4
#define BIGINT_BASE_10 10000
#if defined(__STDC_VERSION__)
typedef int32_t BigInt_limb_t;
#else
typedef int BigInt_limb_t;
#endif

#elif defined(BIGINT_USE_16_BIT)

#define BIGINT_BASE 128
#define BIGINT_BASE_STRING "128"
#define BIGINT_BASE_DIGITS 2
#define BIGINT_BASE_10 100
typedef int BigInt_limb_t;
#if defined(__STDC_VERSION__)
typedef int BigInt_limb_t;
#else
typedef int BigInt_limb_t;
#endif
#else

#error

#endif

#ifdef __cplusplus
extern "C" {
#endif

struct BigInt_ {
  BigInt_limb_t * internalRepresentation;
  int internalSize;
  int allocSize;
  int sign;
};
typedef struct BigInt_ BigInt;
BigInt_limb_t BigInt_atoi_impl(char *);
int BigInt_atoi_impl_with_range(char *, int, int);
void BigInt_itoa_impl(BigInt_limb_t, char *);
void BigInt_zero_all_impl(BigInt_limb_t *, int);
int BigInt_is_zero_impl(BigInt_limb_t *, int);
void BigInt_init(BigInt *);
void BigInt_copy(BigInt *, BigInt *);
void BigInt_copy_to_no_init(BigInt *, BigInt *, int, int);
void BigInt_swap(BigInt *, BigInt *);
void BigInt_destroy(BigInt *);
int BigInt_internal_cmp(BigInt_limb_t *, BigInt_limb_t *, int, int);
void BigInt_internal_shift_towards_front_by_one(BigInt_limb_t *, int);
int BigInt_cmp(BigInt *, BigInt *);
int BigInt_cmp_with_sign(BigInt *, BigInt *);
void BigInt_remove_leading_zeroes(BigInt *);
void BigInt_add_leading_zero(BigInt *);
void BigInt_print(BigInt *);
void BigInt_print_s(BigInt *);
void BigInt_add_impl(BigInt_limb_t *, BigInt_limb_t *, BigInt_limb_t *, int, int, int, BigInt_limb_t);
void BigInt_add(BigInt *, BigInt *, BigInt *);
void BigInt_add_small_impl(BigInt_limb_t *, BigInt_limb_t, BigInt_limb_t *, int, int, BigInt_limb_t);
void BigInt_add_small(BigInt *, BigInt *, BigInt_limb_t);
void BigInt_subtract_impl(BigInt_limb_t *, BigInt_limb_t *, BigInt_limb_t *, int, int, int, BigInt_limb_t);
void BigInt_subtract(BigInt *, BigInt *, BigInt *);
void BigInt_add_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_subtract_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_impl(BigInt_limb_t *, BigInt_limb_t *, BigInt_limb_t *, int, int, int, BigInt_limb_t);
void BigInt_multiply(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_small_impl(BigInt_limb_t *, BigInt_limb_t, BigInt_limb_t *, int, int, BigInt_limb_t);
void BigInt_multiply_small(BigInt *, BigInt *, BigInt_limb_t);
void BigInt_multiply_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_divide_impl(BigInt_limb_t *, BigInt_limb_t *, BigInt_limb_t *, int, int, int, BigInt_limb_t);
void BigInt_divide(BigInt *, BigInt *, BigInt *);
void BigInt_divide_no_copy(BigInt *, BigInt *, BigInt *);
void BigInt_divide_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_divide_no_copy_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_set_from_string_with_small(BigInt *, char *);
void BigInt_set_from_string_impl(BigInt *, char *);
void BigInt_set_from_string(BigInt *, char *);
void BigInt_set_from_string_with_sign(BigInt *, char *);
void BigInt_init_from_string(BigInt *, char *);
void BigInt_init_from_string_with_sign(BigInt *, char *);
void BigInt_add_t(BigInt *, BigInt *, BigInt *);
void BigInt_subtract_t(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_t(BigInt *, BigInt *, BigInt *);
void BigInt_divide_t(BigInt *, BigInt *, BigInt *);
void BigInt_add_ts(BigInt *, BigInt *, BigInt *);
void BigInt_subtract_ts(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_ts(BigInt *, BigInt *, BigInt *);
void BigInt_divide_ts(BigInt *, BigInt *, BigInt *);
char * BigInt_to_string_with_small_base(BigInt *);
int BigInt_count_digits_base_10(BigInt *);
char * BigInt_to_string(BigInt *);
char * BigInt_to_string_with_sign(BigInt *);
void BigInt_print_internal(BigInt *);
void BigInt_shift_left(BigInt *, int);
void BigInt_shift_right(BigInt *, int);
void BigInt_add_leading_zeroes(BigInt *, int);
void BigInt_multiply_karatsuba_impl(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_karatsuba(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_karatsuba_t(BigInt *, BigInt *, BigInt *);

#ifdef BIGINT_IMPL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #include "multiprecisionArithmetic.h" */

void BigInt_reverse_digits_impl(char * arr, int len) {
  int mid = (len - 1) / 2;
  int l = 0, r = len - 1;
  while(l <= mid) {
    char temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
    l++;
    r--;
  }
}

BigInt_limb_t BigInt_min_int(BigInt_limb_t a, BigInt_limb_t b) {
  if (a < b) return a;
  return b;
}


BigInt_limb_t BigInt_atoi_impl (char * src) {
  BigInt_limb_t num = 0;
  int i;
  for (i = 0; i < strlen(src); i++) {
    num = num * 10 + (src[i] - '0');
  }
  return num;
}

int BigInt_atoi_impl_with_range (char * src, int l, int r) {
  int num = 0;
  int i;
  for (i = l; i <= r; i++) {
    num = num * 10 + (src[i] - '0');
  }
  return num;
}

void BigInt_itoa_impl (BigInt_limb_t num, char * dest) {
  int i = 0;
  if (num == 0) {
    dest[0] = '0';
    dest[1] = 0;
    return;
  }
  while (num > 0) {
    int rem = num % 10;
    dest[i] = rem + '0';
    num = num / 10;
    i++;
  }
  dest[i] = 0;
  BigInt_reverse_digits_impl(dest, i);
}

void BigInt_zero_all_impl(BigInt_limb_t * dest, int len) {
  int i;
  for (i = 0; i < len; i++) {
    dest[i] = 0;
  }
}

int BigInt_is_zero_impl(BigInt_limb_t * arr, int len) {
  int i;
  for (i = 0; i < len; i++) {
    if (arr[i] != 0) {
      return 0;
    }
  }
  return 1;
}

void BigInt_init (BigInt * b) {
  b->internalRepresentation = (BigInt_limb_t *)malloc(1 * sizeof(BigInt_limb_t));
  b->internalSize = 1;
  b->internalRepresentation[0] = 0;
  b->allocSize = 1;
  b->sign = 0;
}

void BigInt_copy(BigInt * to, BigInt * from) {
  int i;
  if (to->allocSize < from->internalSize) {
    free(to->internalRepresentation);
    to->internalRepresentation = (BigInt_limb_t *)malloc(sizeof(BigInt_limb_t) * from->internalSize);
    to->allocSize = from->internalSize;
  }
  for (i = 0; i < from->internalSize; i++) {
    to->internalRepresentation[i] = from->internalRepresentation[i];
  }
  to->internalSize = from->internalSize;
  to->sign = from->sign;
}

void BigInt_copy_to_no_init(BigInt * dest, BigInt * src, int allowance, int useAllowance) {
  int i;
  dest->allocSize = src->internalSize + allowance;
  if (useAllowance) {
    dest->internalSize = src->internalSize + allowance;
  } else {
    dest->internalSize = src->internalSize;
  }
  dest->sign = src->sign;
  dest->internalRepresentation = (BigInt_limb_t *)malloc(dest->allocSize * sizeof(BigInt_limb_t));
  for (i = 0; i < dest->allocSize; i++) {
    dest->internalRepresentation[i] = 0;
  }
  for (i = 0; i < src->internalSize; i++) {
    dest->internalRepresentation[i] = src->internalRepresentation[i];
  }
}

void BigInt_swap(BigInt * b1, BigInt * b2) {
  BigInt_limb_t * tempInternalRepresentation = b1->internalRepresentation;
  int tempAllocSize = b1->allocSize;
  int tempInternalSize = b1->internalSize;
  int tempSign = b1->sign;

  b1->internalRepresentation = b2->internalRepresentation;
  b1->allocSize = b2->allocSize;
  b1->internalSize = b2->internalSize;
  b1->sign = b2->sign;

  b2->internalRepresentation = tempInternalRepresentation;
  b2->allocSize = tempAllocSize;
  b2->internalSize = tempInternalSize;
  b2->sign = tempSign;
}

void BigInt_destroy(BigInt * b) {
  free(b->internalRepresentation);
  b->internalRepresentation = NULL;
  b->internalSize = 0;
  b->allocSize = 0;
}

int BigInt_internal_cmp(BigInt_limb_t * num1, BigInt_limb_t * num2, int num1Len, int num2Len) {
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

void BigInt_internal_shift_towards_front_by_one(BigInt_limb_t * arr, int len){
  int i;
  for (i = len - 1; i > 0; i--) {
    arr[i] = arr[i - 1];
  }
}

int BigInt_cmp(BigInt * num1, BigInt * num2) {
  if (num1->internalSize < num2->internalSize) {
    return -1;
  } else if(num1->internalSize > num2->internalSize) {
    return 1;
  } else {
    int i;
    for (i = num1->internalSize - 1; i >= 0; i--) {
      if (num1->internalRepresentation[i] < num2->internalRepresentation[i]) {
        return -1;
      } else if (num1->internalRepresentation[i] > num2->internalRepresentation[i]) {
        return 1;
      }
    }
  }
  return 0;
}


int BigInt_cmp_with_sign(BigInt * num1, BigInt * num2) {
  if (num1->sign >= 0 && num2->sign >= 0) {
    return BigInt_cmp(num1, num2);
  } else if (num1->sign < 0 && num2->sign < 0) {
    return BigInt_cmp(num1, num2) * -1;
  } else {
    if (num1->sign < 0) {
      return -1;
    } else if (num2->sign < 0) {
      return 1;
    }
  }
  return 0;
}

void BigInt_remove_leading_zeroes(BigInt * b) {
  int bInternalSize = b->internalSize;
  int bAllocSize = b->allocSize;
  int i;
  for (i = bInternalSize - 1; i >= 0; i--) {
    if (b->internalRepresentation[i] == 0) {
      b->internalSize--;
    } else {
      break;
    }
  }
  if (b->internalSize == 0) {
    if (bAllocSize > 0) {
      b->internalRepresentation[0] = 0;
      b->internalSize = 1;
      b->sign = 0;
    }
  }
}

void BigInt_add_leading_zero(BigInt * b) {
  int bSize = b->internalSize;
  int i;
  BigInt_limb_t * newInts = NULL;
  if (b->allocSize > bSize) {
    b->internalRepresentation[bSize] = 0;
    b->internalSize = bSize + 1;
  } else {
    newInts = (BigInt_limb_t *)malloc((bSize + 1) * sizeof(BigInt_limb_t));
    for (i = 0; i < bSize; i++) {
      newInts[i] = b->internalRepresentation[i];
    }
    newInts[bSize] = 0;
    free(b->internalRepresentation);
    b->internalRepresentation = newInts;
    b->internalSize = bSize + 1;
    b->allocSize = bSize + 1;
  }
}

void BigInt_print(BigInt * b) {
  char * s = BigInt_to_string(b);
  printf("%s", s);
  free(s);
}

void BigInt_print_s(BigInt * b) {
  char * s = BigInt_to_string_with_sign(b);
  printf("%s", s);
  free(s);
}

void BigInt_add_impl(BigInt_limb_t * addend1, BigInt_limb_t * addend2, BigInt_limb_t * sum, int addend1Len, int addend2Len, int sumLen, BigInt_limb_t limb_base) {
  int i;
  BigInt_limb_t digitSum = 0, carry = 0;
  for (i = 0; i < addend2Len; i++) {
    BigInt_limb_t Addend1 = addend1[i];
    BigInt_limb_t Addend2 = addend2[i];
    digitSum = (Addend1 + Addend2 + carry) % (BigInt_limb_t)limb_base;
    carry = (Addend1 + Addend2 + carry) / (BigInt_limb_t)limb_base;
    sum[i] = digitSum;
  }
  for(; i < sumLen; i++) {
    BigInt_limb_t num = 0;
    if(i < addend1Len) {
      num = addend1[i];
    }
    digitSum = (num + carry) % (BigInt_limb_t)limb_base;
    carry = (num + carry) / (BigInt_limb_t)limb_base;
    sum[i] = digitSum;
  }
}

void BigInt_add(BigInt * sum, BigInt * addend1, BigInt * addend2) {
  if (BigInt_cmp(addend1, addend2) < 0) {
    BigInt * temp = addend1;
    addend1 = addend2;
    addend2 = temp;
  }
  if (sum->allocSize > addend1->internalSize) {
    sum->internalSize = addend1->internalSize + 1;
    sum->internalRepresentation[addend1->internalSize] = 0;
  } else {
    free(sum->internalRepresentation);
    sum->internalRepresentation = (BigInt_limb_t *)malloc((addend1->internalSize + 1) * sizeof(BigInt_limb_t));
    sum->internalRepresentation[addend1->internalSize] = 0;
    sum->internalSize = addend1->internalSize + 1;
    sum->allocSize = addend1->internalSize + 1;
  }
  
  BigInt_add_impl(addend1->internalRepresentation, addend2->internalRepresentation, sum->internalRepresentation, addend1->internalSize, addend2->internalSize, sum->internalSize, BIGINT_BASE);
  BigInt_remove_leading_zeroes(sum);
}

void BigInt_add_small_impl(BigInt_limb_t * addend1, BigInt_limb_t addend2, BigInt_limb_t * sum, int addend1Len, int sumLen, BigInt_limb_t limb_base) {
  int i = 0;
  BigInt_limb_t digitSum = 0, carry = 0;
  BigInt_limb_t Addend1 = addend1[i];
  BigInt_limb_t Addend2 = addend2;
  digitSum = (Addend1 + Addend2 + carry) % limb_base;
  carry = (Addend1 + Addend2 + carry) / limb_base;
  sum[i] = digitSum;
  i++;
  for(; i < sumLen; i++) {
    BigInt_limb_t num = 0;
    if(i < addend1Len) {
      num = addend1[i];
    }
    digitSum = (num + carry) % limb_base;
    carry = (num + carry) / limb_base;
    sum[i] = digitSum;
  }
}

void BigInt_add_small(BigInt * sum, BigInt * addend1, BigInt_limb_t addend2) {
  if (sum->allocSize > addend1->internalSize) {
    sum->internalSize = addend1->internalSize + 1;
  } else {
    free(sum->internalRepresentation);
    sum->internalRepresentation = (BigInt_limb_t *)malloc((addend1->internalSize + 1) * sizeof(BigInt_limb_t));
    sum->internalRepresentation[addend1->internalSize] = 0;
    sum->internalSize = addend1->internalSize + 1;
    sum->allocSize = addend1->internalSize + 1;
  }
  
  BigInt_add_small_impl(addend1->internalRepresentation, addend2, sum->internalRepresentation, addend1->internalSize, sum->internalSize, BIGINT_BASE);
  BigInt_remove_leading_zeroes(sum);
}

void BigInt_subtract_impl(BigInt_limb_t * minuend, BigInt_limb_t * subtrahend, BigInt_limb_t * difference, int minuendLen, int subtrahendLen, int differenceLen, BigInt_limb_t limb_base) {
  int i;
  BigInt_limb_t digitDifference = 0, borrow = 0;
  for (i = 0; i < subtrahendLen; i++) {
    BigInt_limb_t minuendDigit = minuend[i];
    BigInt_limb_t subtrahendDigit = subtrahend[i];
    BigInt_limb_t tempBorrow = borrow;

    if (minuendDigit - tempBorrow < subtrahendDigit) {
      minuendDigit += limb_base;
      borrow = 1;
    } else {
      borrow = 0;
    }
    digitDifference = minuendDigit - tempBorrow - subtrahendDigit;
    difference[i] = digitDifference;
  }

  for (; i < minuendLen; i++) {
    BigInt_limb_t minuendDigit = minuend[i];
    BigInt_limb_t tempBorrow = borrow;
    if (minuendDigit - tempBorrow < 0) {
      minuendDigit += limb_base;
      borrow = 1;
    } else {
      borrow = 0;
    }
    digitDifference = minuendDigit - tempBorrow - 0;
    difference[i] = digitDifference;
  }
}

void BigInt_subtract(BigInt * difference, BigInt * minuend, BigInt * subtrahend) {
  if (difference->allocSize >= minuend->internalSize) {
    difference->internalSize = minuend->internalSize;
  } else {
    free(difference->internalRepresentation);
    difference->internalRepresentation = (BigInt_limb_t *)malloc((minuend->internalSize) * sizeof(BigInt_limb_t));
    difference->internalSize = minuend->internalSize;
    difference->allocSize = minuend->internalSize;
  }
  BigInt_subtract_impl(minuend->internalRepresentation, subtrahend->internalRepresentation, difference->internalRepresentation, minuend->internalSize, subtrahend->internalSize, difference->internalSize, BIGINT_BASE);
  BigInt_remove_leading_zeroes(difference);
}

void BigInt_add_with_sign(BigInt * sum, BigInt * addend1, BigInt * addend2) {
  int sameSign = 0;
  /* addend1 has the biggest absolute value */
  if (BigInt_cmp(addend1, addend2) < 0) {
    BigInt * temp = addend1;
    addend1 = addend2;
    addend2 = temp;
  }

  sum->sign = addend1->sign;
  /* If same sign keep it */
  if (addend1->sign == addend2->sign) {
    sameSign = 1;
  }
  if (sum->allocSize > addend1->internalSize) {
    sum->internalSize = addend1->internalSize + 1;
  } else {
    free(sum->internalRepresentation);
    sum->internalRepresentation = (BigInt_limb_t *)malloc((addend1->internalSize + 1) * sizeof(BigInt_limb_t));
    sum->internalRepresentation[addend1->internalSize] = 0;
    sum->internalSize = addend1->internalSize + 1;
    sum->allocSize = addend1->internalSize + 1;
  }
  if(sameSign) {
    BigInt_add_impl(addend1->internalRepresentation, addend2->internalRepresentation, sum->internalRepresentation, addend1->internalSize, addend2->internalSize, sum->internalSize, BIGINT_BASE);
  } else {
    BigInt_subtract_impl(addend1->internalRepresentation, addend2->internalRepresentation, sum->internalRepresentation, addend1->internalSize, addend2->internalSize, sum->internalSize, BIGINT_BASE);
  }
  
  BigInt_remove_leading_zeroes(sum);
}

void BigInt_subtract_with_sign(BigInt * difference, BigInt * minuend, BigInt * subtrahend) {
  int allowance = 0;
  int subtrahendSign = subtrahend->sign * -1;
  int sameSign = 0;

  if (minuend->sign == subtrahendSign) {
    sameSign = 1;
    allowance = 1;
  }

  if (BigInt_cmp(minuend, subtrahend) < 0) {
    BigInt * temp = minuend;
    minuend = subtrahend;
    subtrahend = temp;
    difference->sign = subtrahendSign;
  } else {
    difference->sign = minuend->sign;
  }

  if (difference->allocSize >= minuend->internalSize + allowance) {
    difference->internalSize = minuend->internalSize + allowance;
  } else {
    free(difference->internalRepresentation);
    difference->internalRepresentation = (BigInt_limb_t *)malloc((minuend->internalSize + allowance) * sizeof(BigInt_limb_t));
    difference->internalRepresentation[minuend->internalSize + allowance] = 0;
    difference->internalSize = minuend->internalSize + allowance;
    difference->allocSize = minuend->internalSize + allowance;
  }
  if (sameSign) {
    BigInt_add_impl(minuend->internalRepresentation, subtrahend->internalRepresentation, difference->internalRepresentation, minuend->internalSize, subtrahend->internalSize, difference->internalSize, BIGINT_BASE);
  } else {
    BigInt_subtract_impl(minuend->internalRepresentation, subtrahend->internalRepresentation, difference->internalRepresentation, minuend->internalSize, subtrahend->internalSize, difference->internalSize, BIGINT_BASE);
  }
  BigInt_remove_leading_zeroes(difference);
}

void BigInt_multiply_impl(BigInt_limb_t * multiplicand, BigInt_limb_t * multiplier, BigInt_limb_t * product, int multiplicandLen, int multiplierLen, int productLen, BigInt_limb_t limb_base) {
  BigInt_limb_t carryM;
  BigInt_limb_t carryA;
  BigInt_limb_t productDigit;
  BigInt_limb_t sumDigit;
  int pIndex = 0, pIndexTemp;
  int i, j;
  for (j = 0; j < multiplierLen; j++) {
    carryA = 0;
    carryM = 0;
    pIndexTemp = pIndex;
    for (i = 0; i < multiplicandLen; i++) {
      BigInt_limb_t m = multiplicand[i];
      BigInt_limb_t n = multiplier[j];
      BigInt_limb_t p = product[pIndex];
      productDigit = (m * n + carryM) % limb_base;
      carryM = (m * n + carryM) / limb_base;
      sumDigit = (productDigit + carryA + p) % limb_base;
      carryA = (productDigit + carryA + p) / limb_base;
      product[pIndex] = sumDigit;
      pIndex++;
    }

    for(; pIndex < productLen; pIndex++) {
      BigInt_limb_t p = product[pIndex];
      sumDigit = (carryM + carryA + p) % limb_base;
      carryA = (carryM + carryA + p) / limb_base;
      product[pIndex] = sumDigit;
      carryM = 0;
    }
    pIndex = pIndexTemp + 1;
  }
}

void BigInt_multiply(BigInt * product, BigInt * multiplicand, BigInt * multiplier) {
  int i;
  if (BigInt_cmp(multiplicand, multiplier) < 0) {
    BigInt * temp = multiplicand;
    multiplicand = multiplier;
    multiplier = temp;
  }
  if (product->allocSize >= multiplicand->internalSize + multiplier->internalSize) {
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
  } else {
    free(product->internalRepresentation);
    product->internalRepresentation = (BigInt_limb_t *)malloc((multiplicand->internalSize + multiplier->internalSize) * sizeof(BigInt_limb_t));
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
    product->allocSize = multiplicand->internalSize + multiplier->internalSize;
  }
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentation[i] = 0;
  }
  BigInt_multiply_impl(multiplicand->internalRepresentation, multiplier->internalRepresentation, product->internalRepresentation, multiplicand->internalSize, multiplier->internalSize, product->internalSize, BIGINT_BASE);
  BigInt_remove_leading_zeroes(product);
}

void BigInt_multiply_small_impl(BigInt_limb_t * multiplicand, BigInt_limb_t multiplier, BigInt_limb_t * product, int multiplicandLen, int productLen, BigInt_limb_t limb_base) {
  BigInt_limb_t carryM;
  BigInt_limb_t carryA;
  BigInt_limb_t productDigit;
  BigInt_limb_t sumDigit;
  int pIndex = 0, pIndexTemp;
  int i, j = 0;
  carryA = 0;
  carryM = 0;
  pIndexTemp = pIndex;
  for (i = 0; i < multiplicandLen; i++) {
    BigInt_limb_t m = multiplicand[i];
    BigInt_limb_t n = multiplier;
    BigInt_limb_t p = product[pIndex];
    productDigit = (m * n + carryM) % limb_base;
    carryM = (m * n + carryM) / limb_base;
    sumDigit = (productDigit + carryA + p) % limb_base;
    carryA = (productDigit + carryA + p) / limb_base;
    product[pIndex] = sumDigit;
    pIndex++;
  }

  for(; pIndex < productLen; pIndex++) {
    BigInt_limb_t p = product[pIndex];
    sumDigit = (carryM + carryA + p) % limb_base;
    carryA = (carryM + carryA + p) / limb_base;
    product[pIndex] = sumDigit;
    carryM = 0;
  }
  pIndex = pIndexTemp + 1;
}

void BigInt_multiply_small(BigInt * product, BigInt * multiplicand, BigInt_limb_t multiplier) {
  int i;
  if (product->allocSize >= multiplicand->internalSize + 1) {
    product->internalSize = multiplicand->internalSize + 1;
  } else {
    free(product->internalRepresentation);
    product->internalRepresentation = (BigInt_limb_t *)malloc((multiplicand->internalSize + 1) * sizeof(BigInt_limb_t));
    product->internalSize = multiplicand->internalSize + 1;
    product->allocSize = multiplicand->internalSize + 1;
  }
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentation[i] = 0;
  }
  BigInt_multiply_small_impl(multiplicand->internalRepresentation, multiplier, product->internalRepresentation, multiplicand->internalSize, product->internalSize, BIGINT_BASE);
  BigInt_remove_leading_zeroes(product);
}

void BigInt_multiply_with_sign(BigInt * product, BigInt * multiplicand, BigInt * multiplier) {
  int i;
  if (BigInt_cmp(multiplicand, multiplier) < 0) {
    BigInt * temp = multiplicand;
    multiplicand = multiplier;
    multiplier = temp;
  }
  product->sign = multiplicand->sign * multiplier->sign;
  if (product->allocSize >= multiplicand->internalSize + multiplier->internalSize) {
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
  } else {
    free(product->internalRepresentation);
    product->internalRepresentation = (BigInt_limb_t *)malloc((multiplicand->internalSize + multiplier->internalSize) * sizeof(BigInt_limb_t));
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
    product->allocSize = multiplicand->internalSize + multiplier->internalSize;
  }
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentation[i] = 0;
  }
  BigInt_multiply_impl(multiplicand->internalRepresentation, multiplier->internalRepresentation, product->internalRepresentation, multiplicand->internalSize, multiplier->internalSize, product->internalSize, BIGINT_BASE);
  BigInt_remove_leading_zeroes(product);
}

void BigInt_divide_impl(BigInt_limb_t * dividend, BigInt_limb_t * divisor, BigInt_limb_t * quotient, int dividendLen, int divisorLen, int quotientLen, BigInt_limb_t limb_base) {
  int remainderLen = divisorLen + 1;
  BigInt_limb_t * remainder = (BigInt_limb_t *)malloc((remainderLen) * sizeof(BigInt_limb_t));
  BigInt_limb_t * tempHolder = (BigInt_limb_t *)malloc((remainderLen) * sizeof(BigInt_limb_t));
  int i, j;
  BigInt_limb_t qDigit1, qDigit2, dvsrDigit, qhat;
  BigInt_limb_t * qDigit = (BigInt_limb_t *)malloc(1 * sizeof(BigInt_limb_t));

  for (i = 0; i < remainderLen; i++) {
    remainder[remainderLen - i - 1] = dividend[dividendLen - i - 1];
  }

  for (i = 0; i < quotientLen; i++) {
    remainder[0] = dividend[quotientLen - i - 1];
    qDigit1 = remainder[remainderLen - 1];
    qDigit2 = remainder[remainderLen - 2];
    dvsrDigit = divisor[divisorLen - 1];
    qhat = (qDigit1 * limb_base + qDigit2) / dvsrDigit;
    qhat = BigInt_min_int(qhat, limb_base - 1);

    qDigit[0] = qhat;
    for (j = 0; j < remainderLen; j++) {
      tempHolder[j] = 0;
    }
    BigInt_multiply_impl(divisor, qDigit, tempHolder, divisorLen, 1, remainderLen, limb_base);
    while(BigInt_internal_cmp(remainder, tempHolder, remainderLen, remainderLen) < 0) {
      qDigit[0]--;
      for (j = 0; j < remainderLen; j++) {
        tempHolder[j] = 0;
      }
      BigInt_multiply_impl(divisor, qDigit, tempHolder, divisorLen, 1, remainderLen, limb_base);
    }
    BigInt_subtract_impl(remainder, tempHolder, remainder, remainderLen, remainderLen, remainderLen, limb_base);
    quotient[quotientLen - i - 1] = qDigit[0];
    BigInt_internal_shift_towards_front_by_one(remainder, remainderLen);
  }

  free(remainder);
  free(tempHolder);
  free(qDigit);
}

void BigInt_divide(BigInt * quotient, BigInt * dividend1, BigInt * divisor) {
  BigInt_limb_t * d = (BigInt_limb_t *)malloc(1 * sizeof(BigInt_limb_t));
  int i;
  BigInt_limb_t * newDividend = NULL;
  BigInt_limb_t * newDivisor = NULL;

  BigInt dividend2;
  BigInt_copy_to_no_init(&dividend2, dividend1, 1, 1);

  d[0] = BIGINT_BASE / (divisor->internalRepresentation[divisor->internalSize - 1] + 1);
  newDividend = (BigInt_limb_t *)malloc((dividend2.internalSize) * sizeof(BigInt_limb_t));
  newDivisor = (BigInt_limb_t *)malloc((divisor->internalSize) * sizeof(BigInt_limb_t));
  for (i = 0; i < dividend2.internalSize; i++) {
    newDividend[i] = 0;
  }
  for (i = 0; i < divisor->internalSize; i++) {
    newDivisor[i] = 0;
  }
  
  if (quotient->allocSize >= dividend2.internalSize - divisor->internalSize) {
    quotient->internalSize = dividend2.internalSize - divisor->internalSize;
  } else {
    free(quotient->internalRepresentation);
    quotient->internalRepresentation = (BigInt_limb_t *)malloc((dividend2.internalSize - divisor->internalSize) * sizeof(BigInt_limb_t));
    quotient->internalSize = dividend2.internalSize - divisor->internalSize;
    quotient->allocSize = dividend2.internalSize - divisor->internalSize;
  }
  BigInt_multiply_impl(dividend2.internalRepresentation, d, newDividend, dividend2.internalSize - 1, 1, dividend2.internalSize, BIGINT_BASE);
  BigInt_multiply_impl(divisor->internalRepresentation, d, newDivisor, divisor->internalSize, 1, divisor->internalSize, BIGINT_BASE);
  BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentation, dividend2.internalSize, divisor->internalSize, quotient->internalSize, BIGINT_BASE);
  BigInt_remove_leading_zeroes(quotient);

  BigInt_destroy(&dividend2);
  free(newDividend);
  free(newDivisor);
  free(d);
}

void BigInt_divide_no_copy(BigInt * quotient, BigInt * dividend, BigInt * divisor) {
  BigInt_limb_t * d = (BigInt_limb_t *)malloc(1 * sizeof(BigInt_limb_t));
  int i;
  BigInt_limb_t * newDividend = NULL;
  BigInt_limb_t * newDivisor = NULL;

  BigInt_add_leading_zero(dividend);

  d[0] = BIGINT_BASE / (divisor->internalRepresentation[divisor->internalSize - 1] + 1);
  newDividend = (BigInt_limb_t *)malloc((dividend->internalSize) * sizeof(BigInt_limb_t));
  newDivisor = (BigInt_limb_t *)malloc((divisor->internalSize) * sizeof(BigInt_limb_t));
  for (i = 0; i < dividend->internalSize; i++) {
    newDividend[i] = 0;
  }
  for (i = 0; i < divisor->internalSize; i++) {
    newDivisor[i] = 0;
  }
  
  if (quotient->allocSize >= dividend->internalSize - divisor->internalSize) {
    quotient->internalSize = dividend->internalSize - divisor->internalSize;
  } else {
    free(quotient->internalRepresentation);
    quotient->internalRepresentation = (BigInt_limb_t *)malloc((dividend->internalSize - divisor->internalSize) * sizeof(BigInt_limb_t));
    quotient->internalSize = dividend->internalSize - divisor->internalSize;
    quotient->allocSize = dividend->internalSize - divisor->internalSize;
  }
  BigInt_multiply_impl(dividend->internalRepresentation, d, newDividend, dividend->internalSize - 1, 1, dividend->internalSize, BIGINT_BASE);
  BigInt_multiply_impl(divisor->internalRepresentation, d, newDivisor, divisor->internalSize, 1, divisor->internalSize, BIGINT_BASE);
  BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentation, dividend->internalSize, divisor->internalSize, quotient->internalSize, BIGINT_BASE);
  BigInt_remove_leading_zeroes(quotient);
  BigInt_remove_leading_zeroes(dividend);

  free(newDividend);
  free(newDivisor);
  free(d);
}

void BigInt_divide_with_sign(BigInt * quotient, BigInt * dividend1, BigInt * divisor) {
  BigInt_limb_t * d = (BigInt_limb_t *)malloc(1 * sizeof(BigInt_limb_t));
  int i;
  BigInt_limb_t * newDividend = NULL;
  BigInt_limb_t * newDivisor = NULL;

  BigInt dividend2;
  BigInt_copy_to_no_init(&dividend2, dividend1, 1, 1);

  d[0] = BIGINT_BASE / (divisor->internalRepresentation[divisor->internalSize - 1] + 1);
  newDividend = (BigInt_limb_t *)malloc((dividend2.internalSize) * sizeof(BigInt_limb_t));
  newDivisor = (BigInt_limb_t *)malloc((divisor->internalSize) * sizeof(BigInt_limb_t));
  for (i = 0; i < dividend2.internalSize; i++) {
    newDividend[i] = 0;
  }
  for (i = 0; i < divisor->internalSize; i++) {
    newDivisor[i] = 0;
  }

  quotient->sign = dividend2.sign * divisor->sign;
  if (BigInt_cmp(&dividend2, divisor) < 0 || BigInt_is_zero_impl(divisor->internalRepresentation, divisor->internalSize)) {
    if (quotient->allocSize >= 1) {
      quotient->internalRepresentation[0] = 0;
      quotient->internalSize = 1;
    } else {
      free(quotient->internalRepresentation);
      quotient->internalRepresentation = (BigInt_limb_t *)malloc(1 * sizeof(BigInt_limb_t));
      quotient->internalRepresentation[0] = 0;
      quotient->internalSize = 1;
      quotient->allocSize = 1;
    }
  } else {
    if (quotient->allocSize >= dividend2.internalSize - divisor->internalSize) {
      quotient->internalSize = dividend2.internalSize - divisor->internalSize;
    } else {
      free(quotient->internalRepresentation);
      quotient->internalRepresentation = (BigInt_limb_t *)malloc((dividend2.internalSize - divisor->internalSize) * sizeof(BigInt_limb_t));
      quotient->internalSize = dividend2.internalSize - divisor->internalSize;
      quotient->allocSize = dividend2.internalSize - divisor->internalSize;
    }
    BigInt_multiply_impl(dividend2.internalRepresentation, d, newDividend, dividend2.internalSize - 1, 1, dividend2.internalSize, BIGINT_BASE);
    BigInt_multiply_impl(divisor->internalRepresentation, d, newDivisor, divisor->internalSize, 1, divisor->internalSize, BIGINT_BASE);
    BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentation, dividend2.internalSize, divisor->internalSize, quotient->internalSize, BIGINT_BASE);
    BigInt_remove_leading_zeroes(quotient);
  }
  
  BigInt_destroy(&dividend2);
  free(newDividend);
  free(newDivisor);
  free(d);
}

void BigInt_divide_no_copy_with_sign(BigInt * quotient, BigInt * dividend, BigInt * divisor) {
  BigInt_limb_t * d = (BigInt_limb_t *)malloc(1 * sizeof(BigInt_limb_t));
  int i;
  BigInt_limb_t * newDividend = NULL;
  BigInt_limb_t * newDivisor = NULL;

  BigInt_add_leading_zero(dividend);

  d[0] = BIGINT_BASE / (divisor->internalRepresentation[divisor->internalSize - 1] + 1);
  newDividend = (BigInt_limb_t *)malloc((dividend->internalSize) * sizeof(BigInt_limb_t));
  newDivisor = (BigInt_limb_t *)malloc((divisor->internalSize) * sizeof(BigInt_limb_t));
  for (i = 0; i < dividend->internalSize; i++) {
    newDividend[i] = 0;
  }
  for (i = 0; i < divisor->internalSize; i++) {
    newDivisor[i] = 0;
  }
  
  quotient->sign = dividend->sign * divisor->sign;

  if (BigInt_cmp(dividend, divisor) < 0 || BigInt_is_zero_impl(divisor->internalRepresentation, divisor->internalSize)) {
    if (quotient->allocSize >= 1) {
      quotient->internalRepresentation[0] = 0;
      quotient->internalSize = 1;
    } else {
      free(quotient->internalRepresentation);
      quotient->internalRepresentation = (BigInt_limb_t *)malloc(1 * sizeof(BigInt_limb_t));
      quotient->internalRepresentation[0] = 0;
      quotient->internalSize = 1;
      quotient->allocSize = 1;
    }
  } else {
    if (quotient->allocSize >= dividend->internalSize - divisor->internalSize) {
      quotient->internalSize = dividend->internalSize - divisor->internalSize;
    } else {
      free(quotient->internalRepresentation);
      quotient->internalRepresentation = (BigInt_limb_t *)malloc((dividend->internalSize - divisor->internalSize) * sizeof(BigInt_limb_t));
      quotient->internalSize = dividend->internalSize - divisor->internalSize;
      quotient->allocSize = dividend->internalSize - divisor->internalSize;
    }
    BigInt_multiply_impl(dividend->internalRepresentation, d, newDividend, dividend->internalSize - 1, 1, dividend->internalSize, BIGINT_BASE);
    BigInt_multiply_impl(divisor->internalRepresentation, d, newDivisor, divisor->internalSize, 1, divisor->internalSize, BIGINT_BASE);
    BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentation, dividend->internalSize, divisor->internalSize, quotient->internalSize, BIGINT_BASE);
    BigInt_remove_leading_zeroes(quotient);
    BigInt_remove_leading_zeroes(dividend);
  }

  free(newDividend);
  free(newDivisor);
  free(d);
}

void BigInt_set_from_string_with_small(BigInt * b, char * str) {
  int len = strlen(str);
  int i;
  BigInt temp, out;
  BigInt_init(&out);
  BigInt_init(&temp);
  for (i = 0; i < len; i++) {
    BigInt_multiply_small(&out, &temp, 10);
    BigInt_add_small(&temp, &out, str[i] - '0');
  }
  BigInt_copy(b, &temp);
  BigInt_destroy(&out);
  BigInt_destroy(&temp);
}

void BigInt_set_from_string_impl(BigInt * b, char * str) {
  int len = strlen(str);
  int i;
  int firstLen = len % BIGINT_BASE_DIGITS;
  BigInt out;
  if (firstLen == 0) { firstLen = BIGINT_BASE_DIGITS; }
  BigInt_init(&out);

  BigInt_add_small(b, &out, BigInt_atoi_impl_with_range(str, 0, firstLen - 1));

  for (i = firstLen; i < len; i+=BIGINT_BASE_DIGITS) {
    BigInt_multiply_small(&out, b, BIGINT_BASE_10);
    BigInt_add_small(b, &out, BigInt_atoi_impl_with_range(str, i, i + BIGINT_BASE_DIGITS - 1));
  }
  BigInt_destroy(&out);
}

void BigInt_set_from_string(BigInt * b, char * str) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_set_from_string_impl(&temp, str);

  BigInt_copy(b, &temp);
  BigInt_destroy(&temp);
}

void BigInt_set_from_string_with_sign(BigInt * b, char * str) {
  BigInt temp;
  int is_negative = 0;
  BigInt_init(&temp);

  if (str[0] == '-') {
    str = str + 1;
    is_negative = 1;
  }

  BigInt_set_from_string_impl(&temp, str);

  if (is_negative) {
    temp.sign = -1;
  } else {
    temp.sign = 1;
  }

  if (BigInt_is_zero_impl(temp.internalRepresentation, temp.internalSize)) {
    temp.sign = 0;
  }

  BigInt_copy(b, &temp);
  BigInt_destroy(&temp);
}

void BigInt_init_from_string(BigInt * b, char * str) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_set_from_string_impl(&temp, str);

  BigInt_copy_to_no_init(b, &temp, 0, 0);
  BigInt_destroy(&temp);
}

void BigInt_init_from_string_with_sign(BigInt * b, char * str) {
  BigInt temp;
  int is_negative = 0;
  BigInt_init(&temp);

  if (str[0] == '-') {
    str = str + 1;
    is_negative = 1;
  }

  BigInt_set_from_string_impl(&temp, str);

  if (is_negative) {
    temp.sign = -1;
  } else {
    temp.sign = 1;
  }

  if (BigInt_is_zero_impl(temp.internalRepresentation, temp.internalSize)) {
    temp.sign = 0;
  }

  BigInt_copy_to_no_init(b, &temp, 0, 0);
  BigInt_destroy(&temp);
}

void BigInt_add_t(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_add(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

void BigInt_subtract_t(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_subtract(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

void BigInt_multiply_t(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_multiply(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

void BigInt_divide_t(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_divide(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

void BigInt_add_ts(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_add_with_sign(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

void BigInt_subtract_ts(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_subtract_with_sign(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

void BigInt_multiply_ts(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_multiply_with_sign(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

void BigInt_divide_ts(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_divide_with_sign(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

void BigInt_set_from_limb(BigInt * b, BigInt_limb_t num, BigInt_limb_t limb_base) {
  int len = 1;
  int i = 0;
  BigInt_limb_t n = num;
  if (num == 0) {
    b->internalRepresentation[0] = 0;
    b->internalSize = 1;
    return;
  }
  while(n >= limb_base) {
    n = n / limb_base;
    len++;
  }
  if (b->allocSize < len) {
    free(b->internalRepresentation);
    b->internalRepresentation = (BigInt_limb_t *)malloc(len * sizeof(BigInt_limb_t));
    b->allocSize = len;
  }
  b->internalSize = len;
  while (num != 0) {
    b->internalRepresentation[i] = num % limb_base;
    num = num / limb_base;
    i++;
  }
}

void BigInt_big_add(BigInt * sum, BigInt * addend1, BigInt * addend2) {
  if (BigInt_cmp(addend1, addend2) < 0) {
    BigInt * temp = addend1;
    addend1 = addend2;
    addend2 = temp;
  }
  if (sum->allocSize > addend1->internalSize) {
    sum->internalSize = addend1->internalSize + 1;
    sum->internalRepresentation[addend1->internalSize] = 0;
  } else {
    free(sum->internalRepresentation);
    sum->internalRepresentation = (BigInt_limb_t *)malloc((addend1->internalSize + 1) * sizeof(BigInt_limb_t));
    sum->internalRepresentation[addend1->internalSize] = 0;
    sum->internalSize = addend1->internalSize + 1;
    sum->allocSize = addend1->internalSize + 1;
  }
  
  BigInt_add_impl(addend1->internalRepresentation, addend2->internalRepresentation, sum->internalRepresentation, addend1->internalSize, addend2->internalSize, sum->internalSize, BIGINT_BASE_10);
  BigInt_remove_leading_zeroes(sum);
}

void BigInt_big_multiply(BigInt * product, BigInt * multiplicand, BigInt * multiplier) {
  int i;
  if (BigInt_cmp(multiplicand, multiplier) < 0) {
    BigInt * temp = multiplicand;
    multiplicand = multiplier;
    multiplier = temp;
  }
  if (product->allocSize >= multiplicand->internalSize + multiplier->internalSize) {
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
  } else {
    free(product->internalRepresentation);
    product->internalRepresentation = (BigInt_limb_t *)malloc((multiplicand->internalSize + multiplier->internalSize) * sizeof(BigInt_limb_t));
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
    product->allocSize = multiplicand->internalSize + multiplier->internalSize;
  }
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentation[i] = 0;
  }
  BigInt_multiply_impl(multiplicand->internalRepresentation, multiplier->internalRepresentation, product->internalRepresentation, multiplicand->internalSize, multiplier->internalSize, product->internalSize, BIGINT_BASE_10);
  BigInt_remove_leading_zeroes(product);
}


void BigInt_B10_add(BigInt * sum, BigInt * addend1, BigInt * addend2) {
  if (BigInt_cmp(addend1, addend2) < 0) {
    BigInt * temp = addend1;
    addend1 = addend2;
    addend2 = temp;
  }
  if (sum->allocSize > addend1->internalSize) {
    sum->internalSize = addend1->internalSize + 1;
    sum->internalRepresentation[addend1->internalSize] = 0;
  } else {
    free(sum->internalRepresentation);
    sum->internalRepresentation = (BigInt_limb_t *)malloc((addend1->internalSize + 1) * sizeof(BigInt_limb_t));
    sum->internalRepresentation[addend1->internalSize] = 0;
    sum->internalSize = addend1->internalSize + 1;
    sum->allocSize = addend1->internalSize + 1;
  }
  
  BigInt_add_impl(addend1->internalRepresentation, addend2->internalRepresentation, sum->internalRepresentation, addend1->internalSize, addend2->internalSize, sum->internalSize, 10);
  BigInt_remove_leading_zeroes(sum);
}

void BigInt_B10_multiply(BigInt * product, BigInt * multiplicand, BigInt * multiplier) {
  int i;
  if (BigInt_cmp(multiplicand, multiplier) < 0) {
    BigInt * temp = multiplicand;
    multiplicand = multiplier;
    multiplier = temp;
  }
  if (product->allocSize >= multiplicand->internalSize + multiplier->internalSize) {
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
  } else {
    free(product->internalRepresentation);
    product->internalRepresentation = (BigInt_limb_t *)malloc((multiplicand->internalSize + multiplier->internalSize) * sizeof(BigInt_limb_t));
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
    product->allocSize = multiplicand->internalSize + multiplier->internalSize;
  }
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentation[i] = 0;
  }
  BigInt_multiply_impl(multiplicand->internalRepresentation, multiplier->internalRepresentation, product->internalRepresentation, multiplicand->internalSize, multiplier->internalSize, product->internalSize, 10);
  BigInt_remove_leading_zeroes(product);
}

char * BigInt_to_string_with_small_base(BigInt * b) {
  int i;
  BigInt out1, out2, base, temp;
  char * str_out;
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);

  BigInt_set_from_limb(&base, BIGINT_BASE, 10);

  for (i = 0; i < b->internalSize; i++) {
    BigInt_B10_multiply(&out2, &out1, &base);
    BigInt_set_from_limb(&temp, b->internalRepresentation[b->internalSize - 1 - i], 10);
    BigInt_B10_add(&out1, &out2, &temp);
  }

  str_out = (char *)malloc((out1.internalSize + 1) * sizeof(char));

  for (i = 0; i < out1.internalSize; i++) {
    str_out[i] = out1.internalRepresentation[out1.internalSize - 1 - i] + '0';
  }

  str_out[out1.internalSize] = 0;

  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);

  return str_out;
}

int BigInt_count_digits_base_10(BigInt * b) {
  int i, msl_count, n, count_digits;
  BigInt out1, out2, base, temp;
  char * str_out;
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);

  BigInt_set_from_limb(&base, BIGINT_BASE, BIGINT_BASE_10);

  for (i = 0; i < b->internalSize; i++) {
    BigInt_big_multiply(&out2, &out1, &base);
    BigInt_set_from_limb(&temp, b->internalRepresentation[b->internalSize - 1 - i], BIGINT_BASE_10);
    BigInt_big_add(&out1, &out2, &temp);
  }

  n = out1.internalRepresentation[out1.internalSize - 1];

  msl_count = 1;
  while (n >= 10) {
    n = n / 10;
    msl_count++;
  }

  count_digits = msl_count + ((out1.internalSize - 1) * BIGINT_BASE_DIGITS);

  

  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);

  return count_digits;
}


char * BigInt_to_string(BigInt * b) {
  int i, j, msl_count, n, count_digits, offset;
  BigInt out1, out2, base, temp;
  char * str_out;
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);

  BigInt_set_from_limb(&base, BIGINT_BASE, BIGINT_BASE_10);

  for (i = 0; i < b->internalSize; i++) {
    BigInt_big_multiply(&out2, &out1, &base);
    BigInt_set_from_limb(&temp, b->internalRepresentation[b->internalSize - 1 - i], BIGINT_BASE_10);
    BigInt_big_add(&out1, &out2, &temp);
  }

  n = out1.internalRepresentation[out1.internalSize - 1];

  msl_count = 1;
  while (n >= 10) {
    n = n / 10;
    msl_count++;
  }

  count_digits = msl_count + ((out1.internalSize - 1) * BIGINT_BASE_DIGITS);

  str_out = (char *)malloc((count_digits + 1)* sizeof(char));

  for (i = 0; i < count_digits; i++) {
    str_out[i] = '0';
  }

  offset = 0;

  for (i = out1.internalSize - 1; i >= 0; i--) {
    n = out1.internalRepresentation[i];
    if (offset == 0) {
      while (n != 0) {
        str_out[msl_count - 1 - offset] = (n % 10) + '0';
        n = n / 10;
        offset++;
      }
    } else {
      j = BIGINT_BASE_DIGITS - 1;
      while(n != 0) {
        str_out[offset + j] = (n % 10) + '0';
        n = n / 10;
        j--;
      }
      offset = offset + BIGINT_BASE_DIGITS;
    }
  }

  str_out[count_digits] = 0;

  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);

  return str_out;
}

char * BigInt_to_string_with_sign(BigInt * b) {
  int i, j, msl_count, n, count_digits, offset, hasSign = 0;
  BigInt out1, out2, base, temp;
  char * str_out;
  BigInt_init(&out1);
  BigInt_init(&out2);
  BigInt_init(&base);
  BigInt_init(&temp);

  if (b->sign == -1) {
    hasSign = 1;
  }

  BigInt_set_from_limb(&base, BIGINT_BASE, BIGINT_BASE_10);

  for (i = 0; i < b->internalSize; i++) {
    BigInt_big_multiply(&out2, &out1, &base);
    BigInt_set_from_limb(&temp, b->internalRepresentation[b->internalSize - 1 - i], BIGINT_BASE_10);
    BigInt_big_add(&out1, &out2, &temp);
  }

  n = out1.internalRepresentation[out1.internalSize - 1];

  msl_count = 1;
  while (n >= 10) {
    n = n / 10;
    msl_count++;
  }

  count_digits = msl_count + ((out1.internalSize - 1) * BIGINT_BASE_DIGITS) + hasSign;

  str_out = (char *)malloc((count_digits + 1) * sizeof(char));

  for (i = 0; i < count_digits; i++) {
    str_out[i] = '0';
  }

  offset = 0;
  if (hasSign) {
    str_out[offset] = '-';
    offset++;
  }

  for (i = out1.internalSize - 1; i >= 0; i--) {
    n = out1.internalRepresentation[i];
    if (i == out1.internalSize - 1) {
      j = 0;
      while (n != 0) {
        str_out[msl_count - 1 - j + offset] = (n % 10) + '0';
        n = n / 10;
        j++;
      }
      offset = offset + j;
    } else {
      j = BIGINT_BASE_DIGITS - 1;
      while(n != 0) {
        str_out[offset + j] = (n % 10) + '0';
        n = n / 10;
        j--;
      }
      offset = offset + BIGINT_BASE_DIGITS;
    }
  }

  str_out[count_digits] = 0;

  BigInt_destroy(&base);
  BigInt_destroy(&temp);
  BigInt_destroy(&out2);
  BigInt_destroy(&out1);

  return str_out;
}

void BigInt_print_internal(BigInt * b) {
  int i;
  printf("[");
  for (i = 0; i < b->internalSize; i++) {
    printf("%d", b->internalRepresentation[i]);
    if (i < b->internalSize - 1) {
      printf(", ");
    }
  }
  printf("]\n");
}

void BigInt_shift_left(BigInt * b, int n) {
  int i, j;
  BigInt_limb_t * temp = NULL;
  if (BigInt_is_zero_impl(b->internalRepresentation, b->internalSize) || n <= 0) {
    return;
  }
  if (b->allocSize < b->internalSize + n) {
    temp = (BigInt_limb_t *)malloc(sizeof(BigInt_limb_t) * (b->internalSize + n));
    for (i = 0; i < b->internalSize; i++) {
      temp[i] = b->internalRepresentation[i];
    }
    free(b->internalRepresentation);
    b->internalRepresentation = temp;
    b->allocSize = b->internalSize + n;
  }
  b->internalSize = b->internalSize + n;
  j = b->internalSize - n - 1;
  i = b->internalSize - 1;
  for (; j >= 0; j--) {
    b->internalRepresentation[i] = b->internalRepresentation[j];
    i--;
  }
  for (; i >= 0; i--) {
    b->internalRepresentation[i] = 0;
  }
}

void BigInt_shift_right(BigInt * b, int n) {
  int i, j;
  if (n >= b->internalSize) {
    b->internalRepresentation[0] = 0;
    b->internalSize = 1;
    return;
  }
  if (BigInt_is_zero_impl(b->internalRepresentation, b->internalSize) || n <= 0) {
    return;
  }
  i = 0;
  for (j = n; j < b->internalSize; j++) {
    b->internalRepresentation[i] = b->internalRepresentation[j];
    i++;
  }
  for (; i < b->internalSize; i++) {
    b->internalRepresentation[i] = 0;
  }
  BigInt_remove_leading_zeroes(b);
}

void BigInt_add_leading_zeroes(BigInt * b, int n) {
  int i;
  BigInt_limb_t * newInts = NULL;

  if (n <= 0) {
    return;
  }

  if (b->allocSize < b->internalSize + n) {
    newInts = (BigInt_limb_t *)malloc(sizeof(BigInt_limb_t) * (b->internalSize + n));
    for (i = 0; i < b->internalSize; i++) {
      newInts[i] = b->internalRepresentation[i];
    }
    free(b->internalRepresentation);
    b->internalRepresentation = newInts;
    b->allocSize = b->internalSize + n;
  }
  b->internalSize = b->internalSize + n;
  for (i = 0; i < n; i++) {
    b->internalRepresentation[b->internalSize - 1 - i] = 0;
  }
}

void BigInt_set_from_view(BigInt * dest, BigInt * source, int start, int end) {
  int i, j;
  BigInt_limb_t * limbs = NULL;
  if (dest->allocSize < (end - start + 1)) {
    limbs = (BigInt_limb_t *)malloc(sizeof(BigInt_limb_t) * (end - start + 1));
    free(dest->internalRepresentation);
    dest->internalRepresentation = limbs;
    dest->allocSize = (end - start + 1);
  }
  dest->internalSize = end - start + 1;
  j = 0;
  for (i = start; i <= end; i++) {
    dest->internalRepresentation[j] = source->internalRepresentation[i];
    j++;
  }
}

void BigInt_multiply_karatsuba_impl(BigInt * multiplicand, BigInt * multiplier, BigInt * product) {
  if (multiplicand->internalSize < 2 || multiplier->internalSize < 2) {
    BigInt_multiply(product, multiplicand, multiplier);
  } else {
    BigInt low1, low2, high1, high2;
    BigInt z0, z1, z2;
    BigInt sum1, sum2;
    int l = multiplicand->internalSize;
    int m = l / 2;
    int len1, len2, lenMax;
    BigInt_init(&low1);
    BigInt_init(&low2);
    BigInt_init(&high1);
    BigInt_init(&high2);

    BigInt_init(&z0);
    BigInt_init(&z1);
    BigInt_init(&z2);


    BigInt_init(&sum1);
    BigInt_init(&sum2);

    BigInt_set_from_view(&low1, multiplicand, 0, m - 1);
    BigInt_set_from_view(&low2, multiplier, 0, m - 1);
    BigInt_set_from_view(&high1, multiplicand, m, l - 1);
    BigInt_set_from_view(&high2, multiplier, m, l - 1);

    BigInt_multiply_karatsuba_impl(&low1, &low2, &z0);
    BigInt_multiply_karatsuba_impl(&high1, &high2, &z2);

    BigInt_add(&sum1, &low1, &high1);
    BigInt_add(&sum2, &low2, &high2);

    len1 = sum1.internalSize;
    len2 = sum2.internalSize;
    lenMax = len1;

    if (len2 > len1) {
      lenMax = len2;
    }

    BigInt_add_leading_zeroes(&sum1, lenMax - len1);
    BigInt_add_leading_zeroes(&sum2, lenMax - len2);
    
    BigInt_multiply_karatsuba_impl(&sum1, &sum2, &z1);
    BigInt_subtract_t(&z1, &z1, &z0);
    BigInt_subtract_t(&z1, &z1, &z2);

    BigInt_shift_left(&z2, 2 * m);
    BigInt_shift_left(&z1, m);
    BigInt_add(&sum1, &z2, &z1);
    BigInt_add(product, &sum1, &z0);

    BigInt_destroy(&sum1);
    BigInt_destroy(&sum2);

    BigInt_destroy(&z0);
    BigInt_destroy(&z1);
    BigInt_destroy(&z2);

    BigInt_destroy(&low1);
    BigInt_destroy(&low2);
    BigInt_destroy(&high1);
    BigInt_destroy(&high2);
  }
}

void BigInt_multiply_karatsuba(BigInt * product, BigInt * multiplicand, BigInt * multiplier) {
  int i, m1_len, m2_len, mlen_max;
  BigInt m1, m2;
  BigInt_copy_to_no_init(&m1, multiplicand, 0, 0);
  BigInt_copy_to_no_init(&m2, multiplier, 0, 0);
  m1_len = m1.internalSize;
  m2_len = m2.internalSize;
  mlen_max = m1_len;
  if (m2_len > m1_len) {
    mlen_max = m2_len;
  }
  BigInt_add_leading_zeroes(&m1, mlen_max - m1_len);
  BigInt_add_leading_zeroes(&m2, mlen_max - m2_len);
  BigInt_multiply_karatsuba_impl(&m1, &m2, product);
  BigInt_destroy(&m1);
  BigInt_destroy(&m2);
  BigInt_remove_leading_zeroes(product);
}

void BigInt_multiply_karatsuba_t(BigInt * out, BigInt * a, BigInt * b) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_multiply_karatsuba(&temp, a, b);
  
  BigInt_copy(out, &temp);
  BigInt_destroy(&temp);
}

#endif

#ifdef __cplusplus
}
#endif
