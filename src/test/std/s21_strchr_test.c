#include "../s21_test.h"

START_TEST(s21_strchr_good_find_1) {
  const char *str = "abcdef";
  int c = 'c';
  ck_assert_ptr_eq(s21_strchr(str, c), str + 2);
}
END_TEST

START_TEST(s21_strchr_good_find_2) {
  const char *str = "1230567";
  int c = '0';
  ck_assert_ptr_eq(s21_strchr(str, c), str + 3);
}
END_TEST

START_TEST(s21_strchr_null_term) {
  const char *str = "abcdef";
  int c = '\0';
  ck_assert_ptr_eq(s21_strchr(str, c), str + 6);
}
END_TEST

START_TEST(s21_strchr_null) {
  const char *str = "abcdef";
  int c = 'g';
  ck_assert_ptr_eq(s21_strchr(str, c), s21_NULL);
}
END_TEST

Suite *suite_s21_strchr_test(void) {
  Suite *s = suite_create("s21_strchr_test");
  TCase *tc = tcase_create("s21_strchr_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strchr_good_find_1);
  tcase_add_test(tc, s21_strchr_good_find_2);
  tcase_add_test(tc, s21_strchr_null_term);
  tcase_add_test(tc, s21_strchr_null);

  return s;
}
