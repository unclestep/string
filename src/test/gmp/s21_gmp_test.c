#include "s21_gmp_test.h"

#include <math.h>

START_TEST(mpz_msb_all_ind) {
  mpz_t op;
  mpz_init(&op);

  ck_assert_int_eq(mpz_msb(&op), -1);
  mpz_set_ull(&op, 1ULL);

  for (int i = 0; i != 64; ++i) {
    ck_assert_int_eq(mpz_msb(&op), i);
    mpz_bitshiftl(&op, &op, 1);
  }

  mpz_clear(&op);
}
END_TEST

START_TEST(mpz_exactsizeinbase10_big_scope) {
  mpz_t op;
  mpz_init(&op);

  ck_assert_int_eq(mpz_exactsizeinbase10(&op), 1);

  mpz_set_ull(&op, 1ULL);

  for (int i = 1; i != 1001; ++i) {
    ck_assert_int_eq(mpz_exactsizeinbase10(&op), floor(log10(i)) + 1);
    mpz_add_ull(&op, &op, 1ULL);
  }

  mpz_clear(&op);
}
END_TEST

START_TEST(mpz_bitwise_and) {
  mpz_t op1, op2, rop, exp;
  mpz_init_set_ull(&op1, 0xABCDEFABCDEFABCDULL);
  mpz_init_set_ull(&op2, 0xFFFFULL);
  mpz_init(&rop);
  mpz_init_set_ull(&exp, 0xABCDULL);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_bitshifts) {
  mpz_t op, rop;
  mpz_init_set_ull(&op, 1);
  mpz_init(&rop);

  mpz_bitshiftl(&rop, &op, 127);
  mpz_bitshiftl(&op, &op, 127);

  ck_assert_int_eq(mpz_cmp(&rop, &op), 0);
  ck_assert_int_eq(mpz_getbit(&rop, 1, 63), 1);
  ck_assert_int_eq(rop.size, 2);
  ck_assert_int_eq(op.size, 2);

  mpz_bitshiftl(&rop, &rop, 0);
  ck_assert_int_eq(mpz_getbit(&rop, 1, 63), 1);
  ck_assert_int_eq(rop.size, 2);

  mpz_bitshiftl(&rop, &rop, 1);
  ck_assert_int_eq(mpz_getbit(&rop, 2, 0), 1);
  ck_assert_int_eq(rop.size, 3);

  mpz_bitshiftr(&rop, &rop, 128);
  ck_assert_int_eq(mpz_getbit(&rop, 0, 0), 1);
  ck_assert_int_eq(rop.size, 1);

  mpz_bitshiftr(&rop, &rop, 1);
  ck_assert_int_eq(mpz_getbit(&rop, 0, 0), 0);
  ck_assert_int_eq(rop.size, 0);

  mpz_clear(&op), mpz_clear(&rop);
}
END_TEST

