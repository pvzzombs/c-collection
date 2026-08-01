#define HASHTABLE_IMPL
#define BIGINT_IMPL

#include "hashtable.h"
#include "../multiprecisionArithmetic/bigInteger.h"

void del(void * s) {
  HashTable_String_type * p_str = (HashTable_String_type *) s;
  HashTable_string_destroy(p_str);
  free(p_str);
}

int main() {
  HashTable t;
  char a[] = "Wow!";
  int * r_only;
  char * str;
  int x = 12, y = 10;
  HashTable_init(&t, 10);
  char tempStr[128];
  
  BigInt b1, b2;
  BigInt * bptr;
  
  
  
  /* BigInt_init_from_int(&b1, 12345);
  BigInt_init_two(&b2); */
  
  /* HashTable_insert_str(&t, "1", HASHTABLE_TYPE_STRING, "Wow!");
  HashTable_insert_str(&t, "2", HASHTABLE_TYPE_INT, &x);
  HashTable_print(&t);

  HashTable_insert_str(&t, "1", HASHTABLE_TYPE_STRING,"Amazing!");
  str = (char *) HashTable_get_value_from_str(&t, "1", HASHTABLE_TYPE_STRING);
  printf("%s\n", str);
  HashTable_print(&t);
  
  r_only = (int *)HashTable_get_value_from_str(&t, "2", HASHTABLE_TYPE_INT);
  
  printf("%d\n", *r_only);
  
  HashTable_remove_str(&t, "2");
  HashTable_print(&t); */
  /* x = 12;
  HashTable_insert_int(&t, 100, HASHTABLE_TYPE_INT, &x);
  HashTable_insert_int(&t, 99, HASHTABLE_TYPE_INT, &x);
  HashTable_insert_int(&t, 99, HASHTABLE_TYPE_INT, &y);
  HashTable_print(&t);

  r_only = (int *) HashTable_get_value_from_int(&t, 99, HASHTABLE_TYPE_INT);
  printf("Num is %d\n", *r_only);

  HashTable_remove_int(&t, 100);
  HashTable_print(&t);*/
  
  /* HashTable_insert_str(&t, "1", HASHTABLE_TYPE_CUSTOM, &b1);
  HashTable_insert_str(&t, "2", HASHTABLE_TYPE_CUSTOM, &b2);
  
  bptr = HashTable_get_value_from_str(&t, "1", HASHTABLE_TYPE_CUSTOM);
  
  BigInt_print_u(bptr);
  
  BigInt_destroy(&b1);
  BigInt_destroy(&b2); */
  
  HashTable_String_type * str1 = malloc(sizeof(HashTable_String_type));
  HashTable_String_type * str2 = malloc(sizeof(HashTable_String_type));
  
  HashTable_string_init(str1, "Hello ");
  HashTable_string_init(str2, "World");
  
  HashTable_string_append_from_ptr(str1, "World!\n");
  
  HashTable_string_print(str1);
  
  HashTable_insert(&t, "1", 1, str1, del);
  HashTable_insert(&t, "1", 1, str2, del);
  
  HashTable_string_print((HashTable_String_type*) HashTable_get(&t, "1", 1));
  
  HashTable_destroy(&t, del);
  return 0;
}
