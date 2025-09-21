#include "s21_std.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const s21_byte_t *cur = (const s21_byte_t *)str;
  const s21_byte_t b = (const s21_byte_t)c;
  void *r = s21_NULL;

  for (s21_size_t i = 0; !r && i != n; ++i, ++cur) {
    if (*cur == b) {
      r = (void *)cur;
    }
  }

  return r;
}