START_TEST(mpz_add_carry_1_limb) {
  mpz_t op1, op2, rop, exp;
  mpz_init_set_ull(&op1, 0xFFFFFFFFFFFFFFFULL);
  mpz_init_set_ull(&op2, 1);
  mpz_init(&rop);
  mpz_init_set_ull(&exp, 0x1000000000000000ULL);

  mpz_add(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_add_carry_2_limb) {
  mpz_t op1, op2, rop, exp;
  mpz_init_set_ull(&op1, 0xFFFFFFFFFFFFFFFFULL);
  mpz_init_set_ull(&op2, 0x8000000000000000ULL);
  mpz_init(&rop);
  mpz_init_set_ull(&exp, 0x7FFFFFFFFFFFFFFFULL);
  mpz_realloc(&exp, 2);
  mpz_setbit(&exp, 1, 0, 1);
  exp.size = 2;

  mpz_add(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&exp, &rop), 0);
  ck_assert_int_eq(rop.size, 2);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_add_no_carry_1_limb) {
  mpz_t op1, op2, rop, exp;
  mpz_init_set_ull(&op1, 0xAAAAAAAAAAAAAAAAULL);
  mpz_init_set_ull(&op2, 0x5555555555555555ULL);
  mpz_init(&rop), mpz_init_set_ull(&exp, 0xFFFFFFFFFFFFFFFFULL);

  mpz_add(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_add_no_carry_2_limb) {
  mpz_t op1, op2, rop, exp;

  mpz_init_set_ull(&op1, 0xAAAAAAAAAAAAAAAAULL);
  mpz_realloc(&op1, 2);
  op1.d[1] = 0xAAAAAAAAAAAAAAAAULL;
  op1.size = 2;

  mpz_init_set_ull(&op2, 0x5555555555555555ULL);
  mpz_realloc(&op2, 2);
  op2.d[1] = 0x5555555555555555ULL;
  op2.size = 2;

  mpz_init(&rop);

  mpz_init(&exp);
  mpz_realloc(&exp, 2);
  exp.d[0] = 0xFFFFFFFFFFFFFFFFULL;
  exp.d[1] = 0xFFFFFFFFFFFFFFFFULL;
  exp.size = 2;

  mpz_add(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 2);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_add_zero_right) {
  mpz_t op1, op2, rop, exp;

  mpz_init_set_ull(&op1, 0xAAAAAAAAAAAAAAAAULL);
  mpz_init(&op2);
  mpz_init(&rop);

  mpz_init_set_ull(&exp, 0xAAAAAAAAAAAAAAAAULL);

  mpz_add(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_add_zero_left) {
  mpz_t op1, op2, rop, exp;

  mpz_init(&op1);
  mpz_init_set_ull(&op2, 0xAAAAAAAAAAAAAAAAULL);
  mpz_init(&rop);

  mpz_init_set_ull(&exp, 0xAAAAAAAAAAAAAAAAULL);

  mpz_add(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_add_zero_both) {
  mpz_t op1, op2, rop, exp;

  mpz_init(&op1);
  mpz_init(&op2);
  mpz_init(&rop);

  mpz_init(&exp);

  mpz_add(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 0);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_add_mixed) {
  mpz_t op1, op2, rop, exp;

  mpz_init_set_ull(&op1, 0x8888888888888888ULL);
  mpz_init_set_ull(&op2, 0xBBBBBBBBBBBBBBBBULL);
  mpz_init(&rop);

  mpz_init_set_ull(&exp, 0x4444444444444443ULL);
  mpz_realloc(&exp, 2);
  mpz_setbit(&exp, 1, 0, 1);
  exp.size = 2;

  mpz_add(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 2);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_sub_borrow_1_limb_1) {
  mpz_t op1, op2, rop, exp;

  mpz_init_set_ull(&op1, 0x8000000000000000ULL);
  mpz_init_set_ull(&op2, 0x7FFFFFFFFFFFFFFFULL);
  mpz_init(&rop);

  mpz_init_set_ull(&exp, 1ULL);

  mpz_sub(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_sub_borrow_1_limb_2) {
  mpz_t op1, op2, rop, exp;

  mpz_init_set_ull(&op1, 0x8000000080000000ULL);
  mpz_init_set_ull(&op2, 0x111111111ULL);
  mpz_init(&rop);

  mpz_init_set_ull(&exp, 0x7FFFFFFF6EEEEEEFULL);

  mpz_sub(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_sub_borrow_2_limb_1) {
  mpz_t op1, op2, rop, exp;

  mpz_init(&op1);
  mpz_realloc(&op1, 2);
  mpz_setbit(&op1, 1, 0, 1);
  op1.size = 2;

  mpz_init_set_ull(&op2, 1ULL);
  mpz_init(&rop);

  mpz_init_set_ull(&exp, 0xFFFFFFFFFFFFFFFFULL);

  mpz_sub(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_sub_borrow_2_limb_2) {
  mpz_t op1, op2, rop, exp;

  mpz_init(&op1);
  mpz_realloc(&op1, 2);
  mpz_setbit(&op1, 1, 0, 1);
  mpz_setbit(&op1, 1, 1, 1);
  op1.size = 2;

  mpz_init_set_ull(&op2, 1ULL);
  mpz_init(&rop);

  mpz_init_set_ull(&exp, 0xFFFFFFFFFFFFFFFFULL);
  mpz_realloc(&exp, 2);
  mpz_setbit(&exp, 1, 1, 1);
  exp.size = 2;

  mpz_sub(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 2);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_sub_no_borrow_1_limb) {
  mpz_t op1, op2, rop, exp;

  mpz_init_set_ull(&op1, 0xFFFFULL);
  mpz_init_set_ull(&op2, 0xFFFFULL);
  mpz_init(&rop);

  mpz_init(&exp);

  mpz_sub(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 0);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_sub_no_borrow_2_limb) {
  mpz_t op1, op2, rop, exp;

  mpz_init_set_ull(&op1, 0xFFFFULL);
  mpz_realloc(&op1, 2);
  op1.d[1] = 0xFFFFULL;
  op1.size = 2;

  mpz_init_set_ull(&op2, 0xFFFFULL);
  mpz_realloc(&op2, 2);
  op2.d[1] = 0xFFFFULL;
  op2.size = 2;

  mpz_init(&rop);

  mpz_init(&exp);

  mpz_sub(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 0);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_sub_zero_right) {
  mpz_t op1, op2, rop, exp;

  mpz_init_set_ull(&op1, 0xFFFFULL);
  mpz_init(&op2);
  mpz_init(&rop);

  mpz_init_set_ull(&exp, 0xFFFFULL);

  mpz_sub(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_sub_zero_both) {
  mpz_t op1, op2, rop, exp;

  mpz_init(&op1);
  mpz_init(&op2);
  mpz_init(&rop);
  mpz_init(&exp);

  mpz_sub(&rop, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 0);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_mul_2exp_default) {
  mpf_t rop;
  mpf_init(&rop);

  mpz_t op;
  mpz_init_set_ull(&op, 0xABCDEFULL);

  mpz_mul_2exp(&rop, &op, 21);

  ck_assert_int_eq(rop.man.d[0], 0x1579BDE00000ULL);
  ck_assert_int_eq(rop.exp, 13);
  ck_assert_int_eq(rop.fig, 14);

  mpz_clear(&op), mpf_clear(&rop);
}
END_TEST

START_TEST(mpz_mul_2exp_zero_exp) {
  mpf_t rop;
  mpf_init(&rop);

  mpz_t op;
  mpz_init_set_ull(&op, 0xABCDEFULL);

  mpz_mul_2exp(&rop, &op, 0);

  ck_assert_int_eq(rop.man.d[0], 0xABCDEFULL);
  ck_assert_int_eq(rop.exp, 7);
  ck_assert_int_eq(rop.fig, 8);

  mpz_clear(&op), mpf_clear(&rop);
}
END_TEST

START_TEST(mpz_mul10_once) {
  mpz_t op, rop, exp;

  mpz_init_set_ull(&op, 123456789ULL);
  mpz_init(&rop);
  mpz_init_set_ull(&exp, 1234567890ULL);

  mpz_mul10(&rop, &op);

  ck_assert_int_eq(mpz_cmp(&rop, &exp), 0);
  ck_assert_int_eq(rop.size, 1);

  mpz_clear(&op), mpz_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_mul10_many) {
  mpz_t op, exp;

  mpz_init_set_ull(&op, 123456789ULL);
  mpz_init_set_ull(&exp, 123456789000000ULL);

  for (int i = 0; i != 6; ++i) {
    mpz_mul10(&op, &op);
  }

  ck_assert_int_eq(mpz_cmp(&op, &exp), 0);
  ck_assert_int_eq(op.size, 1);

  mpz_clear(&op), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_div_left_less) {
  mpz_t op1, op2, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op1, 3);
  mpz_init_set_ull(&op2, 6);
  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init(&equo);
  mpz_init_set_ull(&erem, 3);

  mpz_div(&rquo, &rrem, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 0);
  ck_assert_int_eq(rrem.size, 1);

  mpz_clear(&op1), mpz_clear(&op2);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_div_no_rem_1) {
  mpz_t op1, op2, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op1, 121401);
  mpz_init_set_ull(&op2, 123);
  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 987);
  mpz_init_set_ull(&erem, 0);

  mpz_div(&rquo, &rrem, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 1);
  ck_assert_int_eq(rrem.size, 0);

  mpz_clear(&op1), mpz_clear(&op2);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_div_no_rem_2) {
  mpz_t op1, op2, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op1, 0xFFFFFFFFFFFFFFFFULL);
  mpz_realloc(&op1, 2);
  op1.d[1] = 0xFFFFFFFFFFFFFFFFULL;
  op1.size = 2;

  mpz_init_set_ull(&op2, 0xFFFFFFFFFFFFFFFFULL);
  mpz_realloc(&op2, 2);
  op2.d[1] = 0xFFFFFFFFFFFFFFFFULL;
  op2.size = 2;

  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 1);
  mpz_init_set_ull(&erem, 0);

  mpz_div(&rquo, &rrem, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 1);
  ck_assert_int_eq(rrem.size, 0);

  mpz_clear(&op1), mpz_clear(&op2);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_div_with_rem_1) {
  mpz_t op1, op2, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op1, 1234567890);
  mpz_init_set_ull(&op2, 333);

  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 3707411);
  mpz_init_set_ull(&erem, 27);

  mpz_div(&rquo, &rrem, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 1);
  ck_assert_int_eq(rrem.size, 1);

  mpz_clear(&op1), mpz_clear(&op2);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_div_with_rem_2) {
  mpz_t op1, op2, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op1, 0xFFFFFFFFFFFFFFFFULL);
  mpz_realloc(&op1, 2);
  op1.d[1] = 0xFFFFFFFFFFFFFFFFULL;
  op1.size = 2;

  mpz_init_set_ull(&op2, 2);

  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 0xFFFFFFFFFFFFFFFFULL);
  mpz_realloc(&equo, 2);
  equo.d[1] = 0x7FFFFFFFFFFFFFFFULL;
  equo.size = 2;

  mpz_init_set_ull(&erem, 1);

  mpz_div(&rquo, &rrem, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 2);
  ck_assert_int_eq(rrem.size, 1);

  mpz_clear(&op1), mpz_clear(&op2);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_div_zero_left) {
  mpz_t op1, op2, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op1, 0);
  mpz_init_set_ull(&op2, 6);
  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init(&equo);
  mpz_init_set_ull(&erem, 0);

  mpz_div(&rquo, &rrem, &op1, &op2);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 0);
  ck_assert_int_eq(rrem.size, 0);

  mpz_clear(&op1), mpz_clear(&op2);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_div_repeated) {
  mpz_t op1, op2, rrem;

  long long unsigned num = 123456789ULL;

  mpz_init_set_ull(&op1, num);
  mpz_init_set_ull(&op2, 10);

  mpz_init(&rrem);

  for (int i = 9; i != 0; --i) {
    mpz_div(&op1, &rrem, &op1, &op2);
    num /= 10;

    ck_assert_int_eq(op1.d[0], num);
    ck_assert_int_eq(rrem.d[0], i);
    ck_assert_int_eq(rrem.size, 1);
  }
  ck_assert_int_eq(op1.size, 0);

  mpz_clear(&op1), mpz_clear(&op2), mpz_clear(&rrem);
}
END_TEST

