#include "s21_sscanf_test.h"

#define LOCALE "en_US.UTF-8"

START_TEST(s21_sscanf_uint) {
  char in[] = "1 1000000000 1 -1";
  char f[] = "%u%lu%*u%hu";
  int i_std, i_s21;
  short hi_std, hi_s21;
  long li_std, li_s21;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &i_s21, &li_s21, &hi_s21);
  count_std = sscanf(in, f, &i_std, &li_std, &hi_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_int_eq(i_s21, i_std);
  ck_assert_int_eq(li_s21, li_std);
  ck_assert_int_eq(hi_s21, hi_std);
}
END_TEST

START_TEST(s21_sscanf_int_octal) {
  char in[] = "01 01000000000 01 01";
  char f[] = "%i%li%*i%hi";
  int i_std, i_s21;
  short hi_std, hi_s21;
  long li_std, li_s21;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &i_s21, &li_s21, &hi_s21);
  count_std = sscanf(in, f, &i_std, &li_std, &hi_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_int_eq(i_s21, i_std);
  ck_assert_int_eq(li_s21, li_std);
  ck_assert_int_eq(hi_s21, hi_std);
}
END_TEST

START_TEST(s21_sscanf_int) {
  char in[] = "1 1000000000 1 1";
  char f[] = "%d%ld%*d%hd";
  int i_std, i_s21;
  short hi_std, hi_s21;
  long li_std, li_s21;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &i_s21, &li_s21, &hi_s21);
  count_std = sscanf(in, f, &i_std, &li_std, &hi_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_int_eq(i_s21, i_std);
  ck_assert_int_eq(li_s21, li_std);
  ck_assert_int_eq(hi_s21, hi_std);
}
END_TEST

START_TEST(s21_sscanf_m_int) {
  char in[] = "-1 -1000000000 -1 -1";
  char f[] = "%d%ld%*d%hd";
  int i_std, i_s21;
  short hi_std, hi_s21;
  long li_std, li_s21;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &i_s21, &li_s21, &hi_s21);
  count_std = sscanf(in, f, &i_std, &li_std, &hi_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_int_eq(i_s21, i_std);
  ck_assert_int_eq(li_s21, li_std);
  ck_assert_int_eq(hi_s21, hi_std);
}
END_TEST

START_TEST(s21_sscanf_str) {
  char in[] = "%\t foo\n bar foo";
  char f[] = "%% %s%*s foo%n";
  char s_s21[10], s_std[10];
  int count_s21, count_std;
  s21_size_t n_s21;
  int n_std;
  count_s21 = s21_sscanf(in, f, s_s21, &n_s21);
  count_std = sscanf(in, f, s_std, &n_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_uint_eq(n_s21, n_std);
  ck_assert_str_eq(s_s21, s_std);
}
END_TEST

START_TEST(s21_sscanf_wide) {
  setlocale(LC_ALL, LOCALE);
  char in[] = "\u00df\u6c34\U0001F34C \u00df\u6c34\U0001F34C \U0001F34C";
  char f[] = "%lc%ls%*ls%*lc";
  wchar_t wc_s21, wc_std;
  wchar_t ws_s21[20], ws_std[20];
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &wc_s21, ws_s21);
  count_std = sscanf(in, f, &wc_std, ws_std);
  printf("ws_s21: %ls\nws_std: %ls\n\n", ws_s21, ws_std);
  fflush(stdout);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert(wcsncmp(&wc_s21, &wc_std, 1) == 0);
  ck_assert(wcscmp(ws_s21, ws_std) == 0);
}
END_TEST

START_TEST(s21_sscanf_char) {
  char in[] = "foo";
  char f[] = "fo%c";
  char c_s21, c_std;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &c_s21);
  count_std = sscanf(in, f, &c_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_int_eq(c_s21, c_std);
}
END_TEST

START_TEST(s21_sscanf_lflt) {
  char in[] = "1.234 2.345e-12 12";
  char f[] = "%f%Lf%*f";
  float f_s21, f_std;
  long double lf_s21, lf_std;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &f_s21, &lf_s21);
  count_std = sscanf(in, f, &f_std, &lf_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_float_eq(f_s21, f_std);
  ck_assert_double_eq(lf_s21, lf_std);
}
END_TEST

START_TEST(s21_sscanf_flt) {
  char in[] = "1.234 2.345e-2 12";
  char f[] = "%f%lf%*f";
  float f_s21, f_std;
  double lf_s21, lf_std;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &f_s21, &lf_s21);
  count_std = sscanf(in, f, &f_std, &lf_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_float_eq(f_s21, f_std);
  ck_assert_double_eq(lf_s21, lf_std);
}
END_TEST

START_TEST(s21_sscanf_ptr) {
  int i;
  int *p_s21, *p_std;
  char in[20];
  sprintf(in, "%p", &i);
  char f[] = "%p";
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &p_s21);
  count_std = sscanf(in, f, &p_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_ptr_eq(p_s21, p_std);
}
END_TEST

START_TEST(s21_sscanf_uint_octal) {
  char in[] = "01234";
  char f[] = "%o";
  unsigned int ui_s21, ui_std;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &ui_s21);
  count_std = sscanf(in, f, &ui_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_uint_eq(ui_s21, ui_std);
}

START_TEST(s21_sscanf_uint_hex) {
  char in[] = "0xF1234";
  char f[] = "%x";
  unsigned int ui_s21, ui_std;
  int count_s21, count_std;
  count_s21 = s21_sscanf(in, f, &ui_s21);
  count_std = sscanf(in, f, &ui_std);
  ck_assert_int_eq(count_s21, count_std);
  ck_assert_uint_eq(ui_s21, ui_std);
}

Suite *suite_s21_sscanf_test(void) {
  Suite *s = suite_create("s21_sscanf_test");
  TCase *tc = tcase_create("s21_sscanf_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_sscanf_uint);
  tcase_add_test(tc, s21_sscanf_int_octal);
  tcase_add_test(tc, s21_sscanf_int);
  tcase_add_test(tc, s21_sscanf_m_int);
  tcase_add_test(tc, s21_sscanf_str);
  tcase_add_test(tc, s21_sscanf_wide);
  tcase_add_test(tc, s21_sscanf_char);
  tcase_add_test(tc, s21_sscanf_lflt);
  tcase_add_test(tc, s21_sscanf_flt);
  tcase_add_test(tc, s21_sscanf_ptr);
  tcase_add_test(tc, s21_sscanf_uint_octal);
  tcase_add_test(tc, s21_sscanf_uint_hex);

  return s;
}
