#include "s21_sprintf.h"

#define getintarg(INT_TYPE, ARG)                                          \
  do {                                                                    \
    if (mods->len == 'h') {                                               \
      ARG = (INT_TYPE long)((INT_TYPE short)va_arg(*args, INT_TYPE int)); \
    } else if (mods->len == 'l') {                                        \
      ARG = (INT_TYPE long)va_arg(*args, INT_TYPE long);                  \
    } else if (mods->len == -1) {                                         \
      ARG = (INT_TYPE long)va_arg(*args, INT_TYPE int);                   \
    }                                                                     \
  } while (0)

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *scur = str;
  const char *fcur = format;
  int written = 0;
  bool is_error = false;

  for (; !is_error && *fcur; ++fcur) {
    if (*fcur == '%') {
      is_error = tostr(&scur, &fcur, &written, &args);
    } else {
      *scur++ = *fcur;
      ++written;
    }
  }

  *scur = '\0';
  va_end(args);

  return is_error ? -1 : written;
}

bool tostr(char **scur, const char **fcur, int *written, va_list *args) {
  bool is_error = false;
  conv_t mods = {.minus = 0,
                 .plus = 0,
                 .space = 0,
                 .hash = 0,
                 .zero = 0,
                 .wid = -1,
                 .prec = -1,
                 .len = -1,
                 .spec = -1};

  is_error = get_convmods(fcur, &mods, args);
  if (!is_error) {
    adjust_convmods(&mods);
    is_error = convert(scur, written, &mods, args);
  }
  return is_error;
}

bool get_convmods(const char **fcur, conv_t *mods, va_list *args) {
  ++*fcur;
  bool is_error = false;
  char ch = '\0';

  for (; (ch = **fcur) && (s21_strchr("-+ #0", ch)); ++*fcur) {
    if (ch == '-')
      mods->minus = true;
    else if (ch == '+')
      mods->plus = true;
    else if (ch == ' ')
      mods->space = true;
    else if (ch == '#')
      mods->hash = true;
    else if (ch == '0')
      mods->zero = true;
  }

  if (**fcur == '*') {
    mods->wid = va_arg(*args, int);
    if (mods->wid < 0) {
      mods->wid = mods->wid != INT_MIN ? abs(mods->wid) : INT_MAX;
      mods->minus = true;
    }
    ++*fcur;
  } else if ((**fcur >= '0' && **fcur <= '9') || **fcur == '-') {
    mods->wid = 0;
    long tmp = 0;

    if (**fcur == '-') {
      mods->minus = true;
      ++*fcur;
    }
    for (; **fcur >= '0' && **fcur <= '9' && tmp <= INT_MAX; ++*fcur) {
      tmp = mods->wid * 10 + (**fcur - '0');
      mods->wid = tmp <= INT_MAX ? tmp : INT_MAX;
    }
  }

  if (**fcur == '.') {
    ++*fcur;
    if (**fcur == '*') {
      mods->prec = va_arg(*args, int);
      ++*fcur;
    } else if ((**fcur >= '0' && **fcur <= '9') || **fcur == '-') {
      mods->prec = 0;
      int coef = 1;
      long tmp = 0;
      if (**fcur == '-') {
        coef = -1;
        ++*fcur;
      }
      for (; **fcur >= '0' && **fcur <= '9' && tmp <= INT_MAX; ++*fcur) {
        tmp = mods->prec * 10 + (**fcur - '0');
        mods->prec = tmp <= INT_MAX ? tmp : INT_MAX;
      }
      mods->prec *= coef;
    } else {
      mods->prec = 0;
    }
  }

  if ((ch = **fcur) && (s21_strchr("hlL", ch))) {
    mods->len = ch;
    ++*fcur;
  }

  if ((ch = **fcur) && (s21_strchr("%csdioxXufeEgGnp", ch))) {
    mods->spec = ch;
  } else {
    is_error = true;
  }

  return is_error;
}

void adjust_convmods(conv_t *mods) {
  if (mods->plus || s21_strchr("csoxXu", mods->spec)) {
    mods->space = false;
  }

  if ((mods->prec >= 0 && s21_strchr("dioxXu", mods->spec)) || mods->minus ||
      s21_strchr("cs", mods->spec)) {
    mods->zero = false;
  }

  if (s21_strchr("oxXu", mods->spec)) {
    mods->plus = false;
    mods->space = false;
  }
}

