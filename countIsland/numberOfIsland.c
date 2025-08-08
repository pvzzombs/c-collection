// Leetcode Solution

void search(char ** grid, int i, int j, int rows, int cols, int * islandSize) {
  if (i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] == '0' || grid[i][j] == '2') {
    return ;
  }
  if (grid[i][j] == '1') {
    ++(*islandSize);
    grid[i][j] = '2';
    // top
    search(grid, i - 1, j, rows, cols, islandSize);
    // bottom
    search(grid, i + 1, j, rows, cols, islandSize);
    // left
    search(grid, i, j - 1, rows, cols, islandSize);
    // Right
    search(grid, i, j + 1, rows, cols, islandSize); 
  }
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
  int count = 0;
  int islandSize = 0;
  int rows = gridSize;
  int cols = gridColSize[0];
  for(int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      search(grid, i, j, rows, cols, &islandSize);
      if (islandSize > 0) {
        count++;
        islandSize = 0;
      }
    }
  }
  return count;
}