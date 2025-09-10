#include "Problem5.h"

void appendStr(char *dest, char c);
char *shaveStr(char *in);

void strXpos(char *dest, const char *src) {
  // base case
  if (src[0] == '\0' || src[1] == '\0') {
    appendStr(dest, src[0]);
    if (src[1] == '\0') {
      appendStr(dest, src[1]);
    }
    return;
  }
  // build the new string
  char first = src[1];
  char second = src[0];
  appendStr(dest, first);
  appendStr(dest, second);
  // and recurse further
  return strXpos(dest, src + 2);
}

void appendStr(char *dest, char c) {
  if (*dest == '\0') {
    *dest = c;
    dest++;
    *dest = '\0';
    return;
  }
  appendStr(dest + 1, c);
}
