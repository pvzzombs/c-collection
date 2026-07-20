#define MPA_IMPL
#include "bigDecimal.h"

int main() {
  BigDec sum, a, b;
  char * s;
  
  BigDec_init(&sum);
  BigDec_init(&a);
  BigDec_init(&b);
  
  BigDec_set_from_string(&a, "8.88888");
  BigDec_set_from_string(&b, "9.99999");
  
  BigDec_multiply_prec(&sum, &a, &b, 9);
  
  s = BigDec_to_string(&sum);
  
  printf("%s\n", s);
  
  free(s);
  
  s = BigDec_to_string(&a);
  
  printf("%s\n", s);
  
  free(s);
  
  s = BigDec_to_string(&b);
  
  printf("%s\n", s);
  
  free(s);
  
  /* BigDec_sqrt(&sum, &a, 100);
  
  s = BigDec_to_string(&sum);
  
  printf("%s\n", s);
  
  free(s); */
  
  BigDec_destroy(&sum);
  BigDec_destroy(&a);
  BigDec_destroy(&b);
  return 0;
}
