#include "../include/s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *scur = str;
  const char *fcur = format;
  int written = 0;
  bool is_error = false;

  for (; !is_error && *fcur; ++fcur) {
    if (*fcur == '%') {
      is_error = conversion_specification(&scur, &fcur, &written, &args);
    } else {
      *scur++ = *fcur;
      ++written;
    }
  }

  *scur = '\0';
  va_end(args);

  return is_error ? -1 : written;
}

bool conversion_specification(char **scur, const char **fcur, int *written,
                              va_list *args) {
  bool is_error = false;
  ConvMods_t mods = {.minus = 0,
                     .plus = 0,
                     .space = 0,
                     .hash = 0,
                     .zero = 0,
                     .wid = -1,
                     .prec = -1,
                     .len = -1,
                     .spec = -1};

  is_error = get_modifiers(fcur, &mods, args);
  if (!is_error) {
    adjust_modifiers(&mods);
    is_error = handle_conversion(scur, written, &mods, args);
  }
  return is_error;
}

bool get_modifiers(const char **fcur, ConvMods_t *mods, va_list *args) {
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
    ++*fcur;
  } else if (**fcur >= '0' && **fcur <= '9') {
    mods->wid = 0;
    for (; **fcur >= '0' && **fcur <= '9'; ++*fcur) {
      mods->wid = mods->wid * 10 + (**fcur - '0');
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
      if (**fcur == '-') {
        coef = -1;
        ++*fcur;
      }
      for (; **fcur >= '0' && **fcur <= '9'; ++*fcur) {
        mods->prec = mods->prec * 10 + (**fcur - '0') * coef;
      }
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

void adjust_modifiers(ConvMods_t *mods) {
  if (mods->plus || s21_strchr("csoxXu", mods->spec)) {
    mods->space = false;
  }

  if ((mods->prec >= 0 && s21_strchr("dioxXu", mods->spec)) || mods->minus ||
      s21_strchr("cs", mods->spec)) {
    mods->zero = false;
  }
}

bool handle_conversion(char **scur, int *written, ConvMods_t *mods,
                       va_list *args) {
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
      spec_di(scur, written, mods, args);
      break;
    case 'o':
      spec_o(scur, written, mods, args);
      break;
    case 'x':
    case 'X':
      spec_xX(scur, written, mods, args);
      break;
    case 'u':
      spec_u(scur, written, mods, args);
      break;
    case 'f':
      // spec_f(scur, written, mods, args);
      break;
    case 'e':
    case 'E':
      // spec_eE(scur, written, mods, args);
      break;
    case 'g':
    case 'G':
      // spec_gG(scur, written, mods, args);
      break;
    case 'n':
      // spec_n(scur, written, mods, args);
      break;
    case 'p':
      spec_p(scur, written, mods, args);
      break;
  }

  return is_error;
}

bool wcrtostr(SizeChar_t *mb, ConvMods_t *mods, wchar_t *wc, s21_size_t wc_sz) {
  bool is_error = false;
  bool prec_max = false;
  bool nterm = false;

  mbstate_t state;
  s21_memset(&state, 0, sizeof(state));

  char *mbcur = mb->array;

  for (s21_size_t i = 0; !is_error && !prec_max && !nterm && i < wc_sz; ++i) {
    char mbbuf[MB_LEN_MAX + 1] = "\0";
    int wrch = wcrtomb(mbbuf, wc[i], &state);

    if (wrch == -1) {
      is_error = 1;
    } else if ((int)mb->size + wrch > mods->prec && mods->prec >= 0) {
      prec_max = true;
      *mbcur = '\0';
      mbcur += 1;
    } else {
      s21_strcpy(mbcur, mbbuf);
      if (!*mbcur && mods->spec == 's') {
        nterm = true;
      } else {
        mb->size = i < wc_sz - 1 ? mb->size + wrch : mb->size;
        mbcur += wrch;
      }
    }
  }

  return is_error;
}

bool addwid(SizeChar_t *array, ConvMods_t *mods) {
  char widfil = mods->zero ? '0' : ' ';
  int widdif = mods->wid - array->size > 0 ? mods->wid - array->size : 0;
  s21_size_t needed_capacity = array->size + widdif + 1;
  bool is_error = false;

  if (widdif > 0) {
    if (needed_capacity > array->capacity) {
      char *buf = malloc(needed_capacity);
      is_error = !buf;
      if (buf && !mods->minus) {
        s21_memset(buf, widfil, widdif);
        s21_memcpy(buf + widdif, array->array, array->size + 1);
      } else if (buf && mods->minus) {
        s21_memcpy(buf, array->array, array->size);
        s21_memset(buf + array->size, widfil, widdif);
        buf[array->size + widdif] = '\0';
      }

      if (buf) {
        free(array->array);
        array->array = buf;
      }
    } else {
      if (!mods->minus) {
        for (int i = array->size; i >= 0; --i) {
          array->array[i + widdif] = array->array[i];
        }
        s21_memset(array->array, widfil, widdif);
      } else {
        s21_memset(array->array + array->size, widfil, widdif);
        array->array[array->size + widdif] = '\0';
      }
    }

    array->size += widdif;
  }

  return is_error;
}

int intlen(long long i) {
  i = llabs(i);
  int intlen = 1;

  if (i >= 1000000000000000000) {
    intlen = 19;
  } else if (i >= 100000000000000000) {
    intlen = 18;
  } else if (i >= 10000000000000000) {
    intlen = 17;
  } else if (i >= 1000000000000000) {
    intlen = 16;
  } else if (i >= 100000000000000) {
    intlen = 15;
  } else if (i >= 10000000000000) {
    intlen = 14;
  } else if (i >= 1000000000000) {
    intlen = 13;
  } else if (i >= 100000000000) {
    intlen = 12;
  } else if (i >= 10000000000) {
    intlen = 11;
  } else if (i >= 1000000000) {
    intlen = 10;
  } else if (i >= 100000000) {
    intlen = 9;
  } else if (i >= 10000000) {
    intlen = 8;
  } else if (i >= 1000000) {
    intlen = 7;
  } else if (i >= 100000) {
    intlen = 6;
  } else if (i >= 10000) {
    intlen = 5;
  } else if (i >= 1000) {
    intlen = 4;
  } else if (i >= 100) {
    intlen = 3;
  } else if (i >= 10) {
    intlen = 2;
  } else if (i >= 0) {
    intlen = 1;
  }

  return intlen;
}

int uintlen(unsigned long i) {
  int intlen = 1;

  if (i >= 10000000000000000000ULL) {
    intlen = 20;
  } else if (i >= 1000000000000000000) {
    intlen = 19;
  } else if (i >= 100000000000000000) {
    intlen = 18;
  } else if (i >= 10000000000000000) {
    intlen = 17;
  } else if (i >= 1000000000000000) {
    intlen = 16;
  } else if (i >= 100000000000000) {
    intlen = 15;
  } else if (i >= 10000000000000) {
    intlen = 14;
  } else if (i >= 1000000000000) {
    intlen = 13;
  } else if (i >= 100000000000) {
    intlen = 12;
  } else if (i >= 10000000000) {
    intlen = 11;
  } else if (i >= 1000000000) {
    intlen = 10;
  } else if (i >= 100000000) {
    intlen = 9;
  } else if (i >= 10000000) {
    intlen = 8;
  } else if (i >= 1000000) {
    intlen = 7;
  } else if (i >= 100000) {
    intlen = 6;
  } else if (i >= 10000) {
    intlen = 5;
  } else if (i >= 1000) {
    intlen = 4;
  } else if (i >= 100) {
    intlen = 3;
  } else if (i >= 10) {
    intlen = 2;
  } else {
    intlen = 1;
  }

  return intlen;
}

bool spec_c(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  mods->prec = -1;

  SizeChar_t buf = {0};
  buf.capacity = (MB_LEN_MAX + 1) * 3;
  buf.array = malloc(buf.capacity);
  bool is_error = !buf.array;

  if (!is_error) {
    if (mods->len == 'l') {
      wchar_t arg = (wchar_t)va_arg(*args, int);
      wchar_t wc[2];
      wc[0] = (wchar_t)arg;
      wc[1] = 0;
      is_error = wcrtostr(&buf, mods, wc, 2);
    } else {
      unsigned char arg = (unsigned char)va_arg(*args, int);
      buf.array[0] = (unsigned char)arg;
      buf.array[1] = '\0';
      buf.size = 1;
    }
  }

  if (!is_error) {
    is_error = addwid(&buf, mods);
  }

  if (!is_error) {
    for (s21_size_t i = 0; i < buf.size; ++i, ++*scur) {
      **scur = buf.array[i];
    }
    *written += buf.size;
  }

  if (buf.array) {
    free(buf.array);
  }

  return is_error;
}

bool spec_s(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  bool is_error = false;
  SizeChar_t buf = {0};
  s21_size_t szwnt = 0;

  if (mods->len == 'l') {
    wchar_t *wca = va_arg(*args, wchar_t *);

    for (; wca[szwnt]; ++szwnt) {
    }
    szwnt += 1;

    buf.capacity = szwnt * MB_CUR_MAX * 3;
    buf.array = malloc(buf.capacity);
    is_error = !buf.array;

    if (!is_error) {
      is_error = wcrtostr(&buf, mods, wca, szwnt);
    }
  } else {
    char *ca = va_arg(*args, char *);
    szwnt = s21_strlen(ca) + 1;

    buf.capacity = szwnt * 3;
    buf.array = malloc(buf.capacity);
    is_error = !buf.array;

    if (!is_error) {
      for (s21_size_t i = 0; i < szwnt && (int)i != mods->prec; ++i) {
        buf.array[i] = ca[i];
        buf.size = buf.array[i] ? buf.size + 1 : buf.size;
      }
    }
  }

  if (!is_error) {
    is_error = addwid(&buf, mods);
  }

  if (!is_error) {
    for (s21_size_t i = 0; i < buf.size; ++i, ++*scur) {
      **scur = buf.array[i];
    }
    *written += buf.size;
  }

  if (buf.array) {
    free(buf.array);
  }

  return is_error;
}

bool spec_di(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  bool is_error = false;
  SizeChar_t buf = {0};

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
  int widdif = mods->wid - (arglen + precdif + sign) > 0
                   ? mods->wid - (arglen + precdif + sign)
                   : 0;
  int needed_capacity = arglen + precdif + sign + widdif + 1;

  buf.capacity = needed_capacity;
  buf.size = precdif + sign + arglen;
  buf.array = malloc(needed_capacity);
  char *bufcur = buf.array;
  is_error = !buf.array;

  if (!is_error) {
    if (arg < 0) {
      *bufcur++ = '-';
      arg = llabs(arg);
    } else if (mods->space) {
      *bufcur++ = ' ';
    } else if (mods->plus) {
      *bufcur++ = '+';
    }

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
      **scur = buf.array[i];
    }
    *written += buf.size;
  }

  if (buf.array) {
    free(buf.array);
  }

  return is_error;
}

