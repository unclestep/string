#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_p_zero_ptr) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%p", s21_NULL);
  int read2 = sprintf(str2, "%p", s21_NULL);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_p_zero_ptr_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%25p", s21_NULL);
  int read2 = sprintf(str2, "%25p", s21_NULL);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_p_zero_ptr_width_minus) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-25p", s21_NULL);
  int read2 = sprintf(str2, "%-25p", s21_NULL);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_p_some_ptr) {
  char str1[128];
  char str2[128];

  int a = 123;
  char b = '4';
  short c = 5;
  long d = 6;
  long long e = 7;
  float f = 123.45;
  double g = 123.45;
  long double h = 123.45;

  int read1 =
      s21_sprintf(str1, "%p%p%p%p%p%p%p%p", &a, &b, &c, &d, &e, &f, &g, &h);
  int read2 = sprintf(str2, "%p%p%p%p%p%p%p%p", &a, &b, &c, &d, &e, &f, &g, &h);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_p_some_ptr_width) {
  char str1[512];
  char str2[512];

  int a = 123;
  char b = '4';
  short c = 5;
  long d = 6;
  long long e = 7;
  float f = 123.45;
  double g = 123.45;
  long double h = 123.45;

  int read1 = s21_sprintf(str1, "%25p%25p%25p%25p%25p%25p%25p%25p", &a, &b, &c,
                          &d, &e, &f, &g, &h);
  int read2 = sprintf(str2, "%25p%25p%25p%25p%25p%25p%25p%25p", &a, &b, &c, &d,
                      &e, &f, &g, &h);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_p_some_ptr_width_minus) {
  char str1[512];
  char str2[512];

  int a = 123;
  char b = '4';
  short c = 5;
  long d = 6;
  long long e = 7;
  float f = 123.45;
  double g = 123.45;
  long double h = 123.45;

  int read1 = s21_sprintf(str1, "%-25p%-25p%-25p%-25p%-25p%-25p%-25p%-25p", &a,
                          &b, &c, &d, &e, &f, &g, &h);
  int read2 = sprintf(str2, "%-25p%-25p%-25p%-25p%-25p%-25p%-25p%-25p", &a, &b,
                      &c, &d, &e, &f, &g, &h);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_p(void) {
  TCase *tc_p = tcase_create("s21_sprintf_p");
  tcase_add_test(tc_p, s21_sprintf_spec_p_zero_ptr);
  tcase_add_test(tc_p, s21_sprintf_spec_p_zero_ptr_width);
  tcase_add_test(tc_p, s21_sprintf_spec_p_zero_ptr_width_minus);
  tcase_add_test(tc_p, s21_sprintf_spec_p_some_ptr);
  tcase_add_test(tc_p, s21_sprintf_spec_p_some_ptr_width);
  tcase_add_test(tc_p, s21_sprintf_spec_p_some_ptr_width_minus);

  return tc_p;
}
