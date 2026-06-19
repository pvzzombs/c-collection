#include <stdio.h>
#include <stdlib.h>

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
  int iterations_a, iterations_b, i;
  BigInt a, b, c;
  int limb_sizes[] = {8, 16, 32, 64, 128, 256, 512, 1024};
  int limb_sizes_count = 8;
  
  FILE * f = fopen("limbs.csv", "w");
  
  fprintf(f, "limb_size,schoolbook,karatsuba\n");
  
  for (i = 0; i < limb_sizes_count; i++) {
    BigInt_init_random_limb(&a, limb_sizes[i]);
    BigInt_init_random_limb(&b, limb_sizes[i]);
    BigInt_init(&c);

    start_time = get_time();
    iterations_a = 0;
    do {
      BigInt_multiply(&c, &a, &b);
      end_time = get_time();
      ++iterations_a;
    } while (end_time - start_time < 1.0f);
    
    start_time = get_time();
    iterations_b = 0;
    do {
      BigInt_multiply_karatsuba(&c, &a, &b);
      end_time = get_time();
      ++iterations_b;
    } while (end_time - start_time < 1.0f);
    
    printf("Limb size: %d\n", limb_sizes[i]);
    printf("School book multiplication: %d\n", iterations_a);
    printf("Karatsuba multiplication: %d\n", iterations_b);
    
    fprintf(f, "%d,%d,%d\n", limb_sizes[i], iterations_a, iterations_b);
    
    BigInt_destroy(&a);
    BigInt_destroy(&b);
    BigInt_destroy(&c);
  }
  
  fclose(f);
  
  return 0;
}
