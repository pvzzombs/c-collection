#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define HASHTABLE_TYPE_STRING 1
#define HASHTABLE_TYPE_INT 2
#define HASHTABLE_TYPE_NONE 0

typedef struct HashTable_Entry_List_ HashTable_Entry_List;
struct HashTable_Entry_List_ {
  char * strKey;
  int numKey;
  int type;
  char * strVal;
  int numVal;
  
  HashTable_Entry_List * next;
};

typedef struct HashTable_Entry_ HashTable_Entry;
struct HashTable_Entry_ {
  HashTable_Entry_List * head;
  int len;
};

typedef struct HashTable_ HashTable;
struct HashTable_ {
  int table_size;
  HashTable_Entry * table;
};

void HashTable_entry_list_init(HashTable_Entry_List *);
void HashTable_entry_init(HashTable_Entry *);
int HashTable_entry_contains_str(HashTable_Entry *, char *);
int HashTable_entry_contains_int(HashTable_Entry *, int);
void HashTable_entry_add_str(HashTable_Entry *, char *, int, void *);
void HashTable_entry_delete_str(HashTable_Entry *, char *);
void HashTable_entry_update_str(HashTable_Entry *, char *, int, void *);
void * HashTable_entry_find_str(HashTable_Entry *, char *, int);
void HashTable_entry_add_int(HashTable_Entry *, int, int, void *);
void HashTable_entry_delete_int(HashTable_Entry *, int);
void HashTable_entry_update_int(HashTable_Entry *, int, int, void *);
void * HashTable_entry_find_int(HashTable_Entry *, int, int);
void HashTable_entry_destroy(HashTable_Entry *);
void HashTable_entry_print(HashTable_Entry *);
void HashTable_init(HashTable *, int);
void HashTable_destroy(HashTable *);
unsigned long HashTable_hash_string_djb2(char *);
void HashTable_insert_str(HashTable *, char *, int, void *);
void HashTable_remove_str(HashTable *, char *);
void HashTable_set_value_from_str(HashTable *, char *, int, void *);
void * HashTable_get_value_from_str(HashTable *, char *, int);
void HashTable_print(HashTable *);

#if defined(HASHTABLE_IMPL)

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void HashTable_entry_list_init(HashTable_Entry_List * hel) {
  hel->next = NULL;
  hel->numKey = 0;
  hel->numVal = 0;
  hel->strKey = NULL;
  hel->strVal = NULL;
  hel->type = HASHTABLE_TYPE_NONE;
}

void HashTable_entry_init(HashTable_Entry * he) {
  he->head = NULL;
  he->len = 0;
}

int HashTable_entry_contains_str(HashTable_Entry * he, char * str) {
  HashTable_Entry_List * current = he->head;
  int j = 0;
  while (current != NULL) {
    if (strcmp(current->strKey, str) == 0) {
      return j;
    }
    current = current->next;
    j++;
  }
  return -1;
}

int HashTable_entry_contains_int(HashTable_Entry * he, int key) {
  HashTable_Entry_List * current = he->head;
  int j = 0;
  while (current != NULL) {
    if (current->numKey == key) {
      return j;
    }
    current = current->next;
    j++;
  }
  return -1;
}

void HashTable_entry_add_str(HashTable_Entry * he, char * str, int type, void * val) {
  char * key = malloc(sizeof(char) * (strlen(str) + 1));
  if (HashTable_entry_contains_str(he, str) == -1) {
    HashTable_Entry_List * newNode = malloc(sizeof(HashTable_Entry_List));
    strcpy(key, str);
    HashTable_entry_list_init(newNode);
    newNode->type = HASHTABLE_TYPE_STRING;
    newNode->strKey = key;
    if (he->len == 0) {
      he->head = newNode;
      he->head->next = NULL;
      he->len++;
    } else {
      newNode->next = he->head;
      he->head = newNode;
      he->len++;
    }
    if (type == HASHTABLE_TYPE_STRING) {
      newNode->strVal = malloc(sizeof(char) * (strlen((char*)val) + 1));
      strcpy(newNode->strVal, (char *)val);
    } else if (type == HASHTABLE_TYPE_INT) {
      newNode->numVal = *((int *)val);
    }
  } else {
    HashTable_entry_update_str(he, str, type, val);
  }
}

