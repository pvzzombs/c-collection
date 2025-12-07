#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* Bounds */

#define QUEUE_BOUND 1024
#define SET_BOUND 1024

/* Data Structures */

typedef struct Node_ {
  int r, c;
} Node;

typedef struct Queue_ {
  Node * arr;
  int l, r;
  int alloc_size;
} Queue;

typedef struct Set_ {
  Node * arr;
  int ptr;
  int alloc_size;
} Set;

/* Utility functions */

void print_node(Node n) {
  printf("Node: row: %d, col: %d", n.r, n.c);
}

Queue * queue_init() {
  Queue * q = malloc(sizeof(Queue));
  q->arr = malloc(sizeof(Node) * QUEUE_BOUND);
  q->l = 0;
  q->r = 0;
  q->alloc_size = QUEUE_BOUND;
  return q;
}

void queue_push(Queue * q, Node n) {
  if (q->r == q->alloc_size) {
    int i;
    int j = 0;
    q->alloc_size = q->alloc_size * 2;
    Node * temp = malloc(sizeof(Node) * q->alloc_size);
    for (i = q->l; i < q->r; i++) {
      temp[j] = q->arr[i];
      j++;
    }
    free(q->arr);
    q->arr = temp;
    q->l = 0;
    q->r = j;
  }
  // assert(q->r < q->alloc_size);
  q->arr[q->r] = n;
  q->r = q->r + 1;
}

Node queue_pop(Queue * q) {
  Node output = q->arr[q->l];
  if (q->l == q->r) {
    /* TODO Add resizing */
    printf("Hey!!!\n");
  }
  q->l = q->l + 1;
  return output;
}

Node queue_front(Queue * q) {
  return q->arr[q->l];
}

Node queue_back(Queue * q) {
  return q->arr[q->r - 1];
}

int queue_size(Queue * q) {
  return q->r - q->l;
}

int queue_empty(Queue * q) {
  return q->l == q->r;
}

void queue_clear(Queue * q) {
  q->l = 0;
  q->r = 0;
}

void queue_print(Queue * q) {
  int i;
  for (i = q->l; i < q->r; i++) {
    print_node(q->arr[i]);
    printf("\n");
  }
}

void queue_destroy(Queue * q) {
  free(q->arr);
  free(q);
}

Set * set_init() {
  Set *s = malloc(sizeof(Set));
  s->arr = malloc(sizeof(Node) * SET_BOUND);
  s->ptr = 0;
  s->alloc_size = SET_BOUND;
  return s;
}

int set_node_equal(Node a, Node b) {
  return a.r == b.r && a.c == b.c;
}

void set_push(Set * s, Node n) {
  int i;
  for (i = 0; i < s->ptr; i++) {
    if (set_node_equal(s->arr[i], n)) {
      return;
    }
  }
  if (s->ptr == s->alloc_size) {
    s->alloc_size = s->alloc_size * 2;
    Node * temp = malloc(sizeof(Node) * s->alloc_size);
    int i;
    for(i = 0; i < s->ptr; i++) {
      temp[i] = s->arr[i];
    }
    free(s->arr);
    s->arr = temp;
    s->ptr = i;
  }
  /* Not found, so unique*/
  s->arr[s->ptr] = n;
  s->ptr = s->ptr + 1;
}

void set_pop(Set * s, Node n) {
  int i;
  int p = -1;
  int j = 0;
  for (i = 0; i < s->ptr; i++) {
    if (set_node_equal(s->arr[i], n)) {
      p = i;
      break;
    }
  }

  if (p < 0) {
    return;
  }

  for (i = 0; i < s->ptr; i++) {
    if (i == p) {
      continue;
    }
    s->arr[j] = s->arr[i];
    j++;
  }
  s->ptr = s->ptr - 1;
}

int set_exists(Set * s, Node n) {
  int i;
  for (i = 0; i < s->ptr; i++) {
    if (set_node_equal(s->arr[i], n)) {
      return 1;
    }
  }
  return 0;
}

void set_clear(Set * s) {
  s->ptr = 0;
}

int set_size(Set * s) {
  return s->ptr;
}

void set_print(Set * s) {
  int i;
  for (i = 0; i < s->ptr; i++) {
    print_node(s->arr[i]);
    printf("\n");
  }
} 

void set_destroy(Set * s) {
  free(s->arr);
  free(s);
}

