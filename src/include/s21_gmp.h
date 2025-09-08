#ifndef S21_GMP_H
#define S21_GMP_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_defines.h"
#include "s21_std.h"

typedef struct mpz_t {
  limb_t *d;       /* Pointer to the number */
  mp_size_t size;  /* Actual number of used limbs */
  mp_size_t alloc; /* Number of allocated limbs */
  mp_size_t e10;   /* For scientific notation */
} mpz_t;

void mpz_add(mpz_t *res, const mpz_t *val1, const mpz_t *val2);
void mpz_sub(mpz_t *res, const mpz_t *val1, const mpz_t *val2);
void mpz_div(mpz_t *quo, mpz_t *rem, const mpz_t *val1, const mpz_t *val2);

static inline void mpz_init(mpz_t *val) {
  val->d = (limb_t *)calloc(1, sizeof(limb_t));
  val->size = 0;
  val->alloc = 1;
  val->e10 = 0;
}

static inline void mpz_realloc(mpz_t *val, mp_size_t new_alloc) {
  limb_t *new_d = (limb_t *)realloc(val->d, new_alloc * sizeof(limb_t));

  val->d = new_d;
  if (new_alloc > val->alloc) {
    s21_memset(val->d + val->alloc, 0,
               (new_alloc - val->alloc) * sizeof(limb_t));
  }
  val->alloc = new_alloc;
}

static inline void mpz_clear(mpz_t *val) {
  if (val->d) {
    free(val->d);
  }
  val->size = 0;
  val->alloc = 0;
  val->e10 = 0;
}

static inline void mpz_set_ull(mpz_t *val, const unsigned long long d) {
  val->d[0] = d;
  val->size = !d ? 0 : 1;
}

static inline void mpz_set(mpz_t *dst, const mpz_t *src) {
  if (dst->alloc < src->size) {
    mpz_realloc(dst, src->size);
  }

  s21_memcpy(dst->d, src->d, src->size * sizeof(limb_t));
  dst->size = src->size;
  dst->e10 = src->e10;
}

static inline void mpz_init_set_ull(mpz_t *val, const unsigned long long d) {
  val->d = (limb_t *)malloc(sizeof(limb_t));
  val->d[0] = d;
  val->size = !d ? 0 : 1;
  val->alloc = 1;
  val->e10 = 0;
}

static inline void mpz_init_set(mpz_t *dst, mpz_t *src) {
  dst->d = (limb_t *)malloc(src->alloc * sizeof(limb_t));
  s21_memcpy(dst->d, src->d, src->alloc * sizeof(limb_t));
  dst->size = src->size;
  dst->alloc = src->alloc;
  dst->e10 = src->e10;
}

static inline unsigned mpz_getbit(const mpz_t *val, const mp_size_t ilimb,
                                  const mp_size_t ibit) {
  assert(ilimb >= 0 && ilimb < val->alloc);
  assert(ibit >= 0 && ibit < LIMB_SIZE);
  return (val->d[ilimb] >> ibit) & (limb_t)1U;
}

static inline void mpz_setbit(mpz_t *val, const int ilimb, const int ibit,
                              limb_t setbit) {
  assert(ilimb >= 0 && ilimb < val->alloc);
  assert(ibit >= 0 && ibit < LIMB_SIZE);
  val->d[ilimb] &= ~((limb_t)1U << ibit);
  val->d[ilimb] |= setbit << ibit;
}

/* Returns index of most significant bit in high word */
static inline int mpz_msb(const mpz_t *val) {
  limb_t hword = val->d[val->size - 1];
  int msb = -1;

  if (hword) {
#ifdef USE_GCC_BUILTINS
    msb = LIMB_SIZE - __builtin_clzll(hword) - 1;
#else
    /* De Bruijn Table */
    static const int BitPosLookup[64] = {
        0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28,
        62, 5,  39, 46, 44, 42, 22, 9,  24, 35, 59, 56, 49, 18, 29, 11,
        63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
        51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};

    hword |= hword >> 1;
    hword |= hword >> 2;
    hword |= hword >> 4;
    hword |= hword >> 8;
    hword |= hword >> 16;
    hword |= hword >> 32;

    msb = BitPosLookup[((limb_t)(hword * 0x022FDD63CC95386DUL)) >> 58];
#endif
  }

  return msb;
}

