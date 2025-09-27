#include "s21_std.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;

  for (; str1[i] && !s21_strchr(str2, str1[i]); ++i) {
  }

  return i;
}
