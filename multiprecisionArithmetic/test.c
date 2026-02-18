#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiprecisionArithmetic.h"

#define BIGINT_IMPL
#include "bigInteger.h"

int main() {
  char a[] = "9876543210987654321987654321";
  char b[] = "12345678901234567890";
  char * c = NULL;
  char sum[] = "9876543223333333223222222211";
  char diff[] = "9876543198641975420753086431";
  char prod[] = "121932631137021795235939643223609205901126352690";
  char quot[] = "800000007";

  BigInt b1, b2, b3;

  printf("First number: %s\n", a);
  printf("Second number: %s\n", b);

  c = mpa_add(a, b);
  printf("Sum: %s\n", c);
  if (strcmp(c, sum) == 0) {
    printf("[INFO] Sum is correct\n");
  }
  free(c);

  c = mpa_subtract(a, b);
  printf("Difference: %s\n", c);
  if (strcmp(c, diff) == 0) {
    printf("[INFO] Difference is correct\n");
  }
  free(c);

  c = mpa_multiply(a, b);
  printf("Product: %s\n", c);
  if (strcmp(c, prod) == 0) {
    printf("[INFO] Product is correct\n");
  }
  free(c);

  c = mpa_divide(a, b);
  printf("Quotient: %s\n", c);
  if (strcmp(c, quot) == 0) {
    printf("[INFO] Quotient is correct\n");
  }
  free(c);

  BigInt_init_from_string(&b1, a);
  BigInt_init_from_string(&b2, b);
  BigInt_init(&b3);

  BigInt_add(&b3, &b1, &b2);
  c = BigInt_to_string(&b3);
  printf("%s\n", c);
  free(c);

  BigInt_destroy(&b1);

  BigInt_init_from_string_with_sign(&b1, "-1000");
  // BigInt_set_from_string_with_sign(&b1, "-100");

  c = BigInt_to_string_with_sign(&b1);
  printf("%s\n",c);
  free(c);

  BigInt_destroy(&b1);
  BigInt_destroy(&b2);
  BigInt_destroy(&b3);

  return 0;
}
