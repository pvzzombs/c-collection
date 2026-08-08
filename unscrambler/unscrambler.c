#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../others/linenoise.h"

typedef struct Word_ Word;
struct Word_ {
  char* word;
  int len;
  char letters[26];
};

typedef struct WordArray_ WordArray;
struct WordArray_ {
  Word* arr;
  int len;
  int capacity;
};

void Word_destroy(Word* w);

void WordArray_init(WordArray* wa) {
  wa->arr = malloc(sizeof(Word));
  wa->len = 0;
  wa->capacity = 1;
}

void WordArray_destroy(WordArray* wa) {
  int i;
  for (i = 0; i < wa->len; i++) {
    Word_destroy(&(wa->arr[i]));
  }
  free(wa->arr);
  wa->len = 0;
  wa->capacity = 0;
}

void WordArray_push(WordArray* wa, Word word) {
  wa->len = wa->len + 1;
  if (wa->len > wa->capacity) {
    Word* temp = malloc(sizeof(Word) * wa->capacity * 2);
    int new_capacity = wa->capacity * 2;
    int i;
    for (i = 0; i < wa->len - 1; i++) {
      temp[i] = wa->arr[i];
    }
    temp[i] = word;
    free(wa->arr);
    wa->arr = temp;
    wa->capacity = new_capacity;
    return;
  }
  wa->arr[wa->len - 1] = word;
}

void WordArray_print(WordArray* wa) {
  int i;
  for (i = 0; i < wa->len; i++) {
    printf("%s\n", wa->arr[i].word);
  }
}

void WordArray_clear(WordArray* wa) { wa->len = 0; }

void Word_init(Word* w, char* src) {
  int i;
  int len = strlen(src);

  w->word = malloc(len * sizeof(char) + 1);
  strcpy(w->word, src);

  for (i = 0; i < 26; i++) {
    w->letters[i] = 0;
  }

  for (i = 0; i < len; i++) {
    int index = src[i] - 'a';
    w->letters[index]++;
  }

  w->len = len;
}

void Word_destroy(Word* w) { free(w->word); }

void removeLineChar(char* b) {
  int l = strlen(b);
  int i;
  for (i = 0; i < l; i++) {
    if (b[i] == '\n') {
      b[i] = 0;
      break;
    }
  }
}

void choose(WordArray* dest, WordArray* src, Word w) {
  int len = src->len;
  int i, j, passed = 1;
  for (i = 0; i < len; i++) {
    passed = 1;
    for (j = 0; j < 26; j++) {
      if (src->arr[i].letters[j] != 0 &&
          w.letters[j] < src->arr[i].letters[j]) {
        passed = 0;
        break;
      }
    }
    if (passed) {
      Word w;
      Word_init(&w, src->arr[i].word);
      WordArray_push(dest, w);
    }
  }
}

int compareWords(const void * a, const void * b) {
  Word * w1 = (Word *)a;
  Word * w2 = (Word *)b;
  
  return w1->len - w2->len;
}

int main(int argc, char ** argv) {
  char dictionary_name[128];
  FILE* f;
  char buffer[128];
  WordArray arr;
  
  if (argc < 2) {
    strcpy(dictionary_name, "twl.txt");
  } else {
    strcpy(dictionary_name, argv[1]);
  }
  printf("Using the dictionary: %s\n", dictionary_name);
  
  f = fopen(dictionary_name, "r");

  WordArray_init(&arr);

  if (f != NULL) {
    while (fgets(buffer, 128, f) != NULL) {
      Word w;
      removeLineChar(buffer);
      Word_init(&w, buffer);
      WordArray_push(&arr, w);
    }
    fclose(f);
  } else {
    printf("Dictionary file (%s) NOT FOUND!!!\n", dictionary_name);
  }
  
  linenoiseHistorySetMaxLen(20);

  while (1) {
    WordArray selections;
    Word toBeUnscrambled;
    char * buffer;

    WordArray_init(&selections);
    
    buffer = linenoise("Enter letters: ");

    /* printf("Enter letters: ");
    fgets(buffer, 128, stdin);
    removeLineChar(buffer); */
    
    if (strcmp(buffer, "") == 0) {
      linenoiseFree(buffer);
      WordArray_destroy(&selections);
      break;
    }
    
    Word_init(&toBeUnscrambled, buffer);
    choose(&selections, &arr, toBeUnscrambled);
    
    qsort(selections.arr, selections.len, sizeof(Word), compareWords);
    
    WordArray_print(&selections);
    
    linenoiseHistoryAdd(buffer);
    linenoiseFree(buffer);
    
    Word_destroy(&toBeUnscrambled);
    WordArray_destroy(&selections);
  }
  WordArray_destroy(&arr);

  return 0;
}