bool convert(char **scur, int *written, conv_t *mods, va_list *args) {
  bool is_error = false;

  switch (mods->spec) {
    case '%':
      *(*scur)++ = '%';
      ++*written;
      break;
    case 'c':
      is_error = spec_c(scur, written, mods, args);
      break;
    case 's':
      is_error = spec_s(scur, written, mods, args);
      break;
    case 'd':
    case 'i':
    case 'o':
    case 'x':
    case 'X':
    case 'u':
      is_error = spec_dioxXu(scur, written, mods, args);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      is_error = spec_feEgG(scur, written, mods, args);
      break;
    case 'n':
      is_error = spec_n(scur, written, mods, args);
      break;
    case 'p':
      is_error = spec_p(scur, written, mods, args);
      break;
  }

  return is_error;
}

bool spec_c(char **scur, int *written, conv_t *mods, va_list *args) {
  mods->prec = -1;

  sc_t buf = {0};
  buf.alloc = (MB_LEN_MAX + 1) * 3;
  buf.d = malloc(buf.alloc);
  bool is_error = !buf.d;

  if (!is_error) {
    if (mods->len == 'l') {
      wchar_t arg = (wchar_t)va_arg(*args, int);
      wchar_t wc[2];
      wc[0] = (wchar_t)arg;
      wc[1] = 0;
      is_error = wcrtostr(&buf, mods, wc, 2);
    } else {
      unsigned char arg = (unsigned char)va_arg(*args, int);
      buf.d[0] = (unsigned char)arg;
      buf.d[1] = '\0';
      buf.size = 1;
    }
  }

  if (!is_error) {
    is_error = addwid(&buf, mods);
  }

  if (!is_error) {
    for (s21_size_t i = 0; i < buf.size; ++i, ++*scur) {
      **scur = buf.d[i];
    }
    *written += buf.size;
  }

  if (buf.d) {
    free(buf.d);
  }

  return is_error;
}

bool spec_s(char **scur, int *written, conv_t *mods, va_list *args) {
  bool is_error = false;
  sc_t buf = {0};
  s21_size_t szwnt = 0;

  if (mods->len == 'l') {
    wchar_t *wca = va_arg(*args, wchar_t *);

    for (; wca[szwnt]; ++szwnt) {
    }
    szwnt += 1;

    buf.alloc = szwnt * MB_CUR_MAX * 3 + 1;
    buf.d = malloc(buf.alloc);
    is_error = !buf.d;

    if (!is_error) {
      is_error = wcrtostr(&buf, mods, wca, szwnt);
    }
  } else {
    char *ca = va_arg(*args, char *);
    szwnt = s21_strlen(ca);

    buf.alloc = szwnt * 3 + 1;
    buf.d = malloc(buf.alloc);
    is_error = !buf.d;

    if (!is_error) {
      for (s21_size_t i = 0; i < szwnt && (int)i != mods->prec;
           ++i, ++buf.size) {
        buf.d[i] = ca[i];
      }
      buf.d[buf.size] = '\0';
    }
  }

  if (!is_error) {
    is_error = addwid(&buf, mods);
  }

  if (!is_error) {
    for (s21_size_t i = 0; i < buf.size; ++i, ++*scur) {
      **scur = buf.d[i];
    }
    *written += buf.size;
  }

  if (buf.d) {
    free(buf.d);
  }

  return is_error;
}

