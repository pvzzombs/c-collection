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
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
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

  int ** mat = NULL;
  int rows;
  int cols;
  scanf("%d %d", & rows, & cols);
  mat = (int ** ) malloc(rows * sizeof(int * ));
  for (int i = 0; i < rows; i++) {
    mat[i] = (int * ) malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      scanf("%d", & mat[i][j]);
    }
  }

  // for (int i = 0; i < rows; i++)
  // {
  //   for (int j = 0; j < cols; j++)
  //   {
  //     printf("%d", mat[i][j]);
  //   }
  //   printf("\n");
  // }

  printf("Number of islands: %d\n", countIslands(mat, rows, cols));

  for (int i = 0; i < rows; i++) {
    free(mat[i]);
  }
  free(mat);

  return 0;
}