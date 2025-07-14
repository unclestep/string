#include "../s21_test.h"

START_TEST(s21_to_lower_nullptr) {
  ck_assert_ptr_eq(s21_to_lower(s21_NULL), s21_NULL);
}
END_TEST

START_TEST(s21_to_lower_only_lower_alphabet) {
  const char *str = "abcdefghijklmn";
  char *r = s21_to_lower(str);
  ck_assert_int_eq(s21_strcmp(r, str), 0);
  free(r);
}
END_TEST

START_TEST(s21_to_lower_only_upper_alphabet) {
  const char *str = "ABCDEFGHIKLMN";
  char *r = s21_to_lower(str);
  for (char *rcur = r; *str; ++str, ++rcur) {
    ck_assert_int_eq(*rcur, *str + CASE_SHIFT);
  }
  free(r);
}
END_TEST

START_TEST(s21_to_lower_mixed) {
  const char *str = "aB123cDEFghi";
  char *r = s21_to_lower(str);
  ck_assert_int_eq(s21_strcmp(r, "ab123cdefghi"), 0);
  free(r);
}
END_TEST

Suite *suite_s21_to_lower_test(void) {
  Suite *s = suite_create("s21_to_lower_test");
  TCase *tc = tcase_create("s21_to_lower_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_to_lower_nullptr);
  tcase_add_test(tc, s21_to_lower_only_lower_alphabet);
  tcase_add_test(tc, s21_to_lower_only_upper_alphabet);
  tcase_add_test(tc, s21_to_lower_mixed);

  return s;
}
