#include "../include/s21_gmp.h"

#include <stdio.h>

/* Arithmetic Functions */
#ifdef USE_GCC_BUILTINS
/* Better performance function based on gcc builtins */
void mpz_add(mpz_t *res, const mpz_t *val1, const mpz_t *val2) {
  /* Copy val1, val2 in op1, op2 in case when val1 = res and/or val2 = res */
  mpz_t op1, op2;
  mpz_init_set(&op1, val1), mpz_init_set(&op2, val2);

  mpz_t *gr, *le;
  mpz_cmp(&op1, &op2) >= 0 ? (gr = &op1, le = &op2) : (gr = &op2, le = &op1);

  if (op1.size == op2.size && mpz_msb(gr) == 63 && mpz_msb(le) == 63) {
    mpz_realloc(res, gr->size + 1);
  } else {
    mpz_realloc(res, gr->size);
  }

  limb_t carry = 0;
  mp_size_t cur_limb = 0;

  for (; cur_limb != le->size; ++cur_limb) {
    res->d[cur_limb] =
        __builtin_addcll(gr->d[cur_limb], le->d[cur_limb], carry, &carry);
  }

  for (; cur_limb != gr->size; ++cur_limb) {
    res->d[cur_limb] = __builtin_addcll(gr->d[cur_limb], 0U, carry, &carry);
  }

  if (carry) {
    res->d[cur_limb] = carry;
  }

  res->size = carry ? cur_limb + 1 : cur_limb;

  mpz_clear(&op1), mpz_clear(&op2);
}
#else
void mpz_add(mpz_t *res, const mpz_t *val1, const mpz_t *val2) {
  /* Copy val1, val2 in op1, op2 in case when val1 = res and/or val2 = res */
  mpz_t op1, op2;
  mpz_init_set(&op1, val1), mpz_init_set(&op2, val2);

  mpz_t *gr, *le;
  op1.size >= op2.size ? (gr = &op1, le = &op2) : (gr = &op2, le = &op1);

  if (op1.size == op2.size && mpz_msb(gr) == 63 && mpz_msb(le) == 63) {
    mpz_realloc(res, gr->size + 1);
  } else {
    mpz_realloc(res, gr->size);
  }

  unsigned carry = 0;
  mp_size_t cur_limb = 0;

  for (; cur_limb != le->size; ++cur_limb) {
    for (mp_size_t cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = mpz_getbit(gr, cur_limb, cur_bit);
      unsigned b2 = mpz_getbit(le, cur_limb, cur_bit);

      unsigned sum = b1 ^ b2 ^ carry;
      carry = (b1 & b2) | (b1 & carry) | (b2 & carry);

      mpz_setbit(res, cur_limb, cur_bit, sum);
    }
  }

  for (; cur_limb != gr->size; ++cur_limb) {
    for (mp_size_t cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = mpz_getbit(gr, cur_limb, cur_bit);

      unsigned sum = b1 ^ carry;
      carry = b1 & carry;

      mpz_setbit(res, cur_limb, cur_bit, sum);
    }
  }

  if (carry) {
    mpz_setbit(res, cur_limb, 0, carry);
  }

  res->size = carry ? cur_limb + 1 : cur_limb;

  mpz_clear(&op1), mpz_clear(&op2);
}
#endif

