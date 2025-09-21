#include "s21_std.h"

int s21_strcmp(const char *str1, const char *str2) {
  const unsigned char *cur1 = (const unsigned char *)str1;
  const unsigned char *cur2 = (const unsigned char *)str2;
  int r = 0;

  for (; !r && (*cur1 || *cur2); ++cur1, ++cur2) {
    r = *cur1 - *cur2;
  }

  return r;
}
