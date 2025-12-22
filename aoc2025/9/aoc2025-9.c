#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define HORIZONTAL_EDGE 1
#define VERTICAL_EDGE 2

typedef struct Node_ {
  int x, y;
} Node;

typedef struct NodeArray_ {
  Node * arr;
  int len;
  int allocLen;
} NodeArray;

typedef struct TwoPoints_ {
  int p1x, p1y, p2x, p2y;
  int type;
} TwoPoints;

typedef struct TwoPointsArray_ {
  TwoPoints * arr;
  int len;
  int allocLen;
} TwoPointsArray;

NodeArray * NodeArray_init() {
  NodeArray * out = NULL;
  out = malloc(sizeof(NodeArray));
  out->arr = NULL;
  out->allocLen = 1024;
  out->arr = malloc(sizeof(Node) * 1024);
  out->len = 0;
  return out;
}

void NodeArray_destroy(NodeArray * n) {
  free(n->arr);
  free(n);
}

void NodeArray_push(NodeArray * arr, Node * n) {
  int i;
  if (arr->len == arr->allocLen) {
    arr->allocLen = arr->allocLen * 2;
    Node * temp = malloc(sizeof(Node) * arr->allocLen);
    for (i = 0; i < arr->len; i++) {
      temp[i] = arr->arr[i];
    }
    free(arr->arr);
    arr->arr = temp;
  }
  arr->arr[arr->len].x = n->x;
  arr->arr[arr->len].y = n->y;
  arr->len = arr->len + 1;
}

int NodeArray_exists(NodeArray * arr, Node * n) {
  int i;
  for (i = 0; i < arr->len; i++) {
    if (arr->arr[i].x == n->x && arr->arr[i].y == n->y) {
      return 1;
    }
  }
  return 0;
}

TwoPointsArray * TwoPointsArray_init() {
  TwoPointsArray * out = NULL;
  out = malloc(sizeof(TwoPointsArray));
  out->arr = NULL;
  out->allocLen = 1024;
  out->arr = malloc(sizeof(TwoPoints) * 1024);
  out->len = 0;
  return out;
}

void TwoPointsArray_destroy(TwoPointsArray * obj) {
  free(obj->arr);
  free(obj);
}

void TwoPointsArray_push(TwoPointsArray * obj, TwoPoints * p) {
  int i;
  if (obj->len == obj->allocLen) {
    obj->allocLen = obj->allocLen * 2;
    TwoPoints * arr = malloc(sizeof(TwoPoints) * obj->allocLen);
    for (i = 0; i < obj->len; i++) {
      arr[i] = obj->arr[i];
    }
    free(obj->arr);
    obj->arr = arr;
  }
  obj->arr[obj->len].p1x = p->p1x;
  obj->arr[obj->len].p1y = p->p1y;
  obj->arr[obj->len].p2x = p->p2x;
  obj->arr[obj->len].p2y = p->p2y;
  obj->arr[obj->len].type = p->type;
  obj->len = obj->len + 1;
}

void parseLine(char * buf, NodeArray * arr) {
  int len = strlen(buf);
  int i;
  int flag = 0;

  arr->arr[arr->len].x = 0;
  arr->arr[arr->len].y = 0;

  for (i = 0; i < len; i++) {
    char c = buf[i];
    if (c == ',') {
      flag = 1;
    } else {
      if (flag == 0) {
        arr->arr[arr->len].x = arr->arr[arr->len].x * 10 + (c - '0');
      } else if (flag == 1) {
        arr->arr[arr->len].y = arr->arr[arr->len].y * 10 + (c - '0');
      }
    }
  }

  arr->len = arr->len + 1;
}

void parseEdges(TwoPointsArray * t, NodeArray * arr, Node * temp) {
  TwoPoints a;
  a.p1x = temp->x;
  a.p1y = temp->y;
  a.p2x = arr->arr[arr->len - 1].x;
  a.p2y = arr->arr[arr->len - 1].y;
  if (a.p1x == a.p2x) {
    a.type = VERTICAL_EDGE;
  }
  if (a.p1y == a.p2y) {
    a.type = HORIZONTAL_EDGE;
  }
  TwoPointsArray_push(t, &a);
  temp->x = arr->arr[arr->len - 1].x;
  temp->y = arr->arr[arr->len - 1].y;
}

void printNode(Node * n) {
  printf("Node x: %d y: %d", n->x, n->y);
}

