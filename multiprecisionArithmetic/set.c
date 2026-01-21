#include "multiprecisionArithmetic.h"
#include "bigInteger.h"

int main() {
  BigInt num1, num2;
  BigInt_init(&num1);
  BigInt_init(&num2);
  char * s;


  BigInt_set_from_string_with_small(&num1, "123456");
  s = BigInt_to_string(&num1);
  printf("Num1 is %s\n", s);
  free(s);

  //BigInt_copy(&num2, &num1);
  BigInt_set_from_string_with_small_base_10000(&num2, "123456789801234567890");
  s = BigInt_to_string(&num2);
  printf("Num2 is %s\n", s);
  free(s);
  
  BigInt_destroy(&num1);
  BigInt_destroy(&num2);

  return 0;
}
