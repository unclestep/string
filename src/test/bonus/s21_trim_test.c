#include "s21_bonus_test.h"

START_TEST(s21_trim_null) {
  const char *src = NULL;
  const char *trim_chars = "abcdef";
  char *r = s21_trim(src, trim_chars);
  ck_assert_ptr_eq(r, s21_NULL);
}
END_TEST

START_TEST(s21_trim_src_empty) {
  const char *src = "\0";
  const char *trim_chars = "abcdef";
  char *r = s21_trim(src, trim_chars);
  ck_assert_int_eq(s21_strcmp(r, "\0"), 0);
  free(r);
}
END_TEST

START_TEST(s21_trim_src_is_trim_chars) {
  const char *src = "abcdef";
  const char *trim_chars = "abcdef";
  char *r = s21_trim(src, trim_chars);
  ck_assert_int_eq(s21_strcmp(r, "\0"), 0);
  free(r);
}
END_TEST

START_TEST(s21_trim_trim_chars_empty) {
  const char *src = "abcdef";
  const char *trim_chars = "\0";
  char *r = s21_trim(src, trim_chars);
  ck_assert_int_eq(s21_strcmp(r, src), 0);
  free(r);
}
END_TEST

START_TEST(s21_trim_both_sides) {
  const char *src = "*** Hello, World!!! ***";
  const char *trim_chars = "* !";
  char *r = s21_trim(src, trim_chars);
  ck_assert_int_eq(s21_strcmp(r, "Hello, World"), 0);
  free(r);
}
END_TEST

START_TEST(s21_trim_left_side) {
  const char *src = "*** Hello, World!###";
  const char *trim_chars = "* ";
  char *r = s21_trim(src, trim_chars);
  ck_assert_int_eq(s21_strcmp(r, "Hello, World!###"), 0);
  free(r);
}
END_TEST

START_TEST(s21_trim_right_side) {
  const char *src = "###Hello, World! ***";
  const char *trim_chars = "* ";
  char *r = s21_trim(src, trim_chars);
  ck_assert_int_eq(s21_strcmp(r, "###Hello, World!"), 0);
  free(r);
}
END_TEST

Suite *suite_s21_trim_test(void) {
  Suite *s = suite_create("s21_trim_test");
  TCase *tc = tcase_create("s21_trim_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_trim_null);
  tcase_add_test(tc, s21_trim_src_empty);
  tcase_add_test(tc, s21_trim_src_is_trim_chars);
  tcase_add_test(tc, s21_trim_trim_chars_empty);
  tcase_add_test(tc, s21_trim_both_sides);
  tcase_add_test(tc, s21_trim_left_side);
  tcase_add_test(tc, s21_trim_right_side);

  return s;
}