void printNodeArr(Node * arr, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printNode(&(arr[i]));
    printf("\n");
  }
}

void getLargestArea(NodeArray * arr, unsigned long long * area) {
  int i, j;
  unsigned long long maxArea = 0;
  for(i = 0; i < arr->len; i++) {
    for(j = i + 1; j < arr->len; j++) {
      unsigned long long width = abs(arr->arr[i].x - arr->arr[j].x) + 1;
      unsigned long long height = abs(arr->arr[i].y - arr->arr[j].y) + 1;
      unsigned long long a = width * height;
      if (a > maxArea) {
        maxArea = a;
      }
    }
  }
  *area = maxArea;
}

int sortEdges(const void * a, const void * b) {
  const TwoPoints * m = a;
  const TwoPoints * n = b;
  if (m->p1x < n->p1x) {
    return -1;
  } else if (m->p1x > n->p1x) {
    return 1;
  } else {
    if (m->p1y < n->p1y) {
      return -1;
    } else if (m->p1y > n->p1y) {
      return 1;
    }
  }
  return 0;
}

void buildEdges(NodeArray * arr, TwoPointsArray * twoArr) {
  int i, j;
  for (i = 0; i < arr->len; i++) {
    for (j = i + 1; j < arr->len; j++) {
      TwoPoints t;
      Node temp;
      Node a = arr->arr[i];
      Node b = arr->arr[j];
      if (b.x < a.x || (a.x == b.x && b.y < a.y)) {
        temp = a;
        a = b;
        b = temp;
      }
      if (a.x == b.x) {
        t.p1x = a.x;
        t.p1y = a.y;
        t.p2x = b.x;
        t.p2y = b.y;
        t.type = VERTICAL_EDGE;
        TwoPointsArray_push(twoArr, &t);
      } else if (a.y == b.y) {
        t.p1x = a.x;
        t.p1y = a.y;
        t.p2x = b.x;
        t.p2y = b.y;
        t.type = HORIZONTAL_EDGE;
        TwoPointsArray_push(twoArr, &t);
      }
    }
  }
  qsort(twoArr->arr, twoArr->len, sizeof(TwoPoints), sortEdges);
}

void fixEdges(TwoPointsArray * t) {
  int i;
  for (i = 0; i < t->len; i++) {
    if (t->arr[i].p2x < t->arr[i].p1x || (t->arr[i].p1x == t->arr[i].p2x && t->arr[i].p2y < t->arr[i].p1y)) {
      int tempX = t->arr[i].p1x;
      int tempY = t->arr[i].p1y;
      t->arr[i].p1x = t->arr[i].p2x;
      t->arr[i].p1y = t->arr[i].p2y;
      t->arr[i].p2x = tempX;
      t->arr[i].p2y = tempY;
    }
  }
  qsort(t->arr, t->len, sizeof(TwoPoints), sortEdges);
}

int isPointInsidePolygon(TwoPointsArray * t, Node * a, Node * b) {
  int stop1 = 0;
  int stop2 = 0;
  int count1 = 0;
  int count2 = 0;
  int i;

  int aLastX = 0;
  int bLastX = 0;
  int aLastY = 0;
  int bLastY = 0;

  for (i = 0; i < t->len; i++) {
    if (!stop1) {
      if (a->x < t->arr[i].p1x) {
        stop1 = 1;
      } else {
        if (t->arr[i].type == HORIZONTAL_EDGE ) {
          if (a->y == t->arr[i].p1y) {
            if (a->x >= t->arr[i].p1x && a->x <= t->arr[i].p2x) {
              stop1 = 1;
              count1 = 1;
            } else {
              if (aLastX != t->arr[i].p1x) {
                count1 += 1;
              }
              aLastX = t->arr[i].p2x;
            }
          }
        } else if (t->arr[i].type == VERTICAL_EDGE) {
          if (a->y >= t->arr[i].p1y && a->y <= t->arr[i].p2y) {
            if (a->x == t->arr[i].p1x) {
              stop1 = 1;
              count1 = 1;
            } else {
              count1 += 1;
            }
          }
        }
      }
    }
    
    if (!stop2) {
      if (b->x < t->arr[i].p1x) {
        stop2 = 1;
      } else {
        if (t->arr[i].type == HORIZONTAL_EDGE ) {
          if (b->y == t->arr[i].p1y) {
            if (b->x >= t->arr[i].p1x && b->x <= t->arr[i].p2x) {
              stop2 = 1;
              count2 = 1;
            } else {
              if (bLastX != t->arr[i].p1x) {
                count2 += 1;
              }
              bLastX = t->arr[i].p2x;
            }
          }
        } else if (t->arr[i].type == VERTICAL_EDGE) {
          if (b->y >= t->arr[i].p1y && b->y <= t->arr[i].p2y) {
            if (b->x == t->arr[i].p1x) {
              stop2 = 1;
              count2 = 1;
            } else {
              count2 += 1;
            }
          }
        }
      }
    }

    if (stop1 && stop2) {
      break;
    }
  }
  if (count1 % 2 > 0 && count2 % 2 > 0) {
    return 1;
  }
  return 0;
}

