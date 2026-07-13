#define BIGINT_IMPL

#include "bigInteger.h"

int main() {
  BigInt a, result;
  int exp = 4;
  
  BigInt_init_from_int(&a, -3);
  BigInt_init_none(&result);
  
  BigInt_power(&result, &a, exp);
  
  BigInt_print_internal(&result);
  
  BigInt_print(&result);
  
  printf("\n");
  
  BigInt_destroy(&a);
  BigInt_destroy(&result);
  return 0;
}
