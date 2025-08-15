#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Reverse digits.
* @param arr The big integer
* @param len The length of the big integer
*/
void reverseDigits(char * arr, int len) {
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

/*
* Compares big integer digit by digit.
* @param num1 The first number
* @param num2 The second number
* @return `-1` if `num1` is less than `num2`, `0` if `num1` is equal to `num2`, 1 if `num1` is greater than `num2`
*/
int bigIntCmp(char * num1, char * num2) {
  if (strlen(num1) < strlen(num2)) {
    return -1;
  } else if (strlen(num1) > strlen(num2)) {
    return 1;
  } else {
    for (int i = 0; i < strlen(num1); i++) {
      if (num1[i] < num2[i]) {
        return -1;
      } else if (num1[i] > num2[i]) {
        return 1;
      }
    }
  }
  return 0;
}

/*
* Compares big integer digit by digit, but in reverse.
* @param num1 The first number
* @param num2 The second number
* @return `-1` if `num1` is less than `num2`, `0` if `num1` is equal to `num2`, 1 if `num1` is greater than `num2`
*/
int bigIntCmpReverse(char * num1, char * num2) {
  if (strlen(num1) < strlen(num2)) {
    return -1;
  } else if (strlen(num1) > strlen(num2)) {
    return 1;
  } else {
    for (int i = strlen(num1) - 1; i >= 0; i--) {
      if (num1[i] < num2[i]) {
        return -1;
      } else if (num1[i] > num2[i]) {
        return 1;
      }
    }
  }
  return 0;
}

/*
* Remove leading zeroes, zeroes located infront of the number.
* Returns string zero if string only contains zero characters.
* @param c The big integer
* @return The big integer modified
*/
char * removeLeadingZeroes(char * c) {
  int target = 0;
  int len = strlen(c);
  int i;
  
  while(target < len){
    if(c[target] != '0') {
      break;
    }
    target++;
  }
  
  if(target >= len) {
    // it means all digits is zero
    if(len >= 1) {
      // this means the string has some contents, we can modify this
      c[0] = '0';
      c[1] = 0;
    }
    return c;
  }
  
  for (i = 0; i < len - target; i++) {
    c[i] = c[target + i];
  }
  c[len - target] = 0;
  return c;
}

/*
* Core addition logic implementation.
* `sum` can be the `addend1` or `addend2`.
* You can use this technique above to reduce memory allocations.
* Note that `addend1` and `addemd2` must be reversed before using this.
* Assumes `sumLen` is bigger than or equal to `addend1Len` or `addend2Len`.
* Assumes `sum` is big enough for the result to be stored correctly.
* NOTE: The result is reversed, so you need to reverse it again.
* @param addend1 The first addend 
* @param addend2 The second addend
* @param sum Location of the sum
* @param addend1Len Number of digits of the first addend
* @param addend2Len Number of digits of the second addend
* @param sumLen Number of digits of the sum
*/
void add_impl(char * addend1, char * addend2, char * sum, int addend1Len, int addend2Len, int sumLen) {
  int i;
  int digitSum = 0, carry = 0;
  for (i = 0; i < addend2Len; i++) {
    int digitAddend1 = addend1[i] - '0';
    int digitAddend2 = addend2[i] - '0';
    digitSum = (digitAddend1 + digitAddend2 + carry) % 10;
    carry = (digitAddend1 + digitAddend2 + carry) / 10;
    sum[i] = digitSum + '0';
  }
  for(; i < sumLen; i++) {
    int num = 0;
    if(i < addend1Len) {
      num = addend1[i] - '0';
    }
    digitSum = (num + carry) % 10;
    carry = (num + carry) / 10;
    sum[i] = digitSum + '0';
  }
}

/*
* Addition, no assumptions.
* But for better, `num1` should be bigger to `num2`.
* @param num1 The first big integer
* @param num2 The second big integer
* @return The newly allocated sum
*/
char * add(char * num1, char * num2) {
  char * addend1 = malloc((strlen(num1) + 1) * sizeof(char));
  char * addend2 = malloc((strlen(num2) + 1) * sizeof(char));

  strcpy(addend1, num1);
  strcpy(addend2, num2);

  int lenA, lenB;
  int lenC;
  lenA = strlen(addend1);
  lenB = strlen(addend2);
  reverseDigits(addend1, lenA);
  reverseDigits(addend2, lenB);
  char * sum = NULL;

  // this condition should be ignored
  // as long as addend1 is bigger or
  // equal to addend2
  if (lenB > lenA) {
    char * temp = addend1;
    addend1 = addend2;
    addend2 = temp;
    int c = lenA;
    lenA = lenB;
    lenB = c;
  }

  // len = lenB; // smallest length
  lenC = lenA + 1; // length of the sum
  sum = malloc((lenC + 1) * sizeof(char));
  // lenC + 1 to accomodate the extra zero byte terminator
  sum[lenC - 1] = '0'; // first digit set to 0, no need to actually do this
  sum[lenC] = 0; // the zero byte;
  
  add_impl(addend1, addend2, sum, lenA, lenB, lenC);

  reverseDigits(sum, strlen(sum));
  removeLeadingZeroes(sum);

  free(addend1);
  free(addend2);

  return sum;
}

/*
* Core subtraction logic implementation.
* `difference` can be `minuend` or `subtrahend`.
* You can use this technique above to reduce memory allocations.
* Note that `minuend` and `subtrahend` must be reversed before using this.
* Assumes `differenceLen` is equal to `minuendLen` or `subtrahendLen`.
* Assumes `difference` is big enough to store the result correctly.
* NOTE: The result is reversed, so you need to reverse it again.
* @param minuend The minuend or the number to start with
* @param subtrahend The subtrahend or the number used to subtract
* @param difference The location of the result
* @param minuendLen The number of digits of minuend
* @param subtrahendLen The number of digits of subtrahend
* @param differenceLen The number of digits of difference
*/
void subtract_impl(char * minuend, char * subtrahend, char * difference, int minuendLen, int subtrahendLen, int differenceLen) {
  int i;
  int digitDifference = 0, borrow = 0;
  for (i = 0; i < subtrahendLen; i++) {
    int minuendDigit = minuend[i] - '0';
    int subtrahendDigit = subtrahend[i] - '0';
    int tempBorrow = borrow;

    //printf("Digit is %d\n", minuendDigit);

    if (minuendDigit - tempBorrow < subtrahendDigit) {
      minuendDigit += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }
    digitDifference = minuendDigit - tempBorrow - subtrahendDigit;
    difference[i] = digitDifference + '0';
    //printf("d is %d\n", difference[i] - '0');
  }

  for (; i < minuendLen; i++) {
    int minuendDigit = minuend[i] - '0';
    int tempBorrow = borrow;
    //printf("---Digit is %d\n", minuendDigit);
    if (minuendDigit - tempBorrow < 0) {
      minuendDigit += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }
    digitDifference = minuendDigit - tempBorrow - 0;
    difference[i] = digitDifference + '0';
    //printf("d is %d\n", difference[i] - '0');
  }
}

/*
* Subtraction, assumes that `num1` is always
* bigger than `num2`.
* @param num1 The minuend
* @param num2 The subtrahend
* @return The newly allocated difference
*/
char * subtract(char * num1, char * num2) {
  char * minuend = malloc((strlen(num1) + 1) * sizeof(char));
  char * subtrahend = malloc((strlen(num2) + 1) * sizeof(char));

  strcpy(minuend, num1);
  strcpy(subtrahend, num2);

  int lenA, lenB;
  // int len;
  lenA = strlen(minuend);
  lenB = strlen(subtrahend);
  reverseDigits(minuend, lenA);
  reverseDigits(subtrahend, lenB);
  char * difference = NULL;

  // this condition should be ignored
  // as long as minuend is bigger or
  // equal to subtrahend
  // if (lenB > lenA) {
  //   char * temp = minuend;
  //   minuend = subtrahend;
  //   subtrahend = temp;
  //   int c = lenA;
  //   lenA = lenB;
  //   lenB = c;
  // }

  // len = lenB;
  difference = malloc((lenA + 1) * sizeof(char));

  //printf("Size of difference is %d\n", len);

  difference[lenA] = 0;

  subtract_impl(minuend, subtrahend, difference, lenA, lenB, lenA);

  reverseDigits(difference, strlen(difference));

  //printf("===DEBUG: %s\n", difference);

  removeLeadingZeroes(difference);
  //printf("===DEBUG: %s\n", difference);

  free(minuend);
  free(subtrahend);

  return difference;
}

/*
* Core multiplication logic implementation.
* Assumes `product` is zeroed, which means all elements are zero characters.
* If `product` is non zero, product will be added to `product`, which
* might not be what you want.
* Note that `multiplicand` and `multiplier` must be reversed before using this.
* Assumes `productLen` is the size of `multiplicandLen` plus `multiplierLen`.
* Assumes `product` is big enough to store the result correctly.
* NOTE: The result is reversed, so you need to reverse it again.
* @param multiplicand The number to start with
* @param multiplier The number that tells how many times to add
* @param product The location of the product
* @param multiplicandLen The number of digits of multiplicand
* @param multiplierLen The number of digits of multiplier
* @param productLen The number of digits of product
*/
void multiply_impl(char * multiplicand, char * multiplier, char * product, int multiplicandLen, int multiplierLen, int productLen) {
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
      int m = multiplicand[i] - '0';
      int n = multiplier[j] - '0';
      int p = product[pIndex] - '0';
      productDigit = (m * n + carryM) % 10;
      carryM = (m * n + carryM) / 10;
      sumDigit = (productDigit + carryA + p) % 10;
      carryA = (productDigit + carryA + p) / 10;
      product[pIndex] = sumDigit + '0';
      pIndex++;
    }

    // printf("Middle: %d", productDigit);
    for(; pIndex < productLen; pIndex++) {
      int p = product[pIndex] - '0';
      sumDigit = (carryM + carryA + p) % 10;
      carryA = (carryM + carryA + p) / 10;
      product[pIndex] = sumDigit + '0';
      carryM = 0;
    }
    pIndex = pIndexTemp + 1;
  }
}

