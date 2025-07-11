#include "../s21_test.h"

START_TEST(s21_memset_n2) {
  unsigned int str = 0xFFFFFFFF;
  int c = 0;
  s21_size_t n = 2;
  ck_assert_int_eq(*((unsigned int *)s21_memset(&str, c, n)), 0xFFFF0000);
}
END_TEST

START_TEST(s21_memset_n4) {
  unsigned int str = 0xFFFFFFFF;
  int c = 0;
  s21_size_t n = 4;
  ck_assert_int_eq(*((unsigned int *)s21_memset(&str, c, n)), 0x00000000);
}
END_TEST

START_TEST(s21_memset_n0) {
  unsigned int str = 0xFFFFFFFF;
  int c = 0;
  s21_size_t n = 0;
  ck_assert_int_eq(*((unsigned int *)s21_memset(&str, c, n)), 0xFFFFFFFF);
}
END_TEST

Suite *suite_s21_memset_test(void) {
  Suite *s = suite_create("s21_memset_test");
  TCase *tc = tcase_create("s21_memset_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_memset_n2);
  tcase_add_test(tc, s21_memset_n4);
  tcase_add_test(tc, s21_memset_n0);

  return s;
}
