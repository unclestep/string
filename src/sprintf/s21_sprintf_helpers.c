#include "../include/s21_sprintf.h"

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

  return is_error;
}

bool addwid(sc_t *arr, conv_t *mods) {
  char widfil = mods->zero ? '0' : ' ';
  int widdif = mods->wid - arr->size > 0 ? mods->wid - arr->size : 0;
  s21_size_t needed_alloc = arr->size + widdif + 1;
  bool is_error = false;

  if (widdif > 0) {
    if (needed_alloc > arr->alloc) {
      char *buf = malloc(needed_alloc);
      is_error = !buf;
      if (buf && !mods->minus) {
        s21_memset(buf, widfil, widdif);
        s21_memcpy(buf + widdif, arr->d, arr->size + 1);
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
        for (int i = arr->size; i >= 0; --i) {
          arr->d[i + widdif] = arr->d[i];
        }
        s21_memset(arr->d, widfil, widdif);
      } else {
        s21_memset(arr->d + arr->size, widfil, widdif);
        arr->d[arr->size + widdif] = '\0';
      }
    }

    arr->size += widdif;
  }

  return is_error;
}