/*
* Multiplication, no assumptions.
* But for better, `num1` should be bigger to `num2`.
* @param num1 The multiplicand
* @param num2 The multiplier
* @return The newly allocated product
*/
char * multiply(char * num1, char * num2) {
  char * multiplicand = malloc((strlen(num1) + 1) * sizeof(char));
  char * multiplier = malloc((strlen(num2) + 1) * sizeof(char));

  strcpy(multiplicand, num1);
  strcpy(multiplier, num2);

  int lenA, lenB;
  lenA = strlen(multiplicand);
  lenB = strlen(multiplier);

  reverseDigits(multiplicand, lenA);
  reverseDigits(multiplier, lenB);

  char * product = NULL;

  if (lenB > lenA) {
    char * temp = multiplicand;
    multiplicand = multiplier;
    multiplier = temp;
    int c = lenA;
    lenA = lenB;
    lenB = c;
  }

  product = malloc((lenA + lenB + 1) * sizeof(char));

  product[lenA + lenB] = 0;

  for (int i = 0; i < lenA + lenB; i++) {
    product[i] = '0';
  }

  multiply_impl(multiplicand, multiplier, product, lenA, lenB, lenA + lenB);
  // printf("DEBUG: %s", product);
  reverseDigits(product, strlen(product));

  removeLeadingZeroes(product);

  free(multiplicand);
  free(multiplier);

  return product;
}

