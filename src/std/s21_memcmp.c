#include "s21_std.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const s21_byte_t *cur1 = (const s21_byte_t *)str1;
  const s21_byte_t *cur2 = (const s21_byte_t *)str2;
  int r = 0;

  for (s21_size_t i = 0; !r && i != n; ++i, ++cur1, ++cur2) {
    r = *cur2 - *cur2;
  }

  return r;
}
