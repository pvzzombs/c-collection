#include "multiprecisionArithmetic.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BIGINT_IMPL
#define BIGINT_USE_64_BIT
#include "bigInteger.h"
#include "../others/acutest.h"

#define DIGIT_COUNT 100

void generateBigInteger(char * dest) {
  int i;
  for(i = 0; i < DIGIT_COUNT; i++) {
    dest[i] = (rand() % 10) + '0';
  }
  dest[i] = 0;
}

void generateBigIntegerN(char * dest, int n) {
  int i;
  for(i = 0; i < n; i++) {
    dest[i] = (rand() % 10) + '0';
  }
  dest[i] = 0;
}

void additionTest() {
  char * addends1[] = {
    "12345678901234567890",
    "99999999999999999999",
    "12345",
    "314159265358979323846264338327950288419716939937510",
    "123456789"
  };

  char * addends2[] = {
    "98765432109876543210",
    "1",
    "987654321",
    "271828182845904523536028747135266249775724709369995",
    "0"
  };

  char * sums[] = {
    "111111111011111111100",
    "100000000000000000000",
    "987666666",
    "585987448204883847382293085463216538195441649307505",
    "123456789"
  };

  char * names[] = {
    "Simple addition",
    "Carry over in each digit",
    "Different lengths",
    "Very large numbers",
    "Adding zero"
  };

  int i;
  BigInt a, b, c;
  char * s;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  for (i = 0; i < 5; i++) {
    TEST_CASE_("Iteration #%d, %s", i, names[i]);
    BigInt_set_from_string(&a, addends1[i]);
    BigInt_set_from_string(&b, addends2[i]);
    BigInt_add(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(s, sums[i]) == 0);
    TEST_MSG("Expected: %s, Output: %s, Addend1: %s, Addend2: %s", sums[i], s, addends1[i], addends2[i]);
    free(s);
  }

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void subtractionTest() {
  char * minuend[] = {
    "98765432109876543210",
    "123456789123456789",
    "1000000000000000000",
    "314159265358979323846264338327950288419716939937510",
    "1000001000001"
  };

  char * subtrahend[] = {
    "12345678901234567890",
    "123456789123456789",
    "1",
    "271828182845904523536028747135266249775724709369995",
    "999999999999"
  };

  char * difference[] = {
    "86419753208641975320",
    "0",
    "999999999999999999",
    "42331082513074800310235591192684038643992230567515",
    "1000002"
  };

  char * names[] = {
    "Simple subtraction",
    "Result is zero",
    "Borrow across digits",
    "Very large numbers",
    "Subtraction leading to multiple borrows"
  };

  int i;
  BigInt a, b, c;
  char * s;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  for (i = 0; i < 5; i++) {
    TEST_CASE_("Iteration #%d, %s", i, names[i]);
    BigInt_set_from_string(&a, minuend[i]);
    BigInt_set_from_string(&b, subtrahend[i]);
    BigInt_subtract(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(s, difference[i]) == 0);
    TEST_MSG("Expected: %s, Output: %s, Minuend: %s, Subtrahend: %s", difference[i], s, minuend[i], subtrahend[i]);
    free(s);
  }

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void multiplicationTest() {
  char * multiplicand[] = {
    "123456789",
    "123456789",
    "987654321",
    "12345",
    "314159265358979323846264338327950288419716939937510"
  };

  char * multiplier[] = {
    "987654321",
    "0",
    "1",
    "987654321",
    "271828182845904523536028747135266249775724709369995"
  };

  char * product[] = {
    "121932631112635269",
    "0",
    "987654321",
    "12192592592745",
    "85397342226735670654635508695465744950348885357650690581833014653136349617576232159238592126769012450"
  };

  char * names[] = {
    "Simple multiplication",
    "Multiply by zero",
    "Multiply by one",
    "Different lengths",
    "Very large numbers"
  };

  int i;
  BigInt a, b, c;
  char * s;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  for (i = 0; i < 5; i++) {
    TEST_CASE_("Iteration #%d, %s", i, names[i]);
    BigInt_set_from_string(&a, multiplicand[i]);
    BigInt_set_from_string(&b, multiplier[i]);
    BigInt_multiply(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(s, product[i]) == 0);
    TEST_MSG("Expected: %s, Output: %s, Multiplicand: %s, Multiplier: %s", product[i], s, multiplicand[i], multiplier[i]);
    free(s);
  }

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void divisionTest() {
  char * dividend[] = {
    "121932631112635269",
    "100",
    "1000000000000",
    "314159265358979323846264338327950288419716939937510",
    "99999999999999999999"
  };

  char * divisor[] = {
    "123456789",
    "3",
    "1000000",
    "271828182845904523536028747135266249775724709369995",
    "1"
  };

  char * quotient[] = {
    "987654321",
    "33",
    "1000000",
    "1",
    "99999999999999999999"
  };

  char * names[] = {
    "Simple division",
    "Division with remainder",
    "Powers of 10",
    "Very large numbers",
    "Division by 1"
  };

  int i;
  BigInt a, b, c;
  char * s;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  for (i = 0; i < 5; i++) {
    TEST_CASE_("Iteration #%d, %s", i, names[i]);
    BigInt_set_from_string(&a, dividend[i]);
    BigInt_set_from_string(&b, divisor[i]);
    BigInt_divide_no_copy(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(s, quotient[i]) == 0);
    TEST_MSG("Expected: %s, Output: %s, Dividend: %s, Divisor: %s", quotient[i], s, dividend[i], divisor[i]);
    free(s);
  }

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void inputAndOutputTest() {
  char buf[1024];
  char * s;
  int i;
  BigInt a;
  srand(time(NULL));
  BigInt_init(&a);
  for (i = 0; i < 100; i++) {
    generateBigInteger(buf);
    mpa_removeLeadingZeroes(buf);
    BigInt_set_from_string(&a, buf);
    s = BigInt_to_string(&a);
    TEST_CHECK(strcmp(buf, s) == 0);
    TEST_MSG("Expected: %s, Output: %s", buf, s);
    free(s);
  }
  BigInt_destroy(&a);
}

void randomizedAdd() {
  char num1[1024];
  char num2[1024];
  char num3[1024];
  char * s;
  char * target;
  int i;
  BigInt a,b,c;
  srand(time(NULL));
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);
  for (i = 0; i < 100; i++) {
    generateBigInteger(num1);
    generateBigInteger(num2);
    mpa_removeLeadingZeroes(num1);
    mpa_removeLeadingZeroes(num2);
    target = mpa_add(num1, num2);
    BigInt_set_from_string(&a, num1);
    BigInt_set_from_string(&b, num2);
    BigInt_add(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(target, s) == 0);
    TEST_MSG("Expected: %s, Output: %s, Numbers: %s + %s", target, s, num1, num2);
    free(target);
    free(s);
  }
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void randomizedSubtract() {
  char num1[1024];
  char num2[1024];
  char num3[1024];
  char * s;
  char * target;
  int i;
  BigInt a,b,c;
  srand(time(NULL));
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);
  for (i = 0; i < 100; i++) {
    generateBigInteger(num1);
    generateBigInteger(num2);
    mpa_removeLeadingZeroes(num1);
    mpa_removeLeadingZeroes(num2);
    if (mpa_bigIntCmp(num1, num2) < 0) {
      continue;
    }
    target = mpa_subtract(num1, num2);
    BigInt_set_from_string(&a, num1);
    BigInt_set_from_string(&b, num2);
    BigInt_subtract(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(target, s) == 0);
    TEST_MSG("Expected: %s, Output: %s, Numbers: %s - %s", target, s, num1, num2);
    free(target);
    free(s);
  }
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void randomizedMultiply() {
  char num1[1024];
  char num2[1024];
  char num3[1024];
  char * s;
  char * target;
  int i;
  BigInt a,b,c;
  srand(time(NULL));
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);
  for (i = 0; i < 100; i++) {
    generateBigInteger(num1);
    generateBigInteger(num2);
    mpa_removeLeadingZeroes(num1);
    mpa_removeLeadingZeroes(num2);
    target = mpa_multiply(num1, num2);
    BigInt_set_from_string(&a, num1);
    BigInt_set_from_string(&b, num2);
    BigInt_multiply(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(target, s) == 0);
    TEST_MSG("Expected: %s, Output: %s, Numbers: %s * %s", target, s, num1, num2);
    free(target);
    free(s);
  }
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void randomizedMultiplyKaratsuba() {
  char num1[1024];
  char num2[1024];
  char num3[1024];
  char * s;
  char * target;
  int i;
  BigInt a,b,c;
  srand(time(NULL));
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);
  for (i = 0; i < 100; i++) {
    generateBigInteger(num1);
    generateBigInteger(num2);
    mpa_removeLeadingZeroes(num1);
    mpa_removeLeadingZeroes(num2);
    target = mpa_multiply(num1, num2);
    BigInt_set_from_string(&a, num1);
    BigInt_set_from_string(&b, num2);
    BigInt_multiply_karatsuba(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(target, s) == 0);
    TEST_MSG("Expected: %s, Output: %s, Numbers: %s * %s", target, s, num1, num2);
    free(target);
    free(s);
  }
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void randomizedDivide() {
  char num1[1024];
  char num2[1024];
  char num3[1024];
  char * s;
  char * target;
  int i;
  BigInt a,b,c;
  srand(time(NULL));
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);
  for (i = 0; i < 100; i++) {
    generateBigInteger(num1);
    generateBigInteger(num2);
    mpa_removeLeadingZeroes(num1);
    mpa_removeLeadingZeroes(num2);
    if (mpa_bigIntCmp(num1, num2) < 0) {
      continue;
    }
    target = mpa_divide(num1, num2);
    BigInt_set_from_string(&a, num1);
    BigInt_set_from_string(&b, num2);
    BigInt_divide(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(target, s) == 0);
    TEST_MSG("Len is %d %d", strlen(target), strlen(s));
    TEST_MSG("Expected: %s, Output: %s, Numbers: %s / %s", target, s, num1, num2);
    free(target);
    free(s);
  }
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

void randomizedDivide100by50() {
  char num1[1024];
  char num2[1024];
  char num3[1024];
  char * s;
  char * target;
  int i;
  BigInt a,b,c;
  srand(time(NULL));
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);
  for (i = 0; i < 100; i++) {
    generateBigIntegerN(num1, 100);
    generateBigIntegerN(num2, 50);
    mpa_removeLeadingZeroes(num1);
    mpa_removeLeadingZeroes(num2);
    if (mpa_bigIntCmp(num1, num2) < 0) {
      continue;
    }
    target = mpa_divide(num1, num2);
    BigInt_set_from_string(&a, num1);
    BigInt_set_from_string(&b, num2);
    BigInt_divide(&c, &a, &b);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(target, s) == 0);
    TEST_MSG("Len is %d %d", strlen(target), strlen(s));
    TEST_MSG("Expected: %s, Output: %s, Numbers: %s / %s", target, s, num1, num2);
    free(target);
    free(s);
  }
  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

/*void inputAndOutputTest2() {
  char buf[1024];
  char * s;
  int i;
  BigInt a;
  srand(time(NULL));
  BigInt_init(&a);
  for (i = 0; i < 100; i++) {
    generateBigInteger(buf);
    mpa_removeLeadingZeroes(buf);
    BigInt_set_from_string_2(&a, buf);
    s = BigInt_to_string_2(&a);
    TEST_CHECK(strcmp(buf, s) == 0);
    TEST_MSG("Expected: %s, Output: %s", buf, s);
    free(s);
  }
  BigInt_destroy(&a);
}*/

void specificDigitCountTest() {
  char num1[] = "1070066266382758936764980584457396885083683896632151665013235203375314520604694040621889147582489792657804694888177591957484336466672569959512996030461262748092482186144069433051234774442750273781753087579391666192149259186759553966422837148943113074699503439547001985432609723067290192870526447243726117715821825548491120525013201478612965931381792235559657452039506137551467837543229119602129934048260706175397706847068202895486902666185435124521900369480641357447470911707619766945691070098024393439617474103736912503231365532164773697023167755051595173518460579954919410967778373229665796581646513903488154256310184224190259846088000110186255550245493937113651657039447629584714548523425950428582425306083544435428212611008992863795048006894330309773217834864543113205765659868456288616808718693835297350643986297640660000723562917905207051164077614812491885830945940566688339109350944456576357666151619317753792891661581327159616877487983821820492520348473874384736771934512787029218636250627816";
  int count = strlen(num1);
  int guess;

  BigInt a;

  BigInt_init(&a);

  BigInt_set_from_string(&a, num1);
  
  guess = BigInt_count_digits_base_10(&a);
  TEST_CHECK(count == guess);
  TEST_MSG("Expected: %d, Output: %d", count, guess);

  BigInt_destroy(&a);
}

void digitCountTest() {
  char buf[10001];
  char * s;
  int i;
  int count, guess;
  BigInt a;
  srand(time(NULL));
  BigInt_init(&a);
  for (i = 0; i < 100; i++) {
    count = rand() % 10000;
    generateBigIntegerN(buf, count);
    mpa_removeLeadingZeroes(buf);
    count = strlen(buf);
    BigInt_set_from_string(&a, buf);
    guess = BigInt_count_digits_base_10(&a);
    s = BigInt_to_string(&a);
    TEST_CHECK(count == guess);
    TEST_MSG("Expected: %d, Output: %d, Number: %s", count, guess, s);
    free(s);
  }
  BigInt_destroy(&a);
}

/*void digitCountTest2() {
  char buf[10001];
  char * s;
  int i;
  int count, guess;
  BigInt a;
  srand(time(NULL));
  BigInt_init(&a);
  for (i = 0; i < 100; i++) {
    count = rand() % 10000;
    generateBigIntegerN(buf, count);
    mpa_removeLeadingZeroes(buf);
    count = strlen(buf);
    BigInt_set_from_string_2(&a, buf);
    guess = BigInt_count_digits_base_10_2(&a);
    s = BigInt_to_string_2(&a);
    TEST_CHECK(count == guess);
    TEST_MSG("Expected: %d, Output: %d, Number: %s", count, guess, s);
    free(s);
  }
  BigInt_destroy(&a);
}*/

TEST_LIST = {
  {"addition", additionTest},
  {"subtraction", subtractionTest},
  {"multiplication", multiplicationTest},
  {"division", divisionTest},
  {"randomized input and output test", inputAndOutputTest},
  {"randomized positive addition test", randomizedAdd},
  {"randomized positive subtraction test", randomizedSubtract},
  {"randomized positive multiplication test", randomizedMultiply},
  {"randomized positive multiplication karatsuba test", randomizedMultiplyKaratsuba},
  {"randomized positive division test", randomizedDivide},
  {"randomized positive division test max(100) digits by max(50) digits", randomizedDivide100by50},
  /*{"randomized fast input and output test", inputAndOutputTest2},*/
  {"specific digit count test", specificDigitCountTest},
  {"randomized digit count test", digitCountTest},
  /*{"randomized digit count test 2", digitCountTest2},*/
  {NULL, NULL}
};