bool spec_o(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  bool is_error = false;
  SizeChar_t buf = {0};

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

  char *tmp = malloc(32);
  char *tcur = tmp;
  is_error = !tmp;

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
      mods->wid - (arglen + precdif) > 0 ? mods->wid - (arglen + precdif) : 0;
  int needed_capacity = arglen + precdif + widdif + 1;
  buf.capacity = needed_capacity;
  buf.size = precdif + arglen;
  buf.array = malloc(needed_capacity);
  char *bufcur = buf.array;
  is_error = !buf.array;

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
      **scur = buf.array[i];
    }
    *written += buf.size;
  }

  if (buf.array) {
    free(buf.array);
  }

  if (tmp) {
    free(tmp);
  }

  return is_error;
}

bool spec_xX(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  bool is_error = false;
  SizeChar_t buf = {0};

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

  char *tmp = malloc(32);
  char *tcur = tmp;
  is_error = !tmp;

  if (!is_error) {
    char *alphabet =
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
  }

  int prefix = mods->hash && arg ? 2 : 0;
  int prec = mods->prec < 0 ? 1 : mods->prec;
  int precdif = prec - arglen > 0 ? prec - arglen : 0;
  int widdif = mods->wid - (arglen + precdif + prefix) > 0
                   ? mods->wid - (arglen + precdif + prefix)
                   : 0;
  int needed_capacity = arglen + precdif + widdif + prefix + 1;
  buf.capacity = needed_capacity;
  buf.size = precdif + arglen + prefix;
  buf.array = malloc(needed_capacity);
  char *bufcur = buf.array;
  is_error = !buf.array;

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
      **scur = buf.array[i];
    }
    *written += buf.size;
  }

  if (buf.array) {
    free(buf.array);
  }

  if (tmp) {
    free(tmp);
  }

  return is_error;
}

