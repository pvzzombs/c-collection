#define BIGINT_IMPL
#define BIGINT_USE_64_BIT
#include "bigInteger.h"

int main() {
  BigInt num1, num2;
  BigInt_init(&num1);
  BigInt_init(&num2);
  char * s;


  BigInt_set_from_string_with_sign(&num1, "-123456");
  s = BigInt_to_string_with_sign(&num1);
  printf("Num1 is %s\n", s);
  free(s);

  //BigInt_copy(&num2, &num1);
  BigInt_set_from_string_2_with_sign(&num2, "-123456789801234567890");
  s = BigInt_to_string_with_sign(&num2);
  //printf("Sign is %d\n", num2.sign);
  printf("Num2 is %s\n", s);
  free(s);

  //BigInt_copy(&num2, &num1);
  BigInt_set_from_string_2(&num2, "1234567890123456789012345678901234567890123456789012345678901234567890");
  s = BigInt_to_string(&num2);
  //printf("Sign is %d\n", num2.sign);
  printf("Num2 is %s\n", s);
  free(s);
  s = BigInt_to_string_with_small_base(&num2);
  printf("Num2 is %s\n", s);
  free(s);

  s = BigInt_to_string_2(&num2);
  printf("Num2 is %s\n", s);
  free(s);

  BigInt_destroy(&num1);

  BigInt_init_from_string_with_sign(&num1, "-123");
  s = BigInt_to_string_with_sign(&num1);
  printf("Number init is %s\n", s);
  free(s);
  
  BigInt_destroy(&num1);
  BigInt_destroy(&num2);

  return 0;
}
