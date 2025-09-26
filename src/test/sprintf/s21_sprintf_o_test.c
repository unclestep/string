#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_o_default) {
  char str1[128];
  char str2[128];

  for (unsigned i = 0; i <= 12345; ++i) {
    int read1 = s21_sprintf(str1, "%o", i);
    int read2 = sprintf(str2, "%o", i);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_o_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-o", 21);
  int read2 = sprintf(str2, "%-o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "25"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#o", 21);
  int read2 = sprintf(str2, "%#o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5o", 21);
  int read2 = sprintf(str2, "%5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   25"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05o", 21);
  int read2 = sprintf(str2, "%05o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5o", 21);
  int read2 = sprintf(str2, "%-5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "25   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-05o", 21);
  int read2 = sprintf(str2, "%-5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "25   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5o", 21);
  int read2 = sprintf(str2, "%.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%.odef", 0);
  int read2 = sprintf(str2, "abc%.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%5.odef", 0);
  int read2 = sprintf(str2, "abc%5.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5.odef", 0);
  int read2 = sprintf(str2, "abc%-5.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#.odef", 0);
  int read2 = sprintf(str2, "abc%#.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#5.odef", 0);
  int read2 = sprintf(str2, "abc%#5.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc    0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%0#5.0odef", 0);
  int read2 = sprintf(str2, "abc%#5.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc    0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_7) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#-5.0odef", 0);
  int read2 = sprintf(str2, "abc%#-5.0odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0    def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_8) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#odef", 0);
  int read2 = sprintf(str2, "abc%#odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_zero_9) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#8.5odef", 0);
  int read2 = sprintf(str2, "abc%#8.5odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc   00000def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_hash_extreme_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#.3o", 123);
  int read2 = sprintf(str2, "%#.3o", 123);

  ck_assert_int_eq(s21_strcmp(str1, "0173"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_hash_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#o", 1);
  int read2 = sprintf(str2, "%#o", 1);

  ck_assert_int_eq(s21_strcmp(str1, "01"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_hash_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%0#6.5o", 21);
  int read2 = sprintf(str2, "%#6.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, " 00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5o", 21);
  int read2 = sprintf(str2, "%8.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_width_flags) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5o", 21);
  int read2 = sprintf(str2, "%-8.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00025   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5o", 21);
  int read2 = sprintf(str2, "%8.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%256.128o", UINT_MAX);
  int read2 = sprintf(str2, "%256.128o", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%3.3o", 64);
  int read2 = sprintf(str2, "%3.3o", 64);

  ck_assert_int_eq(s21_strcmp(str1, "100"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5.4o", 64);
  int read2 = sprintf(str2, "%5.4o", 64);

  ck_assert_int_eq(s21_strcmp(str1, " 0100"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5.4o", 64);
  int read2 = sprintf(str2, "%-5.4o", 64);

  ck_assert_int_eq(s21_strcmp(str1, "0100 "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05.8o", UINT_MAX);
  int read2 = sprintf(str2, "%5.4o", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "37777777777"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_hlen_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ho", USHRT_MAX);
  int read2 = sprintf(str2, "%ho", USHRT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "177777"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_hlen_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ho", UINT_MAX);
  int read2 = sprintf(str2, "%ho", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "177777"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_hlen_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ho", 0x12345678);
  int read2 = sprintf(str2, "%ho", 0x12345678);

  ck_assert_int_eq(s21_strcmp(str1, "53170"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_o_prec_llen) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lo", LONG_MAX);
  int read2 = sprintf(str2, "%lo", LONG_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "777777777777777777777"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_o(void) {
  TCase *tc_o = tcase_create("s21_sprintf_o");

  tcase_add_test(tc_o, s21_sprintf_spec_o_default);
  tcase_add_test(tc_o, s21_sprintf_spec_o_flags_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_flags_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_width);
  tcase_add_test(tc_o, s21_sprintf_spec_o_width_flags_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_width_flags_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_width_flags_unwork);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_3);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_4);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_5);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_6);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_7);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_8);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_9);
  tcase_add_test(tc_o, s21_sprintf_spec_o_hash_extreme_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_hash_extreme_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_hash_unwork);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_unwork);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_3);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_4);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_5);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_hlen_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_hlen_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_hlen_3);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_llen);

  return tc_o;
}
