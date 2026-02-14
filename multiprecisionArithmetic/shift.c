#include <stdio.h>

#define BIGINT_IMPL
#define BIGINT_USE_64_BIT
#include "bigInteger.h"

int main() {
  BigInt a, b;
  BigInt_init_from_string(&a, "123456789012345678901234567890");
  BigInt_init(&b);

  BigInt_print_internal(&a);
  /* BigInt_shift_left(&a, 5);
  BigInt_print_internal(&a); */
  /* BigInt_shift_right(&a, 2); */
  BigInt_add_leading_zeroes(&a, 10);
  BigInt_print_internal(&a);
  BigInt_set_from_view(&b, &a, 2, 3);
  BigInt_print_internal(&b);

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  return 0;
}
