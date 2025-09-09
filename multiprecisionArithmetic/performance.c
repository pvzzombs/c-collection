#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigInteger.h"

#define ITERATIONS_COUNT 10
#define DIGIT_COUNT 100

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

void generateBigInteger(char * dest) {
  int i;
  for(i = 0; i < DIGIT_COUNT; i++) {
    dest[i] = (rand() % 10) + '0';
  }
}

int main() {
  char * bigNum1 = malloc((DIGIT_COUNT + 1) * sizeof(char));
  char * bigNum2 = malloc((DIGIT_COUNT + 1) * sizeof(char));
  char * s;
  int i;
  float startTime, endTime;
  float totalTime = 0, average;
  int iterations = 0, totalIteratons = 0;
  BigInt a, b, c;
  
  srand(time(NULL));
  bigNum1[DIGIT_COUNT] = 0;
  bigNum2[DIGIT_COUNT] = 0;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  /* generateBigInteger(bigNum1);
  generateBigInteger(bigNum2);
  printf("Num1: %s\n", bigNum1);
  printf("Num2: %s\n", bigNum2); */

  printf("Maximum digits: %d\n", DIGIT_COUNT);

  printf("Addition performance test...\n");

  for (i = 0; i < ITERATIONS_COUNT; i++) {
    iterations = 0;
    generateBigInteger(bigNum1);
    generateBigInteger(bigNum2);
    mpa_removeLeadingZeroes(bigNum1);
    mpa_removeLeadingZeroes(bigNum2);
    BigInt_set_from_string(&a, bigNum1);
    BigInt_set_from_string(&b, bigNum2);
    BigInt_set_from_string(&c, "0");
    printf("Processing number/s done...\n");
    startTime = get_time();
    endTime = startTime;
    do {
      BigInt_add(&c, &a, &b);
      ++iterations;
      endTime = get_time();
    } while(endTime - startTime < 1.0);
    totalIteratons += iterations;
    printf("Iterations executed: %d\n", iterations);
  }

  printf("Average: %d per second.\n", totalIteratons / ITERATIONS_COUNT);

  totalIteratons = 0;
  printf("Multiplication performance test...\n");

  for (i = 0; i < ITERATIONS_COUNT; i++) {
    iterations = 0;
    generateBigInteger(bigNum1);
    generateBigInteger(bigNum2);
    mpa_removeLeadingZeroes(bigNum1);
    mpa_removeLeadingZeroes(bigNum2);
    BigInt_set_from_string(&a, bigNum1);
    BigInt_set_from_string(&b, bigNum2);
    BigInt_set_from_string(&c, "0");
    printf("Processing number/s done...\n");
    startTime = get_time();
    endTime = startTime;
    do {
      BigInt_multiply(&c, &a, &b);
      ++iterations;
      endTime = get_time();
    } while(endTime - startTime < 1.0);
    totalIteratons += iterations;
    printf("Iterations executed: %d\n", iterations);
  }

  printf("Average: %d per second.\n", totalIteratons / ITERATIONS_COUNT);

  totalIteratons = 0;
  printf("Subtraction performance test...\n");

  for (i = 0; i < ITERATIONS_COUNT; i++) {
    iterations = 0;
    generateBigInteger(bigNum1);
    generateBigInteger(bigNum2);
    mpa_removeLeadingZeroes(bigNum1);
    mpa_removeLeadingZeroes(bigNum2);
    BigInt_set_from_string(&a, bigNum1);
    BigInt_set_from_string(&b, bigNum2);
    if (BigInt_cmp(&a, &b) < 0) {
      BigInt_swap(&a, &b);
    }
    BigInt_set_from_string(&c, "0");
    printf("Processing number/s done...\n");
    startTime = get_time();
    endTime = startTime;
    do {
      BigInt_subtract(&c, &a, &b);
      ++iterations;
      endTime = get_time();
    } while(endTime - startTime < 1.0);
    totalIteratons += iterations;
    printf("Iterations executed: %d\n", iterations);
  }

  printf("Average: %d per second.\n", totalIteratons / ITERATIONS_COUNT);

  totalIteratons = 0;
  printf("Division performance test...\n");

  for (i = 0; i < ITERATIONS_COUNT; i++) {
    iterations = 0;
    generateBigInteger(bigNum1);
    generateBigInteger(bigNum2);
    mpa_removeLeadingZeroes(bigNum1);
    mpa_removeLeadingZeroes(bigNum2);
    BigInt_set_from_string(&a, bigNum1);
    BigInt_set_from_string(&b, bigNum2);
    if (BigInt_cmp(&a, &b) < 0) {
      BigInt_swap(&a, &b);
    }
    BigInt_set_from_string(&c, "0");
    printf("Processing number/s done...\n");
    startTime = get_time();
    endTime = startTime;
    do {
      BigInt_divide(&c, &a, &b);
      ++iterations;
      endTime = get_time();
    } while(endTime - startTime < 1.0);
    totalIteratons += iterations;
    printf("Iterations executed: %d\n", iterations);
  }

  printf("Average: %d per second.\n", totalIteratons / ITERATIONS_COUNT);

  free(bigNum1);
  free(bigNum2);

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
  return 0;
}