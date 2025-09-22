#include <stdio.h>

#include "s21_std_test.h"

START_TEST(s21_strerror_all) {
  for (int errnum = -200; errnum <= 200; ++errnum) {
    ck_assert_str_eq(strerror(errnum), s21_strerror(errnum));
  }
}
END_TEST

Suite *suite_s21_strerror_test(void) {
  Suite *s = suite_create("s21_strerror_test");
  TCase *tc = tcase_create("s21_strerror_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strerror_all);
  return s;
}
