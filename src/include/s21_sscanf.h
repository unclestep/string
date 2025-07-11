#ifndef SSCANF_H
#define SSCANF_H

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "s21_defines.h"

#define ALL 0
#define DECIMAL 10
#define OCTAL 8
#define HEX 16
struct Specifier {
  char sup;
  char len;
  char conspec;
};

struct State {
  char error;
  const char **formatp;
  int count;
  s21_size_t stri;
  struct Specifier conspec;
};

int s21_sscanf(const char *str, const char *format, ...);

void s21_scan(const char *str, va_list *args, struct State *state);
void s21_setspec(struct State *state);
void s21_validate(struct State *state);
void s21_convert(const char *str, va_list *args, struct State *state);
void s21_convert_c(const char *str, va_list *args, struct State *state);
void s21_convert_n(va_list *args, struct State *state);
void s21_convert_pe(const char *str, struct State *state);
void s21_convert_f(const char *str, va_list *args, struct State *state);
void s21_convert_i_sig(const char *str, va_list *args, struct State *state,
                       int base);
void s21_convert_i_unsig(const char *str, va_list *args, struct State *state,
                         int base);
void s21_convert_p(const char *str, va_list *args, struct State *state);
void s21_convert_s(const char *str, va_list *args, struct State *state);
void s21_convert_s_helper(const char *str, va_list *args, struct State *state);
void s21_convert_ws_helper(const char *str, va_list *args, struct State *state);
#endif