char ** genTable(char ** table, char * buf, int * width, int * height) {
  int len = strlen(buf);
  char ** t = NULL;
  int i;
  if (table == NULL) {
    t = malloc(sizeof(char *) * 1);
    t[0] = strdup(buf);
  } else {
    t = malloc(sizeof(char *) * (*height + 1));
    for (i = 0; i < *height; i++) {
      t[i] = table[i];
    }
    t[*height] = strdup(buf);
    free(table);
  }
  if (*width == 0) {
    *width = len;
  }
  *height = *height + 1;
  return t;
}

void printTable(char ** table, int height) {
  int i;
  for (i = 0; i < height; i++) {
    printf("%s\n", table[i]);
  }
}

void solveBeam(char ** table, int w, int h, Queue * q, Set * s, int * count) {
  Node startPos;
  startPos.r = 0;
  int i;
  for(i = 0; i < w; i++) {
    char c = table[0][i];
    if (c == 'S') {
      startPos.c = i;
      break;
    }
  }

  queue_push(q, startPos);

  while(queue_size(q) > 0) {
    Node temp = queue_pop(q);
    int nr = temp.r;
    int nc = temp.c;
    Node newTemp;
    newTemp.r = nr + 1;
    newTemp.c = nc;

    if (nr >= h || nc < 0 || nc >= w) {
      continue;
    }
    if (table[nr][nc] == '^' && !set_exists(s, temp)) {
      Node left, right;
      left.r = temp.r;
      right.r = temp.r;
      left.c = nc - 1;
      right.c = nc + 1;
      queue_push(q, left);
      queue_push(q, right);
      set_push(s, temp);
      *count = *count + 1;
    } else {
      if (!set_exists(s, temp)) {
        queue_push(q, newTemp);
      }
    }
  }
}

void resetTable(char ** table, int w, int h) {
  int i, j;
  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      if (table[i][j] == '-') {
        table[i][j] = '^';
      }
    }
  }
}

void solveBeam2(char ** table, int w, int h, unsigned long long * timeline) {
  unsigned long long ** dp = NULL;
  int i, j;
  dp = malloc(sizeof(unsigned long long *) * h);
  for (i = 0; i < h; i++) {
    dp[i] = malloc(sizeof(unsigned long long) * w);
    for(j = 0; j < w; j++) {
      dp[i][j] = 0;
    }
  }

  for (i = 0; i < h; i++) {
    if (i > 0) {
      for(j = 0; j < w; j++) {
        dp[i][j] = dp[i - 1][j];
      }
      for(j = 0; j < w; j++) {
        char c = table[i][j];
        if (c == '^') {
          int l = j - 1;
          int r = j + 1;
          if (l >= 0) {
            dp[i][l] += dp[i - 1][j];
          }
          if (r >= 0) {
            dp[i][r] += dp[i - 1][j];
          }
          dp[i][j] = 0;
        }
      }
    } else {
      for (j = 0; j < w; j++) {
        if (table[i][j] == 'S') {
          dp[i][j] = 1;
        }
      }
    }
  }

  /* for (i = 0; i < h; i++) {
    for(j = 0; j < w; j++) {
      printf("%d ", dp[i][j]);
    }
    printf("\n");
  } */

  for (i = 0; i < w; i++) {
    *timeline = *timeline + dp[h - 1][i];
  }

  for (i = 0; i < h; i++) {
    free(dp[i]);
  }
  free(dp);
}

int main() {
  FILE * fptr;
  char buf[256];
  char ** table = NULL;
  int width = 0;
  int height = 0;
  int i;
  int count = 0;
  unsigned long long timeline = 0;
  Queue *q = NULL;
  Set *s = NULL;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    while(fgets(buf, 256, fptr)) {
      if (strstr(buf, "\n") != NULL) {
        buf[strstr(buf, "\n") - buf] = 0;
      }
      if (strcmp(buf, "") != 0) {
        table = genTable(table, buf, &width, &height);
      }
    }

    fclose(fptr);
    /* printTable(table, height); */
    /* try_structures(); */
    q = queue_init();
    s = set_init();
    
    solveBeam(table, width, height, q, s, &count);

    queue_clear(q);
    set_clear(s);

    resetTable(table, width, height);
    solveBeam2(table, width, height, &timeline);

    /* printf("Set size is: %d\n", set_size(s));
    printf("Queue size is: %d\n", q->alloc_size); */

    queue_destroy(q);
    set_destroy(s);
    printf("Part 1 answer is: %d\n", count);
    printf("Part 2 answer is: %llu\n", timeline);
  }

  /* Free */
  for (i = 0; i < height; i++) {
    free(table[i]);
  }

  free(table);

  return 0;
}