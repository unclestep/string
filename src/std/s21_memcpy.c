#include "s21_std.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  s21_byte_t *db = (s21_byte_t *)dest;
  const s21_byte_t *sb = (const s21_byte_t *)src;

  for (s21_size_t i = 0; i != n; ++i, ++db, ++sb) {
    *db = *sb;
  }

  return dest;
}
