#include "../others/acutest.h"

#define MPA_IMPL

#include "bigDecimal.h"

void additionTest() {
  char * num1[] = {
    "123.45",
    "999.999",
    "-25.75",
    "-123.456",
    "0.000001"
  };

  char * num2[] = {
    "67.89",
    "0.001",
    "10.50",
    "-876.544",
    "999999.999999"
  };

  char * result[] = {
    "191.34",
    "1000.000",
    "-15.25",
    "-1000.000",
    "1000000.000000"
  };

  int i;
  BigDec a, b, c, r;
  char * s1;

  for (i = 0; i < 5; i++) {
    
    BigDec_init_from_string(&a, num1[i]);
    BigDec_init_from_string(&b, num2[i]);
    BigDec_init_from_string(&c, result[i]);
    BigDec_init(&r);
    
    BigDec_add(&r, &a, &b);
    
    s1 = BigDec_to_string(&r);

    TEST_CHECK(BigDec_cmp(&r, &c) == 0);
    TEST_MSG("Result: %s, Expected: %s, %s, %s", s1, result[i], num1[i],  num2[i]);
    
    free(s1);
    
    BigDec_destroy(&r);
    BigDec_destroy(&a);
    BigDec_destroy(&b);
    BigDec_destroy(&c);
  }
}

void subtractionTest() {
  char * num1[] = {
    "123.45",
    "1000.000",
    "-10.25",
    "5.75",
    "0.000001"
  };

  char * num2[] = {
    "23.45",
    "0.001",
    "5.75",
    "-10.25",
    "0.000002"
  };

  char * result[] = {
    "100.00",
    "999.999",
    "-16.00",
    "16.00",
    "-0.000001"
  };

  int i;
  BigDec a, b, c, r;
  char * s1;

  for (i = 0; i < 5; i++) {
    
    BigDec_init_from_string(&a, num1[i]);
    BigDec_init_from_string(&b, num2[i]);
    BigDec_init_from_string(&c, result[i]);
    BigDec_init(&r);
    
    BigDec_subtract(&r, &a, &b);
    
    s1 = BigDec_to_string(&r);

    TEST_CHECK(BigDec_cmp(&r, &c) == 0);
    TEST_MSG("Result: %s, Expected: %s, %s, %s", s1, result[i], num1[i],  num2[i]);
    
    free(s1);
    
    BigDec_destroy(&r);
    BigDec_destroy(&a);
    BigDec_destroy(&b);
    BigDec_destroy(&c);
  }
}

void multiplicationTest() {
  char * num1[] = {
    "12.5",
    "0.001",
    "-12.34",
    "-5.5",
    "123456789.123"
  };

  char * num2[] = {
    "4",
    "0.001",
    "2",
    "-2.2",
    "1000"
  };

  char * result[] = {
    "50.0",
    "0.000001",
    "-24.68",
    "12.10",
    "123456789123.000"
  };

  int i;
  BigDec a, b, c, r;
  char * s1;

  for (i = 0; i < 5; i++) {
    
    BigDec_init_from_string(&a, num1[i]);
    BigDec_init_from_string(&b, num2[i]);
    BigDec_init_from_string(&c, result[i]);
    BigDec_init(&r);
    
    BigDec_multiply(&r, &a, &b);
    
    s1 = BigDec_to_string(&r);

    TEST_CHECK(BigDec_cmp(&r, &c) == 0);
    TEST_MSG("Result: %s, Expected: %s, %s, %s", s1, result[i], num1[i],  num2[i]);
    
    free(s1);
    
    BigDec_destroy(&r);
    BigDec_destroy(&a);
    BigDec_destroy(&b);
    BigDec_destroy(&c);
  }
}

void divisionTest() {
  char * num1[] = {
    "10",
    "1",
    "-15",
    "123.456",
    "1000"
  };

  char * num2[] = {
    "2",
    "8",
    "4",
    "0.1",
    "0.001"
  };

  char * result[] = {
    "5",
    "0.125",
    "-3.75",
    "1234.56",
    "1000000"
  };

  int i;
  BigDec a, b, c, r;
  char * s1;

  for (i = 0; i < 5; i++) {
    
    BigDec_init_from_string(&a, num1[i]);
    BigDec_init_from_string(&b, num2[i]);
    BigDec_init_from_string(&c, result[i]);
    BigDec_init(&r);
    
    BigDec_divide(&r, &a, &b, 10);
    
    s1 = BigDec_to_string(&r);

    TEST_CHECK(BigDec_cmp(&r, &c) == 0);
    TEST_MSG("Result: %s, Expected: %s, %s, %s", s1, result[i], num1[i],  num2[i]);
    
    free(s1);
    
    BigDec_destroy(&r);
    BigDec_destroy(&a);
    BigDec_destroy(&b);
    BigDec_destroy(&c);
  }
}

void divisionRepeatedDecimalTest() {
  char * num1[] = {
    "1",
    "2",
    "1",
    "1",
    "10"
  };

  char * num2[] = {
    "3",
    "3",
    "6",
    "7",
    "9"
  };

  char * result[] = {
    "0.3333333333",
    "0.6666666667",
    "0.1666666667",
    "0.1428571429",
    "1.1111111111"
  };

  int i;
  BigDec a, b, c, r;
  char * s1;

  for (i = 0; i < 5; i++) {
    
    BigDec_init_from_string(&a, num1[i]);
    BigDec_init_from_string(&b, num2[i]);
    BigDec_init_from_string(&c, result[i]);
    BigDec_init(&r);
    
    BigDec_divide(&r, &a, &b, 10);
    
    s1 = BigDec_to_string(&r);

    TEST_CHECK(BigDec_cmp(&r, &c) == 0);
    TEST_MSG("Result: %s, Expected: %s, %s, %s", s1, result[i], num1[i],  num2[i]);
    
    free(s1);
    
    BigDec_destroy(&r);
    BigDec_destroy(&a);
    BigDec_destroy(&b);
    BigDec_destroy(&c);
  }
}

TEST_LIST = {
  {"addition", additionTest},
  {"subtraction", subtractionTest},
  {"multiplication", multiplicationTest},
  {"division", divisionTest},
  {"division repeating decimals", divisionRepeatedDecimalTest},
  {NULL, NULL}
};
