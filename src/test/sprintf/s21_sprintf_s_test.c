#include "s21_sprintf_test.h"

#define BENCH_SPEC "s"
#include "s21_sprintf_bench.h"

START_TEST(s21_sprintf_spec_s_default_one_string) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%s", "abcdef");
  int read2 = sprintf(str2, "%s", "abcdef");

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_default_many_strings) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%s%s %s  %s%s", "ab", "cd", "ef", "\0", "gh");
  int read2 = sprintf(str2, "%s%s %s  %s%s", "ab", "cd", "ef", "\0", "gh");

  ck_assert_int_eq(s21_strcmp(str1, "abcd ef  gh"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_one_string_1) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls", L"abcdef");
  int read2 = sprintf(str2, "%ls", L"abcdef");

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_one_string_2) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls", L"Привет");
  int read2 = sprintf(str2, "%ls", L"Привет");

  ck_assert_int_eq(s21_strcmp(str1, "Привет"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_one_string_3) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls", L"水是生命之源");
  int read2 = sprintf(str2, "%ls", L"水是生命之源");

  ck_assert_int_eq(s21_strcmp(str1, "水是生命之源"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_one_string_4) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls", L"🍌🍇🍆🍑🍒🍓🌽");
  int read2 = sprintf(str2, "%ls", L"🍌🍇🍆🍑🍒🍓🌽");

  ck_assert_int_eq(s21_strcmp(str1, "🍌🍇🍆🍑🍒🍓🌽"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_many_strings) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls%ls%ls%ls%ls", L"🍌🍇🍆🍑🍒🍓🌽", L"Привет",
                          L"水是生命之源", L"", L"abcdef");
  int read2 = sprintf(str2, "%ls%ls%ls%ls%ls", L"🍌🍇🍆🍑🍒🍓🌽", L"Привет",
                      L"水是生命之源", L"", L"abcdef");

  ck_assert_int_eq(s21_strcmp(str1, "🍌🍇🍆🍑🍒🍓🌽Привет水是生命之源abcdef"),
                   0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_default_one_string) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.s", "abcdef");
  int read2 = sprintf(str2, "%.s", "abcdef");

  ck_assert_int_eq(s21_strcmp(str1, "\0"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_default_many_strings_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%s%.s%s", "ab", "cd", "ef");
  int read2 = sprintf(str2, "%s%.s%s", "ab", "cd", "ef");

  ck_assert_int_eq(s21_strcmp(str1, "abef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_default_many_strings_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.1s%.3s%.5s%.7s", "abcdef", "123456",
                          "ghijkl", "000000");
  int read2 =
      sprintf(str2, "%.1s%.3s%.5s%.7s", "abcdef", "123456", "ghijkl", "000000");

  ck_assert_int_eq(s21_strcmp(str1, "a123ghijk000000"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_default_many_strings_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%3.1s%5.3s%7.5s%9.7s", "abcdef", "123456",
                          "ghijkl", "000000");
  int read2 = sprintf(str2, "%3.1s%5.3s%7.5s%9.7s", "abcdef", "123456",
                      "ghijkl", "000000");

  ck_assert_int_eq(s21_strcmp(str1, "  a  123  ghijk   000000"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_wide_one_string) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.ls", L"🍌🍇🍆🍑🍒🍓");
  int read2 = sprintf(str2, "%.ls", L"🍌🍇🍆🍑🍒🍓");

  ck_assert_int_eq(s21_strcmp(str1, "\0"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_wide_many_strings_1) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls%.ls%ls", L"🍌🍇", L"🍆🍑", L"🍒🍓");
  int read2 = sprintf(str2, "%ls%.ls%ls", L"🍌🍇", L"🍆🍑", L"🍒🍓");

  ck_assert_int_eq(s21_strcmp(str1, "🍌🍇🍒🍓"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_wide_many_strings_2) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.1ls%.3ls%.5ls%.7ls", L"abc", L"Привет",
                          L"水是生命之源", L"🍌🍇🍒🍓");
  int read2 = sprintf(str2, "%.1ls%.3ls%.5ls%.7ls", L"abc", L"Привет",
                      L"水是生命之源", L"🍌🍇🍒🍓");

  ck_assert_int_eq(s21_strcmp(str1, "aП水🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_wide_many_strings_width) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%3.1ls%5.3ls%7.5ls%9.7ls", L"abc", L"Привет",
                          L"水是生命之源", L"🍌🍇🍒🍓");
  int read2 = sprintf(str2, "%3.1ls%5.3ls%7.5ls%9.7ls", L"abc", L"Привет",
                      L"水是生命之源", L"🍌🍇🍒🍓");

  ck_assert_int_eq(s21_strcmp(str1, "  a   П    水     🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_default_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5s", "abc");
  int read2 = sprintf(str2, "%5s", "abc");

  ck_assert_int_eq(s21_strcmp(str1, "  abc"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_default_width_flag) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5s", "abc");
  int read2 = sprintf(str2, "%-5s", "abc");

  ck_assert_int_eq(s21_strcmp(str1, "abc  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_default_width_flag_many) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5s%-5s", "abc", "def");
  int read2 = sprintf(str2, "%5s%-5s", "abc", "def");

  ck_assert_int_eq(s21_strcmp(str1, "  abcdef  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_width_many) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 =
      s21_sprintf(str1, "%7ls%7ls%7ls%7ls", L"az", L"αß", L"水是", L"🍌🌽");
  int read2 = sprintf(str2, "%7ls%7ls%7ls%7ls", L"az", L"αß", L"水是", L"🍌🌽");

  ck_assert_int_eq(s21_strcmp(str1, "     az   αß 水是🍌🌽"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_width_flag_many) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 =
      s21_sprintf(str1, "%-7ls%-7ls%-7ls%-7ls", L"az", L"αß", L"水是", L"🍌🌽");
  int read2 =
      sprintf(str2, "%-7ls%-7ls%-7ls%-7ls", L"az", L"αß", L"水是", L"🍌🌽");

  ck_assert_int_eq(s21_strcmp(str1, "az     αß   水是 🍌🌽"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_realloc_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%256s", "abcdef");
  int read2 = sprintf(str2, "%256s", "abcdef");

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_realloc_2) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%-256s", "abcdef");
  int read2 = sprintf(str2, "%-256s", "abcdef");

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_must_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%07s", "123456");
  int read2 = sprintf(str2, "%7s", "123456");

  ck_assert_int_eq(s21_strcmp(str1, " 123456"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_empty_default) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%sdef", "\0");
  int read2 = sprintf(str2, "abc%sdef", "\0");

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_empty_default_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%3sdef", "\0");
  int read2 = sprintf(str2, "abc%3sdef", "\0");

  ck_assert_int_eq(s21_strcmp(str1, "abc   def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_empty_wide) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%lsdef", L"\0");
  int read2 = sprintf(str2, "abc%lsdef", L"\0");

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_empty_wide_width) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%3lsdef", L"\0");
  int read2 = sprintf(str2, "abc%3lsdef", L"\0");

  ck_assert_int_eq(s21_strcmp(str1, "abc   def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_percent) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%%ab%%c%3s%%def", "\0");
  int read2 = sprintf(str2, "%%ab%%c%3s%%def", "\0");

  ck_assert_int_eq(s21_strcmp(str1, "%ab%c   %def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_s(void) {
  TCase *tc_s = tcase_create("s21_sprintf_s");
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_one_string);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_many_strings);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_one_string_1);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_one_string_2);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_one_string_3);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_one_string_4);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_many_strings);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_default_one_string);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_default_many_strings_1);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_default_many_strings_2);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_default_many_strings_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_wide_one_string);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_wide_many_strings_1);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_wide_many_strings_2);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_wide_many_strings_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_width_flag);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_width_flag_many);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_width_many);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_width_flag_many);
  tcase_add_test(tc_s, s21_sprintf_spec_s_realloc_1);
  tcase_add_test(tc_s, s21_sprintf_spec_s_realloc_2);
  tcase_add_test(tc_s, s21_sprintf_spec_s_must_unwork);
  tcase_add_test(tc_s, s21_sprintf_spec_s_empty_default);
  tcase_add_test(tc_s, s21_sprintf_spec_s_empty_default_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_empty_wide);
  tcase_add_test(tc_s, s21_sprintf_spec_s_empty_wide_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_percent);

  return tc_s;
}
