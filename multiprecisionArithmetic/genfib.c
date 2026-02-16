#include <stdio.h>
#include <stdlib.h>

#define BIGINT_IMPL
#include "bigInteger.h"

int main() {
  /*
    int a = 1, b = 1, temp;
    temp = a + b;
    a = b;
    b = temp;
  */
  FILE * file;
  BigInt a, b, temp;
  int index = 1;
  char * s = NULL;

  file = fopen("fib.bin", "w");

  if (file != NULL) {
    BigInt_init_from_string(&a, "1");
    BigInt_init_from_string(&b, "1");
    BigInt_init(&temp);
    fprintf(file, "1\n");

    while(BigInt_count_digits_base_10(&a) < 1000) {
      BigInt_add(&temp, &a, &b);
      BigInt_copy(&a, &b);
      BigInt_copy(&b, &temp);
      index++;
      s = BigInt_to_string_2(&a);
      fprintf(file, s);
      fprintf(file, "\n");
      free(s);
    }

    BigInt_destroy(&a);
    BigInt_destroy(&b);
    BigInt_destroy(&temp);

    fclose(file);
  }
  return 0;
}