void HashTable_entry_delete_str(HashTable_Entry * he, char * str) {
  HashTable_Entry_List * parent = NULL;
  HashTable_Entry_List * current = he->head;
  HashTable_Entry_List * next = NULL;
  while(current != NULL) {
    if (strcmp(current->strKey, str) == 0) {
      /* Key found! */
      next = current->next;
      break;
    }
    parent = current;
    current = current->next;
  }
  
  if (current != NULL) {
    if (parent != NULL) {
      parent->next = next;
    } else {
      he->head = next;
    }
    if (current->type == HASHTABLE_TYPE_STRING) {
      free(current->strKey);
    }
    free(current->strVal);
    free(current);
    he->len--;
  }
}

void HashTable_entry_update_str(HashTable_Entry * he, char * str, int type, void * val) {
  HashTable_Entry_List * current = he->head;
  while(current != NULL) {
    if (strcmp(current->strKey, str) == 0) {
      /* Key found! */
      break;
    }
    current = current->next;
  }
  
  if (current != NULL) {
    if (type == HASHTABLE_TYPE_STRING) {
      char * s = (char *) val;
      current->strVal = malloc(sizeof(char) * (strlen(s) + 1));
      strcpy(current->strVal, s);
    } else if (type == HASHTABLE_TYPE_INT) {
      int * num = (int *) val;
      current->numVal = *num;
    }
  }
}

void * HashTable_entry_find_str(HashTable_Entry * he, char * str, int type) {
  HashTable_Entry_List * current = he->head;
  while(current != NULL) {
    if (strcmp(current->strKey, str) == 0) {
      /* Key found! */
      break;
    }
    current = current->next;
  }
  
  if (current != NULL) {
    if (type == HASHTABLE_TYPE_STRING) {
      return (void *) current->strVal;
    } else if (type == HASHTABLE_TYPE_INT) {
      return (void *) &(current->numVal);
    }
    return NULL;
  }
  return NULL;
}

void HashTable_entry_add_int(HashTable_Entry * he, int num, int type, void * val) {
  int key = num;
  if (HashTable_entry_contains_int(he, key) == -1) {
    HashTable_Entry_List * newNode = malloc(sizeof(HashTable_Entry_List));
    HashTable_entry_list_init(newNode);
    newNode->type = HASHTABLE_TYPE_INT;
    newNode->numKey = key;
    if (he->len == 0) {
      he->head = newNode;
      he->head->next = NULL;
      he->len++;
    } else {
      newNode->next = he->head;
      he->head = newNode;
      he->len++;
    }
  } else {
    HashTable_entry_update_int(he, num, type, val);
  }
}

void HashTable_entry_delete_int(HashTable_Entry * he, int key) {
  HashTable_Entry_List * parent = NULL;
  HashTable_Entry_List * current = he->head;
  HashTable_Entry_List * next = NULL;
  while(current != NULL) {
    if (current->numKey == key) {
      /* Key found! */
      next = current->next;
      break;
    }
    parent = current;
    current = current->next;
  }
  
  if (current != NULL) {
    if (parent != NULL) {
      parent->next = next;
    } else {
      he->head = next;
    }
    if (current->type == HASHTABLE_TYPE_STRING) {
      free(current->strKey);
    }
    free(current->strVal);
    free(current);
    he->len--;
  }
}

void HashTable_entry_update_int(HashTable_Entry * he, int key, int type, void * val) {
  HashTable_Entry_List * current = he->head;
  while(current != NULL) {
    if (current->numKey == key) {
      /* Key found! */
      break;
    }
    current = current->next;
  }
  
  if (current != NULL) {
    if (type == HASHTABLE_TYPE_STRING) {
      char * s = (char *) val;
      current->strVal = malloc(sizeof(char) * (strlen(s) + 1));
      strcpy(current->strVal, s);
    } else if (type == HASHTABLE_TYPE_INT) {
      int * num = (int *) val;
      current->numVal = *num;
    }
  }
}

void * HashTable_entry_find_int(HashTable_Entry * he, int key, int type) {
  HashTable_Entry_List * current = he->head;
  while(current != NULL) {
    if (current->numKey == key) {
      /* Key found! */
      break;
    }
    current = current->next;
  }
  
  if (current != NULL) {
    if (type == HASHTABLE_TYPE_STRING) {
      return (void *) current->strVal;
    } else if (type == HASHTABLE_TYPE_INT) {
      return (void *) &(current->numVal);
    }
    return NULL;
  }
  return NULL;
}

