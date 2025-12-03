#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mod(int a, int b) {
  while (a < 0) {
    a += b;
  }
  return a % b;
}

void movelock(char * str, int * lock, int * password) {
  if (str[0] == 'L') {
    int move = atoi(str + 1);
    *lock = mod(*lock - move, 100);
  } else if (str[0] == 'R') {
    int move = atoi(str + 1);
    *lock = mod(*lock + move, 100);
  }
  if (*lock == 0) {
    *password = *password + 1;
  }
}

void spin(char c, int move, int *lock, int * password) {
  int i = 0;
  if (c == 'L') {
    while (i < move) {
      *lock = *lock - 1;
      if (*lock == -1) {
        *lock = 99;
      }
      if (*lock == 0) { *password = *password + 1; }
      i++;
    }
  } else if (c == 'R') {
    while (i < move) {
      *lock = *lock + 1;
      if (*lock == 100) {
        *lock = 0;
      }
      if (*lock == 0) { *password = *password + 1; }
      i++;
    }
  } else {
    printf("Warning!");
  }
}

void movelock3(char * str, int * lock, int * password) {
  int move = atoi(str + 1);
  spin(str[0], move, lock, password);
}

/* Does not work */
void movelock2(char * str, int * lock, int * password) {
  int move;
  if (str[0] == 'L') {
    move = atoi(str + 1);
    int temp = *lock - move;
    while (temp < 0) {
      temp += 100;
      *password = *password + 1;
    }
    *lock = temp;
  } else if (str[0] == 'R') {
    move = atoi(str + 1);
    int temp = *lock + move;
    while (temp >= 100) {
      temp -= 100;
      *password = *password + 1;
    }
    *lock = temp;
  }
}



int main() {
  FILE * fptr;
  char buf[128];
  int lock1 = 50;
  int password1 = 0;
  int lock2 = 50;
  int password2 = 0;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    while(fgets(buf, 128, fptr)) {
      buf[strstr(buf, "\n") - buf] = 0;
      if (strcmp(buf, "") != 0) {
        movelock(buf, &lock1, &password1);
        movelock3(buf, &lock2, &password2);
      }
    }

    fclose(fptr);

    printf("Part 1 password: %d\n", password1);
    printf("Part 2 password: %d\n", password2);
  }

  return 0;
}