START_TEST(mpz_idiv_2exp_left_less) {
  mpz_t op, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op, 7);
  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init(&equo);
  mpz_init_set_ull(&erem, 7);

  mpz_idiv_2exp(&rquo, &rrem, &op, 3);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 0);
  ck_assert_int_eq(rrem.size, 1);

  mpz_clear(&op);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_idiv_2exp_no_rem_1) {
  mpz_t op, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op, 0x8000000000000000ULL);
  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 0x80000000ULL);
  mpz_init_set_ull(&erem, 0);

  mpz_idiv_2exp(&rquo, &rrem, &op, 32);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 1);
  ck_assert_int_eq(rrem.size, 0);

  mpz_clear(&op);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_idiv_2exp_no_rem_2) {
  mpz_t op, rquo, rrem, equo, erem;

  mpz_init(&op);
  mpz_setbit(&op, 1, 63, 1);

  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 1);
  mpz_init_set_ull(&erem, 0);

  mpz_idiv_2exp(&rquo, &rrem, &op, 127);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 1);
  ck_assert_int_eq(rrem.size, 0);

  mpz_clear(&op);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_idiv_2exp_with_rem_1) {
  mpz_t op, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op, 0xFEDCBA9876543210ULL);

  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 0x7F6E5D4C3B2ULL);
  mpz_init_set_ull(&erem, 0x143210ULL);

  mpz_idiv_2exp(&rquo, &rrem, &op, 21);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 1);
  ck_assert_int_eq(rrem.size, 1);

  mpz_clear(&op);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_idiv_2exp_with_rem_2) {
  mpz_t op, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op, 0xFFFFFFFFFFFFFFFFULL);
  mpz_realloc(&op, 2);
  op.d[1] = 0xFEDCBA9876543210ULL;
  op.size = 2;

  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 0xFEDCBA9876543210ULL);
  mpz_init_set_ull(&erem, 0xFFFFFFFFFFFFFFFFULL);

  mpz_idiv_2exp(&rquo, &rrem, &op, 64);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 1);
  ck_assert_int_eq(rrem.size, 1);

  mpz_clear(&op);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_idiv_2exp_zero_exp) {
  mpz_t op, rquo, rrem, equo, erem;

  mpz_init_set_ull(&op, 0xFFFFFFFFFFFFFFFF);
  mpz_init(&rquo);
  mpz_init(&rrem);

  mpz_init_set_ull(&equo, 0xFFFFFFFFFFFFFFFF);
  mpz_init_set_ull(&erem, 0);

  mpz_idiv_2exp(&rquo, &rrem, &op, 0);

  ck_assert_int_eq(mpz_cmp(&rquo, &equo), 0);
  ck_assert_int_eq(mpz_cmp(&rrem, &erem), 0);
  ck_assert_int_eq(rquo.size, 1);
  ck_assert_int_eq(rrem.size, 0);

  mpz_clear(&op);
  mpz_clear(&rquo), mpz_clear(&rrem);
  mpz_clear(&equo), mpz_clear(&erem);
}
END_TEST

