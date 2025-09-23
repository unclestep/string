#include "s21_sprintf.h"

int intlen(long long i) {
  int intlen = 1;

  if (i == LLONG_MIN) {
    i = LLONG_MAX;
  } else {
    i = llabs(i);
  }

  if (i != 0) {
    intlen = (int)log10l(i) + 1;
  }

  return intlen;
}

int uintlen(unsigned long long i) {
  int intlen = 1;

  if (i != 0) {
    intlen = (int)log10l(i) + 1;
  }

  return intlen;
}

bool wcrtostr(sc_t *mb, conv_t *mods, wchar_t *wc, s21_size_t wc_sz) {
  bool is_error = false;
  bool prec_max = false;
  bool nterm = false;

  mbstate_t state;
  s21_memset(&state, 0, sizeof(state));

  char *mbcur = mb->d;

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

  mb->d[mb->size] = '\0';

  return is_error;
}

bool addsign(sc_t *arr, conv_t *mods, bool is_negative) {
  bool is_error = false;

  if (is_negative) {
    arr->d[arr->size++] = '-';
  } else if (mods->space) {
    arr->d[arr->size++] = ' ';
  } else if (mods->plus) {
    arr->d[arr->size++] = '+';
  }
  arr->d[arr->size] = '\0';

  return is_error;
}

bool addwid(sc_t *arr, conv_t *mods) {
  char widfil = mods->zero ? '0' : ' ';

  int widdif = mods->wid - arr->size > 0 ? mods->wid - arr->size : 0;
  s21_size_t new_alloc = arr->size + widdif + 1;

  bool is_error = false;
  char sign = arr->d[0];
  bool is_sign = s21_strchr("+- ", sign) && mods->zero;

  if (widdif > 0) {
    if (new_alloc > arr->alloc) {
      char *buf = malloc(new_alloc);
      is_error = !buf;

      if (buf && !mods->minus) {
        if (is_sign) *buf = sign;
        s21_memset(buf + is_sign, widfil, widdif);
        s21_memcpy(buf + is_sign + widdif, arr->d + is_sign,
                   arr->size - is_sign + 1);
      } else if (buf && mods->minus) {
        s21_memcpy(buf, arr->d, arr->size);
        s21_memset(buf + arr->size, widfil, widdif);
        buf[arr->size + widdif] = '\0';
      }

      if (buf) {
        free(arr->d);
        arr->d = buf;
      }
    } else {
      if (!mods->minus) {
        for (int i = arr->size; i >= is_sign; --i) {
          arr->d[i + widdif] = arr->d[i];
        }
        s21_memset(arr->d + is_sign, widfil, widdif);
      } else {
        s21_memset(arr->d + arr->size, widfil, widdif);
        arr->d[arr->size + widdif] = '\0';
      }
    }

    arr->size += widdif;
  }

  return is_error;
}

