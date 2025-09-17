#include "../include/s21_std.h"

char *s21_strchr(const char *str, int c) {
  const unsigned char *cur = (const unsigned char *)str;
  char ch = (char)c;

  for (; *cur && ch != *cur; ++cur) {
  }

  return !ch || *cur ? (char *)cur : s21_NULL;
}