void HashTable_entry_destroy(HashTable_Entry * he) {
  HashTable_Entry_List * parent = NULL;
  HashTable_Entry_List * current = he->head;
  
  while (current != NULL) {
    if (parent != NULL && parent->type == HASHTABLE_TYPE_STRING) {
      free(parent->strKey);
    }
    if (parent != NULL) {
      free(parent->strVal);
    }
    free(parent);
    parent = current;
    current = current->next;
  }
  if (parent != NULL && parent->type == HASHTABLE_TYPE_STRING) {
      free(parent->strKey);
  }
  if (parent != NULL) {
    free(parent->strVal);
  }
  free(parent);
  he->len = 0;
  he->head = NULL;
}

void HashTable_entry_print(HashTable_Entry * he) {
  HashTable_Entry_List * current = he->head;
  while (current != NULL) {
    if (current->type == HASHTABLE_TYPE_STRING) {
      printf("(%s) ", current->strKey);
    } else if (current->type == HASHTABLE_TYPE_INT) {
      printf("(%d) ", current->numKey);
    }
    current = current->next;
  }
}

void HashTable_init(HashTable * h, int size) {
  int i;
  h->table_size = size;
  h->table = (HashTable_Entry*) malloc(sizeof(HashTable_Entry) * size);
  for (i = 0; i < size; i++) {
    HashTable_entry_init(&(h->table[i]));
  }
}

void HashTable_destroy(HashTable * h) {
  int i;
  for (i = 0; i < h->table_size; i++) {
    HashTable_entry_destroy(&(h->table[i]));
  }
  free(h->table);
}

unsigned long HashTable_hash_string_djb2(char * str) {
  unsigned long hash = 5381;
  int len = strlen(str);
  int i;
  int ch;
  for (i = 0; i < len; i++) {
    ch = str[i];
    hash = (hash * 33) + ch;
  }
  return hash;
}

unsigned long HashTable_hash_int_djb2(int num) {
  unsigned long hash = 5381;
  while (num > 0) {
    hash = hash * 33 + (num % 10 + '0');
    num = num / 10;
  }
  hash = hash * 33 + '0';
  return hash;
}

void HashTable_insert_str(HashTable * h, char * key, int type, void * val) {
  unsigned long i = HashTable_hash_string_djb2(key);
  i = i % h->table_size;
  HashTable_entry_add_str(&(h->table[i]), key, type, val);
}

void HashTable_remove_str(HashTable * h, char * key) {
  unsigned long i = HashTable_hash_string_djb2(key);
  i = i % h->table_size;
  HashTable_entry_delete_str(&(h->table[i]), key);
}

void HashTable_set_value_from_str(HashTable * h, char * key, int type, void * val) {
  unsigned long i = HashTable_hash_string_djb2(key);
  i = i % h->table_size;
  HashTable_entry_update_str(&(h->table[i]), key, type, val);
}

void * HashTable_get_value_from_str(HashTable * h, char * key, int type) {
  unsigned long i = HashTable_hash_string_djb2(key);
  i = i % h->table_size;
  return HashTable_entry_find_str(&(h->table[i]), key, type);
}

void HashTable_insert_int(HashTable * h, int key, int type, void * val) {
  unsigned long i = HashTable_hash_int_djb2(key);
  i = i % h->table_size;
  HashTable_entry_add_int(&(h->table[i]), key, type, val);
}

void HashTable_remove_int(HashTable * h, int key) {
  unsigned long i = HashTable_hash_int_djb2(key);
  i = i % h->table_size;
  HashTable_entry_delete_int(&(h->table[i]), key);
}

void HashTable_set_value_from_int(HashTable * h, int key, int type, void * val) {
  unsigned long i = HashTable_hash_int_djb2(key);
  i = i % h->table_size;
  HashTable_entry_update_int(&(h->table[i]), key, type, val);
}

void * HashTable_get_value_from_int(HashTable * h, int key, int type) {
  unsigned long i = HashTable_hash_int_djb2(key);
  i = i % h->table_size;
  return HashTable_entry_find_int(&(h->table[i]), key, type);
}

void HashTable_print(HashTable * h) {
  int i;
  for (i = 0; i < h->table_size; i++) {
    printf("%d: ", i);
    HashTable_entry_print(&(h->table[i]));
    printf("\n");
  }
}
#endif

#ifdef __cplusplus
}
#endif