void flttostr(sc_t *dst, const uint128_t bits, const uint32_t manbits,
              const uint32_t expbits, const bool explicit_leading_bit,
              conv_t *mods) {
  const uint32_t bias = (1U << (expbits - 1)) - 1;
  const uint32_t ieee_sign = (bits >> (manbits + expbits)) & 1;
  const uint128_t ieee_man = bits & ((ONE << manbits) - 1);
  const uint32_t ieee_exp =
      (uint32_t)((bits >> manbits) & ((ONE << expbits) - 1));
  bool is_inf_nan = false;

  if (ieee_exp == ((1U << expbits) - 1U) && ieee_man == 0) {
    addsign(dst, mods, ieee_sign);
    if (mods->spec == 'E' || mods->spec == 'G') {
      s21_strcpy(dst->d + dst->size, "INF");
    } else {
      s21_strcpy(dst->d + dst->size, "inf");
    }
    dst->size += 3;
    is_inf_nan = true;
    mods->zero = false;
  } else if (ieee_exp == ((1U << expbits) - 1U) && ieee_man != 0) {
#if defined(__linux__)
    addsign(dst, mods, ieee_sign);
#endif
    if (mods->spec == 'E' || mods->spec == 'G') {
      s21_strcpy(dst->d + dst->size, "NAN");
    } else {
      s21_strcpy(dst->d + dst->size, "nan");
    }
    dst->size += 3;
    is_inf_nan = true;
    mods->zero = false;
  }

  if (!is_inf_nan) {
    addsign(dst, mods, ieee_sign);

    /* f = m * 2^e */
    int32_t e = 0;
    uint128_t m = 0;

    if (explicit_leading_bit) {
      e = ieee_exp == 0 ? 1 - bias - manbits + 1
                        : ieee_exp - bias - manbits + 1;
      m = ieee_man;
    } else {
      e = ieee_exp == 0 ? 1 - bias - manbits : ieee_exp - bias - manbits;
      m = ieee_exp == 0 ? ieee_man : (ONE << manbits) | ieee_man;
    }

    long long unsigned lower = (long long unsigned)m;
    long long unsigned upper = (long long unsigned)(m - (uint128_t)lower);

    mpf_t mpres;
    mpz_t mpman;
    mpf_init(&mpres);
    mpz_init_set_ull(&mpman, lower);
    if (upper) {
      mpz_realloc(&mpman, 2);
      mpman.size = 2;
      mpman.d[1] = upper;
    }
    // printf("Before calc:\nLower: %llu\nUpper: %llu\nExp: %d\n", lower, upper,
    //        e);

    int prec = mods->prec < 0 ? 6 : mods->prec;
    if (!prec && mods->spec == 'g') prec = 1;

    /* Bitwise left shift by e (multiplication) */
    if (e >= 0) {
      mpz_mul_2exp(&mpres, &mpman, e);
    } else { /* Bitwise right shift by e until needed precision is reached
                (fractional division) */
      e = -e;
      mpz_fdiv_2exp(&mpres, &mpman, e, prec);
    }

    // printf("After calc:\nExp: %d\nFig: %d\n", mpres.exp, mpres.fig);

    /* Conversion to string */
    if (mods->spec == 'f') {
      mpf_to_fltnot(dst, &mpres, prec);
      // printf("After Conv Value's:\nExp: %d\nFig: %d\n", mpres.exp,
      // mpres.fig); printf("After fltnot:\nsc_t size: %lu\nvalue: %s\n\n",
      // dst->size, dst->d);

      if (mods->hash && !s21_strchr(dst->d, '.')) {
        dst->d[dst->size++] = '.';
        dst->d[dst->size] = '\0';
      }
      // printf("After hash:\nsc_t size: %lu\nvalue: %s\n\n", dst->size,
      // dst->d);
    } else if (mods->spec == 'e' || mods->spec == 'E') {
      mpf_to_scinot(dst, &mpres, prec, mods->spec == 'E');

      if (mods->hash && !s21_strchr(dst->d, '.')) {
        char *expstart = s21_strchr(dst->d, 'e');
        char *expend = dst->d + dst->size;

        for (; expend >= expstart; --expend) {
          *(expend + 1) = *expend;
        }
        *expstart = '.';
        dst->size += 1;
      }
    } else if (mods->spec == 'g' || mods->spec == 'G') {
      if (prec > mpres.exp && mpres.exp >= -4) {
        mpf_to_fltnot(dst, &mpres, prec - 1 - mpres.exp);

        if (mods->hash && !s21_strchr(dst->d, '.')) {
          dst->d[dst->size++] = '.';
          dst->d[dst->size] = '\0';
        } else if (!mods->hash && s21_strchr(dst->d, '.')) {
          char *cur = dst->d + dst->size - 1;

          for (; *cur == '0'; --cur, --dst->size) {
          }

          if (*cur == '.') {
            *cur = '\0';
            --dst->size;
          } else {
            *(cur + 1) = '\0';
          }
        }
      } else {
        mpf_to_scinot(dst, &mpres, prec - 1, mods->spec == 'G');

        char *expstart = s21_strchr(dst->d, 'e');
        char *expend = dst->d + dst->size;

        if (mods->hash && !s21_strchr(dst->d, '.')) {
          for (; expend >= expstart; --expend) {
            *(expend + 1) = *expend;
          }
          *expstart = '.';
          dst->size += 1;
        } else if (!mods->hash && s21_strchr(dst->d, '.')) {
          char *frac = expstart - 1;

          for (; *frac == '0'; --frac, --dst->size) {
          }

          if (*frac == '.') {
            --dst->size;
          } else {
            ++frac;
          }

          s21_strcpy(frac, expstart);
        }
      }
    }

    mpf_clear(&mpres);
    mpz_clear(&mpman);
  }
}