void useRayCast(NodeArray * n, TwoPointsArray * t, unsigned long long * area) {
  int i, j;
  unsigned long long maxArea = 0;
  for (i = 0; i < n->len; i++) {
    for (j = i + 1; j < n->len; j++) {
      Node temp;
      Node a = n->arr[i];
      Node b = n->arr[j];
      if (b.x < a.x || (a.x == b.x && b.y < a.y)) {
        temp = a;
        a = b;
        b = temp;
      }
      Node c = a;
      Node d = a;
      c.x = b.x;
      d.y = b.y;
      int result = isPointInsidePolygon(t, &c, &d);
      if (result) {
        unsigned long long width = abs(n->arr[i].x - n->arr[j].x) + 1;
        unsigned long long height = abs(n->arr[i].y - n->arr[j].y) + 1;
        unsigned long long a = width * height;
        if (a > maxArea) {
          maxArea = a;
        }
      }
    }
  }
  *area = maxArea;
}

int sortEdgesByY(const void * a, const void * b) {
  const TwoPoints * m = a;
  const TwoPoints * n = b;
  if (m->p1y < n->p1y) {
    return -1;
  } else if (m->p1y > n->p1y) {
    return 1;
  } else {
    if (m->p1x < n->p1x) {
      return -1;
    } else if (m->p1x > n->p1x) {
      return 1;
    }
  }
  return 0;
}

int sortEdgesByX(const void * a, const void * b) {
  const TwoPoints * m = a;
  const TwoPoints * n = b;
  if (m->p1x < n->p1x) {
    return -1;
  } else if (m->p1x > n->p1x) {
    return 1;
  }
  return 0;
}

int isEdgeInside(TwoPoints * m, TwoPoints * n) {
  return (n->p1x >= m->p1x) && (n->p2x <= m->p2x);
}

int isEdgeOverlapStrict(TwoPoints * m, TwoPoints * n) {
  return n->p1x < m->p2x;
}

