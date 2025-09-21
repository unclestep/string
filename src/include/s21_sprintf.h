#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_defines.h"
#include "s21_gmp.h"
#include "s21_std.h"

/* Helpers */
bool wcrtostr(sc_t *mb, conv_t *mods, wchar_t *wc, s21_size_t wc_sz);
bool addwid(sc_t *arr, conv_t *mods);
int intlen(long long i);
int uintlen(unsigned long long i);
void flttostr(char *dst, const uint128_t bits, const uint32_t manbits,
              const uint32_t expbits, const bool explicit_leading_bit,
              conv_t *mods);

/* Main Functions */
int s21_sprintf(char *str, const char *format, ...);
bool tostr(char **scur, const char **fcur, int *written, va_list *args);
bool get_convmods(const char **fcur, conv_t *mods, va_list *args);
void adjust_convmods(conv_t *mods);
bool convert(char **scur, int *written, conv_t *mods, va_list *args);

bool spec_c(char **scur, int *written, conv_t *mods, va_list *args);
bool spec_s(char **scur, int *written, conv_t *mods, va_list *args);
bool spec_di(char **scur, int *written, conv_t *mods, va_list *args);
bool spec_o(char **scur, int *written, conv_t *mods, va_list *args);
bool spec_xX(char **scur, int *written, conv_t *mods, va_list *args);
bool spec_u(char **scur, int *written, conv_t *mods, va_list *args);
bool spec_feEgG(char **scur, int *written, conv_t *mods, va_list *args);
bool spec_n(char **scur, int *written, conv_t *mods, va_list *args);
bool spec_p(char **scur, int *written, conv_t *mods, va_list *args);

#endif
