#include <unistd.h>

#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_xX_default) {
  char str1[128];
  char str2[128];

  for (unsigned i = 0; i <= 12345; ++i) {
    int read1 = s21_sprintf(str1, "%x", i);
    int read2 = sprintf(str2, "%x", i);

    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_xX_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-x", 21);
  int read2 = sprintf(str2, "%-x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "15"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#x", 21);
  int read2 = sprintf(str2, "%#x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "0x15"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5x", 21);
  int read2 = sprintf(str2, "%5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   15"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05x", 21);
  int read2 = sprintf(str2, "%05x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5x", 21);
  int read2 = sprintf(str2, "%-5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "15   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-05x", 21);
  int read2 = sprintf(str2, "%-5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "15   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5x", 21);
  int read2 = sprintf(str2, "%.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5x", 0);
  int read2 = sprintf(str2, "%8.5x", 0);

  ck_assert_int_eq(s21_strcmp(str1, "   00000"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%.xdef", 0);
  int read2 = sprintf(str2, "abc%.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%5.xdef", 0);
  int read2 = sprintf(str2, "abc%5.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5.xdef", 0);
  int read2 = sprintf(str2, "abc%-5.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#.xdef", 0);
  int read2 = sprintf(str2, "abc%#.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#5.xdef", 0);
  int read2 = sprintf(str2, "abc%#5.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%0#5.0xdef", 0);
  int read2 = sprintf(str2, "abc%#5.0xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_7) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#-5.0xdef", 0);
  int read2 = sprintf(str2, "abc%#-5.0xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_8) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#Xdef", 0);
  int read2 = sprintf(str2, "abc%#Xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_zero_9) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#8.5Xdef", 0);
  int read2 = sprintf(str2, "abc%#8.5Xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc   00000def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_hash_extreme_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#.3x", 123);
  int read2 = sprintf(str2, "%#.3x", 123);

  ck_assert_int_eq(s21_strcmp(str1, "0x07b"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_hash_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-#6.3X", 123);
  int read2 = sprintf(str2, "%-#6.3X", 123);

  ck_assert_int_eq(s21_strcmp(str1, "0X07B "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_hash_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%0#8.5x", 21);
  int read2 = sprintf(str2, "%#8.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, " 0x00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5x", 21);
  int read2 = sprintf(str2, "%8.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width_flags) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5x", 21);
  int read2 = sprintf(str2, "%-8.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00015   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5x", 21);
  int read2 = sprintf(str2, "%8.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%156.128x", UINT_MAX);
  int read2 = sprintf(str2, "%156.128x", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%2.2x", 153);
  int read2 = sprintf(str2, "%2.2x", 153);

  ck_assert_int_eq(s21_strcmp(str1, "99"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%4.3x", 153);
  int read2 = sprintf(str2, "%4.3x", 153);

  ck_assert_int_eq(s21_strcmp(str1, " 099"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-4.3x", 153);
  int read2 = sprintf(str2, "%-4.3x", 153);

  ck_assert_int_eq(s21_strcmp(str1, "099 "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%X", 11259375);
  int read2 = sprintf(str2, "%X", 11259375);

  ck_assert_int_eq(s21_strcmp(str1, "ABCDEF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#10.8X", UINT_MAX);
  int read2 = sprintf(str2, "%#10.8X", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "0XFFFFFFFF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_hlen_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hX", USHRT_MAX);
  int read2 = sprintf(str2, "%hX", USHRT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "FFFF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_hlen_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hX", UINT_MAX);
  int read2 = sprintf(str2, "%hX", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "FFFF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_hlen_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hx", 0x12345678);
  int read2 = sprintf(str2, "%hx", 0x12345678);

  ck_assert_int_eq(s21_strcmp(str1, "5678"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_xX_prec_llen) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lX", ULONG_MAX);
  int read2 = sprintf(str2, "%lX", ULONG_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "FFFFFFFFFFFFFFFF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_x(void) {
  TCase *tc_xX = tcase_create("s21_sprintf_x");
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_default);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_flags_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_flags_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_width);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_width_flags_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_width_flags_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_width_flags_unwork);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_3);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_4);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_5);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_6);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_7);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_8);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_9);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_hash_extreme_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_hash_extreme_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_hash_unwork);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_unwork);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_3);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_4);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_5);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_6);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_hlen_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_hlen_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_hlen_3);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_llen);

  return tc_xX;
}
