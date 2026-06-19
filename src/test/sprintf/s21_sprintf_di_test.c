#include "s21_sprintf_test.h"

#define BENCH_SPEC "di"
#include "s21_sprintf_bench.h"

START_TEST(s21_sprintf_spec_di_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-d", 21);
  int read2 = sprintf(str2, "%-d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+d", 21);
  int read2 = sprintf(str2, "%+d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "+21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_flags_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% d", 21);
  int read2 = sprintf(str2, "% d", 21);

  ck_assert_int_eq(s21_strcmp(str1, " 21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_flags_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% +d", 21);
  int read2 = sprintf(str2, "%+d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "+21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_flags_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% +d", -21);
  int read2 = sprintf(str2, "%+d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_width_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5d", 21);
  int read2 = sprintf(str2, "%5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_width_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5d", -21);
  int read2 = sprintf(str2, "%5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "  -21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05d", 21);
  int read2 = sprintf(str2, "%05d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);

  read1 = s21_sprintf(str1, "%+05d", 21);
  read2 = sprintf(str2, "%+05d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "+0021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);

  read1 = s21_sprintf(str1, "% 05d", 21);
  read2 = sprintf(str2, "% 05d", 21);

  ck_assert_int_eq(s21_strcmp(str1, " 0021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05d", -21);
  int read2 = sprintf(str2, "%05d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-0021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_width_flags_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5d", 21);
  int read2 = sprintf(str2, "%-5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "21   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_width_flags_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5d", -21);
  int read2 = sprintf(str2, "%-5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-21  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-05d", -21);
  int read2 = sprintf(str2, "%-5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-21  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5d", 21);
  int read2 = sprintf(str2, "%.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5d", -21);
  int read2 = sprintf(str2, "%.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_zero_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%.ddef", 0);
  int read2 = sprintf(str2, "abc%.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_zero_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%5.ddef", 0);
  int read2 = sprintf(str2, "abc%5.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_zero_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5.ddef", 0);
  int read2 = sprintf(str2, "abc%-5.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_zero_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%+.ddef", 0);
  int read2 = sprintf(str2, "abc%+.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc+def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_zero_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc% .ddef", 0);
  int read2 = sprintf(str2, "abc% .ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_zero_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%05.ddef", 0);
  int read2 = sprintf(str2, "abc%5.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_zero_7) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%+ddef", 0);
  int read2 = sprintf(str2, "abc%+ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc+0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_zero_8) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5ddef", 0);
  int read2 = sprintf(str2, "abc%-5ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0    def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_flags) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+.5d", 21);
  int read2 = sprintf(str2, "%+.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "+00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5d", 21);
  int read2 = sprintf(str2, "%8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5d", -21);
  int read2 = sprintf(str2, "%8.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "  -00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5d", 21);
  int read2 = sprintf(str2, "%-8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5d", -21);
  int read2 = sprintf(str2, "%-8.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-00021  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5d", 21);
  int read2 = sprintf(str2, "%8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5d", -21);
  int read2 = sprintf(str2, "%8.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "  -00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% 8.5d", 21);
  int read2 = sprintf(str2, "% 8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+8.5d", 21);
  int read2 = sprintf(str2, "%+8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "  +00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+8.5d", -21);
  int read2 = sprintf(str2, "%+8.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "  -00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_extreme_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%+256.128d", INT_MAX);
  int read2 = sprintf(str2, "%+256.128d", INT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_width_flags_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5d", INT_MIN);
  int read2 = sprintf(str2, "%8.5d", INT_MIN);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_hlen_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hd", SHRT_MAX);
  int read2 = sprintf(str2, "%hd", SHRT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "32767"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_hlen_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hd", UINT_MAX);
  int read2 = sprintf(str2, "%hd", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "-1"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_hlen_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hd", 0x12345678);
  int read2 = sprintf(str2, "%hd", 0x12345678);

  ck_assert_int_eq(s21_strcmp(str1, "22136"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_di_prec_llen) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ld", LONG_MAX);
  int read2 = sprintf(str2, "%ld", LONG_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "9223372036854775807"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_di(void) {
  TCase *tc_di = tcase_create("s21_sprintf_di");
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_4);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_5);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_4);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_unwork);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_4);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_5);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_6);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_7);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_8);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_flags);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_4);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_5);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_extreme_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_extreme_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_hlen_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_hlen_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_hlen_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_llen);

  return tc_di;
}
