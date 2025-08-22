#include "bigInteger.h"
#include "../acutest/acutest.h"

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
  int i;
  BigInt a, b, c;
  char * s;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  for (i = 0; i < 5; i++) {
    BigInt_set_from_string(&a, addends1[i]);
    BigInt_set_from_string(&b, addends2[i]);
    BigInt_add(&a, &b, &c);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(s, sums[i]) == 0);
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
  int i;
  BigInt a, b, c;
  char * s;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  for (i = 0; i < 5; i++) {
    BigInt_set_from_string(&a, minuend[i]);
    BigInt_set_from_string(&b, subtrahend[i]);
    BigInt_subtract(&a, &b, &c);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(s, difference[i]) == 0);
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
  int i;
  BigInt a, b, c;
  char * s;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  for (i = 0; i < 5; i++) {
    BigInt_set_from_string(&a, multiplicand[i]);
    BigInt_set_from_string(&b, multiplier[i]);
    BigInt_multiply(&a, &b, &c);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(s, product[i]) == 0);
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
  int i;
  BigInt a, b, c;
  char * s;
  BigInt_init(&a);
  BigInt_init(&b);
  BigInt_init(&c);

  for (i = 0; i < 5; i++) {
    BigInt_set_from_string(&a, dividend[i]);
    BigInt_set_from_string(&b, divisor[i]);
    BigInt_divide(&a, &b, &c);
    s = BigInt_to_string(&c);
    TEST_CHECK(strcmp(s, quotient[i]) == 0);
    free(s);
  }

  BigInt_destroy(&a);
  BigInt_destroy(&b);
  BigInt_destroy(&c);
}

TEST_LIST = {
  {"addition", additionTest},
  {"subtraction", subtractionTest},
  {"multiplication", multiplicationTest},
  {"division", divisionTest},
  {NULL, NULL}
};