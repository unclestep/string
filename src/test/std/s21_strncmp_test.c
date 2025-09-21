#include "s21_std_test.h"

START_TEST(s21_strncmp_equal_n_true) {
  const char *str1 = "abcdef";
  const char *str2 = "abcdef";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), 0);
}
END_TEST

START_TEST(s21_strncmp_equal_n_false) {
  const char *str1 = "abcdef";
  const char *str2 = "abcdef";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), 0);
}
END_TEST

START_TEST(s21_strncmp_inequal) {
  const char *str1 = "123456";
  const char *str2 = "123406";
  ck_assert_int_ge(s21_strncmp(str1, str2, 6), 0);
}
END_TEST

START_TEST(s21_strncmp_inequal_str1_longer) {
  const char *str1 = "abcdef";
  const char *str2 = "abcd";
  ck_assert_int_ge(s21_strncmp(str1, str2, 6), 0);
}
END_TEST

START_TEST(s21_strncmp_inequal_str1_shorter) {
  const char *str1 = "abcd";
  const char *str2 = "abcdef";
  ck_assert_int_le(s21_strncmp(str1, str2, 6), 0);
}
END_TEST

START_TEST(s21_strncmp_inequal_n0) {
  const char *str1 = "abcd";
  const char *str2 = "abcdef";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), 0);
}
END_TEST

Suite *suite_s21_strncmp_test(void) {
  Suite *s = suite_create("s21_strncmp_test");
  TCase *tc = tcase_create("s21_strncmp_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strncmp_equal_n_true);
  tcase_add_test(tc, s21_strncmp_equal_n_false);
  tcase_add_test(tc, s21_strncmp_inequal);
  tcase_add_test(tc, s21_strncmp_inequal_str1_longer);
  tcase_add_test(tc, s21_strncmp_inequal_str1_shorter);
  tcase_add_test(tc, s21_strncmp_inequal_n0);

  return s;
}
