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
  int i;
  int aEnd, bEnd;
  char * c = NULL;

  fgets(testcasesBuffer, 5, stdin);

  testcases = atoi(testcasesBuffer);

  testcasesResults = malloc(testcases * sizeof(char *));

  for (i = 0; i < testcases; i++) {
    fgets(a, MAXDIGITS, stdin);
    fgets(b, MAXDIGITS, stdin);

    aEnd = strstr(a, "\n") - a;
    bEnd = strstr(b, "\n") - b;

    a[aEnd] = 0;
    b[bEnd] = 0;

    c = mpa_add(a, b);

    testcasesResults[i] = c;
  }

  for (i = 0; i < testcases; i++) {
    printf("%s\n", testcasesResults[i]);
    free(testcasesResults[i]);
  }

  free(testcasesResults);
  return 0;
}