/*
* The inverse of removeLeadingZeroes
* @param arr The big integer
* @param count The number of zeroes to add
* @return The newly allocated big int, with zeroes in front
*/
char * addLeadingZeroes(char * arr, int count) {
  char * newArr = malloc((strlen(arr) + count + 1) * sizeof(char));
  newArr[strlen(arr) + count] = 0;
  memset(newArr, '0', strlen(arr) + count);
  int x = 0;
  for (int i = count; i < strlen(newArr); i++) {
    newArr[i] = arr[x];
    x++;
  }
  return newArr;
}

char * addTrailingZeroes(char * arr, int count) {
  char * newArr = malloc((strlen(arr) + count + 1) * sizeof(char));
  memset(newArr, '0', strlen(arr) + count);
  newArr[strlen(arr) + count] = 0;
  for (int i = 0; i < strlen(arr); i++) {
    newArr[i] = arr[i];
  }
  return newArr;
}

/*
* @param a The first number
* @param b The second number
* @return The smallest number
*/
int mininumInt(int a, int b) {
  return a < b ? a : b;
}

/*
* Compares big integer digit by digit.
* Tells whether `num1` is less than `num2`.
* @param num1 The first number
* @param num2 The second number
* @return `1` if true, `0` otherwise
*/
int lessThanInt(char * num1, char * num2) {
  if (strlen(num1) < strlen(num2)) {
    return 1;
  } else if (strlen(num1) > strlen(num2)) {
    return 0;
  } else {
    for (int i = 0; i < strlen(num1); i++) {
      if (num1[i] < num2[i]) {
        return 1;
      } else if (num1[i] > num2[i]) {
        return 0;
      }
    }
  }
  return 0;
}

