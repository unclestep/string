#include "s21_std.h"

char *s21_strrchr(const char *str, int c) {
  const unsigned char *cur = (const unsigned char *)str;
  const unsigned char *last_match = s21_NULL;
  char ch = (char)c;

  for (; *cur; ++cur) {
    last_match = *cur == ch ? cur : last_match;
  }

  return !ch ? (char *)cur : (char *)last_match;
}
