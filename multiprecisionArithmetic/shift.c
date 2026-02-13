#include <stdio.h>

#define BIGINT_IMPL
#define BIGINT_USE_64_BIT
#include "bigInteger.h"

int main() {
  BigInt a;
  BigInt_init_from_string(&a, "100000000000000000001");

  BigInt_print_internal(&a);
  /* BigInt_shift_left(&a, 5);
  BigInt_print_internal(&a); */
  BigInt_shift_right(&a, 2); 
  BigInt_print_internal(&a);

  BigInt_destroy(&a);
  return 0;
}
