#include "../include/s21_std.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *cur = str1;
  s21_size_t max_len = 0;
  s21_size_t cur_len = 0;

  for (; *cur; ++cur) {
    bool match = false;

    for (const char *forbid = str2; !match && *forbid; ++forbid) {
      match = *cur == *forbid;
    }

    max_len = match && max_len < cur_len ? cur_len : max_len;
    cur_len = match ? 0 : cur_len + 1;
  }

  return max_len;
}