static inline long long mpz_bitlen(mpz_t *val) {
  return !val->size
             ? 0LL
             : (long long)((val->size - 1) * LIMB_SIZE + mpz_msb(val) + 1);
}

static inline void mpz_bitshiftr(mpz_t *res, const mpz_t *val,
                                 const mp_size_t shift) {
  if (res != val) {
    mpz_set(res, val);
  }

  mp_size_t cur = 0;
  mp_size_t big_shift = shift / LIMB_SIZE;
  mp_size_t small_shift = shift % LIMB_SIZE;

  bool is_zero = false;

  if (big_shift >= res->size) {
    s21_memset(res->d, 0, res->size * sizeof(limb_t));
    res->size = 0;
    is_zero = true;
  }

  if (!is_zero && big_shift) {
    for (; cur != res->size - big_shift; ++cur) {
      res->d[cur] = res->d[cur + big_shift];
    }
    s21_memset(res->d + cur, 0, (res->size - cur) * sizeof(limb_t));
    res->size -= big_shift;
  }

  if (!is_zero && small_shift) {
    for (cur = 0; cur != res->size; ++cur) {
      res->d[cur] >>= small_shift;
      if (cur + 1 < res->size) {
        limb_t carry = res->d[cur + 1] & (((limb_t)1 << small_shift) - 1);
        res->d[cur] |= carry << (LIMB_SIZE - small_shift);
      }
    }

    for (; res->size != 0 && !res->d[res->size - 1]; --res->size) {
    }
  }
}

static inline void mpz_bitshiftl(mpz_t *res, const mpz_t *val,
                                 const mp_size_t shift) {
  mp_size_t new_size = val->size + (mpz_msb(val) + 1 + shift) / LIMB_SIZE;
  if (res->alloc < new_size) {
    mpz_realloc(res, new_size);
  }
  if (res != val) {
    mpz_set(res, val);
  }

  mp_size_t big_shift = shift / LIMB_SIZE;
  mp_size_t small_shift = shift % LIMB_SIZE;

  if (big_shift) {
    for (mp_size_t cur = res->size + big_shift; cur != big_shift; --cur) {
      res->d[cur - 1] = res->d[cur - 1 - big_shift];
    }
    s21_memset(res->d, 0, big_shift * sizeof(limb_t));
  }

  if (small_shift) {
    for (mp_size_t cur = new_size; cur != 0; --cur) {
      res->d[cur - 1] <<= small_shift;
      if (cur > 1) {
        limb_t carry = res->d[cur - 2] >> (LIMB_SIZE - small_shift);
        res->d[cur - 1] |= carry;
      }
    }
  }

  res->size = new_size;
}

static inline void mpz_mul_2exp(mpz_t *res, const mpz_t *val, const int exp) {
  mpz_bitshiftl(res, val, exp);
}

static inline void mpz_mul10(mpz_t *res, const mpz_t *val) {
  mpz_t add1, add2;
  mpz_init(&add1), mpz_init(&add2);

  mpz_bitshiftl(&add1, val, 3), mpz_bitshiftl(&add2, val, 2);
  mpz_add(res, &add1, &add2);

  mpz_clear(&add1);
  mpz_clear(&add2);
}

static inline void mpz_idiv10(mpz_t *quo, mpz_t *rem, mpz_t *val) {}

static inline void mpz_to_str(char *str, mpz_t *val) {}

static inline int mpz_compare(const mpz_t *val1, const mpz_t *val2) {
  int result = 0;

  result = val1->size > val2->size ? 1 : -1;

  if (!result) {
    for (int cur_limb = val1->size - 1; !result && cur_limb >= 0; --cur_limb) {
      result = val1->d[cur_limb] > val2->d[cur_limb] ? 1 : -1;
    }
  }

  return result;
}

static inline void fdiv_2exp(char *res, mpz_t *v, int e, int decdigits) {}

static inline void idiv_2exp(mpz_t *q, mpz_t *r, mpz_t *v, int e) {}

#endif
