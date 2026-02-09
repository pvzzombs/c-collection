#pragma once

#ifdef BIGINT_USE_64_BIT

#include <stdint.h>
#define BIGINT_BASE 1073741824LL
#define BIGINT_BASE_STRING "1073741824"
#define BIGINT_BASE_DIGITS 9
#define BIGINT_BASE_10 1000000000LL
typedef int64_t BigInt_limb_t;

#else

#define BIGINT_BASE 32768
#define BIGINT_BASE_STRING "32768"
#define BIGINT_BASE_DIGITS 4
#define BIGINT_BASE_10 10000
typedef int BigInt_limb_t;

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
void BigInt_from_string_impl(char *, BigInt_limb_t *, int *);
int BigInt_count_digits_to_base_Big(char * );
void BigInt_init_from_string(BigInt *, char *);
void BigInt_init_from_string_with_sign(BigInt *, char *);
void BigInt_set_from_string(BigInt *, char *);
void BigInt_set_from_string_with_sign(BigInt *, char *);
void BigInt_to_string_impl(BigInt_limb_t *, char *, int);
int BigInt_count_digits_to_base_10(int);
int BigInt_count_digits_base_10(BigInt *);
char * BigInt_to_string(BigInt *);
char * BigInt_to_string_with_sign(BigInt *);
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
void BigInt_add_impl(BigInt_limb_t *, BigInt_limb_t *, BigInt_limb_t *, int, int, int);
void BigInt_add(BigInt *, BigInt *, BigInt *);
void BigInt_add_small_impl(BigInt_limb_t *, BigInt_limb_t, BigInt_limb_t *, int, int);
void BigInt_add_small(BigInt *, BigInt *, BigInt_limb_t);
void BigInt_subtract_impl(BigInt_limb_t *, BigInt_limb_t *, BigInt_limb_t *, int, int, int);
void BigInt_subtract(BigInt *, BigInt *, BigInt *);
void BigInt_add_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_subtract_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_impl(BigInt_limb_t *, BigInt_limb_t *, BigInt_limb_t *, int, int, int);
void BigInt_multiply(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_small_impl(BigInt_limb_t *, BigInt_limb_t, BigInt_limb_t *, int, int);
void BigInt_multiply_small(BigInt *, BigInt *, BigInt_limb_t);
void BigInt_multiply_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_divide_impl(BigInt_limb_t *, BigInt_limb_t *, BigInt_limb_t *, int, int, int);
void BigInt_divide(BigInt *, BigInt *, BigInt *);
void BigInt_divide_no_copy(BigInt *, BigInt *, BigInt *);
void BigInt_divide_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_divide_no_copy_with_sign(BigInt *, BigInt *, BigInt *);
void BigInt_set_from_string_with_small(BigInt *, char *);
void BigInt_set_from_string_with_small_base_impl(BigInt *, char *);
void BigInt_set_from_string_with_small_base(BigInt *, char *);
void BigInt_set_from_string_with_small_base_with_sign(BigInt *, char *);
void BigInt_add_t(BigInt *, BigInt *, BigInt *);
void BigInt_subtract_t(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_t(BigInt *, BigInt *, BigInt *);
void BigInt_divide_t(BigInt *, BigInt *, BigInt *);
void BigInt_add_ts(BigInt *, BigInt *, BigInt *);
void BigInt_subtract_ts(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_ts(BigInt *, BigInt *, BigInt *);
void BigInt_divide_ts(BigInt *, BigInt *, BigInt *);

#ifdef BIGINT_IMPL

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "multiprecisionArithmetic.h"

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
  mpa_reverseDigits(dest, i);
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
  b->internalRepresentation = malloc(1 * sizeof(BigInt_limb_t));
  b->internalSize = 1;
  b->internalRepresentation[0] = 0;
  b->allocSize = 1;
  b->sign = 0;
}

void BigInt_from_string_impl (char * str, BigInt_limb_t * tempArray, int * i) {
  char * tmp = NULL;
  char * rem = NULL;
  char * mul = NULL;
  char * str2 = malloc((strlen(str) + 1) * sizeof(char));
  int clearTemp = 1;

  strcpy(str2, str);

  if (mpa_bigIntCmp(str2, BIGINT_BASE_STRING) < 0) {
    tempArray[*i] = BigInt_atoi_impl(str2);
    (*i)++;
    clearTemp = 0;
  } else {
    tmp = mpa_divide(str2, BIGINT_BASE_STRING);
    while(mpa_bigIntCmp(tmp, "0") > 0) {
      mul = mpa_multiply(tmp, BIGINT_BASE_STRING);
      rem = mpa_subtract(str2, mul);
      tempArray[*i] = BigInt_atoi_impl(rem);
      (*i)++;
      free(mul);
      free(rem);
      strcpy(str2, tmp);
      free(tmp);
      if (mpa_bigIntCmp(str2, BIGINT_BASE_STRING) < 0) {
        tempArray[*i] = BigInt_atoi_impl(str2);
        (*i)++;
        clearTemp = 0;
        break;
      } else {
        tmp = mpa_divide(str2, BIGINT_BASE_STRING);
      }
    }
  }

  if (clearTemp) {
    free(tmp);
  }
  free(str2);
}

int BigInt_count_digits_to_base_Big(char * str) {
  /* return (strlen(str) * 8 / BIGINT_BASE_BITS_COUNT) + 1; */
  double L = strlen(str);
  double B = BIGINT_BASE;
  double log10B = log10(B);
  /* double result = ceil(L / log10B); */
  double result = (L / log10B) + 1.0;
  return (int) result;
}

void BigInt_init_from_string (BigInt * b, char * str) {
  BigInt_limb_t * tempArray = malloc(BigInt_count_digits_to_base_Big(str) * sizeof(BigInt_limb_t));
  int i = 0;
  int x;
  BigInt_from_string_impl(str, tempArray, &i);
  b->internalRepresentation = malloc(i * sizeof(BigInt_limb_t));
  b->allocSize = i;
  for (x = 0; x < i; x++) {
    b->internalRepresentation[x] = tempArray[x];
  }
  b->internalSize = i;
  free(tempArray);
}

void BigInt_init_from_string_with_sign (BigInt * b, char * str) {
  BigInt_limb_t * tempArray = NULL;
  int i = 0;
  int x;
  char * absnum = str;
  if (str[0] == '-') {
    b->sign = -1;
    absnum = str + 1;
  } else {
    b->sign = 1;
  }
  tempArray = malloc(BigInt_count_digits_to_base_Big(absnum) * sizeof(BigInt_limb_t));
  BigInt_from_string_impl(absnum, tempArray, &i);

  if (BigInt_is_zero_impl(tempArray, i)) {
    b->sign = 0;
  }

  b->internalRepresentation = malloc(i * sizeof(BigInt_limb_t));
  b->allocSize = i;
  for (x = 0; x < i; x++) {
    b->internalRepresentation[x] = tempArray[x];
  }
  b->internalSize = i;
  free(tempArray);
}

void BigInt_set_from_string(BigInt * b, char * str) {
  BigInt_limb_t * tempArray = malloc(BigInt_count_digits_to_base_Big(str) * sizeof(BigInt_limb_t));
  int i = 0;
  int x;

  BigInt_from_string_impl(str, tempArray, &i);

  /* printf("Len is %d, I is %d, number is %s\n", BigInt_count_digits_to_base_Big(str), i, str); */
  
  if (b->allocSize >= i) {
    b->internalSize = i;
    for (x = 0; x < i; x++) {
      b->internalRepresentation[x] = tempArray[x];
    }
  } else {
    free(b->internalRepresentation);
    b->internalRepresentation = malloc(i * sizeof(BigInt_limb_t));
    b->internalSize = i;
    for (x = 0; x < i; x++) {
      b->internalRepresentation[x] = tempArray[x];
    }
    b->allocSize = i;
  }
  free(tempArray);
}

void BigInt_set_from_string_with_sign(BigInt * b, char * str) {
  BigInt_limb_t * tempArray = NULL;
  int i = 0;
  int x;
  char * absnum = str;

  if (str[0] == '-') {
    b->sign = -1;
    absnum = str + 1;
  } else {
    b->sign = 1;
  }

  tempArray = malloc(BigInt_count_digits_to_base_Big(absnum) * sizeof(BigInt_limb_t));
  BigInt_from_string_impl(absnum, tempArray, &i);

  if (BigInt_is_zero_impl(tempArray, i)) {
    b->sign = 0;
  }

  /* printf("Len is %d, I is %d, number is %s\n", BigInt_count_digits_to_base_Big(str), i, str); */
  
  if (b->allocSize >= i) {
    b->internalSize = i;
    for (x = 0; x < i; x++) {
      b->internalRepresentation[x] = tempArray[x];
    }
  } else {
    free(b->internalRepresentation);
    b->internalRepresentation = malloc(i * sizeof(BigInt_limb_t));
    b->internalSize = i;
    for (x = 0; x < i; x++) {
      b->internalRepresentation[x] = tempArray[x];
    }
    b->allocSize = i;
  }
  free(tempArray);
}

void BigInt_to_string_impl(BigInt_limb_t * arr, char * output, int arrLen) {
  char * tmpMul;
  char * tmpAdd;
  int x;
  if (arrLen == 0) {
    output[0] = '0';
    output[1] = 0;
  } else {
    BigInt_itoa_impl(arr[arrLen - 1], output);
    for (x = arrLen - 2; x >= 0; x--) {
      tmpMul = mpa_multiply(output, BIGINT_BASE_STRING);
      BigInt_itoa_impl(arr[x], output);
      tmpAdd = mpa_add(tmpMul, output);
      free(tmpMul);
      strcpy(output, tmpAdd);
      free(tmpAdd);
    }
  }
}

int BigInt_count_digits_to_base_10(int num) {
  double L = num;
  double B = BIGINT_BASE;
  double log10B = log10(B);
  double result = L * log10B + 1.0;
  return (int) result;
}

int BigInt_count_digits_base_10(BigInt * b) {
  double k = b->internalSize;
  double f = b->internalRepresentation[b->internalSize - 1];
  double B = BIGINT_BASE;
  double log10B = log10(B);
  double log10f = log10(f);
  double result = (k - 1) * log10B + log10f;

  if (BigInt_is_zero_impl(b->internalRepresentation, b->internalSize)) {
    return 1;
  }

  return (int) result + 1;
}

char * BigInt_to_string(BigInt * b) {
  int len = b->internalSize;
  int charLen = BigInt_count_digits_to_base_10(len);
  char * output = malloc((charLen + 1) * sizeof(char));

  memset(output, 0, charLen + 1);

  BigInt_to_string_impl(b->internalRepresentation, output, len);

  mpa_removeLeadingZeroes(output);

  return output;
}

char * BigInt_to_string_with_sign(BigInt * b) {
  int len = b->internalSize;
  int charLen = BigInt_count_digits_to_base_10(len);
  char * output = malloc((charLen + 2) * sizeof(char));
  int tempLen;
  int i;

  memset(output, 0, charLen + 2);

  BigInt_to_string_impl(b->internalRepresentation, output, len);

  mpa_removeLeadingZeroes(output);

  if (strcmp(output, "0") == 0) {
    return output;
  }

  tempLen = strlen(output);
  if (b->sign == -1) {
    for (i = tempLen + 1; i > 0; i--) {
      output[i] = output[i - 1];
    }
    output[0] = '-';
  }

  return output;
}

void BigInt_copy(BigInt * to, BigInt * from) {
  int i;
  if (to->allocSize < from->internalSize) {
    free(to->internalRepresentation);
    to->internalRepresentation = malloc(sizeof(BigInt_limb_t) * from->internalSize);
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
  dest->internalRepresentation = malloc(dest->allocSize * sizeof(BigInt_limb_t));
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
    newInts = malloc((bSize + 1) * sizeof(BigInt_limb_t));
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

void BigInt_add_impl(BigInt_limb_t * addend1, BigInt_limb_t * addend2, BigInt_limb_t * sum, int addend1Len, int addend2Len, int sumLen) {
  int i;
  BigInt_limb_t digitSum = 0, carry = 0;
  for (i = 0; i < addend2Len; i++) {
    BigInt_limb_t Addend1 = addend1[i];
    BigInt_limb_t Addend2 = addend2[i];
    digitSum = (Addend1 + Addend2 + carry) % (BigInt_limb_t)BIGINT_BASE;
    carry = (Addend1 + Addend2 + carry) / (BigInt_limb_t)BIGINT_BASE;
    sum[i] = digitSum;
  }
  for(; i < sumLen; i++) {
    BigInt_limb_t num = 0;
    if(i < addend1Len) {
      num = addend1[i];
    }
    digitSum = (num + carry) % (BigInt_limb_t)BIGINT_BASE;
    carry = (num + carry) / (BigInt_limb_t)BIGINT_BASE;
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
  } else {
    free(sum->internalRepresentation);
    sum->internalRepresentation = malloc((addend1->internalSize + 1) * sizeof(BigInt_limb_t));
    sum->internalRepresentation[addend1->internalSize] = 0;
    sum->internalSize = addend1->internalSize + 1;
    sum->allocSize = addend1->internalSize + 1;
  }
  
  BigInt_add_impl(addend1->internalRepresentation, addend2->internalRepresentation, sum->internalRepresentation, addend1->internalSize, addend2->internalSize, sum->internalSize);
  BigInt_remove_leading_zeroes(sum);
}

void BigInt_add_small_impl(BigInt_limb_t * addend1, BigInt_limb_t addend2, BigInt_limb_t * sum, int addend1Len, int sumLen) {
  int i = 0;
  BigInt_limb_t digitSum = 0, carry = 0;
  BigInt_limb_t Addend1 = addend1[i];
  BigInt_limb_t Addend2 = addend2;
  digitSum = (Addend1 + Addend2 + carry) % BIGINT_BASE;
  carry = (Addend1 + Addend2 + carry) / BIGINT_BASE;
  sum[i] = digitSum;
  i++;
  for(; i < sumLen; i++) {
    BigInt_limb_t num = 0;
    if(i < addend1Len) {
      num = addend1[i];
    }
    digitSum = (num + carry) % BIGINT_BASE;
    carry = (num + carry) / BIGINT_BASE;
    sum[i] = digitSum;
  }
}

void BigInt_add_small(BigInt * sum, BigInt * addend1, BigInt_limb_t addend2) {
  if (sum->allocSize > addend1->internalSize) {
    sum->internalSize = addend1->internalSize + 1;
  } else {
    free(sum->internalRepresentation);
    sum->internalRepresentation = malloc((addend1->internalSize + 1) * sizeof(BigInt_limb_t));
    sum->internalRepresentation[addend1->internalSize] = 0;
    sum->internalSize = addend1->internalSize + 1;
    sum->allocSize = addend1->internalSize + 1;
  }
  
  BigInt_add_small_impl(addend1->internalRepresentation, addend2, sum->internalRepresentation, addend1->internalSize, sum->internalSize);
  BigInt_remove_leading_zeroes(sum);
}

void BigInt_subtract_impl(BigInt_limb_t * minuend, BigInt_limb_t * subtrahend, BigInt_limb_t * difference, int minuendLen, int subtrahendLen, int differenceLen) {
  int i;
  BigInt_limb_t digitDifference = 0, borrow = 0;
  for (i = 0; i < subtrahendLen; i++) {
    BigInt_limb_t minuendDigit = minuend[i];
    BigInt_limb_t subtrahendDigit = subtrahend[i];
    BigInt_limb_t tempBorrow = borrow;

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
    BigInt_limb_t minuendDigit = minuend[i];
    BigInt_limb_t tempBorrow = borrow;
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

void BigInt_subtract(BigInt * difference, BigInt * minuend, BigInt * subtrahend) {
  if (difference->allocSize >= minuend->internalSize) {
    difference->internalSize = minuend->internalSize;
  } else {
    free(difference->internalRepresentation);
    difference->internalRepresentation = malloc((minuend->internalSize) * sizeof(BigInt_limb_t));
    difference->internalSize = minuend->internalSize;
    difference->allocSize = minuend->internalSize;
  }
  BigInt_subtract_impl(minuend->internalRepresentation, subtrahend->internalRepresentation, difference->internalRepresentation, minuend->internalSize, subtrahend->internalSize, difference->internalSize);
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
    sum->internalRepresentation = malloc((addend1->internalSize + 1) * sizeof(BigInt_limb_t));
    sum->internalRepresentation[addend1->internalSize] = 0;
    sum->internalSize = addend1->internalSize + 1;
    sum->allocSize = addend1->internalSize + 1;
  }
  if(sameSign) {
    BigInt_add_impl(addend1->internalRepresentation, addend2->internalRepresentation, sum->internalRepresentation, addend1->internalSize, addend2->internalSize, sum->internalSize);
  } else {
    BigInt_subtract_impl(addend1->internalRepresentation, addend2->internalRepresentation, sum->internalRepresentation, addend1->internalSize, addend2->internalSize, sum->internalSize);
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
    difference->internalRepresentation = malloc((minuend->internalSize + allowance) * sizeof(BigInt_limb_t));
    difference->internalRepresentation[minuend->internalSize + allowance] = 0;
    difference->internalSize = minuend->internalSize + allowance;
    difference->allocSize = minuend->internalSize + allowance;
  }
  if (sameSign) {
    BigInt_add_impl(minuend->internalRepresentation, subtrahend->internalRepresentation, difference->internalRepresentation, minuend->internalSize, subtrahend->internalSize, difference->internalSize);
  } else {
    BigInt_subtract_impl(minuend->internalRepresentation, subtrahend->internalRepresentation, difference->internalRepresentation, minuend->internalSize, subtrahend->internalSize, difference->internalSize);
  }
  BigInt_remove_leading_zeroes(difference);
}

void BigInt_multiply_impl(BigInt_limb_t * multiplicand, BigInt_limb_t * multiplier, BigInt_limb_t * product, int multiplicandLen, int multiplierLen, int productLen) {
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
      productDigit = (m * n + carryM) % BIGINT_BASE;
      carryM = (m * n + carryM) / BIGINT_BASE;
      sumDigit = (productDigit + carryA + p) % BIGINT_BASE;
      carryA = (productDigit + carryA + p) / BIGINT_BASE;
      product[pIndex] = sumDigit;
      pIndex++;
    }

    for(; pIndex < productLen; pIndex++) {
      BigInt_limb_t p = product[pIndex];
      sumDigit = (carryM + carryA + p) % BIGINT_BASE;
      carryA = (carryM + carryA + p) / BIGINT_BASE;
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
    product->internalRepresentation = malloc((multiplicand->internalSize + multiplier->internalSize) * sizeof(BigInt_limb_t));
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
    product->allocSize = multiplicand->internalSize + multiplier->internalSize;
  }
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentation[i] = 0;
  }
  BigInt_multiply_impl(multiplicand->internalRepresentation, multiplier->internalRepresentation, product->internalRepresentation, multiplicand->internalSize, multiplier->internalSize, product->internalSize);
  BigInt_remove_leading_zeroes(product);
}

void BigInt_multiply_small_impl(BigInt_limb_t * multiplicand, BigInt_limb_t multiplier, BigInt_limb_t * product, int multiplicandLen, int productLen) {
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
    productDigit = (m * n + carryM) % BIGINT_BASE;
    carryM = (m * n + carryM) / BIGINT_BASE;
    sumDigit = (productDigit + carryA + p) % BIGINT_BASE;
    carryA = (productDigit + carryA + p) / BIGINT_BASE;
    product[pIndex] = sumDigit;
    pIndex++;
  }

  for(; pIndex < productLen; pIndex++) {
    BigInt_limb_t p = product[pIndex];
    sumDigit = (carryM + carryA + p) % BIGINT_BASE;
    carryA = (carryM + carryA + p) / BIGINT_BASE;
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
    product->internalRepresentation = malloc((multiplicand->internalSize + 1) * sizeof(BigInt_limb_t));
    product->internalSize = multiplicand->internalSize + 1;
    product->allocSize = multiplicand->internalSize + 1;
  }
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentation[i] = 0;
  }
  BigInt_multiply_small_impl(multiplicand->internalRepresentation, multiplier, product->internalRepresentation, multiplicand->internalSize, product->internalSize);
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
    product->internalRepresentation = malloc((multiplicand->internalSize + multiplier->internalSize) * sizeof(BigInt_limb_t));
    product->internalSize = multiplicand->internalSize + multiplier->internalSize;
    product->allocSize = multiplicand->internalSize + multiplier->internalSize;
  }
  for (i = 0; i < product->internalSize; i++) {
    product->internalRepresentation[i] = 0;
  }
  BigInt_multiply_impl(multiplicand->internalRepresentation, multiplier->internalRepresentation, product->internalRepresentation, multiplicand->internalSize, multiplier->internalSize, product->internalSize);
  BigInt_remove_leading_zeroes(product);
}

