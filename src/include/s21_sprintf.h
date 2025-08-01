#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_defines.h"
#include "s21_std.h"

#define LONG_DOUBLE_MANTISSA_BITS 64
#define LONG_DOUBLE_EXPONENT_BITS 15
#define DOUBLE_MANTISSA_BITS 52
#define DOUBLE_EXPONENT_BITS 11

typedef struct ConvMods_t {
  bool minus;
  bool plus;
  bool space;
  bool hash;
  bool zero;
  int wid;
  int prec;
  int len;
  int spec;
} ConvMods_t;

typedef struct SizeChar_t {
  char *array;
  s21_size_t size;
  s21_size_t capacity;
} SizeChar_t;

typedef struct FloatDec128_t {
  uint128_t mantissa;
  int32_t exponent;
  bool sign;
} FloatDec128_t;

int s21_sprintf(char *str, const char *format, ...);
bool conversion_specification(char **scur, const char **fcur, int *written,
                              va_list *args);
bool get_modifiers(const char **fcur, ConvMods_t *mods, va_list *args);
void adjust_modifiers(ConvMods_t *mods);
bool handle_conversion(char **scur, int *written, ConvMods_t *mods,
                       va_list *args);
bool wcrtostr(SizeChar_t *array, ConvMods_t *mods, wchar_t *wc,
              s21_size_t wc_sz);
bool addwid(SizeChar_t *array, ConvMods_t *mods);
int intlen(long long i);
int uintlen(unsigned long i);

bool spec_c(char **scur, int *written, ConvMods_t *mods, va_list *args);
bool spec_s(char **scur, int *written, ConvMods_t *mods, va_list *args);
bool spec_di(char **scur, int *written, ConvMods_t *mods, va_list *args);
bool spec_o(char **scur, int *written, ConvMods_t *mods, va_list *args);
bool spec_xX(char **scur, int *written, ConvMods_t *mods, va_list *args);
bool spec_u(char **scur, int *written, ConvMods_t *mods, va_list *args);
// bool spec_f(char **scur, int *written, ConvMods_t *mods, va_list *args);
// bool spec_eE(char **scur, int *written, ConvMods_t *mods, va_list *args);
// bool spec_gG(char **scur, int *written, ConvMods_t *mods, va_list *args);
// bool spec_n(char **scur, int *written, ConvMods_t *mods, va_list *args);
bool spec_p(char **scur, int *written, ConvMods_t *mods, va_list *args);

FloatDec128_t ieeetodec(const uint128_t bits, const uint32_t mantissa_n_bits,
                        const uint32_t exponent_n_bits,
                        const bool explicit_leading_bit);

#endif
