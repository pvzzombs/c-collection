#define HASHTABLE_IMPL

#include "hashtable.h"

int main() {
  HashTable t;
  char a[] = "Wow!";
  int * r_only;
  char * str;
  int x = 12, y = 10;
  HashTable_init(&t, 10);
  
  
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
  x = 12;
  HashTable_insert_int(&t, 100, HASHTABLE_TYPE_INT, &x);
  HashTable_insert_int(&t, 99, HASHTABLE_TYPE_INT, &x);
  HashTable_insert_int(&t, 99, HASHTABLE_TYPE_INT, &y);
  HashTable_print(&t);

  r_only = (int *) HashTable_get_value_from_int(&t, 99, HASHTABLE_TYPE_INT);
  printf("Num is %d\n", *r_only);

  HashTable_remove_int(&t, 100);
  HashTable_print(&t);
  
  HashTable_destroy(&t);
  return 0;
}
