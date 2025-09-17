#include "../include/s21_std.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *dest = str1;
  bool match = false;

  for (; !match && *dest;) {
    for (const char *breakset = str2; !match && *breakset; ++breakset) {
      match = *dest == *breakset;
    }
    dest = match ? dest : dest + 1;
  }

  return !*dest ? s21_NULL : (char *)dest;
}
