#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <limits.h>
#include <locale.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_defines.h"
#include "s21_std.h"

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

bool spec_c(char **scur, int *written, ConvMods_t *mods, va_list *args);
bool spec_s(char **scur, int *written, ConvMods_t *mods, va_list *args);
bool spec_di(char **scur, int *written, ConvMods_t *mods, va_list *args);
// void spec_o(char **scur, int *written, ConvMods_t *mods, va_list *args);
// void spec_xX(char **scur, int *written, ConvMods_t *mods, va_list *args);
// void spec_u(char **scur, int *written, ConvMods_t *mods, va_list *args);
// void spec_f(char **scur, int *written, ConvMods_t *mods, va_list *args);
// void spec_eE(char **scur, int *written, ConvMods_t *mods, va_list *args);
// void spec_gG(char **scur, int *written, ConvMods_t *mods, va_list *args);
// void spec_n(char **scur, int *written, ConvMods_t *mods, va_list *args);
// void spec_p(char **scur, int *written, ConvMods_t *mods, va_list *args);

#endif