/*
* Move digits to left by one
* Done in place, no allocation/s done
* Disregard the last digit
* @param arr The big integer
*/
void shiftLeftInPlaceByOne(char * arr) {
  int i = 0;
  for (int j = 1; j < strlen(arr); j++) {
    arr[i] = arr[j];
    i++;
  }
  arr[strlen(arr) - 1] = '0';
}

void shiftRightInPlaceByOne(char * arr) {
  for (int i = strlen(arr) - 1; i > 0; i--) {
    arr[i] = arr[i - 1];
  }
  arr[0] = '0';
}

/*
* Core division logic implementation.
* Assumes `dividend` and `divisor` are normalized.
* Assumes `dividendLen` is bigger than `divisorLen`.
* Assumes `quotient` is big enough to store the result correctly.
* @param dividend The number to be divided
* @param divisor The number that will be used to divide
* @param quotient The location of the quotient
* @param dividendLen The number of digits of dividend
* @param divisorLen The number of digits of divisor
* @param quotientLen The number of digits of quotient
*/
void divide_impl(char * dividend, char * divisor, char * quotient, int dividendLen, int divisorLen, int quotientLen) {
  int remainderLen = divisorLen + 1;
  char * remainder = malloc((remainderLen + 1) * sizeof(char));
  char * tempHolder = malloc((remainderLen + 1) * sizeof(char));

  for (int i = 0; i < remainderLen; i++) {
    remainder[i] = dividend[i];
  }

  remainder[remainderLen] = 0;
  tempHolder[remainderLen] = 0;

  for (int i = 0; i < quotientLen; i++) {
    remainder[remainderLen - 1] = dividend[i + remainderLen - 1];
    int qDigit1 = remainder[0] - '0';
    int qDigit2 = remainder[1] - '0';
    int dvsrDigit = divisor[0] - '0';
    int qhat = (qDigit1 * 10 + qDigit2) / dvsrDigit;
    qhat = mininumInt(qhat, 9);
    // printf("quotion digit candidate is %d\n", qhat);
    char qDigit[] = { qhat + '0', 0};
    reverseDigits(divisor, divisorLen); // reverse divisor
    // reverseDigits(tempHolder, remainderLen); // reverse 
    memset(tempHolder, '0', remainderLen);
    multiply_impl(divisor, qDigit, tempHolder, divisorLen, 1, remainderLen);
    // printf("Currend dividend: %s\n", remainder);
    // printf("Temp is: %s\n", tempHolder);
    reverseDigits(tempHolder, remainderLen); // back to normal
    while (bigIntCmp(remainder, tempHolder) < 0) {
      qDigit[0] -= 1;
      memset(tempHolder, '0', remainderLen);
      multiply_impl(divisor, qDigit, tempHolder, divisorLen, 1, remainderLen);
      reverseDigits(tempHolder, remainderLen); // back to normal
    }
    // printf("Quotient digit is: %d\n", qDigit[0] - '0');
    reverseDigits(remainder, remainderLen); // reverse
    reverseDigits(tempHolder, remainderLen); // reverse
    // char tempRemainder[remainderLen + 1];
    // tempRemainder[remainderLen] = 0;
    // memset(tempRemainder, '0', remainderLen);
    // subtract_impl(remainder, tempHolder, tempRemainder, remainderLen, remainderLen, remainderLen);
    subtract_impl(remainder, tempHolder, remainder, remainderLen, remainderLen, remainderLen);
    quotient[i] = qDigit[0];
    // strcpy(remainder, tempRemainder);
    reverseDigits(remainder, remainderLen); // back to normal
    shiftLeftInPlaceByOne(remainder);
    reverseDigits(tempHolder, remainderLen); // back to normal
    reverseDigits(divisor, divisorLen); // back to normal divisor
    // printf("Remainder new is : %s\n", remainder);
  }

  free(remainder);
  free(tempHolder);
}

