#define BIGINT_IMPL

#include "bigInteger.h"

int main() {
  BigInt a, b, q, r;
  BigInt_init_from_string(&a, "123451234512345123451234512345");
  BigInt_init_from_int(&b, 10000);
  BigInt_init(&q);
  BigInt_init(&r);
  
  BigInt_divmod(&q, &r, &a, &b);
  
  BigInt_print(&q);
  printf("\n");
  BigInt_print(&r);
  printf("\n");
  
  return 0;
}