int scanArea(TwoPointsArray * t, Node * a, Node * b) {
  Node topLeft = *a;
  Node bottomRight = *b;
  if (topLeft.y > bottomRight.y) {
    Node newTopLeft = topLeft;
    Node newBottomRight = topLeft;
    newTopLeft.y = bottomRight.y;
    newBottomRight.x = bottomRight.x;
    topLeft = newTopLeft;
    bottomRight = newBottomRight;
  }
  Node topRight = *a;
  Node bottomLeft = *a;
  topRight.x = bottomRight.x;
  bottomLeft.y = bottomRight.y;
  qsort(t->arr, t->len, sizeof(TwoPoints), sortEdgesByY);

  TwoPoints top, bottom;
  int topOkay = 0, bottomOkay = 0;
  top.p1x = topLeft.x;
  top.p1y = topLeft.y;
  top.p2x = topRight.x;
  top.p2y = topRight.y;

  bottom.p1x = bottomLeft.x;
  bottom.p1y = bottomLeft.y;
  bottom.p2x = bottomRight.x;
  bottom.p2y = bottomRight.y;
  int i;
  int j;
  int target = 0;

  if (topLeft.x == 2 && topLeft.y == 3 && bottomRight.x == 9 && bottomRight.y == 5) {
    target = 1;
  }

  TwoPointsArray * tempArr = TwoPointsArray_init();
  for (i = 0; i < t->len; i++) {
    TwoPoints temp = t->arr[i];
    int isOverlapOrInside = 0;
    if (temp.type != HORIZONTAL_EDGE) { continue; }

    for (j = 0; j < tempArr->len; j++) {
      TwoPoints arrElement = tempArr->arr[j];
      if (isEdgeInside(&arrElement, &temp)) {
        isOverlapOrInside = 1;
        break;
      } else if (temp.p1x < arrElement.p1x) {
        if (isEdgeOverlapStrict(&temp, &arrElement)) {
          isOverlapOrInside = 1;
          break;
        }
      } else if (arrElement.p1x < temp.p1x) {
        if (isEdgeOverlapStrict(&arrElement, &temp)) {
          isOverlapOrInside = 1;
          break;
        }
      }
    }

    if (!isOverlapOrInside) {
      TwoPointsArray_push(tempArr, &temp);
      qsort(tempArr->arr, tempArr->len, sizeof(TwoPoints), sortEdgesByX);
    }

    if (!topOkay && top.p1y == temp.p1y) {
      int started = 0;
      int ended = 0;
      int indexStart = -1, indexEnd = -1;
      for (j = 0; j < tempArr->len; j++) {
        TwoPoints arrElement = tempArr->arr[j];
        if (!started && top.p1x >= arrElement.p1x && top.p1x <= arrElement.p2x && top.p1y >= arrElement.p1y) {
          started = 1;
          indexStart = j;
        }
        if (!ended && top.p2x >= arrElement.p1x && top.p2x <= arrElement.p2x && top.p1y >= arrElement.p1y) {
          ended = 1;
          indexEnd = j;
        }
      }

      if (!started || !ended) {
        TwoPointsArray_destroy(tempArr);
        return 0;
      }

      for (j = indexStart + 1; j <= indexEnd; j++) {
        TwoPoints arrElement = tempArr->arr[j];
        TwoPoints arrElementPrev = tempArr->arr[j - 1];
        if (arrElementPrev.p2x != arrElement.p1x) {
          TwoPointsArray_destroy(tempArr);
          return 0;
        }
      }

      topOkay = 1;
    }

    if (topOkay && !bottomOkay && bottom.p1y == temp.p1y) {
      int started = 0;
      int ended = 0;
      int indexStart = -1, indexEnd = -1;
      for (j = 0; j < tempArr->len; j++) {
        TwoPoints arrElement = tempArr->arr[j];
        if (!started && bottom.p1x >= arrElement.p1x && bottom.p1x <= arrElement.p2x && bottom.p1y >= arrElement.p1y) {
          started = 1;
          indexStart = j;
        }
        if (!ended && bottom.p2x >= arrElement.p1x && bottom.p2x <= arrElement.p2x && bottom.p1y >= arrElement.p1y) {
          ended = 1;
          indexEnd = j;
        }
      }

      if (!started || !ended) {
        TwoPointsArray_destroy(tempArr);
        return 0;
      }

      for (j = indexStart + 1; j <= indexEnd; j++) {
        TwoPoints arrElement = tempArr->arr[j];
        TwoPoints arrElementPrev = tempArr->arr[j - 1];
        if (arrElementPrev.p2x != arrElement.p1x) {
          TwoPointsArray_destroy(tempArr);
          return 0;
        }
      }

      bottomOkay = 1;
      return 1;
    }

    if (isOverlapOrInside) {
      if (topOkay) {
        if (bottom.p1y > temp.p1y) {
          if (isEdgeInside(&bottom, &temp) || isEdgeInside(&temp, &bottom) || isEdgeOverlapStrict(&bottom, &temp) || isEdgeOverlapStrict(&temp, &bottom)) {
            TwoPointsArray_destroy(tempArr);
            return 0;
          }
        }
      }
      int started = 0;
      int ended = 0;
      int indexStart = -1, indexEnd = -1;
      TwoPointsArray * newArr = TwoPointsArray_init();
      for (j = 0; j < tempArr->len; j++) {
        TwoPoints arrElement = tempArr->arr[j];
        if (!started && temp.p1x >= arrElement.p1x && temp.p1x <= arrElement.p2x && temp.p1y >= arrElement.p1y) {
          started = 1;
          indexStart = j;
        }
        if (!ended && temp.p2x >= arrElement.p1x && temp.p2x <= arrElement.p2x && temp.p1y >= arrElement.p1y) {
          ended = 1;
          indexEnd = j;
        }
      }

      if (!started || !ended) {
        TwoPointsArray_destroy(tempArr);
        TwoPointsArray_destroy(newArr);
        return 0;
      }

      for (j = 0; j < tempArr->len; j++) {
        TwoPoints arrElement = tempArr->arr[j];
        if (j == indexStart) {
          if (arrElement.p1x != temp.p1x) {
            TwoPoints newElement;
            newElement.p1x = arrElement.p1x;
            newElement.p2x = temp.p1x;
            newElement.p1y = arrElement.p1y;
            newElement.p2y = arrElement.p2y;
            TwoPointsArray_push(newArr, &newElement);
          } else {
            TwoPointsArray_push(newArr, &arrElement);
          }
        }
        if (indexStart != indexEnd && j == indexEnd) {
          if (arrElement.p2x != temp.p2x) {
            TwoPoints newElement;
            newElement.p1x = temp.p2x;
            newElement.p2x = arrElement.p2x;
            newElement.p1y = arrElement.p1y;
            newElement.p2y = arrElement.p2y;
            TwoPointsArray_push(newArr, &newElement);
          } else {
            TwoPointsArray_push(newArr, &arrElement);
          }
        }
        if (j > indexStart && j < indexEnd) {
          continue;
        } else {
          TwoPointsArray_push(newArr, &arrElement);
        }
      }
      tempArr->len = 0;
      for (j = 0; j < newArr->len; j++) {
        TwoPointsArray_push(tempArr, &(newArr->arr[j]));
      }
      qsort(tempArr->arr, tempArr->len, sizeof(TwoPoints), sortEdgesByX);
      TwoPointsArray_destroy(newArr);
    }

  }
  TwoPointsArray_destroy(tempArr);
  return 1;
}

