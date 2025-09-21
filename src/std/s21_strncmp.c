#include "s21_std.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const unsigned char *cur1 = (const unsigned char *)str1;
  const unsigned char *cur2 = (const unsigned char *)str2;
  int r = 0;

  for (s21_size_t i = 0; !r && i != n && (*cur1 || *cur2);
       ++i, ++cur1, ++cur2) {
    r = *cur1 - *cur2;
  }

  return r;
}