#ifdef USE_GCC_BUILTINS
/* Better performance function based on gcc builtins */
/* Doesn't return sign of subtraction */
/* val1 always must be >= val2 */
void mpz_sub(mpz_t *res, const mpz_t *val1, const mpz_t *val2) {
  /* Copy val1, val2 in op1, op2 in case when val1 = res and/or val2 = res */
  mpz_t op1, op2;
  mpz_init_set(&op1, val1), mpz_init_set(&op2, val2);

  mpz_realloc(res, op1.size);

  limb_t borrow = 0;
  mp_size_t cur_limb = 0;

  for (; cur_limb != op2.size; ++cur_limb) {
    res->d[cur_limb] =
        __builtin_subcll(op1.d[cur_limb], op2.d[cur_limb], borrow, &borrow);
  }

  for (; cur_limb != op1.size; ++cur_limb) {
    res->d[cur_limb] = __builtin_subcll(op1.d[cur_limb], 0, borrow, &borrow);
  }

  for (res->size = op1.size; res->size > 0 && !res->d[res->size - 1];
       --res->size) {
  }

  mpz_clear(&op1), mpz_clear(&op2);
}
#else
/* Doesn't return sign of subtraction */
/* val1 always must be >= val2 */
void mpz_sub(mpz_t *res, const mpz_t *val1, const mpz_t *val2) {
  /* Copy val1, val2 in op1, op2 in case when val1 = res and/or val2 = res */
  mpz_t op1, op2;
  mpz_init_set(&op1, val1), mpz_init_set(&op2, val2);

  mpz_realloc(res, op1.size);

  unsigned borrow = 0;
  mp_size_t cur_limb = 0;

  for (; cur_limb != op2.size; ++cur_limb) {
    for (mp_size_t cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = mpz_getbit(&op1, cur_limb, cur_bit);
      unsigned b2 = mpz_getbit(&op2, cur_limb, cur_bit);

      unsigned dif = b1 ^ b2 ^ borrow;
      /* Let's take b1 = a, b2 = b, borrow = l.
       * Then, there are 4 cases when we have a borrow:
       * (!a * b * l) + (!a * b * !l) + (!a * !b * l) + (a * b * l)
       * Simplifying: !a * (b * l + b * !l + !b * l) + (a * b * l)
       * !a * (b + !b * l) + (a * b * l)
       * !a * (b + l) + (a * b * l)
       * (!a * b) + (!a * l) + (a * b * l)
       * (!a * b) + l * (!a + a * b)
       * (!a * b) + l * (!a * b)
       * (!a * b) + (!a * l) + (b * l)
       * !a * (b + l) + (b * l) */
      borrow = ((!b1) & b2) | ((!b1) & borrow) | (b2 & borrow);

      mpz_setbit(res, cur_limb, cur_bit, dif);
    }
  }

  for (; cur_limb != op1.size; ++cur_limb) {
    for (mp_size_t cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = mpz_getbit(&op1, cur_limb, cur_bit);

      unsigned dif = b1 ^ borrow;
      borrow = (!b1) & borrow;

      mpz_setbit(res, cur_limb, cur_bit, dif);
    }
  }

  for (res->size = op1.size; res->size > 0 && !res->d[res->size - 1];
       --res->size) {
  }

  mpz_clear(&op1), mpz_clear(&op2);
}
#endif

void mpz_div(mpz_t *quo, mpz_t *rem, const mpz_t *val1, const mpz_t *val2) {
  if (mpz_cmp(val1, val2) == -1) {
    mpz_set(rem, val1);
    mpz_set_ull(quo, 0);
  } else {
    mpz_t minue, subtr;
    mpz_init_set(&minue, val1), mpz_init_set(&subtr, val2);
    mpz_realloc(&subtr, minue.size);

    mpz_erase(quo), mpz_erase(rem);

    long bitdif = mpz_sizeinbase2(&minue) - mpz_sizeinbase2(&subtr);
    mpz_bitshiftl(&subtr, &subtr, bitdif);

    for (; bitdif >= 0; --bitdif) {
      mpz_bitshiftl(quo, quo, 1);
      if (mpz_cmp(&minue, &subtr) >= 0) {
        mpz_sub(&minue, &minue, &subtr);
        mpz_setbit(quo, 0, 0, 1);
      }
      mpz_bitshiftr(&subtr, &subtr, 1);
    }

    mpz_set(rem, &minue);
    mpz_clear(&minue), mpz_clear(&subtr);
  }
}

/* NOTE: Always use in pair with mpz_rint to get correct output */
/* This foo generates guard and sticky digits and always iterates p + 2 times */
void mpz_fdiv_2exp(mpf_t *res, const mpz_t *val, int exp, int p) {
  mpz_t quo, rem;
  mpz_init(&quo), mpz_init(&rem);

  mpz_idiv_2exp(&res->man, &rem, val, exp);
  res->fig = mpz_exactsizeinbase10(&res->man);
  res->exp = res->man.size ? res->fig - 1 : -1;

  bool is_signif = res->man.size;
  bool was_divided = true;
  /* If there is no whole part, for sci-notation we need an extra digit */
  p = p + 2 + !is_signif; /* Get guard and sticky digits */

  /* Only to get know if rem < divisor */
  mpz_t divisor;
  mpz_init_set_ull(&divisor, 1);
  mpz_bitshiftl(&divisor, &divisor, exp);

  for (; p && rem.size; p -= is_signif, ++res->fig) {
    mpz_mul10(&rem, &rem);
    mpz_mul10(&res->man, &res->man);

    if (mpz_cmp(&rem, &divisor) == -1) {
      was_divided = false;
      res->exp -= !is_signif;
    } else {
      was_divided = true;
      is_signif = true;

      mpz_idiv_2exp(&quo, &rem, &rem, exp);
      mpz_add(&res->man, &res->man, &quo);
    }
  }

  for (; p; --p, ++res->fig) {
    mpz_mul10(&res->man, &res->man);
  }

  /* Somehow mark if the fraction is not ended */
  /* This is the case when guard = [0, 9], sticky = 0, rem > 0 */
  if (!was_divided) {
    mpz_add_ull(&res->man, &res->man, 1); /* Will be rounded correctly */
  }

  mpz_clear(&quo), mpz_clear(&rem), mpz_clear(&divisor);
}

