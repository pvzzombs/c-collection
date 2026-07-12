#define BIGINT_IMPL

#include "bigInteger.h"

int main() {
  BigInt a, result;
  int exp = 10;
  
  BigInt_init_from_int(&a, BIGINT_BASE_MAX_INT);
  BigInt_init_none(&result);
  
  BigInt_power(&result, &a, exp);
  
  BigInt_print_internal(&result);
  
  BigInt_print_u(&result);
  
  printf("\n");
  
  BigInt_destroy(&a);
  BigInt_destroy(&result);
  return 0;
}
