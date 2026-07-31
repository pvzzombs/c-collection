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

#if defined(HASHTABLE_IMPL)

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void HashTable_entry_init(HashTable_Entry * he) {
  he->head = NULL;
  he->len = 0;
}

void HashTable_entry_add_str(HashTable_Entry * he, char * str, int type, void * val) {
  char * key = malloc(sizeof(char) * (strlen(str) + 1));
  HashTable_Entry_List * newNode = malloc(sizeof(HashTable_Entry_List));
  strcpy(key, str);
  newNode->type = HASHTABLE_TYPE_STRING;
  newNode->strKey = key;
  newNode->strVal = NULL;
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

void HashTable_entry_update_str(HashTable_Entry * he, int type, char * str, void * val) {
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

void * HashTable_entry_find_str(HashTable_Entry * he, int type, char * str) {
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

void HashTable_entry_add_int(HashTable_Entry * he, int num) {
  int key = num;
  HashTable_Entry_List * newNode = malloc(sizeof(HashTable_Entry_List));
  newNode->type = HASHTABLE_TYPE_INT;
  newNode->numKey = key;
  newNode->strKey = NULL;
  newNode->strVal = NULL;
  if (he->len == 0) {
    he->head = newNode;
    he->head->next = NULL;
    he->len++;
  } else {
    newNode->next = he->head;
    he->head = newNode;
    he->len++;
  }
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
  HashTable_entry_update_str(&(h->table[i]), type, key, val);
}

void * HashTable_get_value_from_str(HashTable * h, char * key, int type) {
  unsigned long i = HashTable_hash_string_djb2(key);
  i = i % h->table_size;
  return HashTable_entry_find_str(&(h->table[i]), type, key);
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
