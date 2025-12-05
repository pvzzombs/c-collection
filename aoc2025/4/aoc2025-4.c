#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int ** set_grid(int ** grid, char * buf, int width, int * height){
  int i;
  int ** g;
  if (grid == NULL) {
    grid = malloc(sizeof(int *) * 1);
    grid[0] = malloc(sizeof(int) * width);
    for (i = 0; i < width; i++) {
      if (buf[i] == '@') {
        grid[0][i] = 1;
      } else {
        grid[0][i] = 0;
      }
    }
    g = grid;
  } else {
    int ** newGrid = malloc(sizeof(int *) * (*height + 1));
    for (i = 0; i < *height; i++) {
      newGrid[i] = grid[i];
    }
    newGrid[*height] = malloc(sizeof(int) * width);
    for (i = 0; i < width; i++) {
      if (buf[i] == '@') {
        newGrid[*height][i] = 1;
      } else {
        newGrid[*height][i] = 0;
      }
    }
    g = newGrid;
    free(grid);
  }
  *height = *height + 1;
  return g;
}

void printGrid(int ** grid, int w, int h) {
  for (int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      if (grid[i][j] == 1) {
        printf("@");
      } else if (grid[i][j] == 2) {
        printf("x");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}

void resetGrid(int ** grid, int w, int h) {
  for (int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      if (grid[i][j] == 2) {
        grid[i][j] = 1;
      }
    }
  }
}

int choosePos(int ** g, int i, int j, int w, int h) {
  int x;
  int y;
  int count = 0;
  for (y = -1; y <= 1; y++) {
    for (x = -1; x <= 1; x++) {
      int ni = i + y;
      int nj = j + x;
      if (ni < 0 || nj < 0 || ni >= h || nj >= w || (x == 0 && y == 0)) {
        continue;
      } else {
        if (g[ni][nj] == 1 || g[ni][nj] == 2) {
          count++;
        }
      }
    }
  }
  return count;
}

void solveGrid1(int ** grid, int width, int height, int * count) {
  int i;
  int j;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (grid[i][j] == 1) {
        if (choosePos(grid, i, j, width, height) < 4) {
          *count = *count + 1;
          grid[i][j] = 2;
        }
      }
    }
  }
  // printGrid(grid, width, height);
}

void destroyTaken(int ** grid, int w, int h) {
  for (int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      if (grid[i][j] == 2) {
        grid[i][j] = 0;
      }
    }
  }
}

void solveGrid2(int ** grid, int width, int height, int * count) {
  int i;
  int j;
  int localCount = 0;
  while (1) {
    localCount = 0;
    // printGrid(grid, width, height);
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
        if (grid[i][j] == 1) {
          if (choosePos(grid, i, j, width, height) < 4) {
            localCount = localCount + 1;
            grid[i][j] = 2;
          }
        }
      }
    }
    if (localCount == 0) {
      break;
    }
    *count = *count + localCount;
    destroyTaken(grid, width, height);
  }
}

int main() {
  FILE * fptr;
  char buf[256];
  int ** grid = NULL;
  int height = 0;
  int width = 0;
  int i;
  int count1 = 0;
  int count2 = 0;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    while(fgets(buf, 256, fptr)) {
      if (strstr(buf, "\n") != NULL) {
        buf[strstr(buf, "\n") - buf] = 0;
      }
      if (width == 0) {
        width = strlen(buf);
        // printf("Width: %d\n", width);
      }
      if (strcmp(buf, "") != 0) {
        grid = set_grid(grid, buf, width, &height);
      }
    }

    fclose(fptr);

    // printGrid(grid, width, height);

    solveGrid1(grid, width, height, &count1);
    resetGrid(grid, width, height);
    solveGrid2(grid, width, height, &count2);

    printf("Part 1 answer is %d\n", count1);
    printf("Part 2 answer is %d\n", count2);
  }

  /* Free */

  for (i = 0; i < height; i++) {
    free(grid[i]);
  }

  free(grid);

  return 0;
}