#include "../include/s21_std.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  s21_byte_t *sb = (s21_byte_t *)str;
  s21_byte_t b = (s21_byte_t)c;

  for (s21_size_t i = 0; i != n; ++i) {
    *(sb + i) = b;
  }

  return str;
}
