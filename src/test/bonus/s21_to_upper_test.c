#include "../s21_test.h"

START_TEST(s21_to_upper_nullptr) {
  ck_assert_ptr_eq(s21_to_upper(s21_NULL), s21_NULL);
}
END_TEST

START_TEST(s21_to_upper_only_lower_alphabet) {
  const char *str = "abcdefghijklmn";
  char *r = s21_to_upper(str);
  for (char *rcur = r; *str; ++str, ++rcur) {
    ck_assert_int_eq(*rcur, *str - CASE_SHIFT);
  }
  free(r);
}
END_TEST

START_TEST(s21_to_upper_only_upper_alphabet) {
  const char *str = "ABCDEFGHIKLMN";
  char *r = s21_to_upper(str);
  ck_assert_int_eq(s21_strcmp(r, str), 0);
  free(r);
}
END_TEST

START_TEST(s21_to_upper_mixed) {
  const char *str = "aB123cDEFghi";
  char *r = s21_to_upper(str);
  ck_assert_int_eq(s21_strcmp(r, "AB123CDEFGHI"), 0);
  free(r);
}
END_TEST

Suite *suite_s21_to_upper_test(void) {
  Suite *s = suite_create("s21_to_upper_test");
  TCase *tc = tcase_create("s21_to_upper_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_to_upper_nullptr);
  tcase_add_test(tc, s21_to_upper_only_lower_alphabet);
  tcase_add_test(tc, s21_to_upper_only_upper_alphabet);
  tcase_add_test(tc, s21_to_upper_mixed);

  return s;
}
