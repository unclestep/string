#include "../s21_test.h"

START_TEST(s21_strlen_empty_init) {
  const char str[21] = "\0";
  ck_assert_int_eq(s21_strlen(str), 0);
}
END_TEST

START_TEST(s21_strlen_nonempty_init) {
  const char str[] = "abcde";
  ck_assert_int_eq(s21_strlen(str), 5);
}
END_TEST

Suite *suite_s21_strlen_test(void) {
  Suite *s = suite_create("s21_strlen_test");
  TCase *tc = tcase_create("s21_strlen_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strlen_empty_init);
  tcase_add_test(tc, s21_strlen_nonempty_init);

  return s;
}
