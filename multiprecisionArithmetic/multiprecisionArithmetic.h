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
  char * c = NULL;
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
  c = malloc((lenC + 1) * sizeof(char));
  // lenC + 1 to accomodate the extra zero byte terminator
  c[lenC - 1] = '0'; // first digit set to 0, no need to actually do this
  c[lenC] = 0; // the zero byte;
  int i;
  int digitSum = 0, carry = 0;
  for (i = 0; i < len; i++) {
    int digitAddend1 = addend1[i] - '0';
    int digitAddend2 = addend2[i] - '0';
    digitSum = (digitAddend1 + digitAddend2 + carry) % 10;
    carry = (digitAddend1 + digitAddend2 + carry) / 10;
    c[i] = digitSum + '0';
  }
  for(; i < lenC; i++) {
    int num = 0;
    if(i < lenA) {
      num = addend1[i] - '0';
    }
    digitSum = (num + carry) % 10;
    carry = (num + carry) / 10;
    c[i] = digitSum + '0';
  }
  reverseDigits(c, strlen(c));
  shiftToLeftDigits(c);

  free(addend1);
  free(addend2);

  return c;
}