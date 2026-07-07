#define BIGINT_IMPL
/*#define BIGINT_USE_64_BIT*/
#include "bigInteger.h"

int main() {
  BigInt fact, i, one, end;
  char * s = NULL;
  BigInt_init_one(&fact);
  BigInt_init_one(&i);
  BigInt_init_one(&one);
  BigInt_init_from_string_unsigned(&end, "10000");

  while(BigInt_cmp_unsigned(&i, &end) <= 0) {
    BigInt_multiply_assign_u(&fact, &i); /* fact = fact * i; */
    BigInt_add_assign_u(&i, &one); /* i = i + 1; */
  }

  s = BigInt_to_string_unsigned(&fact);
  printf("Factorial is %s.\n", s);
  free(s);
  /* BigInt_print_internal(&fact); */

  BigInt_destroy(&fact);
  BigInt_destroy(&i);
  BigInt_destroy(&one);
  BigInt_destroy(&end);
  return 0;
}
