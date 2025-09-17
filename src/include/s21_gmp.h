#ifndef S21_GMP_H
#define S21_GMP_H

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "s21_defines.h"
#include "s21_std.h"

/* MPZ Initialization and Assignment Functions */
static inline void mpz_init(mpz_t *val) {
  val->d = (limb_t *)calloc(1, sizeof(limb_t));
  val->size = 0;
  val->alloc = 1;
}

static inline void mpz_realloc(mpz_t *val, mp_size_t new_alloc) {
  if (new_alloc > 0) {
    limb_t *new_d = (limb_t *)realloc(val->d, new_alloc * sizeof(limb_t));

    val->d = new_d;
    if (new_alloc > val->alloc) {
      s21_memset(val->d + val->alloc, 0,
                 (new_alloc - val->alloc) * sizeof(limb_t));
    }
    val->alloc = new_alloc;
  }
}

static inline void mpz_clear(mpz_t *val) {
  if (val->d) {
    free(val->d);
  }
  val->size = 0;
  val->alloc = 0;
}

static inline void mpz_set_ull(mpz_t *val, unsigned long long d) {
  if (val->size > 1) {
    s21_memset(val->d + 1, 0, (val->size - 1) * sizeof(limb_t));
  }
  val->d[0] = d;
  val->size = !d ? 0 : 1;
}

static inline void mpz_set(mpz_t *dst, const mpz_t *src) {
  if (dst->alloc < src->size) {
    mpz_realloc(dst, src->size);
  }

  s21_memcpy(dst->d, src->d, src->size * sizeof(limb_t));
  if (dst->size > src->size) {
    s21_memset(dst->d + src->size, 0, (dst->size - src->size) * sizeof(limb_t));
  }
  dst->size = src->size;
}

static inline void mpz_init_set_ull(mpz_t *val, unsigned long long d) {
  val->d = (limb_t *)malloc(sizeof(limb_t));
  val->d[0] = d;
  val->size = !d ? 0 : 1;
  val->alloc = 1;
}

static inline void mpz_init_set(mpz_t *dst, const mpz_t *src) {
  dst->d = (limb_t *)malloc(src->alloc * sizeof(limb_t));
  s21_memcpy(dst->d, src->d, src->alloc * sizeof(limb_t));
  dst->size = src->size;
  dst->alloc = src->alloc;
}

/* MPF Initialization Functions */
static inline void mpf_init(mpf_t *val) {
  mpz_init(val->man);
  val->exp = 0;
  val->fig = 0;
}

static inline void mpf_clear(mpf_t *val) {
  mpz_clear(val->man);
  val->exp = 0;
  val->fig = 0;
}

/* Logical, Bit and Bit Manipulation Functions */
void mpz_bitshiftr(mpz_t *res, const mpz_t *val, mp_size_t shift);
void mpz_bitshiftl(mpz_t *res, const mpz_t *val, mp_size_t shift);

static inline unsigned mpz_getbit(const mpz_t *val, mp_size_t ilimb,
                                  mp_size_t ibit) {
  assert(ilimb >= 0 && ilimb < val->alloc);
  assert(ibit >= 0 && ibit < LIMB_SIZE);
  return (val->d[ilimb] >> ibit) & (limb_t)1U;
}

static inline void mpz_setbit(mpz_t *val, int ilimb, int ibit, limb_t setbit) {
  assert(ilimb >= 0);
  assert(ibit >= 0 && ibit < LIMB_SIZE);

  if (ilimb >= val->alloc) mpz_realloc(val, ilimb + 1);
  if (ilimb >= val->size && setbit) val->size = ilimb + 1;

  val->d[ilimb] &= ~((limb_t)1U << ibit);
  val->d[ilimb] |= setbit << ibit;
}

/* Returns index of most significant bit in high word */
static inline int mpz_msb(const mpz_t *val) {
  limb_t hword = val->size ? val->d[val->size - 1] : 0;
  int msb = -1;

  if (hword) {
#ifdef USE_GCC_BUILTINS
    msb = LIMB_SIZE - __builtin_clzll(hword) - 1;
#else
    msb = 0;
    if (hword >= 1UL << 32) {
      msb += 32;
      hword >>= 32;
    }
    if (hword >= 1UL << 16) {
      msb += 16;
      hword >>= 16;
    }
    if (hword >= 1UL << 8) {
      msb += 8;
      hword >>= 8;
    }
    if (hword >= 1UL << 4) {
      msb += 4;
      hword >>= 4;
    }
    if (hword >= 1UL << 2) {
      msb += 2;
      hword >>= 2;
    }
    if (hword >= 1UL << 1) {
      msb += 1;
    }
#endif
  }

  return msb;
}

static inline void mpz_and(mpz_t *res, const mpz_t *val1, const mpz_t *val2) {
  const mpz_t *gr, *le;
  val1->size >= val2->size ? (gr = val1, le = val2) : (gr = val2, le = val1);

  mpz_realloc(res, le->size);

  for (mp_size_t cur_limb = 0; cur_limb < le->size; ++cur_limb) {
    res->d[cur_limb] = gr->d[cur_limb] & le->d[cur_limb];
  }

  for (res->size = le->size; res->size > 0 && !res->d[res->size - 1];
       --res->size) {
  }
}

/* Comparison Functions */
int mpz_cmp(const mpz_t *val1, const mpz_t *val2);

/* Conversion Functions */
void mpf_to_fltnot(char *dst, mpf_t *src, int p);
void mpf_to_scinot(char *dst, mpf_t *src, int p, bool big_e);
void mpz_to_mpf(mpf_t *dst, mpz_t *src);

/* Arithmetic Functions */
void mpz_add(mpz_t *res, const mpz_t *val1, const mpz_t *val2);
void mpz_sub(mpz_t *res, const mpz_t *val1, const mpz_t *val2);
void mpz_div(mpz_t *quo, mpz_t *rem, const mpz_t *val1, const mpz_t *val2);

static inline void mpz_add_ull(mpz_t *res, const mpz_t *val1,
                               unsigned long long val2) {
  mpz_t mpval2;
  mpz_init_set_ull(&mpval2, val2);
  mpz_add(res, val1, &mpval2);
  mpz_clear(&mpval2);
}

static inline void mpz_sub_ull(mpz_t *res, const mpz_t *val1,
                               unsigned long long val2) {
  mpz_t mpval2;
  mpz_init_set_ull(&mpval2, val2);
  mpz_sub(res, val1, &mpval2);
  mpz_clear(&mpval2);
}

static inline void mpz_div_ull(mpz_t *quo, mpz_t *rem, const mpz_t *val1,
                               unsigned long long val2) {
  mpz_t mpval2;
  mpz_init_set_ull(&mpval2, val2);
  mpz_div(quo, rem, val1, &mpval2);
  mpz_clear(&mpval2);
}

static inline void mpz_mul10(mpz_t *res, const mpz_t *val) {
  mpz_t add1, add2;
  mpz_init(&add1), mpz_init(&add2);

  mpz_bitshiftl(&add1, val, 3), mpz_bitshiftl(&add2, val, 2);
  mpz_add(res, &add1, &add2);

  mpz_clear(&add1), mpz_clear(&add2);
}

static inline void mpz_mul_2exp(mpf_t *res, const mpz_t *val, int exp) {
  mpz_t tmp;
  mpz_init(&tmp);

  mpz_bitshiftl(&tmp, val, exp);
  mpz_to_mpf(res, &tmp);

  mpz_clear(&tmp);
}

static inline void mpz_div10(mpz_t *quo, mpz_t *rem, const mpz_t *val) {
  mpz_div_ull(quo, rem, val, 10);
}

static inline void mpz_idiv_2exp(mpz_t *quo, mpz_t *rem, const mpz_t *val,
                                 int exp) {
  mpz_bitshiftr(quo, val, exp);

  mpz_t mask;
  mpz_init_set_ull(&mask, 1);
  mpz_bitshiftl(&mask, &mask, exp);
  mpz_sub_ull(&mask, &mask, 1);

  mpz_and(rem, val, &mask);

  mpz_clear(&mask);
}

void mpz_fdiv_2exp(mpf_t *res, const mpz_t *val, int exp, int p);

/* Rounding Functions */
void mpf_rint(mpf_t *val, int p);

/* Miscellaneous Functions */
static inline s21_size_t mpz_sizeinbase2(const mpz_t *val) {
  return val->size
             ? (s21_size_t)((val->size - 1) * LIMB_SIZE + mpz_msb(val) + 1)
             : 0;
}

/* The result will be exact or 1 too big */
static inline s21_size_t mpz_sizeinbase10(const mpz_t *val) {
  return (s21_size_t)(LOG10_2 * mpz_sizeinbase2(val)) + 1;
}

/* The result will be always exact but the function is performance demanding */
static inline s21_size_t mpz_exactsizeinbase10(const mpz_t *val) {
  mpz_t checker;
  mpz_init_set_ull(&checker, 1);

  s21_size_t size = mpz_sizeinbase10(val); /* For now this is inexact */

  for (s21_size_t i = size; i > 0; --i) {
    mpz_mul10(&checker, &checker);
  }

  if (mpz_cmp(&checker, val) == 1) {
    size -= 1; /* And now this is exact */
  }

  mpz_clear(&checker);

  return size;
}

static inline bool mpz_odd(const mpz_t *val) { return mpz_getbit(val, 0, 0); }

#endif
