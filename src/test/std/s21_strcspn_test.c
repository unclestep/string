#include "s21_std_test.h"

START_TEST(s21_strcspn_forbid_end) {
  const char *str1 = "abcdef$#*";
  const char *str2 = "$#*";
  ck_assert_int_eq(s21_strcspn(str1, str2), 6);
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_forbid_in_4_spots) {
  const char *str1 = "abc$#d*efghi*#$wxyz$";
  const char *str2 = "$#*";
  ck_assert_int_eq(s21_strcspn(str1, str2), 3);
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_forbid_whole) {
  const char *str1 = "abcdefghiwxyz";
  const char *str2 = "abcdefghiwxyz";
  ck_assert_int_eq(s21_strcspn(str1, str2), 0);
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_empty) {
  const char *str1 = "\0";
  const char *str2 = "abcdefghiwxyz";
  ck_assert_int_eq(s21_strcspn(str1, str2), 0);
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

Suite *suite_s21_strcspn_test(void) {
  Suite *s = suite_create("s21_strcspn_test");
  TCase *tc = tcase_create("s21_strcspn_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strcspn_forbid_end);
  tcase_add_test(tc, s21_strcspn_forbid_in_4_spots);
  tcase_add_test(tc, s21_strcspn_forbid_whole);
  tcase_add_test(tc, s21_strcspn_empty);

  return s;
}
