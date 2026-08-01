#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define HASHTABLE_TYPE_STRING 1
#define HASHTABLE_TYPE_INT 2
#define HASHTABLE_TYPE_CUSTOM 3
#define HASHTABLE_TYPE_NONE 0

typedef struct HashTable_Entry_List_ HashTable_Entry_List;
struct HashTable_Entry_List_ {
  void * key;
  int keyLen;
  char * strKey;
  int numKey;
  int type;
  char * strVal;
  int numVal;
  void * customVal;
  
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

typedef void(*HashTable_entry_list_destructor)(void *);

typedef struct HashTable_String_Type_ HashTable_String_type;
struct HashTable_String_Type_ {
  unsigned char * data;
  int allocSize;
  int length;
};

void HashTable_entry_list_init(HashTable_Entry_List *);
void HashTable_entry_init(HashTable_Entry *);
int HashTable_entry_contains_str(HashTable_Entry *, char *);
int HashTable_entry_contains_int(HashTable_Entry *, int);
void HashTable_entry_add_str(HashTable_Entry *, char *, int, void *);
void HashTable_entry_delete_str(HashTable_Entry *, char *);
void HashTable_entry_update_str(HashTable_Entry *, char *, int, void *);
void * HashTable_entry_find_str(HashTable_Entry *, char *, int);

void HashTable_entry_add_custom(HashTable_Entry *, void *, int, int, void *, HashTable_entry_list_destructor);
void HashTable_entry_delete_custom(HashTable_Entry *, void *, int, HashTable_entry_list_destructor);
void HashTable_entry_update_custom(HashTable_Entry *, void *, int, int, void *, HashTable_entry_list_destructor);
void * HashTable_entry_find_custom(HashTable_Entry *, void *, int, int);

void HashTable_entry_add_int(HashTable_Entry *, int, int, void *);
void HashTable_entry_delete_int(HashTable_Entry *, int);
void HashTable_entry_update_int(HashTable_Entry *, int, int, void *);
void * HashTable_entry_find_int(HashTable_Entry *, int, int);
void HashTable_entry_destroy(HashTable_Entry *, HashTable_entry_list_destructor);
void HashTable_entry_print(HashTable_Entry *);
void HashTable_init(HashTable *, int);
void HashTable_destroy(HashTable *, HashTable_entry_list_destructor);
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
  hel->customVal = NULL;
  hel->key = NULL;
  hel->keyLen = 0;
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

int HashTable_entry_contains_custom(HashTable_Entry * he, void * k, int len) {
  HashTable_Entry_List * current = he->head;
  int j = 0;
  while (current != NULL) {
    if (current->keyLen == len && memcmp(current->key, k, len) == 0) {
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
  if (HashTable_entry_contains_str(he, str) == -1) {
    char * key = malloc(sizeof(char) * (strlen(str) + 1));
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
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      newNode->customVal = val;
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
      free(current->strVal);
      current->strVal = malloc(sizeof(char) * (strlen(s) + 1));
      strcpy(current->strVal, s);
    } else if (type == HASHTABLE_TYPE_INT) {
      int * num = (int *) val;
      current->numVal = *num;
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      current->customVal = val;
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
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      return current->customVal;
    }
    return NULL;
  }
  return NULL;
}

void HashTable_entry_add_custom(HashTable_Entry * he, void * k, int len, int type, void * val, HashTable_entry_list_destructor func) {
  if (HashTable_entry_contains_custom(he, k, len) == -1) {
    void * key = malloc(len);
    HashTable_Entry_List * newNode = malloc(sizeof(HashTable_Entry_List));
    HashTable_entry_list_init(newNode);
    newNode->type = HASHTABLE_TYPE_CUSTOM;
    memcpy(key, k, len);
    newNode->key = key;
    newNode->keyLen = len;
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
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      newNode->customVal = val;
    }
  } else {
    HashTable_entry_update_custom(he, k, len, type, val, func);
  }
}

void HashTable_entry_delete_custom(HashTable_Entry * he, void * k, int len, HashTable_entry_list_destructor func) {
  HashTable_Entry_List * parent = NULL;
  HashTable_Entry_List * current = he->head;
  HashTable_Entry_List * next = NULL;
  while(current != NULL) {
    if (current->keyLen == len && memcmp(current->key, k, len) == 0) {
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
    } else if (current->type == HASHTABLE_TYPE_CUSTOM) {
      free(current->key);
    }
    if (func != NULL) {
      func(current->customVal);
    }
    free(current->strVal);
    free(current);
    he->len--;
  }
}

void HashTable_entry_update_custom(HashTable_Entry * he, void * k, int len, int type, void * val, HashTable_entry_list_destructor func) {
  HashTable_Entry_List * current = he->head;
  while(current != NULL) {
    if (current->keyLen == len && memcmp(current->key, k, len) == 0) {
      /* Key found! */
      break;
    }
    current = current->next;
  }
  
  if (current != NULL) {
    if (type == HASHTABLE_TYPE_STRING) {
      char * s = (char *) val;
      free(current->strVal);
      current->strVal = malloc(sizeof(char) * (strlen(s) + 1));
      strcpy(current->strVal, s);
    } else if (type == HASHTABLE_TYPE_INT) {
      int * num = (int *) val;
      current->numVal = *num;
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      if (func != NULL) {
        func(current->customVal);
      }
      current->customVal = val;
    }
  }
}

void * HashTable_entry_find_custom(HashTable_Entry * he, void * k, int len, int type) {
  HashTable_Entry_List * current = he->head;
  while(current != NULL) {
    if (current->keyLen == len && memcmp(current->key, k, len) == 0) {
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
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      return current->customVal;
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
    if (type == HASHTABLE_TYPE_STRING) {
      newNode->strVal = malloc(sizeof(char) * (strlen((char*)val) + 1));
      strcpy(newNode->strVal, (char *)val);
    } else if (type == HASHTABLE_TYPE_INT) {
      newNode->numVal = *((int *)val);
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      newNode->customVal = val;
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
      free(current->strVal);
      current->strVal = malloc(sizeof(char) * (strlen(s) + 1));
      strcpy(current->strVal, s);
    } else if (type == HASHTABLE_TYPE_INT) {
      int * num = (int *) val;
      current->numVal = *num;
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      current->customVal = val;
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
    } else if (type == HASHTABLE_TYPE_CUSTOM) {
      return current->customVal;
    }
    return NULL;
  }
  return NULL;
}

void HashTable_entry_destroy(HashTable_Entry * he, HashTable_entry_list_destructor func) {
  HashTable_Entry_List * parent = NULL;
  HashTable_Entry_List * current = he->head;
  
  while (current != NULL) {
    if (parent != NULL) {
      if (parent->type == HASHTABLE_TYPE_STRING) {
        free(parent->strKey);
      } else if (parent->type == HASHTABLE_TYPE_CUSTOM) {
        free(parent->key);
      }
      free(parent->strVal);
      if (func != NULL) {
        func(parent->customVal);
      }
    }
    free(parent);
    parent = current;
    current = current->next;
  }
  if (parent != NULL) {
    if (parent->type == HASHTABLE_TYPE_STRING) {
      free(parent->strKey);
    } else if (parent->type == HASHTABLE_TYPE_CUSTOM) {
      free(parent->key);
    }
    free(parent->strVal);
    if (func != NULL) {
      func(parent->customVal);
    }
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
    } else if (current->type == HASHTABLE_TYPE_CUSTOM) {
      int i = 0;
      unsigned char * cptr = (unsigned char *)current->key;
      printf("(");
      for (i = 0; i < current->keyLen; i++) {
        printf("%d ", (int)(cptr[i]));
      }
      printf(")");
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

void HashTable_destroy(HashTable * h, HashTable_entry_list_destructor func) {
  int i;
  for (i = 0; i < h->table_size; i++) {
    HashTable_entry_destroy(&(h->table[i]), func);
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

unsigned long HashTable_hash_custom_djb2(void * k, int len) {
  unsigned char * c_ptr = (unsigned char *) k;
  unsigned long hash = 5381;
  int i;
  int ch;
  for (i = 0; i < len; i++) {
    ch = c_ptr[i];
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

void HashTable_insert(HashTable * h, void * k, int len, void * v, HashTable_entry_list_destructor f) {
  unsigned long i = HashTable_hash_custom_djb2(k, len);
  i = i % h->table_size;
  HashTable_entry_add_custom(&(h->table[i]), k, len, HASHTABLE_TYPE_CUSTOM, v, f);
}

void HashTable_remove(HashTable * h, void * k, int len, HashTable_entry_list_destructor f) {
  unsigned long i = HashTable_hash_custom_djb2(k, len);
  i = i % h->table_size;
  HashTable_entry_delete_custom(&(h->table[i]), k, len, f);
}
void HashTable_set(HashTable * h, void * k, int len, void * v, HashTable_entry_list_destructor f) {
  unsigned long i = HashTable_hash_custom_djb2(k, len);
  i = i % h->table_size;
  HashTable_entry_update_custom(&(h->table[i]), k, len, HASHTABLE_TYPE_CUSTOM, v, f);
}
void * HashTable_get(HashTable * h, void * k, int len) {
  unsigned long i = HashTable_hash_custom_djb2(k, len);
  i = i % h->table_size;
  return HashTable_entry_find_custom(&(h->table[i]), k, len, HASHTABLE_TYPE_CUSTOM);
}

void HashTable_print(HashTable * h) {
  int i;
  for (i = 0; i < h->table_size; i++) {
    printf("%d: ", i);
    HashTable_entry_print(&(h->table[i]));
    printf("\n");
  }
}

void HashTable_copy_to_char_array(char * str, void * k, int len) {
  
}

void HashTable_string_init(HashTable_String_type * str, char * src) {
  str->data = malloc(strlen(src));
  str->allocSize = strlen(src);
  str->length = strlen(src);
  memcpy(str->data, src, strlen(src));
}

void HashTable_string_destroy(HashTable_String_type * str) {
  free(str->data);
  str->allocSize = 0;
  str->length = 0;
}

void HashTable_string_copy_from_ptr(HashTable_String_type * str, char * src) {
  int len = strlen(src);
  if (len > str->allocSize) {
    free(str->data);
    str->data = malloc(len);
    str->allocSize = len;
  }
  str->length = len;
  memcpy(str->data, src, len);
}

void HashTable_string_append_from_ptr(HashTable_String_type * str, char * src) {
  int len = strlen(src);
  int i;
  int j;
  unsigned char * temp = str->data;
  int shouldFreeTemp = 0;
  if (len + str->length > str->allocSize) {
    str->data = malloc(len + str->length);
    str->allocSize = len + str->length;
    shouldFreeTemp = 1;
  }
  for (i = 0; i < str->length; i++) {
    str->data[i] = temp[i];
  }
  for(j = 0; j < len; j++) {
    str->data[i + j] = src[j];
  }
  str->length = len + str->length;
  if (shouldFreeTemp) {
    free(temp);
  }
}

void HashTable_string_print(HashTable_String_type * str) {
  int i;
  for (i = 0; i < str->length; i++) {
    printf("%c", (char)str->data[i]);
  }
}

#endif

#ifdef __cplusplus
}
#endif
