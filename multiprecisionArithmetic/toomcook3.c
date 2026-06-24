#include <stdio.h>

#define BIGINT_IMPL
#include "bigInteger.h"

int main() {
  BigInt a, b, schoolbook, toomcook3;

  BigInt_init_random_limb(&a, 1024);
  BigInt_init_random_limb(&b, 512);
  BigInt_init(&schoolbook);
  BigInt_init(&toomcook3);
  printf("A is: ");
  BigInt_print_internal(&a);
  printf("B is: ");
  BigInt_print_internal(&b);

  BigInt_multiply(&schoolbook, &a, &b);
  BigInt_print_internal(&schoolbook);
  BigInt_multiply_toomcook3(&toomcook3, &a, &b);
  BigInt_print_internal(&toomcook3);
  
  if (BigInt_cmp(&schoolbook, &toomcook3) == 0) {
    printf("Equal!\n");
  } else {
    int len_schoolbook = schoolbook.internalSize;
    int len_toomcook3 = toomcook3.internalSize;
    int lenMin = len_schoolbook;
    int i;
    
    printf("Not equal!, sizes: %d %d\n", len_schoolbook, len_toomcook3);
    
    /* if (lenMin > len_toomcook3) {
      lenMin = len_toomcook3;
    }
    
    for (i = 0; i < lenMin; i++) {
      if(toomcook3.internalRepresentation[i] != schoolbook.internalRepresentation[i]) {
        printf("i is %d, schoolbook value is %d, toomcook3 is %d\n", i, schoolbook.internalRepresentation[i], toomcook3.internalRepresentation[i]);
      }
    } */
  }
  
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&schoolbook);
  BigInt_destroy(&toomcook3);
  return 0;
}
