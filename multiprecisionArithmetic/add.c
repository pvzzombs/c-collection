#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDIGITS 1024

void reverse(char * arr, int len) {
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

char * shiftToLeft(char * c) {
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

char * add(char * a, char * b) {
  int lenA, lenB;
  int len, lenC;
  lenA = strlen(a);
  lenB = strlen(b);
  reverse(a, lenA);
  reverse(b, lenB);
  char * c = NULL;
  if (lenB > lenA) {
    char * temp = a;
    a = b;
    b = temp;
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
  int s = 0, carry = 0;
  for (i = 0; i < len; i++) {
    int num1 = a[i] - '0';
    int num2 = b[i] - '0';
    s = (num1 + num2 + carry) % 10;
    carry = (num1 + num2 + carry) / 10;
    c[i] = s + '0';
  }
  for(; i < lenC; i++) {
    int num = 0;
    if(i < lenA) {
      num = a[i] - '0';
    }
    s = (num + carry) % 10;
    carry = (num + carry) / 10;
    c[i] = s + '0';
  }
  reverse(c, strlen(c));
  shiftToLeft(c);
  return c;
}

int main(int argc, char *argv[]) {
  char a[MAXDIGITS];
  char b[MAXDIGITS];
  char testcasesBuffer[10];
  int testcases;
  char ** testcasesResults = NULL;

  fgets(testcasesBuffer, 10, stdin);

  testcases = atoi(testcasesBuffer);

  testcasesResults = malloc(testcases * sizeof(char *));

  for (int i = 0; i < testcases; i++) {
    fgets(a, MAXDIGITS, stdin);
    fgets(b, MAXDIGITS, stdin);

    int aEnd = strstr(a, "\n") - a;
    int bEnd = strstr(b, "\n") - b;

    a[aEnd] = 0;
    b[bEnd] = 0;

    char * c = NULL;
    c = add(a, b);

    testcasesResults[i] = c;
  }

  for (int i = 0; i < testcases; i++) {
    printf("%s\n", testcasesResults[i]);
    free(testcasesResults[i]);
  }

  free(testcasesResults);
  return 0;
}