void BigInt_divide_impl(BigInt_limb_t * dividend, BigInt_limb_t * divisor, BigInt_limb_t * quotient, int dividendLen, int divisorLen, int quotientLen) {
  int remainderLen = divisorLen + 1;
  BigInt_limb_t * remainder = malloc((remainderLen) * sizeof(BigInt_limb_t));
  BigInt_limb_t * tempHolder = malloc((remainderLen) * sizeof(BigInt_limb_t));
  int i, j;
  BigInt_limb_t qDigit1, qDigit2, dvsrDigit, qhat;
  BigInt_limb_t * qDigit = malloc(1 * sizeof(int));

  for (i = 0; i < remainderLen; i++) {
    remainder[remainderLen - i - 1] = dividend[dividendLen - i - 1];
  }

  for (i = 0; i < quotientLen; i++) {
    remainder[0] = dividend[quotientLen - i - 1];
    qDigit1 = remainder[remainderLen - 1];
    qDigit2 = remainder[remainderLen - 2];
    dvsrDigit = divisor[divisorLen - 1];
    qhat = (qDigit1 * BIGINT_BASE + qDigit2) / dvsrDigit;
    qhat = mpa_mininumInt(qhat, BIGINT_BASE - 1);

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

void BigInt_divide(BigInt * quotient, BigInt * dividend1, BigInt * divisor) {
  BigInt_limb_t * d = malloc(1 * sizeof(BigInt_limb_t));
  int i;
  BigInt_limb_t * newDividend = NULL;
  BigInt_limb_t * newDivisor = NULL;

  BigInt dividend2;
  BigInt_copy_to_no_init(&dividend2, dividend1, 1, 1);

  d[0] = BIGINT_BASE / (divisor->internalRepresentation[divisor->internalSize - 1] + 1);
  newDividend = malloc((dividend2.internalSize) * sizeof(BigInt_limb_t));
  newDivisor = malloc((divisor->internalSize) * sizeof(BigInt_limb_t));
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
    quotient->internalRepresentation = malloc((dividend2.internalSize - divisor->internalSize) * sizeof(BigInt_limb_t));
    quotient->internalSize = dividend2.internalSize - divisor->internalSize;
    quotient->allocSize = dividend2.internalSize - divisor->internalSize;
  }
  BigInt_multiply_impl(dividend2.internalRepresentation, d, newDividend, dividend2.internalSize - 1, 1, dividend2.internalSize);
  BigInt_multiply_impl(divisor->internalRepresentation, d, newDivisor, divisor->internalSize, 1, divisor->internalSize);
  BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentation, dividend2.internalSize, divisor->internalSize, quotient->internalSize);
  BigInt_remove_leading_zeroes(quotient);

  BigInt_destroy(&dividend2);
  free(newDividend);
  free(newDivisor);
  free(d);
}

