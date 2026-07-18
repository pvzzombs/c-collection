#define MPA_IMPL
#include "bigDecimal.h"

int main() {
  BigDec a, b;
  char * s;
  
  BigDec_init_from_string(&a, "0.01");
  BigDec_init_from_string(&b, "0.01000");
  printf("Compare is %d\n", BigDec_cmp(&a, &b));
  
  BigDec_destroy(&b);
  BigDec_destroy(&a);
  
  return 0;
}
