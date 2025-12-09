#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node_ {
  unsigned long long x, y, z;
  unsigned long long dist;
} Node;

typedef struct NodePair_ {
  Node u, v;
  unsigned long long distance;
} NodePair;

typedef struct NodeType_ {
  Node key;
  Node * value;
  int valueLen;
  int valueAllocLen;
} NodeType;

typedef struct AdjacencyList_ {
  NodeType * arr;
  int arrLen;
  int allocLen;
} AdjacencyList;

AdjacencyList * AL_init() {
  AdjacencyList * out = malloc(sizeof(AdjacencyList));
  out->arr = malloc(sizeof(NodeType) * 128);
  out->allocLen = 128;
  out->arrLen = 0;
  return out;
}

void AL_destroy(AdjacencyList * al) {
  int i;
  for (i = 0; i < al->arrLen; i++) {
    free(al->arr[i].value);
  }
  free(al->arr);
  free(al);
}

int AL_compareNode(Node * a, Node * b) {
  return (a->x == b->x) && (a->y == b->y) && (a->z == b->z);
}

void AL_add(AdjacencyList * al, Node * toCopy) {
  int i;
  /* Check if it exists */
  for (i = 0; i < al->arrLen; i++) {
    if (AL_compareNode(&(al->arr[i].key), toCopy)) {
      return;
    }
  }
  /* Does not exist, add it */
  if (al->arrLen == al->allocLen) {
    NodeType * arr = NULL;
    al->allocLen = al->allocLen * 2;
    arr = malloc(sizeof(NodeType) * al->allocLen);
    for (i = 0; i < al->arrLen; i++) {
      arr[i] = al->arr[i];
    }
    free(al->arr);
    al->arr = arr;
  }
  al->arr[al->arrLen].key.x = toCopy->x;
  al->arr[al->arrLen].key.y = toCopy->y;
  al->arr[al->arrLen].key.z = toCopy->z;
  al->arr[al->arrLen].valueAllocLen = 128;
  al->arr[al->arrLen].valueLen = 0;
  al->arr[al->arrLen].value = malloc(sizeof(Node) * 128);

  al->arrLen = al->arrLen + 1;
}

int AL_getIndex(AdjacencyList * al, Node * n) {
  int i;
  for (i = 0; i < al->arrLen; i++) {
    if (AL_compareNode(&(al->arr[i].key), n)) {
      return i;
    }
  }
  return -1;
}

void AL_push(AdjacencyList * al, Node * a, Node * b) {
  int aIndex = AL_getIndex(al, a);
  int bIndex = AL_getIndex(al, b);
  int i;
  if (al->arr[aIndex].valueLen == al->arr[aIndex].valueAllocLen) {
    al->arr[aIndex].valueAllocLen *= 2;
    Node * temp = malloc(sizeof(Node) * al->arr[aIndex].valueAllocLen);
    for (i = 0; i < al->arr[aIndex].valueLen; i++) {
      temp[i] = al->arr[aIndex].value[i];
    }
    free(al->arr[aIndex].value);
    al->arr[aIndex].value = temp;
  }

  if (al->arr[bIndex].valueLen == al->arr[bIndex].valueAllocLen) {
    al->arr[bIndex].valueAllocLen *= 2;
    Node * temp = malloc(sizeof(Node) * al->arr[bIndex].valueAllocLen);
    for (i = 0; i < al->arr[bIndex].valueLen; i++) {
      temp[i] = al->arr[bIndex].value[i];
    }
    free(al->arr[bIndex].value);
    al->arr[bIndex].value = temp;
  }

  al->arr[aIndex].value[al->arr[aIndex].valueLen].x = b->x;
  al->arr[aIndex].value[al->arr[aIndex].valueLen].y = b->y;
  al->arr[aIndex].value[al->arr[aIndex].valueLen].z = b->z;

  al->arr[bIndex].value[al->arr[bIndex].valueLen].x = a->x;
  al->arr[bIndex].value[al->arr[bIndex].valueLen].y = a->y;
  al->arr[bIndex].value[al->arr[bIndex].valueLen].z = a->z;

  al->arr[aIndex].valueLen += 1;
  al->arr[bIndex].valueLen += 1;
}

void AL_addEdge(AdjacencyList * al, Node * a, Node * b) {
  AL_add(al, a);
  AL_add(al, b);
  AL_push(al, a, b);
}

