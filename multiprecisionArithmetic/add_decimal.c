#define BIGDEC_IMPL
#define BIGINT_IMPL
#include "bigDecimal.h"

int main() {
  BigDec sum, a, b;
  
  BigDec_init(&sum);
  BigDec_init(&a);
  BigDec_init(&b);
  
  BigDec_add(&sum, &a, &b);
  
  BigDec_destroy(&sum);
  BigDec_destroy(&a);
  BigDec_destroy(&b);
  return 0;
}
