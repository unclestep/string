#include "../include/s21_std.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const s21_byte_t *sb = (const s21_byte_t *)str; /* Search bytes */
  const s21_byte_t *esb = sb + n;                 /* End of search bytes */
  const s21_byte_t b = (const s21_byte_t)c;       /* Reference byte */
  void *r = s21_NULL;

  for (const s21_byte_t *cur = sb; !r && cur != esb; ++cur) {
    if (*cur == b) {
      r = (void *)cur;
    }
  }

  return r;
}