void printCoord(Node * n) {
  printf("Coord is x: %d, y: %d, z: %d", n->x, n->y, n->z);
}

void AL_print(AdjacencyList * al) {
  int len = al->arrLen;
  int i;
  int j;
  for (i = 0; i < len; i++) {
    printCoord(&(al->arr[i].key));
    printf("\nNodes:");
    for (j = 0; j < al->arr[i].valueLen; j++) {
      printCoord(&(al->arr[i].value[j]));
      printf(";");
    }
    printf("\n");
  }
}

void parseCoords(char * buf, Node * coords, int * clen) {
  Node temp;
  int flag = 0;
  int len = strlen(buf);
  int i;
  temp.x = 0;
  temp.y = 0;
  temp.z = 0;

  for (i = 0; i < len; i++) {
    char c = buf[i];
    if (c == ',') {
      if (flag == 0) {
        flag = 1;
      } else if (flag == 1) {
        flag = 2;
      }
    } else {
      if (flag == 0) {
        temp.x = temp.x * 10 + (c - '0');
      } else if (flag == 1) {
        temp.y = temp.y * 10 + (c - '0');
      } else if (flag == 2) {
        temp.z = temp.z * 10 + (c - '0');
      }
    }
  }

  coords[*clen] = temp;
  *clen = *clen + 1;
}

void printAllCoords(Node * coords, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printCoord(&coords[i]);
    printf("\n");
  }
}

unsigned long long computeDistance(Node * x, Node * y) {
  unsigned long long xdif = x->x - y->x;
  unsigned long long ydif = x->y - y->y;
  unsigned long long zdif = x->z - y->z;
  return (xdif * xdif) + (ydif * ydif) + (zdif * zdif);
}

NodePair * build_coords_pair(Node * coords, int coordsLen, NodePair * p, int * len, int * allocSize) {
  int i, j;
  int x;
  NodePair * out = p;
  for (i = 0; i < coordsLen; i++) {
    for (j = i + 1; j < coordsLen; j++) {
      NodePair temp;
      temp.u.x = coords[i].x;
      temp.u.y = coords[i].y;
      temp.u.z = coords[i].z;

      temp.v.x = coords[j].x;
      temp.v.y = coords[j].y;
      temp.v.z = coords[j].z;

      temp.distance = computeDistance(&temp.u, &temp.v);

      /* Push */
      if (*len == *allocSize) {
        NodePair * temp2;
        *allocSize = *allocSize * 2;
        temp2 = malloc(sizeof(NodePair) * (*allocSize));
        for (x = 0; x < *len; x++) {
          temp2[x] = out[x];
        }
        free(out);
        out = temp2;
      }
      out[*len] = temp;
      *len = *len + 1;
    }
  }

  return out;
}

void printNodePair(NodePair *p) {
  printf("From coord %d %d %d to %d %d %d with dist of %llu", p->u.x, p->u.y, p->u.z, p->v.x, p->v.y, p->v.z, p->distance);
}

void printCoordsPair(NodePair * p, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printNodePair(&p[i]);
    printf("\n");
  }
}

int sortByDistance(const void * a, const void * b) {
  const NodePair * p1 = a;
  const NodePair * p2 = b;
  if (p1->distance < p2->distance) {
    return -1;
  }
  if (p1->distance > p2->distance) {
    return 1;
  }
  return 0;
}

void sortCoordsPair(NodePair * p, int len) {
  qsort(p, len, sizeof(NodePair), sortByDistance);
}

void tryBuildAL(AdjacencyList * al, Node * arr, int len) {
  int i;
  for (i = 0; i < len; i++) {
    AL_add(al, &(arr[i]));
  }
}

void joinEdges(AdjacencyList * al, NodePair * p, int len, int stop) {
  int i;
  if (len < stop) {
    stop = len;
  }
  for (i = 0; i < stop; i++) {
    AL_addEdge(al, &(p[i].u), &(p[i].v));
  }
}

typedef struct NodeSet_ {
  Node * arr;
  int len;
  int allocLen;
} NodeSet;

NodeSet * NodeSet_init() {
  NodeSet * out = malloc(sizeof(NodeSet));
  out->allocLen = 128;
  out->len = 0;
  out->arr = malloc(sizeof(Node) * 128);
  return out;
}

void NodeSet_destroy(NodeSet * set) {
  free(set->arr);
  free(set);
}

