#include "s21_std_test.h"

START_TEST(s21_strcpy_dest_empty) {
  const char *src = "abcdef";
  char dest[7];
  s21_strcpy(dest, src);
  for (s21_size_t i = 0; i != 6; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(dest[6], '\0');
}
END_TEST

START_TEST(s21_strcpy_all_nonempty) {
  const char *src = "abcdef";
  char dest[] = "1234567";
  s21_strcpy(dest, src);
  for (s21_size_t i = 0; i != 6; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(dest[6], '\0');
}

START_TEST(s21_strcpy_src_empty) {
  const char *src = "\0";
  char dest[] = "1234567";
  s21_strcpy(dest, src);
  ck_assert_int_eq(dest[0], '\0');
}

START_TEST(s21_strcpy_all_empty) {
  const char *src = "\0";
  char dest[] = "\0";
  s21_strcpy(dest, src);
  ck_assert_int_eq(dest[0], '\0');
}

Suite *suite_s21_strcpy_test(void) {
  Suite *s = suite_create("s21_strcpy_test");
  TCase *tc = tcase_create("s21_strcpy_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strcpy_dest_empty);
  tcase_add_test(tc, s21_strcpy_all_nonempty);
  tcase_add_test(tc, s21_strcpy_src_empty);
  tcase_add_test(tc, s21_strcpy_all_empty);

  return s;
}
