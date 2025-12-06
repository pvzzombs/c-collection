#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long ** genTable(char * buf, unsigned long long ** table, int * width, int * height) {
  int len = strlen(buf);
  unsigned long long * row = NULL;
  unsigned long long * rowTemp = NULL;
  unsigned long long ** t;
  int i, j;
  unsigned long long temp = 0;
  int w = 0;

  for (i = 0; i < len; i++) {
    char c = buf[i];
    if (c == ' ') {
      if (temp != 0) {
        /* push to row */
        if (row == NULL) {
          w = w + 1;
          row = malloc(sizeof(unsigned long long) * w);
          row[0] = temp;
        } else {
          rowTemp = malloc(sizeof(unsigned long long) * (w + 1));
          for(j = 0; j < w; j++) {
            rowTemp[j] = row[j];
          }
          rowTemp[w] = temp;
          w = w + 1;
          free(row);
          row = rowTemp;
        }
        temp = 0;
      }
    } else {
      if (c >= '0' && c <= '9') {
        temp = temp * 10 + (c - '0');
      } else {
        if (c == '+') {
          temp = 1;
        } else if (c == '*') {
          temp = 2;
        } else {
          temp = 3;
        }
      }
    }
  }

  if (temp != 0) {
    /* push to row */
    if (row == NULL) {
      w = w + 1;
      row = malloc(sizeof(unsigned long long) * w);
      row[0] = temp;
    } else {
      rowTemp = malloc(sizeof(unsigned long long) * (w + 1));
      for(j = 0; j < w; j++) {
        rowTemp[j] = row[j];
      }
      rowTemp[w] = temp;
      w = w + 1;
      free(row);
      row = rowTemp;
    }
    temp = 0;
  }

  if (table == NULL && *height == 0) {
    t = malloc(sizeof(unsigned long long *) * 1);
    t[0] = row;
  } else {
    t = malloc(sizeof(unsigned long long *) * (*height + 1));
    for (i = 0; i < *height; i++) {
      t[i] = table[i];
    }
    t[*height] = row;
  }

  if (*width == 0) {
    *width = w;
  }
  *height = *height + 1;
  free(table);
  return t;
}

void printTable(unsigned long long ** table, int w, int h) {
  int i, j;
  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      printf("%llu ", table[i][j]);
    }
    printf("\n");
  }
}

void solveTable(unsigned long long ** table, int w, int h, unsigned long long* sum) {
  int i, j;
  unsigned long long result = 0;
  int op = 0;
  for (j = 0; j < w; j++) {
    /* Sum */
    if (table[h - 1][j] == 1) {
      result = 0;
      op = 0;
    } else if (table[h - 1][j] == 2) {
      /* Product */
      result = 1;
      op = 1;
    }
    for (i = 0; i < h - 1; i++) {
      if (op == 0) {
        result = result + table[i][j];
      } else if (op == 1) {
        result = result * table[i][j];
      }
    }
    *sum += result;
  }
}

char ** gemTable2(char * str, char ** table, int * height) {
  int len = strlen(str);
  char ** t;
  int i;
  if (table == NULL) {
    t = malloc(sizeof(char *) * 1);
    t[0] = strdup(str);
    for (i = 0; i < len; i++) {
      if (t[0][i] == ' ') {
        t[0][i] = '0';
      }
    }
  } else {
    t = malloc(sizeof(char *) * (*height + 1));
    for(i = 0; i < *height; i++) {
      t[i] = table[i];
    }
    t[*height] = strdup(str);
    for (i = 0; i < len; i++) {
      if (t[*height][i] == ' ') {
        t[*height][i] = '0';
      }
    }
  }
  *height = *height + 1;
  free(table);
  return t;
}

void printTable2(char ** table, int height) {
  int i;
  for (i = 0; i < height; i++) {
    printf("%s\n", table[i]);
  }
}

unsigned long long arrToULL(char * buf) {
  int len = strlen(buf);
  unsigned long long num = 0;
  int i = 0;
  for (i = 0; i < len; i++) {
    num = num * 10 + (buf[i] - '0');
  }
  return num;
}

void solveTable2(char ** table, int height, int w, unsigned long long * sum) {
  int len = strlen(table[height - 1]);
  /* Parse the last line, the operators line */
  int i, j, tstart = 0, ostart;
  unsigned long long * arr = malloc(sizeof(unsigned long long) * w);
  int ptr = 0;
  unsigned long long count = 0;
  for (i = 0; i < len; i++) {
    char c = table[height - 1][i];
    if (c == '+' || c == '*') {
      if (i == 0) {
        continue;
      } else {
        count++;
        arr[ptr] = count - 1;
        count = 0;
        ptr++;
      }
    } else {
      count++;
    }
  }

  count++;
  arr[ptr] = count;
  count = 0;
  ptr++;

  for (i = 0; i < w; i++) {
    int op = 0;
    unsigned long long result = 0;
    if (table[height - 1][tstart] == '+') {
      op = 1;
      result = 0;
    } else if (table[height - 1][tstart] == '*') {
      op = 2;
      result = 1;
    }
    int start = tstart + arr[i] - 1;
    int stop = arr[i];
    unsigned long long num = 0;
    while (stop > 0) {
      num = 0;
      for (j = 0; j < height - 1; j++) {
        if (table[j][start] != '0') {
          num = num * 10 + (table[j][start] - '0');
        }
      }
      if (op == 1) {
        result += num;
      } else if (op == 2) {
        result *= num;
      }
      stop--;
      start--;
    }
    tstart += arr[i] + 1;
    arr[i] = result;
    *sum = *sum + result;
  }

  free(arr);
}

int main() {
  FILE * fptr;
  char buf[4096];
  unsigned long long ** table = NULL;
  char ** table2 = NULL;
  int table2Height = 0;
  int width = 0;
  int height = 0;
  int i;
  unsigned long long sum = 0;
  unsigned long long sum2 = 0;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    while(fgets(buf, 4096, fptr)) {
      if (strstr(buf, "\n") != NULL) {
        buf[strstr(buf, "\n") - buf] = 0;
      }
      if (strcmp(buf, "") != 0) {
        table = genTable(buf, table, &width, &height);
        table2 = gemTable2(buf, table2, &table2Height);
      }
    }

    fclose(fptr);
    solveTable(table, width, height, &sum);
    solveTable2(table2, table2Height, width, &sum2);
    printf("Part 1 answer is: %llu\n", sum);
    printf("Part 2 answer is: %llu\n", sum2);
  }

  /* Free */
  for(i = 0; i < height; i++) {
    free(table[i]);
  }

  for (i = 0; i < table2Height; i++) {
    free(table2[i]);
  }
  free(table);
  free(table2);

  return 0;
}