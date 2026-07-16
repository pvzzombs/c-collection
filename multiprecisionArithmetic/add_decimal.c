#define MPA_IMPL
#include "bigDecimal.h"

int main() {
  BigDec sum, a, b;
  
  BigDec_init(&sum);
  BigDec_init_from_string(&a, "1234.5678");
  BigDec_init_from_string(&b, "123.4599");
  
  BigDec_add(&sum, &a, &b);
  
  BigDec_destroy(&sum);
  BigDec_destroy(&a);
  BigDec_destroy(&b);
  return 0;
}
