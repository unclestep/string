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

#define LDOUBLE_MANTISSA_BITS 64
#define LDOUBLE_EXPONENT_BITS 15
#define DOUBLE_MANTISSA_BITS 52
#define DOUBLE_EXPONENT_BITS 11

#define ONE (uint128_t)1
#define ZERO (uint128_t)0
#define LIMB_SIZE 128
typedef uint128_t limb_t;

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

typedef struct BigNum_t {
  limb_t *num;
  int e10;
  int msb;
  int limbs;
} BigNum_t;

static inline void bignum_deepcpy(BigNum_t *dst, BigNum_t *src) {
  *dst = *src;
  dst->num = (limb_t *)malloc(sizeof(limb_t) * src->limbs);
  s21_memcpy(dst->num, src->num, sizeof(limb_t) * src->limbs);
}

static inline void bignum_clean(BigNum_t *v) {
  if (v->num) {
    free(v->num);
  }
}

static inline unsigned getbit(BigNum_t *v, int limb, int bit) {
  return (v->num[limb] >> bit) & ONE;
}

static inline void setbit(BigNum_t *v, int limb, int bit, uint128_t vbit) {
  v->num[limb] &= ~(ONE << bit);
  v->num[limb] |= vbit << bit;
}

static inline BigNum_t bitshiftr(BigNum_t *v, int shift) {
  BigNum_t shifted = {0};
  bignum_deepcpy(&shifted, v);

  for (int i = 0; i != shift; ++i) {
    for (int cur_limb = 0; cur_limb != shifted.limbs; ++cur_limb) {
      shifted.num[cur_limb] >>= 1;
      if (cur_limb + 1 < shifted.limbs) {
        setbit(&shifted, cur_limb, LIMB_SIZE - 1,
               getbit(&shifted, cur_limb + 1, 0));
      }
    }
  }

  return shifted;
}

static inline BigNum_t bitshiftl(BigNum_t *v, int shift) {
  BigNum_t shifted = {0};
  bignum_deepcpy(&shifted, v);

  for (int i = 0; i != shift; ++i) {
    for (int cur_limb = shifted.limbs - 1; cur_limb >= 0; --cur_limb) {
      shifted.num[cur_limb] <<= 1;
      if (cur_limb - 1 >= 0) {
        setbit(&shifted, cur_limb, 0,
               getbit(&shifted, cur_limb - 1, LIMB_SIZE - 1));
      }
    }
  }

  return shifted;
}

static inline void mul2(BigNum_t *v, const uint128_t m, const int32_t e) {
  for (s21_size_t v_i = v->msb, m_i = 0; m_i != LIMB_SIZE;
       ++v_i, ++m_i, ++v->msb) {
    s21_size_t limb = v_i / LIMB_SIZE;
    s21_size_t bit = v_i % LIMB_SIZE;
    v->num[limb] |= ((m >> m_i) & ONE) << bit;
  }
}

static inline int max(int v1, int v2) { return v1 > v2 ? v1 : v2; }
static inline int min(int v1, int v2) { return v1 < v2 ? v1 : v2; }

static inline BigNum_t bignum_add(BigNum_t *add1, BigNum_t *add2) {
  BigNum_t res = {0};

  BigNum_t *gr = add1->limbs > add2->limbs ? add1 : add2;
  BigNum_t *le = add1->limbs < add2->limbs ? add1 : add2;

  res.num = (limb_t *)malloc(gr->limbs * sizeof(limb_t));

  unsigned carry = 0;
  int msb = 0;

  for (int cur_limb = 0; cur_limb != le->limbs; ++cur_limb) {
    for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = getbit(add1, cur_limb, cur_bit);
      unsigned b2 = getbit(add2, cur_limb, cur_bit);

      unsigned sum = b1 + b2 + carry;
      carry = (sum > 1) ? 1 : 0;
      unsigned bit_to_set = sum == 1 || sum == 3 ? 1 : 0;

      setbit(&res, cur_limb, cur_bit, bit_to_set);

      if (bit_to_set == 1) {
        msb = cur_limb * LIMB_SIZE + cur_bit;
      }
    }
  }

  for (int cur_limb = le->limbs; cur_limb != gr->limbs; ++cur_limb) {
    for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned sum = getbit(gr, cur_limb, cur_bit) + carry;
      carry = (sum > 1) ? 1 : 0;
      unsigned bit_to_set = sum == 1 ? 1 : 0;

      setbit(&res, cur_limb, cur_bit, bit_to_set);

      if (bit_to_set == 1) {
        msb = cur_limb * LIMB_SIZE + cur_bit;
      }
    }
  }

  res.msb = msb;
  res.limbs = gr->limbs;

  return res;
}

static inline void mul10(BigNum_t *v) {
  BigNum_t add1 = bitshiftl(v, 3), add2 = bitshiftl(v, 2);
  BigNum_t res = bignum_add(&add1, &add2);
  bignum_clean(v);
  bignum_clean(&add1);
  bignum_clean(&add2);
  *v = res;
}

static inline void longdiv2(BigNum_t *m, const int e) {
  int e10 = 0;
  for (int i = 0; i != decdigits; ++i) {
    for () {
    }
  }
}

static inline void div2(BigNum_t *q, BigNum_t *r, BigNum_t m, const int e) {
  *q = 0, *r = 0;

  if (e >= 128) {
    s21_memset(q, 0, sizeof(uint128_t));
    s21_memcpy(r, q, sizeof(uint128_t));
  } else {
    *q |= m >> e;
    *r |= m & ((ONE << e) - 1);
  }
}

void flttostr(char *res, const uint128_t bits, const uint32_t manbits,
              const uint32_t expbits, const bool explicit_leading_bit,
              const int decdigits);

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

#endif
