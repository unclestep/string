#include "s21_sprintf.h"

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
}

bool convert(char **scur, int *written, conv_t *mods, va_list *args) {
  bool is_error = false;

  switch (mods->spec) {
    case '%':
      **scur = '%';
      break;
    case 'c':
      is_error = spec_c(scur, written, mods, args);
      break;
    case 's':
      is_error = spec_s(scur, written, mods, args);
      break;
    case 'd':
    case 'i':
      is_error = spec_di(scur, written, mods, args);
      break;
    case 'o':
      is_error = spec_o(scur, written, mods, args);
      break;
    case 'x':
    case 'X':
      is_error = spec_xX(scur, written, mods, args);
      break;
    case 'u':
      is_error = spec_u(scur, written, mods, args);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      is_error = spec_feEgG(scur, written, mods, args);
      break;
    case 'n':
      // is_error = spec_n(scur, written, mods, args);
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

    buf.alloc = szwnt * MB_CUR_MAX * 3;
    buf.d = malloc(buf.alloc);
    is_error = !buf.d;

    if (!is_error) {
      is_error = wcrtostr(&buf, mods, wca, szwnt);
    }
  } else {
    char *ca = va_arg(*args, char *);
    szwnt = s21_strlen(ca) + 1;

    buf.alloc = szwnt * 3;
    buf.d = malloc(buf.alloc);
    is_error = !buf.d;

    if (!is_error) {
      for (s21_size_t i = 0; i < szwnt && (int)i != mods->prec; ++i) {
        buf.d[i] = ca[i];
        buf.size = buf.d[i] ? buf.size + 1 : buf.size;
      }
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

bool spec_di(char **scur, int *written, conv_t *mods, va_list *args) {
  bool is_error = false;
  sc_t buf = {0};

  long long arg = 0;

  if (mods->len == 'h') {
    arg = (long long)((short)va_arg(*args, int));
  } else if (mods->len == 'l') {
    arg = (long long)va_arg(*args, long);
  } else if (mods->len == -1) {
    arg = (long long)va_arg(*args, int);
  } else {
    is_error = true;
  }

  int prec = mods->prec < 0 ? 1 : mods->prec;
  int arglen = !arg && !mods->prec ? 0 : intlen(arg);
  int precdif = prec - arglen > 0 ? prec - arglen : 0;
  int sign = arg < 0 || mods->plus || mods->space ? 1 : 0;
  int widdif = mods->wid > (arglen + precdif + sign)
                   ? mods->wid - (arglen + precdif + sign)
                   : 0;
  int needed_alloc = arglen + precdif + sign + widdif + 1;

  buf.alloc = needed_alloc;
  buf.size = precdif + sign + arglen;
  buf.d = malloc(needed_alloc);
  char *bufcur = buf.d;
  is_error = !buf.d;

  if (!is_error) {
    if (arg < 0) {
      *bufcur++ = '-';
      arg = llabs(arg);
    } else if (mods->space) {
      *bufcur++ = ' ';
    } else if (mods->plus) {
      *bufcur++ = '+';
    }

    // if (mods->prec < 0 && widdif && mods->zero) {
    //   for (int i = 0; i < widdif; ++i, ++bufcur) {
    //     *bufcur = '0';
    //   }
    //   buf.size += widdif;
    // }

    for (int i = 0; i < precdif; ++i, ++bufcur) {
      *bufcur = '0';
    }

    if (!arg && mods->prec != 0) {
      *bufcur = '0';
    }

    for (char *reverse = bufcur + arglen - 1; arg; arg /= 10, --reverse) {
      *reverse = arg % 10 + '0';
    }
    bufcur += arglen;
    *bufcur = '\0';
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

bool spec_o(char **scur, int *written, conv_t *mods, va_list *args) {
  bool is_error = false;
  sc_t buf = {0};

  unsigned long arg = 0;

  if (mods->len == 'h') {
    arg = (unsigned long)((unsigned short)va_arg(*args, unsigned));
  } else if (mods->len == 'l') {
    arg = (unsigned long)va_arg(*args, unsigned long);
  } else if (mods->len == -1) {
    arg = (unsigned long)va_arg(*args, unsigned);
  } else {
    is_error = true;
  }

  int arglen = 0;
  char tmp[32] = {0};
  char *tcur = tmp;

  if (!is_error) {
    if (!arg && mods->prec != 0) {
      *tcur++ = '0';
      arglen = 1;
    }

    unsigned long decarg = arg;
    for (; decarg; decarg /= 8, ++tcur, ++arglen) {
      *tcur = decarg % 8 + '0';
    }
    *tcur = '\0';
  }

  int prec = mods->prec < 0 ? 1 : mods->prec;
  int precdif =
      (prec - arglen > 0) || (!arg && mods->prec) ? prec - arglen : mods->hash;
  int widdif =
      mods->wid > (arglen + precdif) ? mods->wid - (arglen + precdif) : 0;
  int needed_alloc = arglen + precdif + widdif + 1;
  buf.alloc = needed_alloc;
  buf.size = precdif + arglen;
  buf.d = malloc(needed_alloc);
  char *bufcur = buf.d;
  is_error = !buf.d;

  if (!is_error) {
    for (int i = 0; i < precdif; ++i, ++bufcur) {
      *bufcur = '0';
    }

    for (tcur = !*tcur ? tcur - 1 : tcur; tcur >= tmp; --tcur, ++bufcur) {
      *bufcur = *tcur;
    }
    *bufcur = '\0';
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

bool spec_xX(char **scur, int *written, conv_t *mods, va_list *args) {
  bool is_error = false;
  sc_t buf = {0};

  unsigned long arg = 0;

  if (mods->len == 'h') {
    arg = (unsigned long)((unsigned short)va_arg(*args, unsigned));
  } else if (mods->len == 'l') {
    arg = (unsigned long)va_arg(*args, unsigned long);
  } else if (mods->len == -1) {
    arg = (unsigned long)va_arg(*args, unsigned);
  } else {
    is_error = true;
  }

  int arglen = 0;
  char tmp[32] = {0};
  char *tcur = tmp;

  const char *alphabet =
      mods->spec == 'x' ? "0123456789abcdef" : "0123456789ABCDEF";

  if (!arg && mods->prec != 0) {
    *tcur++ = '0';
    arglen = 1;
  }

  unsigned long decarg = arg;
  for (; decarg; decarg /= 16, ++tcur, ++arglen) {
    *tcur = alphabet[decarg % 16];
  }
  *tcur = '\0';

  int prefix = mods->hash && arg ? 2 : 0;
  int prec = mods->prec < 0 ? 1 : mods->prec;
  int precdif = prec - arglen > 0 ? prec - arglen : 0;
  int widdif = mods->wid > (arglen + precdif + prefix)
                   ? mods->wid - (arglen + precdif + prefix)
                   : 0;
  int needed_alloc = arglen + precdif + widdif + prefix + 1;
  buf.alloc = needed_alloc;
  buf.size = precdif + arglen + prefix;
  buf.d = malloc(needed_alloc);
  char *bufcur = buf.d;
  is_error = !buf.d;

  if (!is_error) {
    if (mods->hash && arg) {
      *bufcur++ = '0';
      *bufcur++ = mods->spec == 'x' ? 'x' : 'X';
    }

    for (int i = 0; i < precdif; ++i, ++bufcur) {
      *bufcur = '0';
    }

    for (tcur = !*tcur ? tcur - 1 : tcur; tcur >= tmp; --tcur, ++bufcur) {
      *bufcur = *tcur;
    }
    *bufcur = '\0';
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

bool spec_u(char **scur, int *written, conv_t *mods, va_list *args) {
  bool is_error = false;
  sc_t buf = {0};

  unsigned long arg = 0;

  if (mods->len == 'h') {
    arg = (unsigned long)((unsigned short)va_arg(*args, unsigned));
  } else if (mods->len == 'l') {
    arg = (unsigned long)va_arg(*args, unsigned long);
  } else if (mods->len == -1) {
    arg = (unsigned long)va_arg(*args, unsigned);
  } else {
    is_error = true;
  }

  int prec = mods->prec < 0 ? 1 : mods->prec;
  int arglen = !arg && !mods->prec ? 0 : uintlen(arg);
  int precdif = prec - arglen > 0 ? prec - arglen : 0;
  int widdif =
      mods->wid > (arglen + precdif) ? mods->wid - (arglen + precdif) : 0;
  int needed_alloc = arglen + precdif + widdif + 1;

  buf.alloc = needed_alloc;
  buf.size = precdif + arglen;
  buf.d = malloc(needed_alloc);
  char *bufcur = buf.d;
  is_error = !buf.d;

  if (!is_error) {
    if (mods->prec < 0 && widdif && mods->zero) {
      for (int i = 0; i < widdif; ++i, ++bufcur) {
        *bufcur = '0';
      }
      buf.size += widdif;
    }

    for (int i = 0; i < precdif; ++i, ++bufcur) {
      *bufcur = '0';
    }

    if (!arg && mods->prec != 0) {
      *bufcur = '0';
    }

    for (char *reverse = bufcur + arglen - 1; arg; arg /= 10, --reverse) {
      *reverse = arg % 10 + '0';
    }
    bufcur += arglen;
    *bufcur = '\0';
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

bool spec_p(char **scur, int *written, conv_t *mods, va_list *args) {
  uintptr_t arg = (uintptr_t)va_arg(*args, void *);

  int arglen = 0;
  char tmp[32] = {0};
  char *tcur = tmp;

  bool is_error = false;

  const char *alphabet = "0123456789abcdef";
  unsigned long decarg = arg;

  if (!arg) {
#if defined(__APPLE__)
    *tcur++ = '0';
    *tcur++ = 'x';
    *tcur++ = '0';
    arglen = 3;
#elif defined(__linux__) && !defined(__GLIBC__)
    *tcur++ = '0';
    arglen = 1;
#elif defined(__linux__) && defined(__GLIBC__)
    *tcur++ = ')';
    *tcur++ = 'l';
    *tcur++ = 'i';
    *tcur++ = 'n';
    *tcur++ = '(';
    arglen = 5;
#endif
  }

  for (; decarg; decarg /= 16, ++tcur, ++arglen) {
    *tcur = alphabet[decarg % 16];
  }

  if (arg) {
    *tcur++ = 'x';
    *tcur++ = '0';
    arglen += 2;
  }

  int widdif = mods->wid - arglen > 0 ? mods->wid - arglen : 0;
  *written += arglen + widdif;

  if (widdif && !mods->minus) {
    for (int i = 0; i < widdif; ++i, ++*scur) {
      **scur = ' ';
    }
  }

  for (tcur = tmp + arglen - 1; tcur >= tmp; --tcur, ++*scur) {
    **scur = *tcur;
  }

  if (widdif && mods->minus) {
    for (int i = 0; i < widdif; ++i, ++*scur) {
      **scur = ' ';
    }
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

  addwid(&buf, mods);

  for (s21_size_t i = 0; i < buf.size; ++i, ++*scur) {
    **scur = buf.d[i];
  }
  *written += buf.size;

  if (buf.d) {
    free(buf.d);
  }

  return is_error;
}

bool spec_n(char **scur, int *written, conv_t *mods, va_list *args) {
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
  } else {
    is_error = true;
  }

  ++*scur;

  return is_error;
}
