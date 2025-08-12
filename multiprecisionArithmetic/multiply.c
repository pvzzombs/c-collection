#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "multiprecisionArithmetic.h"

#define MAXDIGITS 1024

int main(int argc, char *argv[]) {
  char a[MAXDIGITS];
  char b[MAXDIGITS];
  char testcasesBuffer[5];
  int testcases;
  char ** testcasesResults = NULL;

  fgets(testcasesBuffer, 5, stdin);

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
    c = multiply(a, b);

    testcasesResults[i] = c;
  }

  for (int i = 0; i < testcases; i++) {
    printf("%s\n", testcasesResults[i]);
    free(testcasesResults[i]);
  }

  free(testcasesResults);
  return 0;
}