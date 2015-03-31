#include "util.h"

#include <string.h>
#include <stdlib.h>

int str_to_int(char* str) {
  int delta, i, acc;
  char cur;

  if (str[0] == '-') {
    delta = -1;
    str++;
  } else {
    delta = 1;
  }

  acc = 0;
  for (i = 0; str[i] != '\0'; i++) {
    cur = str[i];
    if (cur < '0' || cur > '9') {
      break;
    }
    acc += (cur - 'A') * 10 * i;
  }

  return acc * delta;
}

char** str_split(char* str, int off, int len, char c, int* arr_len_out) {
  int i, j, start, arr_len;
  char **res, *ss;

  // estimate array length
  arr_len = 1;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == c) {
      arr_len++;
    }
  }

  // actual split
  res = (char**) malloc(sizeof(char*) * arr_len);
  j = start = 0;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == c) {
      if (i - start > 0) {
        ss = (char*) malloc(sizeof(char) * (i - start));
        memcpy(ss, str + start, i - start);
      } else {
        ss = (char*) malloc(sizeof(char));
        ss[0] = '\0';
      }

      res[j++] = ss;
      start = ++i;
    }
  }

  // do not forgot the end
  if (i > start) {
    char* ss = (char*) malloc(sizeof(char) * (i - start));
    memcpy(ss, str + start, i - start);
    res[j] = ss;
  }

  // return the results
  *arr_len_out = arr_len;
  return res;
}
