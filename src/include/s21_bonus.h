#ifndef S21_BONUS_H
#define S21_BONUS_H

#include "s21_defines.h"

#define CASE_SHIFT 32

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif
