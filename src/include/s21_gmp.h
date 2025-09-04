#ifndef S21_GMP_H
#define S21_GMP_H

#include <assert.h>
#include <stdlib.h>

#include "s21_defines.h"
#include "s21_std.h"

typedef struct mpz_t {
  limb_t *d; /* Pointer to the number */
  int size;  /* Actual number of used limbs */
  int alloc; /* Number of allocated limbs */
  int e10;   /* For scientific notation */
} mpz_t;

void mpz_add(mpz_t *res, mpz_t *val1, mpz_t *val2);
void mpz_sub(mpz_t *res, mpz_t *val1, mpz_t *val2);
void mpz_div(mpz_t *quo, mpz_t *rem, mpz_t *val1, mpz_t *val2);

static inline void mpz_init(mpz_t *val) {
  if (val->d) {
    free(val->d);
  }

  val->d = (limb_t *)calloc(1, sizeof(limb_t));
  val->size = 1;
  val->alloc = 1;
  val->e10 = 0;
}

static inline void mpz_custom_init(mpz_t *val, const uint64_t d, const int size,
                                   const int alloc, const int e10) {
  if (val->d) {
    free(val->d);
  }

  val->d = (limb_t *)calloc(alloc, sizeof(limb_t));
  val->d[0] = (limb_t)d;
  val->size = size;
  val->alloc = alloc;
  val->e10 = e10;
}

static inline void mpz_clear(mpz_t *val) {
  if (val->d) {
    free(val->d);
  }
  val->size = 0;
  val->alloc = 0;
  val->e10 = 0;
}

static inline void mpz_cpy(mpz_t *dst, const mpz_t *src) {
  mpz_clear(dst);

  dst->d = (limb_t *)malloc(sizeof(limb_t) * src->alloc);
  s21_memcpy(dst->d, src->d, sizeof(limb_t) * src->alloc);
  dst->size = src->size;
  dst->alloc = src->alloc;
  dst->e10 = src->e10;
}

static inline unsigned getbit(const mpz_t *val, const int ilimb,
                              const int ibit) {
  assert(ibit >= 0 && ibit < LIMB_SIZE);
  return (val->d[ilimb] >> ibit) & (limb_t)1U;
}

static inline void setbit(mpz_t *val, const int ilimb, const int ibit,
                          limb_t setbit) {
  assert(ilimb < val->alloc);
  assert(ibit >= 0 && ibit < LIMB_SIZE);
  val->d[ilimb] &= ~((limb_t)1U << ibit);
  val->d[ilimb] |= setbit << ibit;
}

static inline void bitshiftr(mpz_t *res, const mpz_t *val, const int shift) {
  mpz_cpy(res, val);
  int cur_limb = 0;

  for (int i = 0; i != shift; ++i) {
    for (cur_limb = 0; cur_limb != res->alloc && res->d[cur_limb]; ++cur_limb) {
      res->d[cur_limb] >>= 1;
      if (cur_limb + 1 < res->alloc) {
        setbit(res, cur_limb, LIMB_SIZE - 1, getbit(res, cur_limb + 1, 0));
      }
    }
  }

  res->size = cur_limb;
}

static inline void bitshiftl(mpz_t *res, const mpz_t *val, const int shift) {
  mpz_cpy(res, val);

  for (int i = 0; i != shift; ++i) {
    for (int cur_limb = res->alloc - 1; cur_limb >= 0; --cur_limb) {
      res->d[cur_limb] <<= 1;
      if (cur_limb - 1 >= 0 && res->d[cur_limb - 1]) {
        setbit(res, cur_limb, 0, getbit(res, cur_limb - 1, LIMB_SIZE - 1));
      }
    }
  }

  int size = 0;
  for (; size != res->alloc && res->d[size]; ++size) {
  }
  res->size = size;
}

static inline void mpz_mul_2exp(mpz_t *res, const mpz_t *val, const int exp) {
  bitshiftl(res, val, exp);
}

static inline void mpz_mul10(mpz_t *res, const mpz_t *val) {
  mpz_t add1, add2;
  mpz_init(&add1), mpz_init(&add2);

  bitshiftl(&add1, val, 3), bitshiftl(&add2, val, 2);
  mpz_add(res, &add1, &add2);

  mpz_clear(&add1);
  mpz_clear(&add2);
}

static inline void mpz_idiv10(mpz_t *quo, mpz_t *rem, mpz_t *val) {}

static inline void mpz_to_str(char *str, mpz_t *val) {}

static inline int mpz_compare(mpz_t *val1, mpz_t *val2) {
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
