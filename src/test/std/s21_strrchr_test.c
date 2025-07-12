#include "../s21_test.h"

START_TEST(s21_strrchr_good_find_1) {
  const char *str = "abcdefabcdefabcdef";
  int c = 'c';
  ck_assert_ptr_eq(s21_strrchr(str, c), str + 14);
}
END_TEST

START_TEST(s21_strrchr_good_find_2) {
  const char *str = "12300567";
  int c = '0';
  ck_assert_ptr_eq(s21_strrchr(str, c), str + 4);
}
END_TEST

START_TEST(s21_strrchr_null_term) {
  const char *str = "abc\0def";
  int c = '\0';
  ck_assert_ptr_eq(s21_strrchr(str, c), str + 3);
}
END_TEST

START_TEST(s21_strrchr_null) {
  const char *str = "abcdef";
  int c = 'g';
  ck_assert_ptr_eq(s21_strrchr(str, c), s21_NULL);
}
END_TEST

Suite *suite_s21_strrchr_test(void) {
  Suite *s = suite_create("s21_strrchr_test");
  TCase *tc = tcase_create("s21_strrchr_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strrchr_good_find_1);
  tcase_add_test(tc, s21_strrchr_good_find_2);
  tcase_add_test(tc, s21_strrchr_null_term);
  tcase_add_test(tc, s21_strrchr_null);

  return s;
}
