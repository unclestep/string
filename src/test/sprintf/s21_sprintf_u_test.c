#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_u_flags) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-u", 21);
  int read2 = sprintf(str2, "%-u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5u", 21);
  int read2 = sprintf(str2, "%5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05u", 21);
  int read2 = sprintf(str2, "%05u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5u", 21);
  int read2 = sprintf(str2, "%-5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "21   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-05u", 21);
  int read2 = sprintf(str2, "%-5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "21   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5u", 21);
  int read2 = sprintf(str2, "%.5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_zero_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%.udef", 0);
  int read2 = sprintf(str2, "abc%.udef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_zero_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%5.udef", 0);
  int read2 = sprintf(str2, "abc%5.udef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_zero_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5.udef", 0);
  int read2 = sprintf(str2, "abc%-5.udef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_zero_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%05.udef", 0);
  int read2 = sprintf(str2, "abc%5.udef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_zero_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%udef", 0);
  int read2 = sprintf(str2, "abc%udef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_zero_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5udef", 0);
  int read2 = sprintf(str2, "abc%-5udef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0    def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_zero_7) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-8.5udef", 0);
  int read2 = sprintf(str2, "abc%-8.5udef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc00000   def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5u", 21);
  int read2 = sprintf(str2, "%8.5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_width_flags) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5u", 21);
  int read2 = sprintf(str2, "%-8.5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_width_flags_unwork_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5u", 21);
  int read2 = sprintf(str2, "%8.5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_width_flags_unwork_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% 8.5u", 21);
  int read2 = sprintf(str2, "%8.5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_width_flags_unwork_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+8.5u", 21);
  int read2 = sprintf(str2, "%8.5u", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_width_flags_extreme_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%+256.128u", UINT_MAX);
  int read2 = sprintf(str2, "%256.128u", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_width_flags_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%012.11u", UINT_MAX);
  int read2 = sprintf(str2, "%12.11u", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, " 04294967295"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_width_flags_extreme_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%010.10u", UINT_MAX);
  int read2 = sprintf(str2, "%10.10u", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "4294967295"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_hlen_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hu", USHRT_MAX);
  int read2 = sprintf(str2, "%hu", USHRT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "65535"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_hlen_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hu", UINT_MAX);
  int read2 = sprintf(str2, "%hu", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "65535"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_hlen_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hu", 0x12345678);
  int read2 = sprintf(str2, "%hu", 0x12345678);

  ck_assert_int_eq(s21_strcmp(str1, "22136"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_u_prec_llen) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lu", ULONG_MAX);
  int read2 = sprintf(str2, "%lu", ULONG_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "18446744073709551615"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_u(void) {
  TCase *tc_u = tcase_create("s21_sprintf_u");
  tcase_add_test(tc_u, s21_sprintf_spec_u_flags);
  tcase_add_test(tc_u, s21_sprintf_spec_u_width);
  tcase_add_test(tc_u, s21_sprintf_spec_u_width_flags_1);
  tcase_add_test(tc_u, s21_sprintf_spec_u_width_flags_2);
  tcase_add_test(tc_u, s21_sprintf_spec_u_width_flags_unwork);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_zero_1);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_zero_2);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_zero_3);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_zero_4);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_zero_5);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_zero_6);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_zero_7);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_width);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_width_flags);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_width_flags_unwork_1);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_width_flags_unwork_2);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_width_flags_unwork_3);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_width_flags_extreme_1);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_width_flags_extreme_2);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_width_flags_extreme_3);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_hlen_1);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_hlen_2);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_hlen_3);
  tcase_add_test(tc_u, s21_sprintf_spec_u_prec_llen);

  return tc_u;
}