void solve2(NodeArray * n, TwoPointsArray * t, unsigned long long * area) {
  int i, j;
  unsigned long long maxArea = 0;
  for (i = 0; i < n->len; i++) {
    for (j = i + 1; j < n->len; j++) {
      Node temp;
      Node a = n->arr[i];
      Node b = n->arr[j];
      if (b.x < a.x || (a.x == b.x && b.y < a.y)) {
        temp = a;
        a = b;
        b = temp;
      }
      int result = scanArea(t, &a, &b);
      if (result) {
        unsigned long long width = abs(a.x - b.x) + 1;
        unsigned long long height = abs(a.y - b.y) + 1;
        unsigned long long a = width * height;
        if (a > maxArea) {
          maxArea = a;
        }
      }
    }
  }
  *area = maxArea;
}

int NodeArraySortByX(const void * a, const void * b) {
  const Node * n1 = a;
  const Node * n2 = b;
  if (n1->x < n2->x) {
    return -1;
  }
  if (n1->x > n2->x) {
    return 1;
  }
  return 0;
}

int NodeArraySortByY(const void * a, const void * b) {
  const Node * n1 = a;
  const Node * n2 = b;
  if (n1->y < n2->y) {
    return -1;
  }
  if (n1->y > n2->y) {
    return 1;
  }
  return 0;
}

void floodFill(int ** grid, int h, int w, int y, int x) {
  if (x < 0 || x >= w || y < 0 || y >= h || grid[y][x] == 1) {
    return;
  }
  if (grid[y][x] == 0) {
    grid[y][x] = 2;

    floodFill(grid, h, w, y + 1, x);
    floodFill(grid, h, w, y - 1, x);
    floodFill(grid, h, w, y, x + 1);
    floodFill(grid, h, w, y, x - 1);
  }
}

