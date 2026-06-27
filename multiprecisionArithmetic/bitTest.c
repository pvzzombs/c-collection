#define BIGINT_IMPL

#include "bigInteger.h"

int main() {
  BigInt a, b, two, product, ShiftLeftByTwo;
  int i;
  char * s;
  
  BigInt_init_from_string(&a, "123456789012345678901234567890");
  BigInt_init_none(&product);
  BigInt_init_two(&two);
  BigInt_init_from_string(&b, "1");
  BigInt_init_none(&ShiftLeftByTwo);
  
  for (i = 0; i < 100; i++) {
    BigInt_multiply_t(&b, &b, &two);
    BigInt_divide(&product, &a, &b);
    s = BigInt_to_string(&b);
    printf("divider: %s %d\n", s, i + 1);
    free(s);
    BigInt_print_internal(&product);
    BigInt_set_from_string(&ShiftLeftByTwo, "123456789012345678901234567890");
    BigInt_shift_right_bit(&ShiftLeftByTwo, i + 1);
    BigInt_print_internal(&ShiftLeftByTwo);
    
    if (BigInt_cmp(&product, &ShiftLeftByTwo) != 0) {
      printf("Mismatch!\n");
      break;
    }
  }
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&two);
  BigInt_destroy(&product);
  BigInt_destroy(&ShiftLeftByTwo);
  
  return 0;
}