/*
* Division, assumes that `num1` is always bigger than `num2`
* @param num1 The dividend
* @param num2 The divisor
* @return The newly allocated quotient
*/
char * divide(char * num1, char * num2) {
  char * dividend = malloc((strlen(num1) + 1) * sizeof(char));
  char * divisor = malloc((strlen(num2) + 1) * sizeof(char));

  strcpy(dividend, num1);
  strcpy(divisor, num2);

  char * quotient = NULL;
  int dividendLen = strlen(dividend);
  int divisorLen = strlen(divisor);
  int quotientLen = dividendLen - divisorLen;

  char * newDividend = addLeadingZeroes(dividend, 1);
  free(dividend);
  dividend = newDividend;
  dividendLen = strlen(newDividend);
  quotientLen = dividendLen - divisorLen;

  // normalization
  if (divisor[0] - '0' < 5) {
    int d = 10 / ((divisor[0] - '0') + 1);
    // printf("d is %d\n", d);
    char dStr[] = {d + '0', 0};

    char * newDividendTemp = malloc((dividendLen + 1) * sizeof(char));    
    char * newDivisorTemp = malloc((divisorLen + 1) * sizeof(char));    

    memset(newDividendTemp, '0', dividendLen + 1);
    memset(newDivisorTemp, '0', divisorLen + 1);

    newDividendTemp[dividendLen] = 0;
    newDivisorTemp[divisorLen] = 0;

    // printf("dStr is %s\n", dStr);
    reverseDigits(dividend, strlen(dividend));
    reverseDigits(divisor, strlen(divisor));
    multiply_impl(dividend, dStr, newDividendTemp, dividendLen - 1, 1, dividendLen);
    multiply_impl(divisor, dStr, newDivisorTemp, divisorLen, 1, divisorLen);

    // printf("New dividend: %s\n", newDividendTemp);
    // printf("New divisor: %s\n", newDivisorTemp);

    free(dividend);
    free(divisor);

    dividend = newDividendTemp;
    divisor = newDivisorTemp;

    reverseDigits(dividend, strlen(dividend));
    reverseDigits(divisor, strlen(divisor));

    // printf("Dividend is %s\n", dividend);
    // printf("Divisor is %s\n", divisor);

  }

  quotient = malloc((quotientLen + 1) * sizeof(char));
  quotient[quotientLen] = 0;
  
  divide_impl(dividend, divisor, quotient, dividendLen, divisorLen, quotientLen);

  removeLeadingZeroes(quotient);

  free(dividend);
  free(divisor);

  return quotient;
}

