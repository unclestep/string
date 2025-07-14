#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  bool flag = src && str;
  char *r = s21_NULL;

  if (flag) {
    s21_size_t srcl = s21_strlen(src);
    s21_size_t strl = s21_strlen(str);

    r = malloc(srcl + strl + 1);
    flag = r && (start_index <= srcl);
  }

  if (flag) {
    char *rcur = r;
    const char *srccur = src;
    const char *strcur = str;

    for (; srccur != src + start_index; ++srccur, ++rcur) {
      *rcur = *srccur;
    }

    for (; *strcur; ++strcur, ++rcur) {
      *rcur = *strcur;
    }

    for (; *srccur; ++srccur, ++rcur) {
      *rcur = *srccur;
    }
    *rcur = '\0';
  }

  return flag ? (void *)r : s21_NULL;
}
