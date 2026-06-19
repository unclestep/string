#include "s21_sprintf_test.h"

#define BENCH_SPEC "c"
#include "s21_sprintf_bench.h"

START_TEST(s21_sprintf_spec_c_default_char_1) {
  char c = 'a';
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%c", c);
  int read2 = sprintf(str2, "%c", c);

  ck_assert_int_eq(s21_strcmp(str1, "a"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_default_char_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "a %.10c c %.c e %.-c g", 'b', 'd', 'f');
  int read2 = sprintf(str2, "a %c c %c e %c g", 'b', 'd', 'f');

  ck_assert_int_eq(s21_strcmp(str1, "a b c d e f g"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_1) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc", 'z');
  int read2 = sprintf(str2, "%lc", 'z');

  ck_assert_int_eq(s21_strcmp(str1, "z"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_2) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc", L'ß');
  int read2 = sprintf(str2, "%lc", L'ß');

  ck_assert_int_eq(s21_strcmp(str1, "ß"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_3) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc", L'水');
  int read2 = sprintf(str2, "%lc", L'水');

  ck_assert_int_eq(s21_strcmp(str1, "水"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_4) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc", L'🍌');
  int read2 = sprintf(str2, "%lc", L'🍌');

  ck_assert_int_eq(s21_strcmp(str1, "🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_all) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc%lc%lc%lc", 'z', L'ß', L'水', L'🍌');
  int read2 = sprintf(str2, "%lc%lc%lc%lc", 'z', L'ß', L'水', L'🍌');

  ck_assert_int_eq(s21_strcmp(str1, "zß水🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5c", 'a');
  int read2 = sprintf(str2, "%5c", 'a');

  ck_assert_int_eq(s21_strcmp(str1, "    a"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5c", 'a');
  int read2 = sprintf(str2, "%-5c", 'a');

  ck_assert_int_eq(s21_strcmp(str1, "a    "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5c%-5c", 'a', 'b');
  int read2 = sprintf(str2, "%5c%-5c", 'a', 'b');

  ck_assert_int_eq(s21_strcmp(str1, "    ab    "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_4) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5lc%5lc%5lc%5lc", 'z', L'ß', L'水', L'🍌');
  int read2 = sprintf(str2, "%5lc%5lc%5lc%5lc", 'z', L'ß', L'水', L'🍌');

  ck_assert_int_eq(s21_strcmp(str1, "    z   ß  水 🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_5) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 =
      s21_sprintf(str1, "%-5lc%-5lc%-5lc%-5lc", 'z', L'ß', L'水', L'🍌');
  int read2 = sprintf(str2, "%-5lc%-5lc%-5lc%-5lc", 'z', L'ß', L'水', L'🍌');

  ck_assert_int_eq(s21_strcmp(str1, "z    ß   水  🍌 "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_memory_alloc_wid_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%256c", 'a');
  int read2 = sprintf(str2, "%256c", 'a');

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_memory_alloc_wid_2) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%-256c", 'a');
  int read2 = sprintf(str2, "%-256c", 'a');

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_must_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05c", '1');
  int read2 = sprintf(str2, "%5c", '1');

  ck_assert_int_eq(s21_strcmp(str1, "    1"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_empty_char) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%cdef", '\0');
  int read2 = sprintf(str2, "abc%cdef", '\0');

  ck_assert_int_eq(s21_strcmp(str1, "abc"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_empty_char_wid) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%3cdef", '\0');
  int read2 = sprintf(str2, "abc%3cdef", '\0');

  ck_assert_int_eq(s21_strcmp(str1, "abc  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_empty_wchar) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%lcdef", L'\0');
  int read2 = sprintf(str2, "abc%lcdef", L'\0');

  ck_assert_int_eq(s21_strcmp(str1, "abc"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_empty_wchar_wid) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%3lcdef", L'\0');
  int read2 = sprintf(str2, "abc%3lcdef", L'\0');

  ck_assert_int_eq(s21_strcmp(str1, "abc  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_c(void) {
  TCase *tc_c = tcase_create("s21_sprintf_c");
  tcase_add_test(tc_c, s21_sprintf_spec_c_default_char_1);
  tcase_add_test(tc_c, s21_sprintf_spec_c_default_char_2);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_1);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_2);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_3);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_4);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_all);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_1);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_2);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_3);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_4);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_5);
  tcase_add_test(tc_c, s21_sprintf_spec_c_memory_alloc_wid_1);
  tcase_add_test(tc_c, s21_sprintf_spec_c_memory_alloc_wid_2);
  tcase_add_test(tc_c, s21_sprintf_spec_c_must_unwork);
  tcase_add_test(tc_c, s21_sprintf_spec_c_empty_char);
  tcase_add_test(tc_c, s21_sprintf_spec_c_empty_char_wid);
  tcase_add_test(tc_c, s21_sprintf_spec_c_empty_wchar);
  tcase_add_test(tc_c, s21_sprintf_spec_c_empty_wchar_wid);

  return tc_c;
}
