#include "s21_std_test.h"

START_TEST(s21_memcmp_equal) {
  const int str1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  const int str2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  ck_assert_int_eq(s21_memcmp(str1, str2, 10 * sizeof(int)), 0);
}
END_TEST

START_TEST(s21_memcmp_inequal_1) {
  const int str1[] = {0, 1, 2, 3, 9};
  const int str2[] = {0, 1, 2, 7, 5};
  ck_assert_int_le(s21_memcmp(str1, str2, 5 * sizeof(int)), 0);
}
END_TEST

START_TEST(s21_memcmp_inequal_2) {
  const int str1[] = {0, 1, 2, 3, 9};
  const int str2[] = {0, 1, 2, 3, 1};
  ck_assert_int_ge(s21_memcmp(str1, str2, 10 * sizeof(int)), 0);
}
END_TEST

START_TEST(s21_memcmp_inequal_3) {
  const int str1[] = {0, 1, 2, 3, 9};
  const int str2[] = {0, 1, 2, 7, 5};
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), 0);
}
END_TEST

Suite *suite_s21_memcmp_test(void) {
  Suite *s = suite_create("s21_memcmp_test");
  TCase *tc = tcase_create("s21_memcmp_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_memcmp_equal);
  tcase_add_test(tc, s21_memcmp_inequal_1);
  tcase_add_test(tc, s21_memcmp_inequal_2);
  tcase_add_test(tc, s21_memcmp_inequal_3);

  return s;
}
