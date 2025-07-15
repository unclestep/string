#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  bool flag = src && trim_chars;
  s21_size_t srcl = src ? s21_strlen(src) : 0;
  char *r = s21_NULL;

  if (flag) {
    r = malloc(srcl + 1);
    flag = r;
  }

  if (flag) {
    const char *lsrc = src;
    const char *rsrc = src + srcl - 1;
    char *rcur = r;

    for (; *lsrc && s21_strchr(trim_chars, *lsrc); ++lsrc) {
    }

    for (; lsrc <= rsrc && s21_strchr(trim_chars, *rsrc); --rsrc) {
    }

    for (; lsrc <= rsrc; ++lsrc, ++rcur) {
      *rcur = *lsrc;
    }
    *rcur = '\0';
  }

  return flag ? r : s21_NULL;
}
