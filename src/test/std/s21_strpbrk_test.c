#include "../s21_test.h"

START_TEST(s21_strpbrk_good_find_1) {
  const char *str1 = "abcdef";
  const char *str2 = "cd";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), str1 + 2);
  ck_assert_ptr_eq(s21_strpbrk(str1 + 3, str2), str1 + 3);
}
END_TEST

START_TEST(s21_strpbrk_good_find_2) {
  const char *str1 = "1230567";
  const char *str2 = "107";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), str1);
  ck_assert_ptr_eq(s21_strpbrk(str1 + 1, str2), str1 + 3);
  ck_assert_ptr_eq(s21_strpbrk(str1 + 4, str2), str1 + 6);
}
END_TEST

START_TEST(s21_strpbrk_null_term) {
  const char *str1 = "abcdef";
  const char *str2 = "\0";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), s21_NULL);
}
END_TEST

START_TEST(s21_strpbrk_null) {
  const char *str1 = "abcdef";
  const char *str2 = "ghi";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), s21_NULL);
}
END_TEST

START_TEST(s21_strpbrk_empty) {
  const char *str1 = "\0";
  const char *str2 = "abc";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), s21_NULL);
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *suite_s21_strpbrk_test(void) {
  Suite *s = suite_create("s21_strpbrk_test");
  TCase *tc = tcase_create("s21_strpbrk_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strpbrk_good_find_1);
  tcase_add_test(tc, s21_strpbrk_good_find_2);
  tcase_add_test(tc, s21_strpbrk_null_term);
  tcase_add_test(tc, s21_strpbrk_null);
  tcase_add_test(tc, s21_strpbrk_empty);

  return s;
}
