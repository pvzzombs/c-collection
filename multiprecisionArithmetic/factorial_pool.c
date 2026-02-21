#define BIGINT_IMPL
#define MEMORY_POOL_IMPL
#include "pool.h"
#include "bigInteger.h"

int main() {
  BigInt fact, i, one, end;
  char * s = NULL;

  MP_init(&default_pool, sizeof(BigInt_limb_t), 10);
  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);
  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);
  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);
  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);
  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);

  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);
  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);
  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);
  MP_add(&default_pool, sizeof(BigInt_limb_t) * 10000);
  MP_start(&default_pool);

  BigInt_init_from_string(&fact, "1");
  BigInt_init_from_string(&i, "1");
  BigInt_init_from_string(&one, "1");
  BigInt_init_from_string(&end, "10000");

  while(BigInt_cmp(&i, &end) <= 0) {
    BigInt_multiply_assign(&fact, &i); /* fact = fact * i; */
    BigInt_add_assign(&i, &one); /* i = i + 1; */
  }

  s = BigInt_to_string(&fact);
  printf("Factorial is %s.\n", s);
  /* BigInt_print_internal(&fact); */

  BigInt_destroy(&fact);
  BigInt_destroy(&i);
  BigInt_destroy(&one);
  BigInt_destroy(&end);

  MP_destroy(&default_pool);
  return 0;
}
