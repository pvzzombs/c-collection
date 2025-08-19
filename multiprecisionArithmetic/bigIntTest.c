#include "bigInteger.h"

int main() {
  BigInt a;
  char * s;
  BigInt_init_from_string(&a, "0");
  s = BigInt_to_string(&a);
  printf("%s\n", s);
  free(s);
  BigInt_destroy(&a);
  return 0;
}