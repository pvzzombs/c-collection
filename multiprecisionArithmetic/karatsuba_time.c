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
  float start_time, end_time;
  float schoolbook = 0, karatsuba = 0;
  BigInt a, b, c;

  BigInt_init_random_limb(&a, 131072);
  BigInt_init_random_limb(&b, 131072);
  BigInt_init_zero_limb(&c, 131072 + 131072);

  start_time = get_time();
  BigInt_multiply(&c, &a, &b);
  end_time = get_time();
  schoolbook = end_time - start_time;
  
  BigInt_destroy(&c);
  BigInt_init_zero_limb(&c, 131072 + 131072);
  
  start_time = get_time();
  BigInt_multiply_karatsuba(&c, &a, &b);
  end_time = get_time();
  karatsuba = end_time - start_time;
  
  printf("School book multiplication: %f\n", schoolbook);
  printf("Karatsuba multiplication: %f\n", karatsuba);
  
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
  return 0;
}