void solve3(TwoPointsArray * t, NodeArray * n, unsigned long long * area) {
  int i, j, k, l;
  unsigned long long maxArea = 0;
  NodeArray * nCopy = NodeArray_init();
  int * XcoordToIndex = malloc(sizeof(int) * 100000);
  int * YcoordToIndex = malloc(sizeof(int) * 100000);
  int indexX = 0;
  int indexY = 0;
  int ** grid = NULL;
  for (i = 0; i < n->len; i++) {
    NodeArray_push(nCopy, &(n->arr[i]));
  }
  qsort(nCopy->arr, nCopy->len, sizeof(Node), NodeArraySortByX);
  for (i = 0; i < nCopy->len; i++) {
    if (i > 0 && nCopy->arr[i - 1].x == nCopy->arr[i].x) {
      continue;
    }
    XcoordToIndex[nCopy->arr[i].x] = indexX;
    indexX++;
  }
  qsort(nCopy->arr, nCopy->len, sizeof(Node), NodeArraySortByY);
  for (i = 0; i < nCopy->len; i++) {
    if (i > 0 && nCopy->arr[i - 1].y == nCopy->arr[i].y) {
      continue;
    }
    YcoordToIndex[nCopy->arr[i].y] = indexY;
    indexY++;
  }

  grid = malloc(sizeof(int *) * (indexY + 2));
  for (i = 0; i < indexY + 2; i++) {
    grid[i] = malloc(sizeof(int) * (indexX + 2));
    for (j = 0; j < indexX + 2; j++) {
      grid[i][j] = 0;
    }
  }

  for (i = 0; i < t->len; i++) {
    int indexX1 = XcoordToIndex[t->arr[i].p1x] + 1;
    int indexY1 = YcoordToIndex[t->arr[i].p1y] + 1;
    int indexX2 = XcoordToIndex[t->arr[i].p2x] + 1;
    int indexY2 = YcoordToIndex[t->arr[i].p2y] + 1;
    if (indexX1 == indexX2) {
      for (j = indexY1; j <= indexY2; j++) {
        grid[j][indexX1] = 1;
      }
    }
    if (indexY1 == indexY2) {
      for (j = indexX1; j <= indexX2; j++) {
        grid[indexY1][j] = 1;
      }
    }
  }

  floodFill(grid, indexY + 2 , indexX + 2, 0, 0);

  for (i = 0; i < n->len; i++) {
    for (j = i + 1; j < n->len; j++) {
      Node temp;
      Node a = n->arr[i];
      Node b = n->arr[j];
      if (b.x < a.x || (a.x == b.x && b.y < a.y)) {
        temp = a;
        a = b;
        b = temp;
      }
      Node topLeft = a;
      Node bottomRight = b;  
      if (topLeft.y > bottomRight.y) {
        Node newTopLeft = topLeft;
        Node newBottomRight = topLeft;
        newTopLeft.y = bottomRight.y;
        newBottomRight.x = bottomRight.x;
        topLeft = newTopLeft;
        bottomRight = newBottomRight;
      }
      int indexX1 = XcoordToIndex[topLeft.x] + 1;
      int indexX2 = XcoordToIndex[bottomRight.x] + 1;
      int indexY1 = YcoordToIndex[topLeft.y] + 1;
      int indexY2 = YcoordToIndex[bottomRight.y] + 1;

      int stop = 0;
      for (k = indexY1; k <= indexY2; k++) {
        for (l = indexX1; l <= indexX2; l++) {
          if (grid[k][l] == 2) {
            stop = 1;
            break;
          }
        }
        if (stop) {
          break;
        }
      }
      if (!stop) {
        unsigned long long width = abs(n->arr[i].x - n->arr[j].x) + 1;
        unsigned long long height = abs(n->arr[i].y - n->arr[j].y) + 1;
        unsigned long long a = width * height;
        if (a > maxArea) {
          maxArea = a;
        }
      }
    }
  }
  *area = maxArea;
  NodeArray_destroy(nCopy);
  for (i = 0; i < indexY + 2; i++) {
    free(grid[i]);
  }
  free(grid);
  free(XcoordToIndex);
  free(YcoordToIndex);
}

int main() {
  FILE * fptr;
  char buf[128];
  unsigned long long area = 0;
  unsigned long long area2 = 0;
  NodeArray * nodeArray = NodeArray_init();
  TwoPointsArray * twoPointsArr = TwoPointsArray_init();
  Node temp;
  temp.x = 0;
  temp.y = 0;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    while(fgets(buf, 128, fptr)) {
      if (strstr(buf, "\n") != NULL) {
        buf[strstr(buf, "\n") - buf] = 0;
      }
      if (strcmp(buf, "") != 0) {
        parseLine(buf, nodeArray);
        parseEdges(twoPointsArr, nodeArray, &temp);
      }
    }

    fclose(fptr);

    twoPointsArr->arr[0].p1x = temp.x;
    twoPointsArr->arr[0].p1y = temp.y;
    if (twoPointsArr->arr[0].p1x == twoPointsArr->arr[0].p2x) {
      twoPointsArr->arr[0].type = VERTICAL_EDGE;
    }
    if (twoPointsArr->arr[0].p1y == twoPointsArr->arr[0].p2y) {
      twoPointsArr->arr[0].type = HORIZONTAL_EDGE;
    }

    getLargestArea(nodeArray, &area);
    fixEdges(twoPointsArr);
    solve3(twoPointsArr, nodeArray, &area2);

    printf("Part 1 answer is: %llu\n", area);
    printf("Part 2 answer is: %llu\n", area2);
  }

  /* Free */
  NodeArray_destroy(nodeArray);
  TwoPointsArray_destroy(twoPointsArr);

  return 0;
}