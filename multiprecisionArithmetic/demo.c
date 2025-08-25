#include <stdio.h>
#include "bigInteger.h"

int main() {
  char num1[1024];
  char num2[1024];
  char * s;

  BigInt a, b, c;
  int index;
  char * end;

  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  printf("Enter first number: ");
  fgets(num1, 1024, stdin);
  printf("Enter second number: ");
  fgets(num2, 1024, stdin);

  end = strstr(num1, "\n");
  num1[end - num1] = 0;
  end = strstr(num2, "\n");
  num2[end - num2] = 0;

  BigInt_set_from_string(&a, num1);
  BigInt_set_from_string(&b, num2);

  BigInt_add(&c, &a, &b);
  s = BigInt_to_string(&c);
  printf("Sum: %s\n",s);
  free(s);
  BigInt_subtract(&c, &a, &b);
  s = BigInt_to_string(&c);
  printf("Difference: %s\n",s);
  free(s);
  BigInt_multiply(&c, &a, &b);
  s = BigInt_to_string(&c);
  printf("Product: %s\n",s);
  free(s);
  BigInt_divide(&c, &a, &b);
  s = BigInt_to_string(&c);
  printf("Quotient: %s\n",s);
  free(s);

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
  return 0;
}