#include "s21_std.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t nlen = s21_strlen(needle);
  int *lsp = calloc(nlen, sizeof(int));
  int is_error = !lsp;

  s21_size_t l = 0, r = 1;
  while (!is_error && r < nlen) {
    if (needle[l] == needle[r]) {
      lsp[r++] = ++l;
    } else {
      if (l) {
        l = lsp[l - 1];
      } else {
        lsp[r++] = 0;
      }
    }
  }

  s21_size_t i = 0, j = 0;
  while (!is_error && haystack[i] && needle[j]) {
    if (haystack[i] == needle[j]) {
      ++i, ++j;
    } else {
      if (j) {
        j = lsp[j - 1];
      } else {
        ++i;
      }
    }
  }

  if (lsp) free(lsp);
  return j == nlen && !is_error ? (char *)(haystack + (i - j)) : s21_NULL;
}