START_TEST(mpz_idiv_2exp_repeated_quo) {
  mpz_t op, rrem;
  long long unsigned num = 123456789ULL;
  mpz_init_set_ull(&op, num);
  mpz_init(&rrem);

  for (; op.size;) {
    mpz_idiv_2exp(&op, &rrem, &op, 1);
    long long unsigned rem = num & 1;
    num >>= 1;

    ck_assert_int_eq(op.d[0], num);
    ck_assert_int_eq(rrem.d[0], rem);
    if (rem)
      ck_assert_int_eq(rrem.size, 1);
    else
      ck_assert_int_eq(rrem.size, 0);
  }

  mpz_clear(&op), mpz_clear(&rrem);
}
END_TEST

START_TEST(mpz_idiv_2exp_repeated_rem) {
  mpz_t op, quo;

  long long unsigned num = 1301;
  mpz_init_set_ull(&op, num);
  mpz_init(&quo);

  for (int i = 0; i < 8; ++i) {
    mpz_mul10(&op, &op);
    num *= 10;

    mpz_idiv_2exp(&quo, &op, &op, 11);
    long long unsigned equo = (long long unsigned)(num / 2048.0);
    num = num - equo * 2048;

    ck_assert_int_eq(quo.d[0], equo);
    ck_assert_int_eq(op.d[0], num);
  }

  mpz_clear(&op), mpz_clear(&quo);
}
END_TEST

START_TEST(mpz_fdiv_2exp_equal) {
  mpf_t rop;
  mpf_init(&rop);

  mpz_t op, exp;
  mpz_init_set_ull(&op, 0x40000000000000ULL);
  mpz_init_set_ull(&exp, 100000000ULL);

  mpz_fdiv_2exp(&rop, &op, 54, 6);

  ck_assert_int_eq(mpz_cmp(&rop.man, &exp), 0);
  ck_assert_int_eq(rop.exp, 0);
  ck_assert_int_eq(rop.fig, 9);

  mpz_clear(&op), mpf_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_fdiv_2exp_no_rem) {
  mpf_t rop;
  mpf_init(&rop);

  mpz_t op, exp;
  mpz_init_set_ull(&op, 0x40000000000000ULL);
  mpz_init_set_ull(&exp, 409600000000ULL);

  mpz_fdiv_2exp(&rop, &op, 42, 6);

  ck_assert_int_eq(mpz_cmp(&rop.man, &exp), 0);
  ck_assert_int_eq(rop.exp, 3);
  ck_assert_int_eq(rop.fig, 12);

  mpz_clear(&op), mpf_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_fdiv_2exp_finite) {
  mpf_t rop;
  mpf_init(&rop);

  mpz_t op, exp;
  mpz_init_set_ull(&op, 3205833ULL);
  mpz_init_set_ull(&exp, 2504557031250ULL);

  mpz_fdiv_2exp(&rop, &op, 7, 6);

  ck_assert_int_eq(mpz_cmp(&rop.man, &exp), 0);
  ck_assert_int_eq(rop.exp, 4);
  ck_assert_int_eq(rop.fig, 13);

  mpz_clear(&op), mpf_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_fdiv_2exp_infinite) {
  mpf_t rop;
  mpf_init(&rop);

  mpz_t op, exp;
  mpz_init_set_ull(&op, 123456789ULL);
  mpz_init_set_ull(&exp, 6028163525391ULL);

  mpz_fdiv_2exp(&rop, &op, 11, 6);

  ck_assert_int_eq(mpz_cmp(&rop.man, &exp), 0);
  ck_assert_int_eq(rop.exp, 4);
  ck_assert_int_eq(rop.fig, 13);

  mpz_clear(&op), mpf_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpz_fdiv_2exp_zero_exp) {
  mpf_t rop;
  mpf_init(&rop);

  mpz_t op, exp;
  mpz_init_set_ull(&op, 123456789ULL);
  mpz_init_set_ull(&exp, 12345678900000000ULL);

  mpz_fdiv_2exp(&rop, &op, 0, 6);

  ck_assert_int_eq(mpz_cmp(&rop.man, &exp), 0);
  ck_assert_int_eq(rop.exp, 8);
  ck_assert_int_eq(rop.fig, 17);

  mpz_clear(&op), mpf_clear(&rop), mpz_clear(&exp);
}
END_TEST

