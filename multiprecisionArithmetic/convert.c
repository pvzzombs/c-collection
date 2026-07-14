#define BIGINT_IMPL
#include "bigInteger.h"

int main() {
  
  BigInt a, b;
  char * s;
  
  BigInt_init_from_int(&a, 123456789);
  BigInt_init_none(&b);
  
  BigInt_print_internal(&a);
  
  s = BigInt_to_base_string_unsigned(&a, 16);
  
  printf("%s\n", s);
  
  BigInt_set_from_base_string_unsigned(&b, s, 16);
  
  BigInt_print_internal(&b);
  
  if (BigInt_cmp_unsigned(&a, &b) == 0) {
    printf("Equal!!!!\n");
  } else {
    printf("No!!!\n");
  }
  free(s);
  
  BigInt_destroy(&b);
  BigInt_destroy(&a);
  
  return 0;
}
