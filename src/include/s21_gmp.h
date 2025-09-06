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
  if (val->d) {
    free(val->d);
  }

  val->d = (limb_t *)calloc(1, sizeof(limb_t));
  if (!val->d) {
    printf("Failed to allocate the memory.\n");
    exit(EXIT_FAILURE);
  }
  val->size = 1;
  val->alloc = 1;
  val->e10 = 0;
}

static inline void mpz_custom_init(mpz_t *val, const limb_t d,
                                   const mp_size_t size, const mp_size_t alloc,
                                   const mp_size_t e10) {
  if (val->d) {
    free(val->d);
  }

  val->d = (limb_t *)calloc(alloc, sizeof(limb_t));
  if (!val->d) {
    printf("Failed to allocate the memory.\n");
    exit(EXIT_FAILURE);
  }
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

/* Makes full duplicate of src and writes in dst */
static inline void mpz_copy(mpz_t *dst, const mpz_t *src) {
  if (dst->d) {
    free(dst->d);
  }

  dst->d = (limb_t *)malloc(sizeof(limb_t) * src->alloc);
  if (!dst->d) {
    printf("Failed to allocate the memory.\n");
    exit(EXIT_FAILURE);
  }
  s21_memcpy(dst->d, src->d, sizeof(limb_t) * src->alloc);
  dst->size = src->size;
  dst->alloc = src->alloc;
  dst->e10 = src->e10;
}

/* Sets value from src in dst */
/* Uses already allocated memory */
static inline void mpz_set(mpz_t *dst, const mpz_t *src) {
  assert(src->size <= dst->alloc);
  s21_memcpy(dst->d, src->d, sizeof(limb_t) * src->size);
  s21_memset(dst->d + src->size, 0, sizeof(limb_t) * (dst->alloc - src->size));
  dst->size = src->size;
  dst->e10 = src->e10;
}

static inline void mpz_realloc(mpz_t *val, mp_size_t new_alloc) {
  limb_t *new_d = (limb_t *)realloc(val->d, sizeof(limb_t) * new_alloc);
  if (!new_d) {
    printf("Failed to realloc.\n");
    exit(EXIT_FAILURE);
  } else {
    val->d = new_d;
    if (new_alloc > val->alloc) {
      s21_memset(val->d + val->alloc, 0,
                 sizeof(limb_t) * (new_alloc - val->alloc));
    }
    val->alloc = new_alloc;
  }
}

static inline unsigned getbit(const mpz_t *val, const mp_size_t ilimb,
                              const mp_size_t ibit) {
  assert(ilimb >= 0 && ilimb < val->alloc);
  assert(ibit >= 0 && ibit < LIMB_SIZE);
  return (val->d[ilimb] >> ibit) & (limb_t)1U;
}

static inline void setbit(mpz_t *val, const int ilimb, const int ibit,
                          limb_t setbit) {
  assert(ilimb >= 0 && ilimb < val->alloc);
  assert(ibit >= 0 && ibit < LIMB_SIZE);
  val->d[ilimb] &= ~((limb_t)1U << ibit);
  val->d[ilimb] |= setbit << ibit;
}

static inline void bitshiftr(mpz_t *res, const mpz_t *val, const int shift) {
  if (res != val) {
    mpz_cpy(res, val);
  }

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
  if (res != val) {
    mpz_cpy(res, val);
  }

  for (int i = 0; i != shift; ++i) {
    for (int cur_limb = res->alloc - 1; cur_limb >= 0; --cur_limb) {
      res->d[cur_limb] <<= 1;
      if (cur_limb - 1 >= 0 && res->d[cur_limb - 1]) {
        setbit(res, cur_limb, 0, getbit(res, cur_limb - 1, LIMB_SIZE - 1));
      }
    }
  }

  int size = val->size - 1;
  for (; size != res->alloc && res->d[size]; ++size) {
  }
  res->size = size - 1;
}

static inline long long bitlen(mpz_t *val) {
  int ihword = val->size - 1;
  limb_t hword = val->d[ihword];
  long long bitlen = ihword * LIMB_SIZE;

  if (hword) {
#ifdef USE_GCC_BUILTINS
    bitlen += LIMB_SIZE - __builtin_clzll(hword);
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

    bitlen += BitPosLookup[((limb_t)(hword * 0x022FDD63CC95386DUL)) >> 58] + 1;
#endif
  }

  return bitlen;
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
