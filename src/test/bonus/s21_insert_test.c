#include "../include/s21_bonus_test.h"

START_TEST(s21_insert_src_empty) {
  const char *src = "\0";
  const char *str = "abc";
  char *r = s21_insert(src, str, 0);
  ck_assert_int_eq(s21_strcmp(r, str), 0);
  free(r);
}
END_TEST

START_TEST(s21_insert_str_empty) {
  const char *src = "abc";
  const char *str = "\0";
  char *r = s21_insert(src, str, 0);
  ck_assert_int_eq(s21_strcmp(r, src), 0);
  free(r);
}

START_TEST(s21_insert_normal) {
  const char *src = "aaabbb";
  const char *str = " ";
  char *r = s21_insert(src, str, 3);
  ck_assert_int_eq(s21_strcmp(r, "aaa bbb"), 0);
  free(r);
}

START_TEST(s21_insert_to_end) {
  const char *src = "Hello, ";
  const char *str = "world!";
  char *r = s21_insert(src, str, 7);
  ck_assert_int_eq(s21_strcmp(r, "Hello, world!"), 0);
  free(r);
}

START_TEST(s21_insert_null) {
  const char *src = s21_NULL;
  const char *str = "abcdef";
  char *r = s21_insert(src, str, 6);
  ck_assert_ptr_eq(r, s21_NULL);
}

Suite *suite_s21_insert_test(void) {
  Suite *s = suite_create("s21_insert_test");
  TCase *tc = tcase_create("s21_insert_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_insert_src_empty);
  tcase_add_test(tc, s21_insert_str_empty);
  tcase_add_test(tc, s21_insert_normal);
  tcase_add_test(tc, s21_insert_to_end);
  tcase_add_test(tc, s21_insert_null);

  return s;
}