void BigInt_divide_no_copy(BigInt * quotient, BigInt * dividend, BigInt * divisor) {
  BigInt_limb_t * d = malloc(1 * sizeof(BigInt_limb_t));
  int i;
  BigInt_limb_t * newDividend = NULL;
  BigInt_limb_t * newDivisor = NULL;

  BigInt_add_leading_zero(dividend);

  d[0] = BIGINT_BASE / (divisor->internalRepresentation[divisor->internalSize - 1] + 1);
  newDividend = malloc((dividend->internalSize) * sizeof(BigInt_limb_t));
  newDivisor = malloc((divisor->internalSize) * sizeof(BigInt_limb_t));
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
    quotient->internalRepresentation = malloc((dividend->internalSize - divisor->internalSize) * sizeof(BigInt_limb_t));
    quotient->internalSize = dividend->internalSize - divisor->internalSize;
    quotient->allocSize = dividend->internalSize - divisor->internalSize;
  }
  BigInt_multiply_impl(dividend->internalRepresentation, d, newDividend, dividend->internalSize - 1, 1, dividend->internalSize);
  BigInt_multiply_impl(divisor->internalRepresentation, d, newDivisor, divisor->internalSize, 1, divisor->internalSize);
  BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentation, dividend->internalSize, divisor->internalSize, quotient->internalSize);
  BigInt_remove_leading_zeroes(quotient);
  BigInt_remove_leading_zeroes(dividend);

  free(newDividend);
  free(newDivisor);
  free(d);
}

