#include <stdlib.h>
#include <stdio.h>

struct MemoryPoolDetail_ {
  unsigned int is_free;
  unsigned int size;
  unsigned char * start;
  unsigned int alloc_size;
};

typedef struct MemoryPoolDetail_ MemoryPoolDetail;

struct MemoryPool_ {
  unsigned char * mem;
  unsigned int elem_max_size;
  MemoryPoolDetail * details;
  unsigned int details_size;
  unsigned int index;
  unsigned int total_size;
};

typedef struct MemoryPool_ MemoryPool;

void MP_init(MemoryPool *, int, int);
void MP_add(MemoryPool *, int);
void MP_start(MemoryPool *);
unsigned char * MP_alloc(MemoryPool * pool, int);
void MP_free(MemoryPool *, unsigned char *);
void MP_destroy(MemoryPool *);
extern MemoryPool default_pool;

#ifdef MEMORY_POOL_IMPL

MemoryPool default_pool;

void MP_init(MemoryPool * pool, int m, int n) {
  pool->elem_max_size = m;
  pool->details_size = n;
  pool->index = 0;
  pool->details = malloc(sizeof(MemoryPoolDetail) * n);
}

void MP_add(MemoryPool * pool, int bs) {
  pool->details[pool->index].size = bs;
  pool->details[pool->index].is_free = 1;
  pool->index++;
}

void MP_start(MemoryPool * pool) {
  unsigned int total_size = 0;
  unsigned int elem_size;
  unsigned char * mem = NULL;
  int i;
  for(i = 0; i < pool->index; i++) {
    elem_size = pool->details[i].size / pool->elem_max_size;
    elem_size = elem_size * pool->elem_max_size;
    while(elem_size < pool->details[i].size) {
      elem_size = elem_size + pool->elem_max_size;
    }
    pool->details[i].alloc_size = elem_size;
    total_size += elem_size;
  }
  pool->total_size = total_size;
  pool->mem = malloc(total_size);
  mem = pool->mem;
  for(i = 0; i < pool->index; i++) {
    pool->details[i].start = mem;
    mem = mem + pool->details[i].alloc_size;
  }
}

unsigned char * MP_alloc(MemoryPool * pool, int s) {
  int i;
  int best_index = -1;
  int min_size = pool->total_size;
  int has_free = 0;
  unsigned char * output = NULL;
  for (i = 0; i < pool->index; i++) {
    if (pool->details[i].is_free) {
      has_free = 1;
      if (pool->details[i].alloc_size >= s && pool->details[i].alloc_size < min_size) {
        best_index = i;
        min_size = pool->details[i].alloc_size;
      }
    }
  }
  if (best_index == -1) {
    if (has_free) {
      printf("Free found not enough space!\n");
    }
    printf("Not enough allocations!\n");
    return NULL;
  }
  pool->details[best_index].is_free = 0;
  return pool->details[best_index].start;
}

void MP_free(MemoryPool * pool, unsigned char * a) {
  int i;
  for(i = 0; i < pool->index; i++) {
    if (pool->details[i].start == a){
      pool->details[i].is_free = 1;
      break;
    }
  }
}

void MP_destroy(MemoryPool * pool) {
  free(pool->mem);
  free(pool->details);
}

#endif

#define BIGINT_USE_CUSTOM_ALLOC

#define BIGINT_ALLOC(x) MP_alloc(&default_pool, x);
#define BIGINT_FREE(x) MP_free(&default_pool, x);