bool spec_u(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  bool is_error = false;
  SizeChar_t buf = {0};

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
      mods->wid - (arglen + precdif) > 0 ? mods->wid - (arglen + precdif) : 0;
  int needed_capacity = arglen + precdif + widdif + 1;

  buf.capacity = needed_capacity;
  buf.size = precdif + arglen;
  buf.array = malloc(needed_capacity);
  char *bufcur = buf.array;
  is_error = !buf.array;

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
      **scur = buf.array[i];
    }
    *written += buf.size;
  }

  if (buf.array) {
    free(buf.array);
  }

  return is_error;
}

bool spec_p(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  uintptr_t arg = (uintptr_t)va_arg(*args, void *);

  bool is_error = false;
  int arglen = 0;

  char *tmp = malloc(32);
  char *tcur = tmp;
  is_error = !tmp;

  if (!is_error) {
    char *alphabet = "0123456789abcdef";

    unsigned long decarg = arg;

    if (!decarg) {
#if defined(__APPLE__)
      *tcur++ = '0';
#endif

#if defined(__linux__)
      *tcur++ = ')';
      *tcur++ = 'l';
      *tcur++ = 'i';
      *tcur++ = 'n';
      *tcur++ = '(';
      arglen += 2;
#endif
      arglen += 1;
    }

    for (; decarg; decarg /= 16, ++tcur, ++arglen) {
      *tcur = alphabet[decarg % 16];
    }
    *tcur = '\0';
    arglen += 2;

    int widdif = mods->wid - arglen > 0 ? mods->wid - arglen : 0;
    *written += arglen + widdif;

    if (widdif && !mods->minus) {
      for (int i = 0; i < widdif; ++i, ++*scur) {
        **scur = ' ';
      }
    }

    if (arg) {
      *(*scur)++ = '0';
      *(*scur)++ = 'x';
    } else {
#if defined(__APPLE__)
      *(*scur)++ = '0';
      *(*scur)++ = 'x';
#endif
    }

    for (tcur = !*tcur ? tcur - 1 : tcur; tcur >= tmp; --tcur, ++*scur) {
      **scur = *tcur;
    }

    if (widdif && mods->minus) {
      for (int i = 0; i < widdif; ++i, ++*scur) {
        **scur = ' ';
      }
    }
  }

  if (tmp) {
    free(tmp);
  }

  return is_error;
}