START_TEST(mpf_rint_default) {
  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456);
  op.fig = 6;
  op.exp = 5;

  mpf_rint(&op, 3);

  ck_assert_int_eq(op.man.d[0], 123);
  ck_assert_int_eq(op.exp, 5);
  ck_assert_int_eq(op.fig, 3);

  mpf_clear(&op);
}
END_TEST

START_TEST(mpf_rint_roundup_odd) {
  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 15);
  op.fig = 2;
  op.exp = 1;

  mpf_rint(&op, 1);

  ck_assert_int_eq(op.man.d[0], 2);
  ck_assert_int_eq(op.exp, 1);
  ck_assert_int_eq(op.fig, 1);

  mpf_clear(&op);
}
END_TEST

START_TEST(mpf_rint_roundup_sticky) {
  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 2500001);
  op.fig = 7;
  op.exp = 6;

  mpf_rint(&op, 1);

  ck_assert_int_eq(op.man.d[0], 3);
  ck_assert_int_eq(op.exp, 6);
  ck_assert_int_eq(op.fig, 1);

  mpf_clear(&op);
}
END_TEST

START_TEST(mpf_rint_roundup_new_digit_len) {
  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 9950001);
  op.fig = 7;
  op.exp = 1;

  mpf_rint(&op, 2);

  ck_assert_int_eq(op.man.d[0], 100);
  ck_assert_int_eq(op.exp, 2);
  ck_assert_int_eq(op.fig, 3);

  mpf_clear(&op);
}
END_TEST

START_TEST(mpf_rint_rounddown_even) {
  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 250000);
  op.fig = 6;
  op.exp = -1;

  mpf_rint(&op, 1);

  ck_assert_int_eq(op.man.d[0], 2);
  ck_assert_int_eq(op.exp, -1);
  ck_assert_int_eq(op.fig, 1);

  mpf_clear(&op);
}
END_TEST

START_TEST(mpf_rint_zero) {
  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 523);
  op.fig = 6;
  op.exp = -3;

  mpf_rint(&op, 0);

  ck_assert_int_eq(op.man.d[0], 0);
  ck_assert_int_eq(op.exp, -3);
  ck_assert_int_eq(op.fig, 0);

  mpf_clear(&op);
}
END_TEST

