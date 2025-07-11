#include "../s21_test.h"

START_TEST(s21_strncpy_src_shorter_n) {
  const char *src = "hi";
  char dest[] = "abcdef";
  s21_strncpy(dest, src, 5);
  ck_assert_int_eq(dest[0], 'h');
  ck_assert_int_eq(dest[1], 'i');
  ck_assert_int_eq(dest[2], '\0');
  ck_assert_int_eq(dest[3], '\0');
  ck_assert_int_eq(dest[4], '\0');
  ck_assert_int_eq(dest[5], 'f');
  ck_assert_int_eq(dest[6], '\0');
}
END_TEST

START_TEST(s21_strncpy_src_equal_n_wo_nullt) {
  const char *src = "hi";
  char dest[3] = "abc";
  s21_strncpy(dest, src, 2);
  ck_assert_int_eq(dest[0], 'h');
  ck_assert_int_eq(dest[1], 'i');
  ck_assert_int_eq(dest[2], 'c');
}

START_TEST(s21_strncpy_src_equal_n) {
  const char *src = "hi";
  char dest[3] = "abc";
  s21_strncpy(dest, src, 3);
  ck_assert_int_eq(dest[0], 'h');
  ck_assert_int_eq(dest[1], 'i');
  ck_assert_int_eq(dest[2], '\0');
}

Suite *suite_s21_strncpy_test(void) {
  Suite *s = suite_create("s21_strncpy_test");
  TCase *tc = tcase_create("s21_strncpy_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strncpy_src_shorter_n);
  tcase_add_test(tc, s21_strncpy_src_equal_n_wo_nullt);
  tcase_add_test(tc, s21_strncpy_src_equal_n);

  return s;
}
