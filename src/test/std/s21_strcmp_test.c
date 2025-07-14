#include "../s21_test.h"

START_TEST(s21_strcmp_equal) {
  const char *str1 = "abcdef";
  const char *str2 = "abcdef";
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_strcmp_inequal) {
  const char *str1 = "123456";
  const char *str2 = "123406";
  ck_assert_int_ge(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_strcmp_inequal_str1_longer) {
  const char *str1 = "abcdef";
  const char *str2 = "abcd";
  ck_assert_int_ge(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_strcmp_inequal_str1_shorter) {
  const char *str1 = "abcd";
  const char *str2 = "abcdef";
  ck_assert_int_le(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_strcmp_both_nullt) {
  const char *str1 = "\0";
  const char *str2 = "\0";
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

Suite *suite_s21_strcmp_test(void) {
  Suite *s = suite_create("s21_strcmp_test");
  TCase *tc = tcase_create("s21_strcmp_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strcmp_equal);
  tcase_add_test(tc, s21_strcmp_inequal);
  tcase_add_test(tc, s21_strcmp_inequal_str1_longer);
  tcase_add_test(tc, s21_strcmp_inequal_str1_shorter);
  tcase_add_test(tc, s21_strcmp_both_nullt);

  return s;
}