START_TEST(mpf_to_fltnot_exp2_prec6) {
  sc_t dst = {0};
  dst.alloc = 11;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[11] = "123.456789";

  mpf_to_fltnot(&dst, &op, 6);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_exp2_prec3) {
  sc_t dst = {0};
  dst.alloc = 8;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[8] = "123.457";

  mpf_to_fltnot(&dst, &op, 3);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_exp2_prec1) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[6] = "123.5";

  mpf_to_fltnot(&dst, &op, 1);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_exp2_prec0) {
  sc_t dst = {0};
  dst.alloc = 5;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[5] = "123";

  mpf_to_fltnot(&dst, &op, 0);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_exp0_prec8) {
  sc_t dst = {0};
  dst.alloc = 11;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 0;

  char exp[11] = "1.23456789";

  mpf_to_fltnot(&dst, &op, 8);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_exp0_prec3) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 0;

  char exp[6] = "1.235";

  mpf_to_fltnot(&dst, &op, 3);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_exp0_prec1) {
  sc_t dst = {0};
  dst.alloc = 4;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 0;

  char exp[4] = "1.2";

  mpf_to_fltnot(&dst, &op, 1);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_exp0_prec0) {
  sc_t dst = {0};
  dst.alloc = 2;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 0;

  char exp[2] = "1";

  mpf_to_fltnot(&dst, &op, 0);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_expN4_prec12) {
  sc_t dst = {0};
  dst.alloc = 15;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[15] = "0.000123456789";

  mpf_to_fltnot(&dst, &op, 12);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_expN4_prec7) {
  sc_t dst = {0};
  dst.alloc = 10;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[10] = "0.0001235";

  mpf_to_fltnot(&dst, &op, 7);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_expN4_prec6) {
  sc_t dst = {0};
  dst.alloc = 9;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[9] = "0.000123";

  mpf_to_fltnot(&dst, &op, 6);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_expN4_prec4) {
  sc_t dst = {0};
  dst.alloc = 7;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[7] = "0.0001";

  mpf_to_fltnot(&dst, &op, 4);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_expN4_prec3) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[6] = "0.000";

  mpf_to_fltnot(&dst, &op, 3);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_expN4_prec0) {
  sc_t dst = {0};
  dst.alloc = 2;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[2] = "0";

  mpf_to_fltnot(&dst, &op, 0);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_new_diglen_1) {
  sc_t dst = {0};
  dst.alloc = 5;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 995);
  op.fig = 4;
  op.exp = -1;

  char exp[5] = "1.00";

  mpf_to_fltnot(&dst, &op, 2);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, 0);
  ck_assert_int_eq(op.fig, 3);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_new_diglen_2) {
  sc_t dst = {0};
  dst.alloc = 4;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 99501);
  op.fig = 6;
  op.exp = -1;

  char exp[4] = "1.0";

  mpf_to_fltnot(&dst, &op, 1);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, 0);
  ck_assert_int_eq(op.fig, 2);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_new_diglen_3) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 9995);
  op.fig = 4;
  op.exp = 0;

  char exp[6] = "10.00";

  mpf_to_fltnot(&dst, &op, 2);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, 1);
  ck_assert_int_eq(op.fig, 4);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_new_diglen_4) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 95);
  op.fig = 5;
  op.exp = -3;

  char exp[6] = "0.010";

  mpf_to_fltnot(&dst, &op, 3);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, -2);
  ck_assert_int_eq(op.fig, 4);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_new_diglen_5) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 195);  // 0.00195 (1.95e-03) -> 0.002
  op.fig = 6;
  op.exp = -3;

  char exp[6] = "0.002";

  mpf_to_fltnot(&dst, &op, 3);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, -3);
  ck_assert_int_eq(op.fig, 4);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_round_to_even_1) {
  sc_t dst = {0};
  dst.alloc = 4;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 115);
  op.fig = 3;
  op.exp = 0;

  char exp[4] = "1.2";

  mpf_to_fltnot(&dst, &op, 1);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_round_to_even_2) {
  sc_t dst = {0};
  dst.alloc = 4;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 125);
  op.fig = 3;
  op.exp = 0;

  char exp[4] = "1.2";

  mpf_to_fltnot(&dst, &op, 1);
  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_default_round_1) {
  sc_t dst = {0};
  dst.alloc = 2;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 575);
  op.fig = 3;
  op.exp = 0;

  char exp[2] = "6";

  mpf_to_fltnot(&dst, &op, 0);
  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_default_round_2) {
  sc_t dst = {0};
  dst.alloc = 2;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 545);
  op.fig = 3;
  op.exp = 0;

  char exp[2] = "5";

  mpf_to_fltnot(&dst, &op, 0);
  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_grprec_1) {
  sc_t dst = {0};
  dst.alloc = 14;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[14] = "123.456789000";

  mpf_to_fltnot(&dst, &op, 9);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_grprec_2) {
  sc_t dst = {0};
  dst.alloc = 18;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[18] = "0.000123456789000";

  mpf_to_fltnot(&dst, &op, 15);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_zero_prec6) {
  sc_t dst = {0};
  dst.alloc = 9;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 0);
  op.fig = 1;
  op.exp = 0;

  char exp[9] = "0.000000";

  mpf_to_fltnot(&dst, &op, 6);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_fltnot_zero_prec0) {
  sc_t dst = {0};
  dst.alloc = 2;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 0);
  op.fig = 1;
  op.exp = 0;

  char exp[2] = "0";

  mpf_to_fltnot(&dst, &op, 0);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp2_prec8) {
  sc_t dst = {0};
  dst.alloc = 15;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[15] = "1.23456789e+02";

  mpf_to_scinot(&dst, &op, 8, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp2_prec6) {
  sc_t dst = {0};
  dst.alloc = 13;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[13] = "1.234568e+02";

  mpf_to_scinot(&dst, &op, 6, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp2_prec3) {
  sc_t dst = {0};
  dst.alloc = 10;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[10] = "1.235e+02";

  mpf_to_scinot(&dst, &op, 3, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp2_prec2) {
  sc_t dst = {0};
  dst.alloc = 9;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[9] = "1.23e+02";

  mpf_to_scinot(&dst, &op, 2, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp2_prec0) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[6] = "1e+02";

  mpf_to_scinot(&dst, &op, 0, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp0_prec8) {
  sc_t dst = {0};
  dst.alloc = 15;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 0;

  char exp[15] = "1.23456789e+00";

  mpf_to_scinot(&dst, &op, 8, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp0_prec3) {
  sc_t dst = {0};
  dst.alloc = 10;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 0;

  char exp[10] = "1.235e+00";

  mpf_to_scinot(&dst, &op, 3, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp0_prec1) {
  sc_t dst = {0};
  dst.alloc = 8;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 0;

  char exp[8] = "1.2e+00";

  mpf_to_scinot(&dst, &op, 1, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_exp0_prec0) {
  sc_t dst = {0};
  dst.alloc = 8;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 0;

  char exp[8] = "1e+00";

  mpf_to_scinot(&dst, &op, 0, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_expN4_prec8) {
  sc_t dst = {0};
  dst.alloc = 15;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[15] = "1.23456789e-04";

  mpf_to_scinot(&dst, &op, 8, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_expN4_prec3) {
  sc_t dst = {0};
  dst.alloc = 10;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[10] = "1.235e-04";

  mpf_to_scinot(&dst, &op, 3, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_expN4_prec2) {
  sc_t dst = {0};
  dst.alloc = 9;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[9] = "1.23e-04";

  mpf_to_scinot(&dst, &op, 2, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_expN4_prec0) {
  sc_t dst = {0};
  dst.alloc = 7;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[7] = "1e-04";

  mpf_to_scinot(&dst, &op, 0, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_new_diglen_1) {
  sc_t dst = {0};
  dst.alloc = 8;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 995);
  op.fig = 4;
  op.exp = -1;

  char exp[8] = "1.0e+00";

  mpf_to_scinot(&dst, &op, 1, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, 0);
  ck_assert_int_eq(op.fig, 3);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_new_diglen_2) {
  sc_t dst = {0};
  dst.alloc = 8;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 99501);  // 0.99501 (9.9501e-01)
  op.fig = 6;
  op.exp = -1;

  char exp[8] = "1.0e+00";

  mpf_to_scinot(&dst, &op, 1, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, 0);
  ck_assert_int_eq(op.fig, 3);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_new_diglen_3) {
  sc_t dst = {0};
  dst.alloc = 9;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 9995);  // 9.995 -> 10.00
  op.fig = 4;
  op.exp = 0;

  char exp[9] = "1.00e+01";

  mpf_to_scinot(&dst, &op, 2, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, 1);
  ck_assert_int_eq(op.fig, 4);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_new_diglen_4) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 95);  // 0.0095 (9.5e-03) -> 0.010
  op.fig = 5;
  op.exp = -3;

  char exp[6] = "1e-02";

  mpf_to_scinot(&dst, &op, 0, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, -2);
  ck_assert_int_eq(op.fig, 4);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_new_diglen_5) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 195);  // 0.00195 (1.95e-03) -> 0.002
  op.fig = 6;
  op.exp = -3;

  char exp[6] = "2e-03";

  mpf_to_scinot(&dst, &op, 0, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);
  ck_assert_int_eq(op.exp, -3);
  ck_assert_int_eq(op.fig, 4);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_round_to_even_1) {
  sc_t dst = {0};
  dst.alloc = 8;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 115);
  op.fig = 3;
  op.exp = 0;

  char exp[8] = "1.2e+00";

  mpf_to_scinot(&dst, &op, 1, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_round_to_even_2) {
  sc_t dst = {0};
  dst.alloc = 8;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 125);
  op.fig = 3;
  op.exp = 0;

  char exp[8] = "1.2e+00";

  mpf_to_scinot(&dst, &op, 1, false);
  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_default_round_1) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 575);
  op.fig = 3;
  op.exp = 0;

  char exp[6] = "6e+00";

  mpf_to_scinot(&dst, &op, 0, false);
  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_default_round_2) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 545);
  op.fig = 3;
  op.exp = 0;

  char exp[6] = "5e+00";

  mpf_to_scinot(&dst, &op, 0, false);
  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_grprec_1) {
  sc_t dst = {0};
  dst.alloc = 18;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 9;
  op.exp = 2;

  char exp[18] = "1.23456789000e+02";

  mpf_to_scinot(&dst, &op, 11, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_grprec_2) {
  sc_t dst = {0};
  dst.alloc = 18;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 123456789);
  op.fig = 13;
  op.exp = -4;

  char exp[18] = "1.23456789000e-04";

  mpf_to_scinot(&dst, &op, 11, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_zero_prec6) {
  sc_t dst = {0};
  dst.alloc = 13;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 0);
  op.fig = 1;
  op.exp = 0;

  char exp[13] = "0.000000e+00";

  mpf_to_scinot(&dst, &op, 6, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

START_TEST(mpf_to_scinot_zero_prec0) {
  sc_t dst = {0};
  dst.alloc = 6;
  dst.d = malloc(dst.alloc);

  mpf_t op;
  mpf_init(&op);
  mpz_set_ull(&op.man, 0);
  op.fig = 1;
  op.exp = 0;

  char exp[6] = "0e+00";

  mpf_to_scinot(&dst, &op, 0, false);

  ck_assert_int_eq(s21_strcmp(dst.d, exp), 0);

  mpf_clear(&op);

  if (dst.d) {
    free(dst.d);
  }
}
END_TEST

Suite *suite_s21_gmp_test(void) {
  Suite *s = suite_create("s21_gmp_test");

  TCase *tc_add = tcase_create("s21_gmp_add");
  suite_add_tcase(s, tc_add);
  tcase_add_test(tc_add, mpz_add_carry_1_limb);
  tcase_add_test(tc_add, mpz_add_carry_2_limb);
  tcase_add_test(tc_add, mpz_add_no_carry_1_limb);
  tcase_add_test(tc_add, mpz_add_no_carry_2_limb);
  tcase_add_test(tc_add, mpz_add_zero_right);
  tcase_add_test(tc_add, mpz_add_zero_left);
  tcase_add_test(tc_add, mpz_add_zero_both);
  tcase_add_test(tc_add, mpz_add_mixed);

  TCase *tc_sub = tcase_create("s21_gmp_sub");
  suite_add_tcase(s, tc_sub);
  tcase_add_test(tc_sub, mpz_sub_borrow_1_limb_1);
  tcase_add_test(tc_sub, mpz_sub_borrow_1_limb_2);
  tcase_add_test(tc_sub, mpz_sub_borrow_2_limb_1);
  tcase_add_test(tc_sub, mpz_sub_borrow_2_limb_2);
  tcase_add_test(tc_sub, mpz_sub_no_borrow_1_limb);
  tcase_add_test(tc_sub, mpz_sub_no_borrow_2_limb);
  tcase_add_test(tc_sub, mpz_sub_zero_right);
  tcase_add_test(tc_sub, mpz_sub_zero_both);

  TCase *tc_mul_2exp = tcase_create("s21_gmp_mul_2exp");
  suite_add_tcase(s, tc_mul_2exp);
  tcase_add_test(tc_mul_2exp, mpz_mul_2exp_default);
  tcase_add_test(tc_mul_2exp, mpz_mul_2exp_zero_exp);

  TCase *tc_mul10 = tcase_create("s21_gmp_mul10");
  suite_add_tcase(s, tc_mul10);
  tcase_add_test(tc_mul10, mpz_mul10_once);
  tcase_add_test(tc_mul10, mpz_mul10_many);

  TCase *tc_div = tcase_create("s21_gmp_div");
  suite_add_tcase(s, tc_div);
  tcase_add_test(tc_div, mpz_div_left_less);
  tcase_add_test(tc_div, mpz_div_no_rem_1);
  tcase_add_test(tc_div, mpz_div_no_rem_2);
  tcase_add_test(tc_div, mpz_div_with_rem_1);
  tcase_add_test(tc_div, mpz_div_with_rem_2);
  tcase_add_test(tc_div, mpz_div_zero_left);
  tcase_add_test(tc_div, mpz_div_repeated);

  TCase *tc_idiv_2exp = tcase_create("s21_gmp_idiv_2exp");
  suite_add_tcase(s, tc_idiv_2exp);
  tcase_add_test(tc_idiv_2exp, mpz_idiv_2exp_left_less);
  tcase_add_test(tc_idiv_2exp, mpz_idiv_2exp_no_rem_1);
  tcase_add_test(tc_idiv_2exp, mpz_idiv_2exp_no_rem_2);
  tcase_add_test(tc_idiv_2exp, mpz_idiv_2exp_with_rem_1);
  tcase_add_test(tc_idiv_2exp, mpz_idiv_2exp_with_rem_2);
  tcase_add_test(tc_idiv_2exp, mpz_idiv_2exp_zero_exp);
  tcase_add_test(tc_idiv_2exp, mpz_idiv_2exp_repeated_quo);
  tcase_add_test(tc_idiv_2exp, mpz_idiv_2exp_repeated_rem);

  TCase *tc_fdiv_2exp = tcase_create("s21_gmp_fdiv_2exp");
  suite_add_tcase(s, tc_fdiv_2exp);
  tcase_add_test(tc_fdiv_2exp, mpz_fdiv_2exp_equal);
  tcase_add_test(tc_fdiv_2exp, mpz_fdiv_2exp_no_rem);
  tcase_add_test(tc_fdiv_2exp, mpz_fdiv_2exp_finite);
  tcase_add_test(tc_fdiv_2exp, mpz_fdiv_2exp_infinite);
  tcase_add_test(tc_fdiv_2exp, mpz_fdiv_2exp_zero_exp);

  TCase *tc_rint = tcase_create("s21_gmp_rint");
  suite_add_tcase(s, tc_rint);
  tcase_add_test(tc_rint, mpf_rint_default);
  tcase_add_test(tc_rint, mpf_rint_roundup_odd);
  tcase_add_test(tc_rint, mpf_rint_roundup_sticky);
  tcase_add_test(tc_rint, mpf_rint_roundup_new_digit_len);
  tcase_add_test(tc_rint, mpf_rint_rounddown_even);
  tcase_add_test(tc_rint, mpf_rint_zero);

  TCase *tc_to_fltnot = tcase_create("s21_gmp_to_fltnot");
  suite_add_tcase(s, tc_to_fltnot);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_exp2_prec6);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_exp2_prec3);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_exp2_prec1);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_exp2_prec0);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_exp0_prec8);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_exp0_prec3);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_exp0_prec1);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_exp0_prec0);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_expN4_prec12);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_expN4_prec7);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_expN4_prec6);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_expN4_prec4);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_expN4_prec3);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_expN4_prec0);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_new_diglen_1);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_new_diglen_2);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_new_diglen_3);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_new_diglen_4);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_new_diglen_5);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_round_to_even_1);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_round_to_even_2);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_default_round_1);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_default_round_2);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_grprec_1);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_grprec_2);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_zero_prec6);
  tcase_add_test(tc_to_fltnot, mpf_to_fltnot_zero_prec0);

  TCase *tc_to_scinot = tcase_create("s21_gmp_to_scinot");
  suite_add_tcase(s, tc_to_scinot);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp2_prec8);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp2_prec6);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp2_prec3);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp2_prec2);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp2_prec0);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp0_prec8);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp0_prec3);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp0_prec1);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_exp0_prec0);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_expN4_prec8);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_expN4_prec3);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_expN4_prec2);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_expN4_prec0);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_new_diglen_1);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_new_diglen_2);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_new_diglen_3);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_new_diglen_4);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_new_diglen_5);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_round_to_even_1);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_round_to_even_2);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_default_round_1);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_default_round_2);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_grprec_1);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_grprec_2);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_zero_prec6);
  tcase_add_test(tc_to_scinot, mpf_to_scinot_zero_prec0);

  TCase *tc_other = tcase_create("s21_gmp_other");
  tcase_add_test(tc_other, mpz_msb_all_ind);
  tcase_add_test(tc_other, mpz_exactsizeinbase10_big_scope);
  tcase_add_test(tc_other, mpz_bitwise_and);
  tcase_add_test(tc_other, mpz_bitshifts);

  return s;
}
