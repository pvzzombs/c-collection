#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char * shiftToLeftDigits(char * c) {
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

char * add(char * num1, char * num2) {
  char * addend1 = malloc((strlen(num1) + 1) * sizeof(char));
  char * addend2 = malloc((strlen(num2) + 1) * sizeof(char));

  strcpy(addend1, num1);
  strcpy(addend2, num2);

  int lenA, lenB;
  int len, lenC;
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

  len = lenB; // smallest length
  lenC = lenA + 1; // length of the sum
  sum = malloc((lenC + 1) * sizeof(char));
  // lenC + 1 to accomodate the extra zero byte terminator
  sum[lenC - 1] = '0'; // first digit set to 0, no need to actually do this
  sum[lenC] = 0; // the zero byte;
  int i;
  int digitSum = 0, carry = 0;
  for (i = 0; i < len; i++) {
    int digitAddend1 = addend1[i] - '0';
    int digitAddend2 = addend2[i] - '0';
    digitSum = (digitAddend1 + digitAddend2 + carry) % 10;
    carry = (digitAddend1 + digitAddend2 + carry) / 10;
    sum[i] = digitSum + '0';
  }
  for(; i < lenC; i++) {
    int num = 0;
    if(i < lenA) {
      num = addend1[i] - '0';
    }
    digitSum = (num + carry) % 10;
    carry = (num + carry) / 10;
    sum[i] = digitSum + '0';
  }
  reverseDigits(sum, strlen(sum));
  shiftToLeftDigits(sum);

  free(addend1);
  free(addend2);

  return sum;
}

char * subtract(char * num1, char * num2) {
  char * minuend = malloc((strlen(num1) + 1) * sizeof(char));
  char * subtrahend = malloc((strlen(num2) + 1) * sizeof(char));

  strcpy(minuend, num1);
  strcpy(subtrahend, num2);

  int lenA, lenB;
  int len;
  lenA = strlen(minuend);
  lenB = strlen(subtrahend);
  reverseDigits(minuend, lenA);
  reverseDigits(subtrahend, lenB);
  char * difference = NULL;

  // this condition should be ignored
  // as long as minuend is bigger or
  // equal to subtrahend
  if (lenB > lenA) {
    char * temp = minuend;
    minuend = subtrahend;
    subtrahend = temp;
    int c = lenA;
    lenA = lenB;
    lenB = c;
  }

  len = lenB;
  difference = malloc((lenA + 1) * sizeof(char));

  //printf("Size of difference is %d\n", len);

  difference[lenA] = 0;

  int i;
  int digitDifference = 0, borrow = 0;
  for (i = 0; i < len; i++) {
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

  for (; i < lenA; i++) {
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

  reverseDigits(difference, strlen(difference));

  //printf("===DEBUG: %s\n", difference);

  shiftToLeftDigits(difference);
  //printf("===DEBUG: %s\n", difference);

  free(minuend);
  free(subtrahend);

  return difference;
}