#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_n_basic) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;

  int read1 = s21_sprintf(str1, "Hello%nWorld", &n1);
  int read2 = sprintf(str2, "Hello%nWorld", &n2);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_spec_n_beginning) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;

  int read1 = s21_sprintf(str1, "%nHello World", &n1);
  int read2 = sprintf(str2, "%nHello World", &n2);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_spec_n_end) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;

  int read1 = s21_sprintf(str1, "Hello World%n", &n1);
  int read2 = sprintf(str2, "Hello World%n", &n2);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_spec_n_multiple) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1, n3 = -1;
  int n1_std = -1, n2_std = -1, n3_std = -1;

  int read1 = s21_sprintf(str1, "A%nBC%nDEF%n", &n1, &n2, &n3);
  int read2 = sprintf(str2, "A%nBC%nDEF%n", &n1_std, &n2_std, &n3_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
  ck_assert_int_eq(n3, n3_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_empty_string) {
  char str1[64];
  char str2[64];
  int n1 = -1, n2 = -1;

  int read1 = s21_sprintf(str1, "%n", &n1);
  int read2 = sprintf(str2, "%n", &n2);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_spec_hn_short) {
  char str1[128];
  char str2[128];
  short n1 = -1, n2 = -1;

  int read1 = s21_sprintf(str1, "Hello%hnWorld", &n1);
  int read2 = sprintf(str2, "Hello%hnWorld", &n2);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_spec_ln_long) {
  char str1[128];
  char str2[128];
  long n1 = -1, n2 = -1;

  int read1 = s21_sprintf(str1, "Hello%lnWorld", &n1);
  int read2 = sprintf(str2, "Hello%lnWorld", &n2);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_spec_n_with_integers) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;
  int n1_std = -1, n2_std = -1;

  int read1 = s21_sprintf(str1, "%d%n%d%n", 123, &n1, 456, &n2);
  int read2 = sprintf(str2, "%d%n%d%n", 123, &n1_std, 456, &n2_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_with_strings) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;
  int n1_std = -1, n2_std = -1;

  int read1 = s21_sprintf(str1, "%s%n%s%n", "Hello", &n1, "World", &n2);
  int read2 = sprintf(str2, "%s%n%s%n", "Hello", &n1_std, "World", &n2_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_with_chars) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;
  int n1_std = -1, n2_std = -1;

  int read1 = s21_sprintf(str1, "%c%n%c%n", 'A', &n1, 'B', &n2);
  int read2 = sprintf(str2, "%c%n%c%n", 'A', &n1_std, 'B', &n2_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_with_floats) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;
  int n1_std = -1, n2_std = -1;

  int read1 = s21_sprintf(str1, "%f%n%e%n", 123.456, &n1, 789.012, &n2);
  int read2 = sprintf(str2, "%f%n%e%n", 123.456, &n1_std, 789.012, &n2_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_with_width_precision) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;
  int n1_std = -1, n2_std = -1;

  int read1 = s21_sprintf(str1, "%10d%n%.2f%n", 123, &n1, 456.789, &n2);
  int read2 = sprintf(str2, "%10d%n%.2f%n", 123, &n1_std, 456.789, &n2_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_ignore_flags) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1, n3 = -1, n4 = -1, n5 = -1;
  int n1_std = -1, n2_std = -1, n3_std = -1, n4_std = -1, n5_std = -1;

  int read1 =
      s21_sprintf(str1, "ABC%-n%+n% n%#n%0nDEF", &n1, &n2, &n3, &n4, &n5);
  int read2 = sprintf(str2, "ABC%n%n%n%n%nDEF", &n1_std, &n2_std, &n3_std,
                      &n4_std, &n5_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
  ck_assert_int_eq(n3, n3_std);
  ck_assert_int_eq(n4, n4_std);
  ck_assert_int_eq(n5, n5_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_ignore_width) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;
  int n1_std = -1, n2_std = -1;

  int read1 = s21_sprintf(str1, "ABC%10n%*nDEF", &n1, 20, &n2);
  int read2 = sprintf(str2, "ABC%n%nDEF", &n1_std, &n2_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_ignore_precision) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;
  int n1_std = -1, n2_std = -1;

  int read1 = s21_sprintf(str1, "ABC%.5n%.*nDEF", &n1, 10, &n2);
  int read2 = sprintf(str2, "ABC%n%nDEF", &n1_std, &n2_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_consecutive) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1, n3 = -1;
  int n1_std = -1, n2_std = -1, n3_std = -1;

  int read1 = s21_sprintf(str1, "A%n%n%nB", &n1, &n2, &n3);
  int read2 = sprintf(str2, "A%n%n%nB", &n1_std, &n2_std, &n3_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
  ck_assert_int_eq(n3, n3_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_large_count) {
  char str1[512];
  char str2[512];
  int n1 = -1;
  int n1_std = -1;

  char long_text[256];
  for (int i = 0; i < 200; i++) {
    long_text[i] = 'A' + (i % 26);
  }
  long_text[200] = '\0';

  int read1 = s21_sprintf(str1, "%s%n", long_text, &n1);
  int read2 = sprintf(str2, "%s%n", long_text, &n1_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_with_escape_sequences) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1;
  int n1_std = -1, n2_std = -1;

  int read1 = s21_sprintf(str1, "A\\n\\t\\r%nB\\0%n", &n1, &n2);
  int read2 = sprintf(str2, "A\\n\\t\\r%nB\\0%n", &n1_std, &n2_std);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_mixed_types) {
  char str1[256];
  char str2[256];
  int n1 = -1;
  short n2 = -1;
  long n3 = -1;

  int n1_std = -1;
  short n2_std = -1;
  long n3_std = -1;

  int read1 = s21_sprintf(str1, "%d%n%s%hn%f%ln%c", 123, &n1, "test", &n2,
                          45.67, &n3, 'X');
  int read2 = sprintf(str2, "%d%n%s%hn%f%ln%c", 123, &n1_std, "test", &n2_std,
                      45.67, &n3_std, 'X');

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
  ck_assert_int_eq(n3, n3_std);
}
END_TEST

START_TEST(s21_sprintf_spec_n_return_value) {
  char str1[128];
  char str2[128];
  int n1 = -1;
  int n1_std = -1;

  int read1 = s21_sprintf(str1, "Hello%nWorld", &n1);
  int read2 = sprintf(str2, "Hello%nWorld", &n1_std);

  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(read1, 10);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n1, 5);
}
END_TEST

START_TEST(s21_sprintf_spec_n_multiple_return_value) {
  char str1[128];
  char str2[128];
  int n1 = -1, n2 = -1, n3 = -1;
  int n1_std = -1, n2_std = -1, n3_std = -1;

  int read1 = s21_sprintf(str1, "%d%n%s%n%c%n", 42, &n1, "test", &n2, 'X', &n3);
  int read2 =
      sprintf(str2, "%d%n%s%n%c%n", 42, &n1_std, "test", &n2_std, 'X', &n3_std);

  ck_assert_int_eq(read1, read2);
  ck_assert_int_eq(n1, n1_std);
  ck_assert_int_eq(n2, n2_std);
  ck_assert_int_eq(n3, n3_std);
}
END_TEST

TCase *case_s21_sprintf_n(void) {
  TCase *tc_n = tcase_create("s21_sprintf_n");

  tcase_add_test(tc_n, s21_sprintf_spec_n_basic);
  tcase_add_test(tc_n, s21_sprintf_spec_n_beginning);
  tcase_add_test(tc_n, s21_sprintf_spec_n_end);
  tcase_add_test(tc_n, s21_sprintf_spec_n_multiple);
  tcase_add_test(tc_n, s21_sprintf_spec_n_empty_string);
  tcase_add_test(tc_n, s21_sprintf_spec_hn_short);
  tcase_add_test(tc_n, s21_sprintf_spec_ln_long);
  tcase_add_test(tc_n, s21_sprintf_spec_n_with_integers);
  tcase_add_test(tc_n, s21_sprintf_spec_n_with_strings);
  tcase_add_test(tc_n, s21_sprintf_spec_n_with_chars);
  tcase_add_test(tc_n, s21_sprintf_spec_n_with_floats);
  tcase_add_test(tc_n, s21_sprintf_spec_n_with_width_precision);
  tcase_add_test(tc_n, s21_sprintf_spec_n_ignore_flags);
  tcase_add_test(tc_n, s21_sprintf_spec_n_ignore_width);
  tcase_add_test(tc_n, s21_sprintf_spec_n_ignore_precision);
  tcase_add_test(tc_n, s21_sprintf_spec_n_consecutive);
  tcase_add_test(tc_n, s21_sprintf_spec_n_large_count);
  tcase_add_test(tc_n, s21_sprintf_spec_n_with_escape_sequences);
  tcase_add_test(tc_n, s21_sprintf_spec_n_mixed_types);
  tcase_add_test(tc_n, s21_sprintf_spec_n_return_value);
  tcase_add_test(tc_n, s21_sprintf_spec_n_multiple_return_value);

  return tc_n;
}
