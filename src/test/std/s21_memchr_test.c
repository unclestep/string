#include "s21_std_test.h"

START_TEST(s21_memchr_good_find) {
  const char str[] = "123456789";
  int c = '5';
  ck_assert_int_eq(*(const char *)s21_memchr((const void *)str, c, 9), '5');
}
END_TEST

START_TEST(s21_memchr_n_gr_len) {
  const char str[] = "123456789";
  int c = '9';
  ck_assert_int_eq(*(const char *)s21_memchr((const void *)str, c, 10), '9');
}
END_TEST

START_TEST(s21_memchr_n_le_len) {
  const char str[] = "123456789";
  int c = '7';
  ck_assert_ptr_eq(s21_memchr((const void *)str, c, 3), s21_NULL);
}
END_TEST

START_TEST(s21_memchr_n_0) {
  const char str[] = "123456789";
  int c = '9';
  ck_assert_ptr_eq(s21_memchr((const void *)str, c, 0), s21_NULL);
}
END_TEST

START_TEST(s21_memchr_null) {
  const char str[] = "ab\0cd";
  int c = '\0';
  ck_assert_ptr_eq(s21_memchr((const void *)str, c, 5), str + 2);
}
END_TEST

Suite *suite_s21_memchr_test(void) {
  Suite *s = suite_create("s21_memchr_test");
  TCase *tc = tcase_create("s21_memchr_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_memchr_good_find);
  tcase_add_test(tc, s21_memchr_n_gr_len);
  tcase_add_test(tc, s21_memchr_n_le_len);
  tcase_add_test(tc, s21_memchr_n_0);
  tcase_add_test(tc, s21_memchr_null);

  return s;
}
