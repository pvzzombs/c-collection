#define BIGINT_IMPL
#include "bigInteger.h"
#include <stdio.h>

int main() {
  BigInt a, b;
  BigInt_init(&a);
  BigInt_init(&b);

  BigInt_set_from_string(&a, "123");
  BigInt_set_from_string(&b, "123");

  printf("%d\n", BigInt_cmp(&a, &b));

  BigInt_set_from_string(&a, "12345");
  BigInt_set_from_string(&b, "123");

  printf("%d\n", BigInt_cmp(&a, &b));

  BigInt_set_from_string(&a, "123");
  BigInt_set_from_string(&b, "12345");

  printf("%d\n", BigInt_cmp(&a, &b));

  BigInt_set_from_string_with_sign(&a, "123");
  BigInt_set_from_string_with_sign(&b, "123");

  printf("%d\n", BigInt_cmp_with_sign(&a, &b));

  BigInt_set_from_string_with_sign(&a, "12345");
  BigInt_set_from_string_with_sign(&b, "123");

  printf("%d\n", BigInt_cmp_with_sign(&a, &b));

  BigInt_set_from_string_with_sign(&a, "123");
  BigInt_set_from_string_with_sign(&b, "12345");

  printf("%d\n", BigInt_cmp_with_sign(&a, &b));

  BigInt_set_from_string_with_sign(&a, "-123");
  BigInt_set_from_string_with_sign(&b, "-123");

  printf("%d\n", BigInt_cmp_with_sign(&a, &b));

  BigInt_set_from_string_with_sign(&a, "-12345");
  BigInt_set_from_string_with_sign(&b, "123");

  printf("%d\n", BigInt_cmp_with_sign(&a, &b));

  BigInt_set_from_string_with_sign(&a, "123");
  BigInt_set_from_string_with_sign(&b, "-12345");

  printf("%d\n", BigInt_cmp_with_sign(&a, &b));

  BigInt_set_from_string_with_sign(&a, "-123");
  BigInt_set_from_string_with_sign(&b, "-12345");

  printf("%d\n", BigInt_cmp_with_sign(&a, &b));

  BigInt_set_from_string_with_sign(&a, "-12345");
  BigInt_set_from_string_with_sign(&b, "-12340");

  printf("%d\n", BigInt_cmp_with_sign(&a, &b));

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  return 0;
}
