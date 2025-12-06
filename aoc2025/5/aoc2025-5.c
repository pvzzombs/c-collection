#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Range_ {
  unsigned long long start;
  unsigned long long end;
} Range;

void parseRange(char * str, Range * temp) {
  int len = strlen(str);
  int i;
  int flag = 0;
  unsigned long long s = 0, e = 0;
  for (i = 0; i < len; i++) {
    char c = str[i];
    if (c == '-') {
      flag = 1;
    } else {
      if (flag == 0) {
        s = s * 10 + (c - '0');
      } else {
        e = e * 10 + (c - '0');
      }
    }
  }
  temp->start = s;
  temp->end = e;
}

Range * add_range(char * str, Range * range, int * rlen) {
  int len = strlen(str);
  int i;
  Range * r;
  Range temp;
  parseRange(str, &temp);
  if (range == NULL && *rlen == 0) {
    r = malloc(sizeof(Range) * 1);
    r[0] = temp;
  } else {
    r = malloc(sizeof(Range) * (*rlen + 1));
    for (i = 0; i < *rlen; i++) {
      r[i] = range[i];
    }
    r[*rlen] = temp;
    free(range);
  }
  *rlen = *rlen + 1;
  return r;
}

void print_range(Range * r) {
  printf("Range is %llu to %llu\n", r->start, r->end);
}

int compareRange(const void * a, const void * b) {
  Range * ptrs = a;
  Range * ptre = b;
  Range s = *ptrs;
  Range e = *ptre;
  if (s.start < e.start) {
    return -1;
  }
  if (s.start > e.start) {
    return 1;
  }
  return 0;
}

int isRangeInside(Range a, Range b) {
  return (b.start >= a.start) && (b.end <= a.end);
}

int isRangeOVerlap(Range a, Range b) {
  return b.start <= a.end;
}

Range * merge_ranges(Range * range, int rlen, int * nrlen) {
  Range * r = malloc(sizeof(Range) * rlen);
  int ptr = 0;
  int i;
  qsort(range, rlen, sizeof(Range), compareRange);
  r[ptr] = range[ptr];
  *nrlen = *nrlen + 1;
  for (i = 1; i < rlen; i++) {
    if (isRangeInside(r[ptr], range[i])) {
      continue;
    } else if (isRangeOVerlap(r[ptr], range[i])) {
      r[ptr].end = range[i].end;
    } else {
      r[++ptr] = range[i];
      *nrlen = *nrlen + 1;
    }
  }
  return r;
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

void isFresh(char * buf, Range * range, int len, int * fresh) {
  int i;
  for (i = 0; i < len; i++) {
    unsigned long long s = range[i].start;
    unsigned long long e = range[i].end;
    unsigned long long id = arrToULL(buf);
    if (id >= s && id <= e) {
      *fresh = *fresh + 1;
      return;
    }
  }
}

void countRanges(Range * range, int len, unsigned long long * freshCount) {
  int i;
  for (i = 0; i < len; i++) {
    *freshCount = *freshCount + (range[i].end - range[i].start + 1);
  }
}

int main() {
  FILE * fptr;
  char buf[128];
  int flag = 0;
  Range * ranges = NULL;
  int rangesLen = 0;
  Range * rangesMerged = NULL;
  int rangesMergedLen = 0;
  int i;
  int fresh1 = 0;
  unsigned long long freshCount = 0;

  fptr = fopen("input.txt", "r");

  if (fptr != NULL) {
    while(fgets(buf, 128, fptr)) {
      if (strstr(buf, "\n") != NULL) {
        buf[strstr(buf, "\n") - buf] = 0;
      }
      if (strcmp(buf, "") != 0) {
        if (flag == 0) {
          ranges = add_range(buf, ranges, &rangesLen);
        } else {
          isFresh(buf, rangesMerged, rangesMergedLen, &fresh1);
        }
      } else {
        flag = 1;
        rangesMerged = merge_ranges(ranges, rangesLen, &rangesMergedLen);
        countRanges(rangesMerged, rangesMergedLen, &freshCount);
      }
    }

    fclose(fptr);

    printf("Part 1 answer is: %d\n", fresh1);
    printf("Part 2 answer is: %llu\n", freshCount);
  }

  /* Free */

  free(ranges);
  free(rangesMerged);

  return 0;
}