void NodeSet_push(NodeSet * set, Node n) {
  int i;
  if (set->len == set->allocLen) {
    Node * temp = NULL;
    set->allocLen *= 2;
    temp = malloc(sizeof(Node) * set->allocLen);
    for (i = 0; i < set->len; i++) {
      temp[i] = set->arr[i];
    }
    free(set->arr);
    set->arr = temp;
  }
  for (i = 0; i < set->len; i++) {
    if (AL_compareNode(&(set->arr[i]), &n)) {
      return;
    }
  }
  set->arr[set->len] = n;
  set->len += 1;
}

int NodeSet_exists(NodeSet * set, Node n) {
  int i;
  for (i = 0; i < set->len; i++) {
    if (AL_compareNode(&(set->arr[i]), &n)) {
      return 1;
    }
  }
  return 0;
}

void visitNode(AdjacencyList * al, NodeSet * s, int * count, Node n) {
  if (NodeSet_exists(s, n)) {
    return ;
  }
  *count += 1;
  NodeSet_push(s, n);
  int i;
  int index = AL_getIndex(al, &n);
  for (i = 0; i < al->arr[index].valueLen; i++) {
    visitNode(al, s, count, al->arr[index].value[i]);
  }
}

void keepJoiningNodes(Node * arr, int arrLen, NodePair * p,  int pLen, int * product) {
  NodeSet * s = NodeSet_init();
  AdjacencyList * al = AL_init();

  int i;
  for (i = 0; i < arrLen; i++) {
    AL_add(al, &(arr[i]));
  }

  int j = 0;
  int count;

  while(j < pLen) {
    s->len = 0;
    count = 0;
    AL_addEdge(al, &(p[j].u), &(p[j].v));
    visitNode(al, s, &count, p[j].u);
    if (count == arrLen) {
      /* printf("Noice!\n");
      printCoord(&(p[j].u));
      printf("\n");
      printCoord(&(p[j].v));
      printf("\n"); */
      *product = p[j].u.x * p[j].v.x;
      break;
    }
    j++;
  }

  AL_destroy(al);
  NodeSet_destroy(s);
}

int sortInts(const void * a, const void * b) {
  const int * m = a;
  const int * n = b;
  return *n - *m;
}

void countConnected(AdjacencyList * al, NodeSet * set, int * product) {
  int * arr = malloc(sizeof(int) * al->arrLen);
  int len = al->arrLen;
  int i;
  int count;
  for (i = 0; i < len; i++) {
    count = 0;
    visitNode(al, set, &count, al->arr[i].key);
    arr[i] = count;
  }
  qsort(arr, al->arrLen, sizeof(int), sortInts);
  for(int i = 0; i < 3; i++) {
    *product *= arr[i];
  }
  free(arr);
}

int main() {
  FILE * fptr;
  char buf[128];
  Node * coords = malloc(sizeof(Node) * 1024);
  int coordsLen = 0;
  NodePair * coordsPair = malloc(sizeof(NodePair) * 128);
  int coordsPairLen = 0;
  int coordsPairAllocSize = 128;
  AdjacencyList * AL;
  NodeSet * nodeSet;
  int product = 1;
  int product2 = 1;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    while(fgets(buf, 128, fptr)) {
      if (strstr(buf, "\n") != NULL) {
        buf[strstr(buf, "\n") - buf] = 0;
      }
      if (strcmp(buf, "") != 0) {
        parseCoords(buf, coords, &coordsLen);
      }
    }

    fclose(fptr);

    /* printAllCoords(coords, coordsLen); */
    coordsPair = build_coords_pair(coords, coordsLen, coordsPair, &coordsPairLen, &coordsPairAllocSize);
    sortCoordsPair(coordsPair, coordsPairLen);
    
    AL = AL_init();
    nodeSet = NodeSet_init();
    
    tryBuildAL(AL, coords, coordsLen);
    joinEdges(AL, coordsPair, coordsPairLen, 1000);
    countConnected(AL, nodeSet, &product);
    keepJoiningNodes(coords, coordsLen, coordsPair, coordsPairLen, &product2);
    
    printf("Part 1 answer is: %d\n", product);
    printf("Part 2 answer is: %d\n", product2);
  }

  /* Free */
  free(coords);
  free(coordsPair);
  NodeSet_destroy(nodeSet);
  AL_destroy(AL);

  return 0;
}