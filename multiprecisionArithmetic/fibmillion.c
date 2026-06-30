#include <stdio.h>

#define BIGINT_IMPL
#include "bigInteger.h"

#ifdef _WIN32
#include <windows.h>

double get_time() {
    static LARGE_INTEGER freq;
    static int initialized = 0;
    LARGE_INTEGER now;
    if (!initialized) {
        QueryPerformanceFrequency(&freq);
        initialized = 1;
    }
    QueryPerformanceCounter(&now);
    return (double)now.QuadPart / (double)freq.QuadPart;
}

#else
#include <time.h>

double get_time() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}
#endif

int main() {
  BigInt a, b, temp;
  int index = 0, link = 1;
  char * s = NULL;
  double start, end;

  BigInt_init_one(&a);
  BigInt_init_zero_limb(&b, 200000);
  BigInt_init_zero_limb(&temp, 200000);
  
  BigInt_set_from_int(&b, 1);

  start = get_time();
  while(index < 1000000) {
    BigInt_add(&temp, &a, &b);
    BigInt_copy(&a, &b);
    BigInt_copy(&b, &temp);
    index++;
  }
  end = get_time();
  
  printf("Time taken: %lfs\n", end - start);
  
  s = BigInt_to_string(&a);
  printf("Index is %d, digits are %s.\n", index, s);

  free(s);

  /* BigInt_print_internal(&a); */

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&temp);

  return 0;
}
