#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "multiprecisionArithmetic.h"

#define MAXDIGITS 1024

int main() {
  char a[] = "9876543210987654321987654321";
  char b[] = "12345678901234567890";
  char * c = NULL;
  char sum[] = "9876543223333333223222222211";
  char diff[] = "9876543198641975420753086431";

  c = add(a, b);
  printf("Sum: %s\n", c);
  if (strcmp(c, sum) == 0) {
    printf("[INFO] Sum is correct\n");
  }
  free(c);

  c = subtract(a, b);
  printf("Difference: %s\n", c);
  if (strcmp(c, diff) == 0) {
    printf("[INFO] Difference is correct\n");
  }
  free(c);

  return 0;
}