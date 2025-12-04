#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void longToArray(char * buf, unsigned long long num) {
  int i = 0;
  int l = 0;
  int r = 1;
  buf[0] = '0';
  buf[1] = 0;
  while(num != 0) {
    buf[i] = num % 10 + '0';
    num = num / 10;
    i++;
    buf[i] = 0;
  }
  r = i - 1;
  while (l < r) {
    char c = buf[l];
    buf[l] = buf[r];
    buf[r] = c;
    l++;
    r--;
  }
}

int isInvalidID(unsigned long long num) {
  char buffer[16];
  int len;
  longToArray(buffer, num);
  len = strlen(buffer);
  if (len % 2) {
    // printf("Number is valid\n");
    return 0;
  }
  int stop = len / 2;
  for (int i = 0; i < stop; i++) {
    if (buffer[i] != buffer[i + stop]) {
      return 0;
    }
  }
  return 1;
}

void loop(unsigned long long start, unsigned long long finish, unsigned long long * sum) {
  for (unsigned long long i = start; i <= finish; i++) {
    if (isInvalidID(i)) {
      *sum = *sum + i;
    }
  }
}

int isInvalidID2(unsigned long long num) {
  char buffer[16];
  int len;
  longToArray(buffer, num);
  len = strlen(buffer);
  char temp[16];
  int isInvalid = 1;

  for (int i = 1; i <= len / 2; i++) {
    if (len % i) {
      continue;
    }
    for (int j = 0; j < i; j++) {
      temp[j] = buffer[j];
    }
    isInvalid = 1;
    int k = i;
    int m = 0;
    while(k < len) {
      if (buffer[k] != temp[m]) {
        isInvalid = 0;
        break;
      }
      k++;
      m = (m + 1) % i;
    }
    if (isInvalid) {
      return 1;
    }
  }
  return 0;
}

void loop2(unsigned long long start, unsigned long long finish, unsigned long long * sum) {
  for (unsigned long long i = start; i <= finish; i++) {
    if (isInvalidID2(i)) {
      *sum = *sum + i;
    }
  }
}

int main() {
  FILE * fptr;
  char buf[1024];
  int buflen;
  unsigned long long sum1 = 0;
  unsigned long long sum2 = 0;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    fgets(buf, 1024, fptr);

    if (strstr(buf, "\n") != NULL) {
      buf[strstr(buf, "\n") - buf] = 0;
    }

    buflen = strlen(buf);

    unsigned long long a = 0, b = 0;
    int flag = 0;
    for (int i = 0; i < buflen; i++) {
      if (buf[i] == '-') {
        flag = 1;
      } else if (buf[i] == ',') {
        flag = 0;
        /* printf("Range is %llu to %llu\n", a, b); */
        loop(a, b, &sum1);
        loop2(a, b, &sum2);
        a = 0;
        b = 0;
      } else {
        if (flag == 0) {
          a = a * 10 + buf[i] - '0';
        } else if (flag == 1) {
          b = b * 10 + buf[i] - '0';
        }
      }
    }

    /* printf("Range is %llu to %llu\n", a, b); */
    loop(a, b, &sum1);
    loop2(a, b, &sum2);

    printf("Part 1 answer is: %llu\n", sum1);
    printf("Part 2 answer is: %llu\n", sum2);

    fclose(fptr);
  }

  return 0;
}