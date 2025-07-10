#include "s21_string.h"
#define s21_setargi(TYPE, FUNCTION, BASE)                \
  {                                                      \
    TYPE arg;                                            \
    arg = FUNCTION(str_start, &str_end, BASE);           \
    if (str_start == str_end) {                          \
      state->error = 1;                                  \
    }                                                    \
    if (!state->conspec.sup && (str_start != str_end)) { \
      TYPE *argp = va_arg(*args, TYPE *);                \
      *argp = arg;                                       \
    }                                                    \
  }
#define s21_setargf(TYPE, FUNCTION)                      \
  {                                                      \
    TYPE arg;                                            \
    arg = FUNCTION(str_start, &str_end);                 \
    if (str_start == str_end) {                          \
      state->error = 1;                                  \
    }                                                    \
    if (!state->conspec.sup && (str_start != str_end)) { \
      TYPE *argp = va_arg(*args, TYPE *);                \
      *argp = arg;                                       \
    }                                                    \
  }
#define s21_updatestate()          \
  {                                \
    if (!state->error) {           \
      state->stri = str_end - str; \
      if (!state->conspec.sup) {   \
        ++state->count;            \
      }                            \
    }                              \
  }
#define s21_updatecount()                         \
  {                                               \
    if (!str[state->stri] && state->count == 0) { \
      state->count = -1;                          \
    }                                             \
  }

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  struct State state = {0};
  state.formatp = &format;

  while (**state.formatp && !state.error) {
    s21_scan(str, &args, &state);
    ++*state.formatp;
  }
  va_end(args);
  return state.count;
}

void s21_scan(const char *str, va_list *args, struct State *state) {
  if (**state->formatp == '%') {
    s21_setspec(state);
    if (!state->error) {
      s21_convert(str, args, state);
    }
  } else if (isgraph(**state->formatp)) {
    if (str[state->stri] == **state->formatp) {
      ++state->stri;
    } else {
      state->error = 1;
    }
  }
  if (isspace(**state->formatp)) {
    while (isspace(str[state->stri])) {
      ++state->stri;
    }
  }
}

void s21_setspec(struct State *state) {
  ++*state->formatp;
  state->conspec.sup = 0;
  state->conspec.len = 0;
  state->conspec.conspec = 0;
  if (**state->formatp == '*') {
    state->conspec.sup = 1;
    ++*state->formatp;
  }
  if (**state->formatp == 'l' || **state->formatp == 'L' ||
      **state->formatp == 'h') {
    state->conspec.len = **state->formatp;
    ++*state->formatp;
  }
  state->conspec.conspec = **state->formatp;
  s21_validate(state);
}

void s21_validate(struct State *state) {
  char f = state->conspec.conspec;
  char sup = state->conspec.sup;
  if (f == 'c' || f == 'd' || f == 'i' || f == 'e' || f == 'E' || f == 'f' ||
      f == 'g' || f == 'G' || f == 'o' || f == 's' || f == 'u' || f == 'x' ||
      f == 'X' || f == 'p' || f == 'n' || f == '%') {
    ;
  } else {
    state->error = 1;
  }
  if (f == 'n' && sup) {
    state->error = 1;
  }
}

void s21_convert(const char *str, va_list *args, struct State *state) {
  char cs = state->conspec.conspec;
  while (isspace(str[state->stri]) && cs != 'n' && cs != 'c') {
    ++state->stri;
  }
  if (cs == '%') {
    s21_convert_pe(str, state);
  }
  if (cs == 'c') {
    s21_convert_c(str, args, state);
  }
  if (cs == 'n') {
    s21_convert_n(args, state);
  }
  if (cs == 'e' || cs == 'E' || cs == 'f' || cs == 'g' || cs == 'G') {
    s21_convert_f(str, args, state);
  }
  if (cs == 'd') {
    s21_convert_i_sig(str, args, state, DECIMAL);
  }
  if (cs == 'i') {
    s21_convert_i_sig(str, args, state, ALL);
  }
  if (cs == 'o') {
    s21_convert_i_unsig(str, args, state, OCTAL);
  }
  if (cs == 'u') {
    s21_convert_i_unsig(str, args, state, DECIMAL);
  }
  if (cs == 'x' || cs == 'X') {
    s21_convert_i_unsig(str, args, state, HEX);
  }
  if (cs == 'p') {
    s21_convert_p(str, args, state);
  }
  if (cs == 's') {
    s21_convert_s(str, args, state);
  }
}

void s21_convert_pe(const char *str, struct State *state) {
  if (str[state->stri] == '%') {
    ++state->stri;
  } else {
    state->error = 1;
  }
}