bool spec_f(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  uint128_t bits = 0;
  int whole_part_len = 0;
  int sign = 0;
  bool is_error = false;
  bool is_inf_nan = false;

  if (mods->len == 'L') {
    long double arg = va_arg(*args, long double);
    s21_memcpy(&bits, &arg, sizeof(long double));
    whole_part_len = fabsl(arg) ? ceill(log10l(fabsl(arg))) : 0;
    sign = fltdec.sign || mods->space || mods->plus ? 1 : 0;

  } else {
    double arg = va_arg(*args, double);
    s21_memcpy(&bits, &arg, sizeof(double));
    whole_part_len = fabs(arg) ? ceil(log10(fabs(arg))) : 0;
    sign = fltdec.sign || mods->space || mods->plus ? 1 : 0;
  }

  if (!is_error && !is_inf_nan) {
    int prec = mods->prec < 0 ? 6 : mods->prec;
    int dot = prec || (!prec && mods->hash) ? 1 : 0;
    int arglen = whole_part_len + prec + dot + sign;
    int wid = mods->wid < 0 ? 0 : mods->wid;
    int widdif = wid - arglen < 0 ? 0 : wid - arglen;
    int needed_capacity = arglen + widdif;

    SizeChar_t buf = {0};
    buf.size = arglen;
    buf.capacity = needed_capacity;
    buf.array = malloc(needed_capacity);
    is_error = !buf.array;

    mods->len == 'L'
        ? flttostr(buf.array, bits, LDOUBLE_MANTISSA_BITS,
                   LDOUBLE_EXPONENT_BITS, true, whole_part_len + prec)
        : flttostr(buf.array, bits, DOUBLE_MANTISSA_BITS, DOUBLE_EXPONENT_BITS,
                   false, whole_part_len + prec);
  }

  return is_error || is_inf_nan;
}

