#include "s21_std.h"

char *s21_strcat(char *dest, const char *src) {
  char *dcur = dest;
  const char *scur = src;

  for (; *dcur; ++dcur) {
  }
  for (; *scur; ++dcur, ++scur) {
    *dcur = *scur;
  }
  *dcur = '\0';

  return dest;
}
