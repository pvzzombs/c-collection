#include "bigInteger.h"

int main() {
  char test1[] = "9876543210987654321987654321";
  char test2[] = "12345678901234567890";
  BigInt a, b, c;
  char * s;
  BigInt_init_from_string(&a, test1);
  BigInt_init_from_string(&b, test2);
  BigInt_init(&c);
  BigInt_add(&a, &b, &c);
  // printf("Addend1: %s\n", BigInt_to_string(&a));
  // printf("Addend2: %s\n", BigInt_to_string(&b));
  s = BigInt_to_string(&c);
  printf("%s\n", s);
  free(s);
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
  return 0;
}