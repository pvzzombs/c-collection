#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node_ {
  int x, y, z;
} Node;

typedef struct NodePair_ {
  Node u, v;
  int distance;
} NodePair;

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

void printCoord(Node n) {
  printf("Coord is x: %d, y: %d, z: %d", n.x, n.y, n.z);
}

void printAllCoords(Node * coords, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printCoord(coords[i]);
    printf("\n");
  }
}

int computeDistance(Node x, Node y) {
  int xdif = x.x - y.x;
  int ydif = x.y - y.y;
  int zdif = x.z - y.z;
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

      temp.distance = computeDistance(temp.u, temp.v);

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

void printNodePair(NodePair p) {
  printf("From coord %d %d %d to %d %d %d with dist of %d", p.u.x, p.u.y, p.u.z, p.v.x, p.v.y, p.v.z, p.distance);
}

void printCoordsPair(NodePair * p, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printNodePair(p[i]);
    printf("\n");
  }
}

int main() {
  FILE * fptr;
  char buf[128];
  Node * coords = malloc(sizeof(Node) * 1024);
  int coordsLen = 0;
  NodePair * coordsPair = malloc(sizeof(NodePair) * 128);
  int coordsPairLen = 0;
  int coordsPairAllocSize = 128;

  fptr = fopen("small.txt", "r");

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
    printCoordsPair(coordsPair, coordsPairLen);
    printf("Part 1 answer is: \n");
    printf("Part 2 answer is: \n");
  }

  /* Free */
  free(coords);
  free(coordsPair);

  return 0;
}