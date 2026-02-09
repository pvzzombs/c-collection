#include <stdio.h>

#define BIGINT_IMPL
#define BIGINT_USE_64_BIT
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
  char buf[1024];
  int hasMismatch = 0;

  file = fopen("fib.bin", "r");

  if (file != NULL) {
    BigInt_init_from_string(&a, "1");
    BigInt_init_from_string(&b, "1");
    BigInt_init(&temp);
    fgets(buf, 1024, file);
    if (strstr(buf, "\n") != NULL) {
      buf[strstr(buf, "\n") - buf] = 0;
    }
    if (strcmp(buf, "1") != 0) {
      hasMismatch = 1;
      printf("Mismatch!\n");
    }

    while(BigInt_count_digits_base_10(&a) < 1000) {
      BigInt_add(&temp, &a, &b);
      BigInt_copy(&a, &b);
      BigInt_copy(&b, &temp);
      index++;
      s = BigInt_to_string(&a);
      fgets(buf, 1024, file);
      if (strstr(buf, "\n") != NULL) {
        buf[strstr(buf, "\n") - buf] = 0;
      }
      if (strcmp(buf, s) != 0) {
        hasMismatch = 1;
        printf("Mismatch! Expected %s, got %s\n", buf, s);
      }
      free(s);
    }

    BigInt_destroy(&a);
    BigInt_destroy(&b);
    BigInt_destroy(&temp);

    fclose(file);
  }

  if (hasMismatch) {
    printf("Mismatch occured!\n");
  } else {
    printf("All good!\n");
  }
  return 0;
}
