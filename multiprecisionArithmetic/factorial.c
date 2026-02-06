#define BIGINT_IMPL
#include "bigInteger.h"

int main() {
  BigInt fact, i, one, end;
  char * s = NULL;
  BigInt_init_from_string(&fact, "1");
  BigInt_init_from_string(&i, "1");
  BigInt_init_from_string(&one, "1");
  BigInt_init_from_string(&end, "10000");

  while(BigInt_cmp(&i, &end) <= 0) {
    BigInt_multiply_t(&fact, &fact, &i); /* fact = fact * i; */
    BigInt_add_t(&i, &i, &one); /* i = i + 1; */
  }

  s = BigInt_to_string(&fact);
  printf("Factorial is %s.\n", s);
  free(s);

  BigInt_destroy(&fact);
  BigInt_destroy(&i);
  BigInt_destroy(&one);
  BigInt_destroy(&end);
  return 0;
}
