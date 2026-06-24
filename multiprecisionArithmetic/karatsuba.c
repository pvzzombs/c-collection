#include <stdio.h>

#define BIGINT_IMPL
#include "bigInteger.h"

int main() {
  BigInt a, b, schoolbook, karatsuba;

  BigInt_init_random_limb(&a, 86);
  BigInt_init_random_limb(&b, 86);
  BigInt_init(&schoolbook);
  BigInt_init(&karatsuba);
  printf("A is: ");
  BigInt_print_internal(&a);
  printf("B is: ");
  BigInt_print_internal(&b);

  BigInt_multiply(&schoolbook, &a, &b);
  BigInt_print_internal(&schoolbook);
  BigInt_multiply_karatsuba(&karatsuba, &a, &b);
  BigInt_print_internal(&karatsuba);
  
  if (BigInt_cmp(&schoolbook, &karatsuba) == 0) {
    printf("Equal!\n");
  } else {
    printf("Not equal!\n");
  }
  
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&schoolbook);
  BigInt_destroy(&karatsuba);
  return 0;
}
