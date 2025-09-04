#include "../include/s21_gmp.h"

void mpz_add(mpz_t *res, mpz_t *val1, mpz_t *val2) {
  mpz_t *gr, *le;
  mpz_compare(val1, val2) >= 0 ? (gr = val1, le = val2)
                               : (gr = val2, le = val1);

  mpz_custom_init(res, (uint64_t)0U, 0, gr->alloc + 1, 0);

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
      unsigned b = getbit(gr, cur_limb, cur_bit);

      unsigned sum = b ^ carry;
      carry = b & carry;

      setbit(res, cur_limb, cur_bit, sum);
    }
  }

  res->size = cur_limb;
}

/* Works properly only if val1 >= val2 */
void mpz_sub(mpz_t *res, mpz_t *val1, mpz_t *val2) {
  mpz_custom_init(res, (uint64_t)0U, 0, val1->alloc, 0);

  unsigned borrow = 0;

  for (int cur_limb = 0; cur_limb != val1->size; ++cur_limb) {
    for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
      unsigned b1 = getbit(val1, cur_limb, cur_bit);
      unsigned b2 = getbit(val2, cur_limb, cur_bit);

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

  int size = res->alloc - 1;
  for (; size >= 0 && !res->d[size]; --size) {
  }
  res->size = size + 1;
}

void mpz_div(mpz_t *quo, mpz_t *rem, mpz_t *val1, mpz_t *val2) {}
