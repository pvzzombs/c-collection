#define MPA_IMPL
#include "bigDecimal.h"

int main() {
  BigDec sum, a, b;
  char * s;
  
  BigDec_init(&sum);
  BigDec_init(&a);
  BigDec_init(&b);
  
  BigDec_set_from_string(&a, "99");
  BigDec_set_from_string(&b, "1234.44445");
  
  BigDec_power_int(&sum, &a, 10, 5);
  
  s = BigDec_to_string(&sum);
  
  printf("%s\n", s);
  
  free(s);
  
  s = BigDec_to_string(&a);
  
  printf("%s\n", s);
  
  free(s);
  
  BigDec_truncate(&b, &b);
  
  s = BigDec_to_string(&b);
  
  printf("Truncate: %s\n", s);
  
  free(s);
  
  BigDec_e_taylor(&sum, &a, 1000);
  
  s = BigDec_to_string(&sum);
  
  printf("%s\n", s);
  
  free(s);
  
  BigDec_e(&sum, &a, 100);
  
  s = BigDec_to_string(&sum);
  
  printf("E is %s\n", s);
  
  free(s);
  
  BigDec_ln_atanh(&sum, &a, 1000);
  
  s = BigDec_to_string(&sum);
  
  printf("ln is %s\n", s);
  
  free(s);
  
  BigDec_destroy(&sum);
  BigDec_destroy(&a);
  BigDec_destroy(&b);
  return 0;
}