void s21_convert_c(const char *str, va_list *args, struct State *state) {
  if (!str[state->stri]) {
    state->error = 1;
  }
  s21_updatecount();
  switch (state->conspec.len) {
    case 'l': {
      mbstate_t mbstate;
      s21_memset(&mbstate, 0, sizeof mbstate);
      int rc;
      if (!state->error && !state->conspec.sup) {
        wchar_t *pwc = va_arg(*args, wchar_t *);
        rc = mbrtowc(pwc, str + state->stri, s21_strlen(str + state->stri) + 1,
                     &mbstate);
        ++state->count;
      }
      if (!state->error && state->conspec.sup) {
        rc = mbrtowc(s21_NULL, str + state->stri,
                     s21_strlen(str + state->stri) + 1, &mbstate);
      }
      if (!state->error) {
        state->stri += rc;
      }
      break;
    }
    default:
      if (!state->error && !state->conspec.sup) {
        char *c = va_arg(*args, char *);
        *c = str[state->stri];
        ++state->count;
      }
      if (!state->error) {
        ++state->stri;
      }
      break;
  }
}

void s21_convert_n(va_list *args, struct State *state) {
  if (!state->conspec.sup) {
    s21_size_t *diff = va_arg(*args, s21_size_t *);
    *diff = state->stri;
  }
}

void s21_convert_f(const char *str, va_list *args, struct State *state) {
  char *str_end;
  const char *str_start = str + state->stri;
  s21_updatecount();
  switch (state->conspec.len) {
    case 'L':
      s21_setargf(long double, strtold);
      break;
    case 'l':
      s21_setargf(double, strtod);
      break;
    default:
      s21_setargf(float, strtof);
      break;
  }
  s21_updatestate();
}

void s21_convert_i_sig(const char *str, va_list *args, struct State *state,
                       int base) {
  char *str_end;
  const char *str_start = str + state->stri;
  s21_updatecount();
  switch (state->conspec.len) {
    case 'h':
      s21_setargi(signed short, strtol, base);
      break;
    case 'l':
      s21_setargi(signed long, strtol, base);
      break;
    default:
      s21_setargi(signed int, strtol, base);
      break;
  }
  s21_updatestate();
}

void s21_convert_i_unsig(const char *str, va_list *args, struct State *state,
                         int base) {
  char *str_end;
  const char *str_start = str + state->stri;
  s21_updatecount();
  switch (state->conspec.len) {
    case 'h':
      s21_setargi(unsigned short, strtoul, base);
      break;
    case 'l':
      s21_setargi(unsigned long, strtoul, base);
      break;
    default:
      s21_setargi(unsigned int, strtoul, base);
      break;
  }
  s21_updatestate();
}

void s21_convert_p(const char *str, va_list *args, struct State *state) {
  char *str_end;
  const char *str_start = str + state->stri;
  s21_updatecount();
  s21_setargi(uintptr_t, strtoull, HEX);
  s21_updatestate();
}

void s21_convert_s(const char *str, va_list *args, struct State *state) {
  if (!str[state->stri]) {
    state->error = 1;
  }
  s21_updatecount();
  switch (state->conspec.len) {
    case 'l':
      s21_convert_ws_helper(str, args, state);
      break;
    default:
      s21_convert_s_helper(str, args, state);
      break;
  }
}

void s21_convert_ws_helper(const char *str, va_list *args,
                           struct State *state) {
  if (!state->error) {
    mbstate_t mbstate;
    s21_memset(&mbstate, 0, sizeof mbstate);
    int rc;
    if (!state->conspec.sup) {
      wchar_t *pwc = va_arg(*args, wchar_t *);
      while ((rc = mbrtowc(pwc, str + state->stri,
                           s21_strlen(str + state->stri) + 1, &mbstate)) > 0 &&
             iswgraph(*pwc)) {
        ++pwc;
        state->stri += rc;
      }
      *pwc = '\0';
      ++state->count;
    }
    if (state->conspec.sup) {
      wchar_t pwc;
      while ((rc = mbrtowc(&pwc, str + state->stri,
                           s21_strlen(str + state->stri) + 1, &mbstate)) > 0 &&
             iswgraph(pwc)) {
        state->stri += rc;
      }
    }
  }
}

void s21_convert_s_helper(const char *str, va_list *args, struct State *state) {
  if (!state->error && !state->conspec.sup) {
    char *dest = va_arg(*args, char *);
    while (isgraph(str[state->stri])) {
      *(dest++) = str[state->stri++];
    }
    *dest = '\0';
    ++state->count;
  }
  if (!state->error && state->conspec.sup) {
    while (isgraph(str[state->stri++])) {
      ;
    }
  }
}