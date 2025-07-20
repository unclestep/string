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

  printf("End of test case\nWritten str looks like: %s\n", str);
  printf("Bytes: ");
  for (s21_size_t i = 0; i != s21_strlen(str); ++i)
    printf("%#x ", +(unsigned char)str[i]);
  printf("\n\n");
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

  printf("End of parsing of specification: fcur = %c\n", **fcur);

  return is_error;
}

void adjust_modifiers(ConvMods_t *mods) {
  if (mods->plus) {
    mods->space = false;
  }

  if ((mods->prec >= 0 && s21_strchr("dioxXu", mods->spec)) || mods->minus) {
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
      // spec_di(scur, written, mods, args);
      break;
    case 'o':
      // spec_o(scur, written, mods, args);
      break;
    case 'x':
    case 'X':
      // spec_xX(scur, written, mods, args);
      break;
    case 'u':
      // spec_u(scur, written, mods, args);
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
      // spec_p(scur, written, mods, args);
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
  s21_size_t i = 0;
  for (; !is_error && !prec_max && !nterm && i < wc_sz; ++i) {
    char mbbuf[5] = "\0";
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
        mb->size += wrch;
        mbcur += wrch;
      }
    }
  }

  if (i == wc_sz && !nterm) {
    --mb->size;
  }

  return is_error;
}

bool addwid(SizeChar_t *array, ConvMods_t *mods) {
  char widfil = mods->zero && s21_strchr("dioxXufeEgG", mods->spec) ? '0' : ' ';
  int widdif = mods->wid - array->size > 0 ? mods->wid - array->size : 0;
  int needed_capacity = array->size + widdif + 1;
  bool is_error = false;

  if (widdif > 0) {
    if (needed_capacity > (int)array->size) {
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

bool spec_c(char **scur, int *written, ConvMods_t *mods, va_list *args) {
  int arg = va_arg(*args, int);
  bool is_error = false;
  mods->prec = -1;

  s21_size_t buf_sz = 64;
  SizeChar_t buf = {0};
  buf.array = malloc(buf_sz);
  is_error = !buf.array;

  if (!is_error) {
    if (mods->len == 'l') {
      wchar_t wc[2] = (wchar_t[]){arg, 0};
      is_error = wcrtostr(&buf, mods, wc, 2);
    } else {
      buf.array[0] = (unsigned char)arg;
      buf.array[1] = '\0';
      buf.size = 1;
    }
  }

  is_error = addwid(&buf, mods);

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
  s21_size_t buf_sz = 0;

  if (mods->len == 'l') {
    wchar_t *wca = va_arg(*args, wchar_t *);
    wchar_t *wcur = wca;

    for (; *wcur; ++wcur) {
    }
    buf_sz = wcur - wca + 1; /* Including null-terminator */

    is_error = wcrtostr(&buf, mods, wca, buf_sz);
  } else {
    char *ca = va_arg(*args, char *);
    char *cur = ca;

    for (int i = 0; *cur && i != mods->prec; ++cur, ++i, ++*scur, ++*written) {
      **scur = *cur;
    }
    *scur = cur > ca ? *scur - 1 : *scur;
  }

  return is_error;
}
