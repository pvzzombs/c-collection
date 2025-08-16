#include <stdio.h>
#include <stdlib.h>

void search(int ** mat, int i, int j, int rows, int cols, int * islandSize) {
  if (i < 0 || j < 0 || i >= rows || j >= cols || mat[i][j] == 0 || mat[i][j] == 2) {
    return;
  }
  if (mat[i][j] == 1) {
    ++( * islandSize);
    mat[i][j] = 2;
    // top
    search(mat, i - 1, j, rows, cols, islandSize);
    // bottom
    search(mat, i + 1, j, rows, cols, islandSize);
    // left
    search(mat, i, j - 1, rows, cols, islandSize);
    // Right
    search(mat, i, j + 1, rows, cols, islandSize); 
  }
}

int countIslands(int ** mat, int rows, int cols) {
  int count = 0;
  int islandSize = 0;
  int i;
  for (i = 0; i < rows; i++) {
    int j;
    for (j = 0; j < cols; j++) {
      search(mat, i, j, rows, cols, & islandSize);
      if (islandSize > 0) {
        count++;
        islandSize = 0;
      }
    }
  }
  return count;
}

int main() {
  int testcases;
  int ** mat = NULL;
  int rows;
  int cols;
  int * testcasesResult = NULL;
  int i;

  scanf("%d", &testcases);

  testcasesResult = malloc(testcases * sizeof(int));

  for (i = 0; i < testcases; i++) {
    int x;
    scanf("%d %d", & rows, & cols);
    mat = (int ** ) malloc(rows * sizeof(int * ));
    for (x = 0; x < rows; x++) {
      int j;
      mat[i] = (int * ) malloc(cols * sizeof(int));
      for (j = 0; j < cols; j++) {
        scanf("%d", & mat[x][j]);
      }
    }

    // printf("Number of islands: %d\n", countIslands(mat, rows, cols));
    testcasesResult[i] = countIslands(mat, rows, cols);

    for (x = 0; x < rows; x++) {
      free(mat[i]);
    }
    free(mat);
  }

  for (i = 0; i < testcases; i++) {
    printf("%d\n", testcasesResult[i]);
  }

  free(testcasesResult);
  return 0;
}