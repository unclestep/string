#include "../include/s21_gmp.h"

void mpz_add(mpz_t *res, mpz_t *val1, mpz_t *val2) {
  /* Copy val1, val2 in op1, op2 in case when val1 = res and/or val2 = res */
  mpz_t op1, op2;
  mpz_cpy(&op1, val1), mpz_cpy(&op2, val2);

  mpz_t *gr, *le;
  mpz_compare(&op1, &op2) >= 0 ? (gr = &op1, le = &op2)
                               : (gr = &op2, le = &op1);

  mpz_custom_init(res, 0U, 0, gr->size + 1, 0);

  unsigned carry = 0;
  int cur_limb = 0;

  for (; cur_limb != le->size; ++cur_limb) {
    for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = getbit(gr, cur_limb, cur_bit);
      unsigned b2 = getbit(le, cur_limb, cur_bit);

      unsigned sum = b1 ^ b2 ^ carry;
      carry = (b1 & b2) | (b1 & carry) | (b2 & carry);

      setbit(res, cur_limb, cur_bit, sum);
    }
  }

  for (; cur_limb != gr->size; ++cur_limb) {
    for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = getbit(gr, cur_limb, cur_bit);

      unsigned sum = b1 ^ carry;
      carry = b1 & carry;

      setbit(res, cur_limb, cur_bit, sum);
    }
  }

  if (carry) {
    setbit(res, cur_limb, 0, carry);
  }

  res->size = carry ? cur_limb + 1 : cur_limb;

  mpz_clear(&op1), mpz_clear(&op2);
}

/* Better performance function based on gcc builtins */
void mpz_add_gcc(mpz_t *res, mpz_t *val1, mpz_t *val2) {
  /* Copy val1, val2 in op1, op2 in case when val1 = res and/or val2 = res */
  mpz_t op1, op2;
  mpz_cpy(&op1, val1), mpz_cpy(&op2, val2);

  mpz_t *gr, *le;
  mpz_compare(&op1, &op2) >= 0 ? (gr = &op1, le = &op2)
                               : (gr = &op2, le = &op1);

  mpz_custom_init(res, 0U, 0, gr->size + 1, 0);

  limb_t carry = 0;
  int cur_limb = 0;

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

/* Doesn't return sign of subtraction */
/* val1 always must be >= val2 */
void mpz_sub(mpz_t *res, mpz_t *val1, mpz_t *val2) {
  /* Copy val1, val2 in op1, op2 in case when val1 = res and/or val2 = res */
  mpz_t op1, op2;
  mpz_cpy(&op1, val1), mpz_cpy(&op2, val2);

  mpz_custom_init(res, 0U, 0, op1.size, 0);

  unsigned borrow = 0;
  int cur_limb = 0;

  for (; cur_limb != op2.size; ++cur_limb) {
    for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = getbit(&op1, cur_limb, cur_bit);
      unsigned b2 = getbit(&op2, cur_limb, cur_bit);

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
      borrow = !b1 & (b2 | borrow) | (b2 & borrow);

      setbit(res, cur_limb, cur_bit, dif);
    }
  }

  for (; cur_limb != op1.size && borrow; ++cur_limb) {
    for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = getbit(&op1, cur_limb, cur_bit);

      unsigned dif = b1 ^ borrow;
      borrow = !b1 & borrow;

      setbit(res, cur_limb, cur_bit, dif);
    }
  }

  if (!borrow && cur_limb < op1.size) {
    s21_memcpy(res->d + cur_limb, op1.d + cur_limb,
               (op1.size - cur_limb) * sizeof(limb_t));
  }

  int size = op1.size - 1;
  for (; size >= 0 && !res->d[size]; --size) {
  }
  res->size = size + 1;

  mpz_clear(&op1), mpz_clear(&op2);
}

/* Better performance function based on gcc builtins */
/* Doesn't return sign of subtraction */
/* val1 always must be >= val2 */
void mpz_sub_gcc(mpz_t *res, mpz_t *val1, mpz_t *val2) {
  /* Copy val1, val2 in op1, op2 in case when val1 = res and/or val2 = res */
  mpz_t op1, op2;
  mpz_cpy(&op1, val1), mpz_cpy(&op2, val2);

  mpz_custom_init(res, 0U, 0, op1.size, 0);

  limb_t borrow = 0;
  int cur_limb = 0;

  for (; cur_limb != op2.size; ++cur_limb) {
    res->d[cur_limb] =
        __builtin_subcll(op1.d[cur_limb], op2.d[cur_limb], borrow, &borrow);
  }

  for (; cur_limb != op1.size && borrow; ++cur_limb) {
    res->d[cur_limb] = __builtin_subcll(op1.d[cur_limb], 0, borrow, &borrow);
  }

  if (!borrow && cur_limb < op1.size) {
    s21_memcpy(res->d + cur_limb, op1.d + cur_limb,
               (op1.size - cur_limb) * sizeof(limb_t));
  }

  int size = op1.size - 1;
  for (; size >= 0 && !res->d[size]; --size) {
  }
  res->size = size + 1;

  mpz_clear(&op1), mpz_clear(&op2);
}

void mpz_div(mpz_t *quo, mpz_t *rem, mpz_t *val1, mpz_t *val2) {
  mpz_t work;
  mpz_custom_init(&work, (uint64_t)0U, val1->size, val1->alloc, val1->e10);

  if (val1->size < val2->size && mpz_msb(val1) < mpz_msb(val2)) {
    mpz_init(quo);
    mpz_cpy(rem, val1);
  }
}
