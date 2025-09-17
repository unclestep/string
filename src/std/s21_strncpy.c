#include "../include/s21_std.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *dcur = dest;
  const char *scur = src;

  for (s21_size_t i = 0; i != n; ++i, ++dcur) {
    *dcur = *scur;
    scur = *scur ? scur + 1 : scur;
  }

  return dest;
}
