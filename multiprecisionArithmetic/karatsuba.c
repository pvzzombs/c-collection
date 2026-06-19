#include <stdio.h>

#define BIGINT_IMPL
#include "bigInteger.h"

int main() {
  BigInt a, b, c;

  BigInt_init_random_limb(&a, 512);
  BigInt_init_random_limb(&b, 512);
  BigInt_init(&c);

  BigInt_multiply(&c, &a, &b);
  BigInt_print_internal(&c);
  BigInt_multiply_karatsuba(&c, &a, &b);
  BigInt_print_internal(&c);
  
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
  return 0;
}
