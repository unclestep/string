#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  bool flag = str;
  char *r = s21_NULL;

  if (flag) {
    r = malloc(s21_strlen(str) + 1);
    flag = r;
  }

  if (flag) {
    const char *cur = str;
    char *rcur = r;

    for (; *cur; ++cur, ++rcur) {
      *rcur = *cur >= 'a' && *cur <= 'z' ? *cur - CASE_SHIFT : *cur;
    }
    *rcur = '\0';
  }

  return flag ? (void *)r : s21_NULL;
}
