#include <stdio.h>

#define BIGINT_IMPL
/* #define BIGINT_USE_FAST_128BIT */
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
  FILE * f = fopen("fibmillion.bin", "w");

  BigInt_init_zero(&a);
  BigInt_init_zero(&b);
  BigInt_init_zero(&temp);
  
  BigInt_set_from_int(&a, 1);
  BigInt_set_from_int(&b, 1);

  start = get_time();
  while(index < 1000000) {
    BigInt_add(&temp, &a, &b);
    /* BigInt_swap(&a, &b);
    BigInt_swap(&b, &temp); */
    BigInt_copy(&a, &b);
    BigInt_copy(&b, &temp);
    index++;
  }
  end = get_time();
  
  printf("Time taken: %lfs\n", end - start);
  
  s = BigInt_to_string(&a);
  printf("Index is %d.\n", index);
  fprintf(f, "%s", s);
  free(s);

  /* BigInt_print_internal(&a); */

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&temp);
  
  fclose(f);

  return 0;
}