void BigInt_divide_with_sign(BigInt * quotient, BigInt * dividend1, BigInt * divisor) {
  BigInt_limb_t * d = malloc(1 * sizeof(BigInt_limb_t));
  int i;
  BigInt_limb_t * newDividend = NULL;
  BigInt_limb_t * newDivisor = NULL;

  BigInt dividend2;
  BigInt_copy_to_no_init(&dividend2, dividend1, 1, 1);

  d[0] = BIGINT_BASE / (divisor->internalRepresentation[divisor->internalSize - 1] + 1);
  newDividend = malloc((dividend2.internalSize) * sizeof(BigInt_limb_t));
  newDivisor = malloc((divisor->internalSize) * sizeof(BigInt_limb_t));
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
      quotient->internalRepresentation = malloc(1 * sizeof(BigInt_limb_t));
      quotient->internalRepresentation[0] = 0;
      quotient->internalSize = 1;
      quotient->allocSize = 1;
    }
  } else {
    if (quotient->allocSize >= dividend2.internalSize - divisor->internalSize) {
      quotient->internalSize = dividend2.internalSize - divisor->internalSize;
    } else {
      free(quotient->internalRepresentation);
      quotient->internalRepresentation = malloc((dividend2.internalSize - divisor->internalSize) * sizeof(BigInt_limb_t));
      quotient->internalSize = dividend2.internalSize - divisor->internalSize;
      quotient->allocSize = dividend2.internalSize - divisor->internalSize;
    }
    BigInt_multiply_impl(dividend2.internalRepresentation, d, newDividend, dividend2.internalSize - 1, 1, dividend2.internalSize);
    BigInt_multiply_impl(divisor->internalRepresentation, d, newDivisor, divisor->internalSize, 1, divisor->internalSize);
    BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentation, dividend2.internalSize, divisor->internalSize, quotient->internalSize);
    BigInt_remove_leading_zeroes(quotient);
  }
  
  BigInt_destroy(&dividend2);
  free(newDividend);
  free(newDivisor);
  free(d);
}

