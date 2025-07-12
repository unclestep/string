#include "../include/s21_std.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dcur = dest;
  const char *scur = src;

  for (; *dcur; ++dcur) {
  }
  for (s21_size_t i = 0; i != n && *scur; ++dcur, ++scur, ++i) {
    *dcur = *scur;
  }
  *dcur = '\0';

  return dest;
}