/* p - target figures that the value should have */
/* For example, val = 1.23456e+05 (123456), p = 3, final = 1.23e+05 (123000) */
/* For example, val = 1.23456e+02 (123.456), p = 3, final = 1.23e+02 (123) */
/* For example, val = 5.23e-03 (0.00523), p = 4, final = 5e-03 (0.005) */
/* For example, val = 5.23e-03 (0.00523), p = 0, final = 0e+00 (0) */
/* If you're operating with standard notation and want to round the num */
/* Like this: 123.456789 (1.23456789e+02) -> 123.46 (1.23460000e+02) */
/* Use the following formula for p: */
/* val->exp >= 0: val->exp + 1 + desirable_after_dot_precision */
/* val->exp < 0: 1 + desirable_after_dot_precision */
/* NOTE: Any other function must handle the case when p > val's figures */
void mpf_rint(mpf_t *val, int p) {
  mpz_t quo, rem;
  mpz_init(&quo), mpz_init(&rem);

  limb_t guard = 0;
  bool sticky = false;

  for (; val->fig > p; --val->fig) {
    mpz_div10(&val->man, &rem, &val->man);

    if (val->fig - p == 1) {
      guard = rem.d[0];
    } else if (rem.d[0]) {
      sticky = true;
    }
  }

  if (guard > 5 || (guard == 5 && (sticky || mpz_odd(&val->man)))) {
    mpz_div10(&quo, &rem, &val->man);

    if (rem.d[0] == 9) {
      val->exp += 1;

      if (val->exp > 0) val->fig += 1;
    }

    mpz_add_ull(&val->man, &val->man, 1);
  }

  mpz_clear(&quo), mpz_clear(&rem);
}

/* Comparison Functions */
int mpz_cmp(const mpz_t *val1, const mpz_t *val2) {
  int result = 0;

  if (val1->size > val2->size) {
    result = 1;
  } else if (val1->size < val2->size) {
    result = -1;
  }

  for (long cur_limb = val1->size - 1; !result && cur_limb >= 0; --cur_limb) {
    if (val1->d[cur_limb] > val2->d[cur_limb]) {
      result = 1;
    } else if (val1->d[cur_limb] < val2->d[cur_limb]) {
      result = -1;
    }
  }

  return result;
}

/* Logical, Bit and Bit Manipulation Functions */
void mpz_bitshiftr(mpz_t *res, const mpz_t *val, mp_size_t shift) {
  bool is_zero = !val->size;

  if (!is_zero && res != val) {
    mpz_set(res, val);
  }

  mp_size_t cur_limb = 0;
  mp_size_t big_shift = shift / LIMB_SIZE;
  mp_size_t small_shift = shift % LIMB_SIZE;

  if (!is_zero && big_shift >= res->size) {
    s21_memset(res->d, 0, res->size * sizeof(limb_t));
    res->size = 0;
    is_zero = true;
  }

  if (!is_zero && big_shift) {
    for (; cur_limb != res->size - big_shift; ++cur_limb) {
      res->d[cur_limb] = res->d[cur_limb + big_shift];
    }
    s21_memset(res->d + cur_limb, 0, (res->size - cur_limb) * sizeof(limb_t));
    res->size -= big_shift;
  }

  if (!is_zero && small_shift) {
    for (cur_limb = 0; cur_limb != res->size; ++cur_limb) {
      res->d[cur_limb] >>= small_shift;
      if (cur_limb + 1 < res->size) {
        limb_t carry = res->d[cur_limb + 1] & (((limb_t)1 << small_shift) - 1);
        res->d[cur_limb] |= carry << (LIMB_SIZE - small_shift);
      }
    }

    for (; res->size != 0 && !res->d[res->size - 1]; --res->size) {
    }
  }
}

void mpz_bitshiftl(mpz_t *res, const mpz_t *val, mp_size_t shift) {
  mp_size_t new_size =
      val->size ? ceil((double)(mpz_sizeinbase2(val) + shift) / LIMB_SIZE) : 0;
  bool is_zero = !new_size;

  if (!is_zero && res->alloc < new_size) {
    mpz_realloc(res, new_size);
  }
  if (!is_zero && res != val) {
    mpz_set(res, val);
  }

  mp_size_t big_shift = shift / LIMB_SIZE;
  mp_size_t small_shift = shift % LIMB_SIZE;

  if (!is_zero && big_shift) {
    for (mp_size_t cur_limb = res->size + big_shift; cur_limb != big_shift;
         --cur_limb) {
      res->d[cur_limb - 1] = res->d[cur_limb - 1 - big_shift];
    }
    s21_memset(res->d, 0, big_shift * sizeof(limb_t));
  }

  if (!is_zero && small_shift) {
    for (mp_size_t cur_limb = new_size; cur_limb != 0; --cur_limb) {
      res->d[cur_limb - 1] <<= small_shift;
      if (cur_limb > 1) {
        limb_t carry = res->d[cur_limb - 2] >> (LIMB_SIZE - small_shift);
        res->d[cur_limb - 1] |= carry;
      }
    }
  }

  res->size = new_size;
}

