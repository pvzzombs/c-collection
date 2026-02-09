#include <stdio.h>
#define BIGINT_IMPL
#define BIGINT_USE_64_BIT
#include "bigInteger.h"

int main() {
  BigInt a;
  BigInt_init_from_string(&a, "1234");

  printf("Digit count is %d.\n", BigInt_count_digits_base_10(&a));

  BigInt_destroy(&a);
  return 0;
}
