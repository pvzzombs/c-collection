#include <stdio.h>

#define BIGINT_IMPL
#include "bigInteger.h"

int main() {
  BigInt a, b, c;

  BigInt_init_from_string(&a, "1024");
  BigInt_init_from_string(&b, "0");
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
