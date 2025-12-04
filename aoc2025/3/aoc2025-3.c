#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void twobatt(char * str, unsigned long long * sum) {
  int len = strlen(str);
  int max1 = -1;
  int max1pos = -1;
  int max2 = -1;
  int i = 0;
  int j = 0;
  int temp;
  while(i < len) {
    int digit = str[i] - '0';
    if (digit > max1) {
      max1 = digit;
      max1pos = i;
    }
    i++;
  }
  if (max1pos + 1 >= len) {
    i = 0;
    while(i < max1pos) {
      int digit = str[i] - '0';
      if (digit > max2) {
        max2 = digit;
      }
      i++;
    }
    temp = max1;
    max1 = max2;
    max2 = temp;
  } else {
    i = max1pos + 1;
    while (i < len) {
      int digit = str[i] - '0';
      if (digit > max2) {
        max2 = digit;
      }
      i++;
    }
  }
  *sum = *sum + (max1 * 10 + max2);
}

int findLargestLeft(char * str, int * arr, int pos) {
  int index = -1;
  int max = -1;
  for (int i = 0; i <= pos; i++) {
    int d = str[i] - '0';
    if (arr[i] > 0) {
      continue;
    }
    if (d > max) {
      max = d;
      index = i;
    }
  }
  return index;
}

int findLargestRight(char * str, int * arr, int pos) {
  int index = -1;
  int max = -1;
  for (int i = pos; i < strlen(str); i++) {
    int d = str[i] - '0';
    if (arr[i] > 0) {
      continue;
    }
    if (d > max) {
      max = d;
      index = i;
    }
  }
  return index;
}

void twelvebatt(char * str, unsigned long long * sum) {
  int * arr = malloc(strlen(str) * sizeof(int));
  int pos = 0;
  int i, j;
  int lmax, rmax;
  unsigned long long left;
  unsigned long long right;
  unsigned long long num = 0;

  for (i = 0; i < strlen(str); i++) {
    arr[i] = 0;
  }

  for (i = 0; i < 12; i++) {
    int lmaxi = findLargestLeft(str, arr, pos - 1);
    int rmaxi;
    if (i == 0) {
      rmaxi = findLargestRight(str, arr, pos);
    } else {
      rmaxi = findLargestRight(str, arr, pos + 1);
    }

    if (lmaxi == -1) {
      left = 0;
    } else {
      for (j = 0; j < strlen(str); j++) {
        if (arr[j] || j == lmaxi) {
          left = left * 10 + (str[j] - '0');
        }
      }
    }

    if (rmaxi == -1) {
      right = 0;
    } else {
      for (j = 0; j < strlen(str); j++) {
        if (arr[j] || j == rmaxi) {
          right = right * 10 + (str[j] - '0');
        }
      }
    }

    if (left >= right) {
      arr[lmaxi] = 1;
      pos = lmaxi;
    } else {
      arr[rmaxi] = 1;
      pos = rmaxi;
    }

  }

  for (i = 0; i < strlen(str); i++) {
    if (arr[i]) {
      num = num * 10 + (str[i] - '0');
    }
  }

  /* printf("Number is %llu\n", num); */

  free(arr);
}

void twelvebatt2(char * str, unsigned long long * sum) {
  int len = strlen(str);
  int * arr = malloc(len * sizeof(int));
  int i;
  unsigned long long num = 0;

  for (i = 0; i < len; i++) {
    arr[i] = 0;
  }

  for (i = 0; i < 12; i++) {
    int l = 0;
    int lmax = 0;
    int candidate = 0;
    int max = 0;
    int j = 0;
    for (j = 0; j < len; j++) {
      int digit = str[j] - '0';
      if (arr[j]) {
        l = l + digit;
        continue;
      }
      if (l > lmax) {
        lmax = l;
        candidate = j;
        max = digit;
      } else {
        if (digit > max) {
          candidate = j;
          max = digit;
        }
      }
    }
    arr[candidate] = 1;
  }

  for (i = 0; i < len; i++) {
    if (arr[i]) {
      num = num * 10 + (str[i] - '0');
    }
  }

  /* printf("Number is %llu\n", num); */

  *sum = *sum + num;

  free(arr);
}

int main() {
  FILE * fptr;
  char buf[128];
  unsigned long long sum1 = 0;
  unsigned long long sum2 = 0;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    while(fgets(buf, 128, fptr)) {
      if (strstr(buf, "\n") != NULL) {
        buf[strstr(buf, "\n") - buf] = 0;
      }
      if (strcmp(buf, "") != 0) {
        twobatt(buf, &sum1);
        twelvebatt2(buf, &sum2);
      }
    }

    fclose(fptr);

    printf("Part 1 answer is: %llu\n", sum1);
    printf("Part 2 answer is: %llu\n", sum2);
  }

  return 0;
}