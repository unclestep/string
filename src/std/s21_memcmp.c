#include "../include/s21_std.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const s21_byte_t *sb1 = (const s21_byte_t *)str1;
  const s21_byte_t *sb2 = (const s21_byte_t *)str2;
  int r = 0;

  for (s21_size_t i = 0; r == 0 && i != n; ++i) {
    r = *(sb1 + i) - *(sb2 + i);
  }

  return r;
}
