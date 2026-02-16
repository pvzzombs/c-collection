#include <stdio.h>

#define BIGINT_IMPL
#define BIGINT_USE_64_BIT
#include "bigInteger.h"

int main() {
  /*
    int a = 1, b = 1, temp;
    temp = a + b;
    a = b;
    b = temp;
  */
  BigInt a, b, temp;
  int index = 1;
  char * s = NULL;

  BigInt_init_from_string_2(&a, "1");
  BigInt_init_from_string_2(&b, "1");
  BigInt_init(&temp);

  while(BigInt_count_digits_base_10_2(&a) < 1000) {
    BigInt_add(&temp, &a, &b);
    BigInt_copy(&a, &b);
    BigInt_copy(&b, &temp);
    index++;
    /*s = BigInt_to_string_2(&a);
    printf("Index is %d, digits are %s.\n", index, s);
    free(s);*/
  }
  
  s = BigInt_to_string_2(&a);
  printf("Index is %d, digits are %s.\n", index, s);

  free(s);

  /* BigInt_print_internal(&a); */

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&temp);

  return 0;
}
