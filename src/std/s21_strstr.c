#include "s21_std.h"

char *s21_strstr(const char *haystack, const char *needle) {
  const char *hl = haystack;
  const char *hr = haystack;
  bool match = false;

  for (; !match && *hl;) {
    match = true;
    for (const char *ncur = needle; match && *hr && *ncur; ++hr, ++ncur) {
      match = *hr == *ncur;
    }

    if (!match || (!match && !*hr)) {
      hl = hr;
    }
  }

  return *hl ? (char *)hl : s21_NULL;
}
