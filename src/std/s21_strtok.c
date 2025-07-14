#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *search_target;
  search_target = str ? str : search_target;

  for (; *search_target && s21_strchr(delim, *search_target); ++search_target) {
  }

  char *token_end = search_target;
  char *r = s21_NULL;
  bool match = false;

  for (; !match && *token_end; token_end += !match) {
    match = s21_strchr(delim, *token_end);
  }

  if (match || search_target != token_end) {
    r = search_target;
    *token_end = '\0';
  }

  search_target = token_end + match;

  return r;
}
