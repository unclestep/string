#include "s21_std_test.h"

START_TEST(s21_strstr_needle_empty) {
  const char *haystack = "abcdef123456";
  const char *needle = "\0";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), haystack);
}

START_TEST(s21_strstr_needle_in_mid) {
  const char *haystack = "a1b12c123d1e12f123";
  const char *needle = "123";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), haystack + 6);
}

START_TEST(s21_strstr_null) {
  const char *haystack = "abcdef12";
  const char *needle = "1234";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), s21_NULL);
}

Suite *suite_s21_strstr_test(void) {
  Suite *s = suite_create("s21_strstr_test");
  TCase *tc = tcase_create("s21_strstr_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strstr_needle_empty);
  tcase_add_test(tc, s21_strstr_needle_in_mid);
  tcase_add_test(tc, s21_strstr_null);

  return s;
}