void BigInt_divide_no_copy_with_sign(BigInt * quotient, BigInt * dividend, BigInt * divisor) {
  BigInt_limb_t * d = malloc(1 * sizeof(BigInt_limb_t));
  int i;
  BigInt_limb_t * newDividend = NULL;
  BigInt_limb_t * newDivisor = NULL;

  BigInt_add_leading_zero(dividend);

  d[0] = BIGINT_BASE / (divisor->internalRepresentation[divisor->internalSize - 1] + 1);
  newDividend = malloc((dividend->internalSize) * sizeof(BigInt_limb_t));
  newDivisor = malloc((divisor->internalSize) * sizeof(BigInt_limb_t));
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
      quotient->internalRepresentation = malloc(1 * sizeof(BigInt_limb_t));
      quotient->internalRepresentation[0] = 0;
      quotient->internalSize = 1;
      quotient->allocSize = 1;
    }
  } else {
    if (quotient->allocSize >= dividend->internalSize - divisor->internalSize) {
      quotient->internalSize = dividend->internalSize - divisor->internalSize;
    } else {
      free(quotient->internalRepresentation);
      quotient->internalRepresentation = malloc((dividend->internalSize - divisor->internalSize) * sizeof(BigInt_limb_t));
      quotient->internalSize = dividend->internalSize - divisor->internalSize;
      quotient->allocSize = dividend->internalSize - divisor->internalSize;
    }
    BigInt_multiply_impl(dividend->internalRepresentation, d, newDividend, dividend->internalSize - 1, 1, dividend->internalSize);
    BigInt_multiply_impl(divisor->internalRepresentation, d, newDivisor, divisor->internalSize, 1, divisor->internalSize);
    BigInt_divide_impl(newDividend, newDivisor, quotient->internalRepresentation, dividend->internalSize, divisor->internalSize, quotient->internalSize);
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

void BigInt_set_from_string_with_small_base_impl(BigInt * b, char * str) {
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

void BigInt_set_from_string_with_small_base(BigInt * b, char * str) {
  BigInt temp;
  BigInt_init(&temp);

  BigInt_set_from_string_with_small_base_impl(&temp, str);

  BigInt_copy(b, &temp);
  BigInt_destroy(&temp);
}

void BigInt_set_from_string_with_small_base_with_sign(BigInt * b, char * str) {
  BigInt temp;
  int is_negative = 0;
  BigInt_init(&temp);

  if (str[0] == '-') {
    str = str + 1;
    is_negative = 1;
  }

  BigInt_set_from_string_with_small_base_impl(&temp, str);

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

#endif