/* Conversion Functions */
/* NOTE: Use mpz_sizeinbase10 to properly allocate the memory for the string */
void mpf_to_fltnot(char *dst, mpf_t *src, int p) {
  int wholes = src->exp >= 0 ? src->exp + 1 : 1;

  mpf_rint(src, wholes + p);
  wholes = src->exp >= 0 ? src->exp + 1 : 1;

  /* wholes[wholes] + dot[1] + prec[prec] */

  int fracs = src->exp >= 0 ? src->fig - src->exp - 1 : src->fig - 1;
  int pdif = p > fracs ? p - fracs : 0;

  /* pdif > 0 for cases when src is whole but p > 0 (trailing zeros) */
  int cur = wholes + p + (fracs > 0 || pdif > 0);

  dst[cur--] = '\0';

  for (; pdif != 0; --pdif) {
    dst[cur--] = '0';
  }

  mpz_t quo, rem;
  mpz_init_set(&quo, &src->man), mpz_init(&rem);

  for (int fig = src->fig; fig > 0; --fig) {
    if (fig == wholes && p) {
      dst[cur--] = '.';
    }
    mpz_div10(&quo, &rem, &quo);
    dst[cur--] = rem.d[0] + '0';
  }

  mpz_clear(&quo), mpz_clear(&rem);
}

/* NOTE: Use mpz_sizeinbase10 to properly allocate the memory for the string */
/* NOTE: Argument p accepts the fractional precision */
void mpf_to_scinot(char *dst, mpf_t *src, int p, bool big_e) {
  src->exp >= 0 ? mpf_rint(src, p + 1) : mpf_rint(src, abs(src->exp) + p + 1);

  /* whole[1] + dot[1] + prec[p] + e[1] + e_sign[1] + e_len[up to 3] */
  char e = big_e ? 'E' : 'e';
  char e_sign = src->exp >= 0 ? '+' : '-';
  int e_len = abs(src->exp) < 100 ? 2 : 3;
  int e_val = abs(src->exp);

  int fracs = src->exp >= 0 ? src->fig - 1 : src->fig - e_val - 1;
  int pdif = p > fracs ? p - fracs : 0;

  /* fracs > 0 && p — case when there are trailing zero but p == 0 */
  int cur = p + e_len + 3 + ((fracs > 0 && p) || pdif > 0);

  dst[cur--] = '\0';

  for (int i = 0; i != e_len; ++i, e_val /= 10) {
    dst[cur--] = e_val % 10 + '0';
  }

  dst[cur--] = e_sign;
  dst[cur--] = e;

  for (; pdif != 0; --pdif) {
    dst[cur--] = '0';
  }

  mpz_t quo, rem;
  mpz_init_set(&quo, &src->man), mpz_init(&rem);

  for (int f = fracs; f > 0; --f) {
    mpz_div10(&quo, &rem, &quo);
    /* We have unnormalized number so we need to skip trailing zeros */
    if (f <= p) {
      dst[cur--] = rem.d[0] + '0';
    }
  }

  if (p) dst[cur--] = '.';
  mpz_div10(&quo, &rem, &quo);
  dst[cur] = rem.d[0] + '0';

  mpz_clear(&quo), mpz_clear(&rem);
}

/* The result will be always exact but the function is performance demanding */
s21_size_t mpz_exactsizeinbase10(const mpz_t *val) {
  s21_size_t size = mpz_sizeinbase10(val); /* For now this is inexact */

  if (val->size) {
    mpz_t sizechecker;
    mpz_init_set_ull(&sizechecker, 1);

    for (s21_size_t i = 1; i != size; ++i) {
      mpz_mul10(&sizechecker, &sizechecker);
    }

    if (mpz_cmp(val, &sizechecker) == -1) {
      size -= 1; /* And now this is exact */
    }

    mpz_clear(&sizechecker);
  }

  return size;
}

void mpz_to_mpf(mpf_t *dst, mpz_t *src) {
  mpz_set(&dst->man, src);
  dst->fig = mpz_exactsizeinbase10(src);
  dst->exp = dst->fig - 1;
}