bool spec_dioxXu(char **scur, int *written, conv_t *mods, va_list *args) {
  sc_t buf = {0};
  buf.alloc = 256;
  buf.d = malloc(buf.alloc);

  bool is_error = !buf.d;
  bool is_negative = false;
  bool hash_o = mods->hash && mods->spec == 'o';
  bool hash_x = mods->hash && (mods->spec == 'x' || mods->spec == 'X');
  mods->prec = mods->prec < 0 ? 1 : mods->prec;

  unsigned long arg = 0;

  /* Signed integers */
  if (s21_strchr("di", mods->spec)) {
    long sarg = 0;
    getintarg(signed, sarg);
    is_negative = sarg < 0;
    arg = sarg < 0 ? labs(sarg + 1) + 1 : sarg;
  } else { /* Unsigned integers */
    getintarg(unsigned, arg);
  }

  if (!is_error) {
    /* For the case when arg == 0 && prec == 0, it won't work */
    /* Works when:
     * 1) Arg equals zero but precision doesn't equal zero
     * 2) Precision is specified as zero but there's an arg */
    if (arg || mods->prec) {
      utonbase(&buf, arg, mods);
    }
  }

  if (!is_error) {
    /* NOTE: Only for specifier %o and its # */
    /* For zero (prec != 0) or when mods->prec > buf.size, it won't work */
    /* Works when:
     * 1) Number of digits is less or equals precision (21 -> 021)
     * 2) Arg equals zero and precision equals zero (buf.size == prec) */
    if (hash_o &&
        ((!arg && !mods->prec) || (arg && mods->prec <= (int)buf.size))) {
      mods->prec = buf.size + 1;
    }

    is_error = addprec(&buf, mods);
  }

  /* NOTE: Only for specifiers %x %X and its # */
  /* Works when there's an arg */
  if (!is_error && hash_x && arg) {
    shift(buf.d, 2);
    buf.d[0] = '0';
    buf.d[1] = mods->spec == 'x' ? 'x' : 'X';
    buf.size += 2;
  }

  /* NOTE: Only for signed integers */
  if (!is_error && s21_strchr("di", mods->spec)) {
    is_error = addsign(&buf, mods, is_negative);
  }

  if (!is_error) {
    is_error = addwid(&buf, mods);
  }

  if (!is_error) {
    for (s21_size_t i = 0; i < buf.size; ++i, ++*scur) {
      **scur = buf.d[i];
    }
    *written += buf.size;
  }

  if (buf.d) {
    free(buf.d);
  }

  return is_error;
}

bool spec_feEgG(char **scur, int *written, conv_t *mods, va_list *args) {
  sc_t buf = {0};
  buf.alloc = 256;
  buf.d = malloc(buf.alloc);

  uint128_t bits = 0;
  bool is_error = false;

  if (mods->len == 'L') {
    long double ldarg = va_arg(*args, long double);
    s21_memcpy(&bits, &ldarg, sizeof(long double));
    flttostr(&buf, bits, LDOUBLE_MANTISSA_BITS, LDOUBLE_EXPONENT_BITS,
             LDOUBLE_EXPLICIT_LEADING_BIT, mods);
  } else {
    double darg = va_arg(*args, double);
    s21_memcpy(&bits, &darg, sizeof(double));
    flttostr(&buf, bits, DOUBLE_MANTISSA_BITS, DOUBLE_EXPONENT_BITS, false,
             mods);
  }

  if (!is_error) {
    is_error = addwid(&buf, mods);
  }

  if (!is_error) {
    for (s21_size_t i = 0; i < buf.size; ++i, ++*scur) {
      **scur = buf.d[i];
    }
    *written += buf.size;
  }

  if (buf.d) {
    free(buf.d);
  }

  return is_error;
}

bool spec_n(char **scur, int *written, conv_t *mods, va_list *args) {
  UNUSED(scur);
  bool is_error = false;

  if (mods->len == 'h') {
    short *arg = va_arg(*args, short *);
    *arg = (short)*written;
  } else if (mods->len == 'l') {
    long *arg = va_arg(*args, long *);
    *arg = (long)*written;
  } else if (mods->len == -1) {
    int *arg = va_arg(*args, int *);
    *arg = (int)*written;
  }

  return is_error;
}

bool spec_p(char **scur, int *written, conv_t *mods, va_list *args) {
  uintptr_t arg = (uintptr_t)va_arg(*args, void *);

  sc_t buf = {0};
  buf.alloc = 256;
  buf.d = malloc(buf.alloc);
  bool is_error = !buf.d;

  if (!is_error) {
    if (!arg) {
#if defined(__APPLE__)
      s21_strcpy(buf.d, "0x0");
      buf.size += 3;
#elif defined(__linux__) && !defined(__GLIBC__)
      buf.d[0] = '0';
      buf.size += 1;
#elif defined(__linux__) && defined(__GLIBC__)
      s21_strcpy(buf.d, "(nil)");
      buf.size += 5;
#endif
    } else {
      s21_strcpy(buf.d, "0x");
      buf.size += 2;
      utonbase(&buf, arg, mods);
    }
  }

  if (!is_error) {
    is_error = addwid(&buf, mods);
  }

  if (!is_error) {
    for (s21_size_t i = 0; i < buf.size; ++i, ++*scur) {
      **scur = buf.d[i];
    }
    *written += buf.size;
  }

  if (buf.d) {
    free(buf.d);
  }

  return is_error;
}