void flttostr(char *res, const uint128_t bits, const uint32_t manbits,
              const uint32_t expbits, const bool explicit_leading_bit,
              const int decdigits) {
  const uint32_t bias = (1U << (expbits - 1)) - 1;
  const bool ieee_sign = (bits >> (manbits + expbits)) & 1U;
  const uint128_t ieee_man = bits & ((ONE << manbits) - 1);
  const uint32_t ieee_exp =
      (uint32_t)((bits >> manbits) & ((ONE << expbits) - 1));
  bool zero_inf_nan = false;

  if (ieee_exp == 0 && ieee_man == 0) {
    *res++ = '0';
    zero_inf_nan = true;
  } else if (ieee_exp == ((1U << expbits) - 1U) && ieee_man == 0) {
    for (const char *inf = "infinity"; *inf; ++res, ++inf) {
      *res = *inf;
    }
    zero_inf_nan = true;
  } else if (ieee_exp == ((1U << expbits) - 1U) && ieee_man != 0) {
    for (const char *nan = "nan"; *nan; ++res, ++nan) {
      *res = *nan;
    }
    zero_inf_nan = true;
  }

  if (!zero_inf_nan) {
    /* f = m * 2^e */
    int32_t e = 0;
    uint128_t m = 0;

    if (explicit_leading_bit) {
      e = ieee_exp == 0 ? 1 - bias - manbits + 1
                        : ieee_exp - bias - manbits + 1;
      m = ieee_man;
    } else {
      e = ieee_exp == 0 ? 1 - bias - manbits : ieee_exp - bias - manbits;
      m = (ONE << manbits) | ieee_man;
    }

    BigNum_t v = {0};

    if (e >= 0) {
      int32_t m_limbs = 1;
      int32_t e_limbs = ceil(e / (float)LIMB_SIZE);

      v.msb = e;
      v.limbs = m_limbs + e_limbs;
      v.num = (uint128_t *)calloc(v.limbs, sizeof(uint128_t));
      v.e10 = 0;

      mul2(&v, m, e);
    } else {
      e = -e;

      v.msb = -1;
      v.limbs = ceil((float)(decdigits * ceil(log2(10))) / sizeof(uint128_t));
      v.num = (uint128_t *)calloc(v.limbs, sizeof(uint128_t));

      div2(&v, m, e);
    }
  }
}

void div2(BigNum_t *v, const uint128_t m, const int32_t e) {}
