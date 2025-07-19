#include <unistd.h>

#include "../s21_test.h"

#define LOCALE "en_US.UTF-8"

START_TEST(s21_sprintf_spec_c_default_char_1) {
  char c = 'a';
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%c", c);
  sprintf(str2, "%c", c);

  ck_assert_int_eq(s21_strcmp(str1, "a"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_default_char_2) {
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "a %.10c c %.c e %.-c g", 'b', 'd', 'f');
  sprintf(str2, "a %c c %c e %c g", 'b', 'd', 'f');

  ck_assert_int_eq(s21_strcmp(str1, "a b c d e f g"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_1) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%lc", 'z');
  sprintf(str2, "%lc", 'z');
  ck_assert_int_eq(s21_strcmp(str1, "z"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_2) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%lc", L'ß');
  sprintf(str2, "%lc", L'ß');
  ck_assert_int_eq(s21_strcmp(str1, "ß"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_3) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%lc", L'水');
  sprintf(str2, "%lc", L'水');
  ck_assert_int_eq(s21_strcmp(str1, "水"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_4) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%lc", L'🍌');
  sprintf(str2, "%lc", L'🍌');
  ck_assert_int_eq(s21_strcmp(str1, "🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_all) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%lc%lc%lc%lc", 'z', L'ß', L'水', L'🍌');
  sprintf(str2, "%lc%lc%lc%lc", 'z', L'ß', L'水', L'🍌');
  ck_assert_int_eq(s21_strcmp(str1, "zß水🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_1) {
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%5c", 'a');
  sprintf(str2, "%5c", 'a');
  ck_assert_int_eq(s21_strcmp(str1, "    a"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_2) {
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%-5c", 'a');
  sprintf(str2, "%-5c", 'a');
  ck_assert_int_eq(s21_strcmp(str1, "a    "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_3) {
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%5c%-5c", 'a', 'b');
  sprintf(str2, "%5c%-5c", 'a', 'b');
  ck_assert_int_eq(s21_strcmp(str1, "    ab    "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_4) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%5lc%5lc%5lc%5lc", 'z', L'ß', L'水', L'🍌');
  sprintf(str2, "%5lc%5lc%5lc%5lc", 'z', L'ß', L'水', L'🍌');
  ck_assert_int_eq(s21_strcmp(str1, "    z   ß  水 🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_5) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%-5lc%-5lc%-5lc%-5lc", 'z', L'ß', L'水', L'🍌');
  sprintf(str2, "%-5lc%-5lc%-5lc%-5lc", 'z', L'ß', L'水', L'🍌');
  ck_assert_int_eq(s21_strcmp(str1, "z    ß   水  🍌 "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_memory_alloc_wid_1) {
  char str1[512];
  char str2[512];

  s21_sprintf(str1, "%256c", 'a');
  sprintf(str2, "%256c", 'a');
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_memory_alloc_wid_2) {
  char str1[512];
  char str2[512];

  s21_sprintf(str1, "%-256c", 'a');
  sprintf(str2, "%-256c", 'a');
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

START_TEST(s21_sprintf_spec_c_must_unwork) {
  char str1[128];
  char str2[128];

  s21_sprintf(str1, "%05c", '1');
  sprintf(str2, "%5c", '1');
  ck_assert_int_eq(s21_strcmp(str1, "    1"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}
END_TEST

Suite *suite_s21_sprintf_test(void) {
  Suite *s = suite_create("s21_sprintf_test");
  TCase *tc = tcase_create("s21_sprintf_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_sprintf_spec_c_default_char_1);
  tcase_add_test(tc, s21_sprintf_spec_c_default_char_2);
  tcase_add_test(tc, s21_sprintf_spec_c_wide_char_1);
  tcase_add_test(tc, s21_sprintf_spec_c_wide_char_2);
  tcase_add_test(tc, s21_sprintf_spec_c_wide_char_3);
  tcase_add_test(tc, s21_sprintf_spec_c_wide_char_4);
  tcase_add_test(tc, s21_sprintf_spec_c_wide_char_all);
  tcase_add_test(tc, s21_sprintf_spec_c_flag_and_wid_1);
  tcase_add_test(tc, s21_sprintf_spec_c_flag_and_wid_2);
  tcase_add_test(tc, s21_sprintf_spec_c_flag_and_wid_3);
  tcase_add_test(tc, s21_sprintf_spec_c_flag_and_wid_4);
  tcase_add_test(tc, s21_sprintf_spec_c_flag_and_wid_5);
  tcase_add_test(tc, s21_sprintf_spec_c_memory_alloc_wid_1);
  tcase_add_test(tc, s21_sprintf_spec_c_memory_alloc_wid_2);
  tcase_add_test(tc, s21_sprintf_spec_c_must_unwork);

  return s;
}