/*
* Core division logic implementation.
* Note that `dividend` and `divisor` must be reversed before using this.
* Assumes `dividend` and `divisor` are normalized.
* Assumes `dividendLen` is bigger than `divisorLen`.
* Assumes `quotient` is big enough to store the result correctly.
* NOTE: The result is reversed, so you need to reverse it again.
* @param dividend The number to be divided
* @param divisor The number that will be used to divide
* @param quotient The location of the quotient
* @param dividendLen The number of digits of dividend
* @param divisorLen The number of digits of divisor
* @param quotientLen The number of digits of quotient
*/
void divide_impl_reverse(char * dividend, char * divisor, char * quotient, int dividendLen, int divisorLen, int quotientLen) {
  int remainderLen = divisorLen + 1;
  char * remainder = malloc((remainderLen + 1) * sizeof(char));
  char * tempHolder = malloc((remainderLen + 1) * sizeof(char));

  for (int i = 0; i < remainderLen; i++) {
    remainder[remainderLen - i - 1] = dividend[dividendLen - i - 1];
  }

  remainder[remainderLen] = 0;
  tempHolder[remainderLen] = 0;

  for (int i = 0; i < quotientLen; i++) {
    remainder[0] = dividend[quotientLen - 1 - i];
    int qDigit1 = remainder[remainderLen - 1] - '0';
    int qDigit2 = remainder[remainderLen - 2] - '0';
    int dvsrDigit = divisor[divisorLen - 1] - '0';
    int qhat = (qDigit1 * 10 + qDigit2) / dvsrDigit;
    qhat = mininumInt(qhat, 9);
    char qDigit[] = { qhat + '0', 0};
    memset(tempHolder, '0', remainderLen);
    multiply_impl(divisor, qDigit, tempHolder, divisorLen, 1, remainderLen);

    while (bigIntCmpReverse(remainder, tempHolder) < 0) {
      qDigit[0] -= 1;
      memset(tempHolder, '0', remainderLen);
      multiply_impl(divisor, qDigit, tempHolder, divisorLen, 1, remainderLen);
    }

    subtract_impl(remainder, tempHolder, remainder, remainderLen, remainderLen, remainderLen);
    quotient[quotientLen - 1 - i] = qDigit[0];
    shiftRightInPlaceByOne(remainder);
  }

  free(remainder);
  free(tempHolder);
}

/*
* Division, assumes that `num1` is always bigger than `num2`
* @param num1 The dividend
* @param num2 The divisor
* @return The newly allocated quotient
*/
char * divide_reverse(char * num1, char * num2) {
  char * dividend = malloc((strlen(num1) + 1) * sizeof(char));
  char * divisor = malloc((strlen(num2) + 1) * sizeof(char));

  strcpy(dividend, num1);
  strcpy(divisor, num2);

  char * quotient = NULL;
  int dividendLen = strlen(dividend);
  int divisorLen = strlen(divisor);
  int quotientLen = dividendLen - divisorLen;

  char * newDividend = addLeadingZeroes(dividend, 1);
  free(dividend);
  dividend = newDividend;
  dividendLen = strlen(newDividend);
  quotientLen = dividendLen - divisorLen;

  reverseDigits(dividend, dividendLen);
  reverseDigits(divisor, divisorLen);

  // normalization
  if (divisor[divisorLen - 1] - '0' < 5) {
    int d = 10 / ((divisor[divisorLen - 1] - '0') + 1);
    char dStr[] = {d + '0', 0};

    char * newDividendTemp = malloc((dividendLen + 1) * sizeof(char));    
    char * newDivisorTemp = malloc((divisorLen + 1) * sizeof(char));    

    memset(newDividendTemp, '0', dividendLen + 1);
    memset(newDivisorTemp, '0', divisorLen + 1);

    newDividendTemp[dividendLen] = 0;
    newDivisorTemp[divisorLen] = 0;

    multiply_impl(dividend, dStr, newDividendTemp, dividendLen - 1, 1, dividendLen);
    multiply_impl(divisor, dStr, newDivisorTemp, divisorLen, 1, divisorLen);

    free(dividend);
    free(divisor);

    dividend = newDividendTemp;
    divisor = newDivisorTemp;

  }

  quotient = malloc((quotientLen + 1) * sizeof(char));
  quotient[quotientLen] = 0;
  
  divide_impl_reverse(dividend, divisor, quotient, dividendLen, divisorLen, quotientLen);

  reverseDigits(quotient, quotientLen);

  removeLeadingZeroes(quotient);

  free(dividend);
  free(divisor);

  return quotient;
}