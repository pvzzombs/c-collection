#define MPA_IMPL
#include "bigDecimal.h"

int main() {
  BigDec a;
  
  BigDec_init_from_string(&a, "123.45.67");
  BigDec_destroy(&a);
  
  return 0;
}
