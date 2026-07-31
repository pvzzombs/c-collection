#define HASHTABLE_IMPL

#include "hashtable.h"

int main() {
  HashTable t;
  char a[] = "Wow!";
  int * r_only;
  int x = 12;
  HashTable_init(&t, 10);
  
  
  HashTable_insert_str(&t, "1", HASHTABLE_TYPE_STRING, "Wow!");
  HashTable_insert_str(&t, "2", HASHTABLE_TYPE_INT, &x);
  HashTable_print(&t);
  
  /* HashTable_set_value_from_str(&t, "Noice!!", HASHTABLE_TYPE_STRING, a); */
  
  r_only = (int *)HashTable_get_value_from_str(&t, "2", HASHTABLE_TYPE_INT);
  
  printf("%d\n", *r_only);
  
  HashTable_remove_str(&t, "2");
  HashTable_print(&t);
  
  HashTable_destroy(&t);
  return 0;
}
