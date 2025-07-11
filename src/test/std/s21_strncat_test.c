#include "../s21_test.h"

START_TEST(s21_strncat_n_eq_len_1) {
  char dest[6] = "\0";
  const char src[] = "abcde";
  s21_strncat(dest, src, 5);
  for (s21_size_t i = 0; i != 5; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(s21_strlen(dest), s21_strlen(src));
}
END_TEST

START_TEST(s21_strncat_n_eq_len_2) {
  char dest[7] = "abc";
  const char src[] = "def";
  s21_strncat(dest, src, 3);
  for (s21_size_t i = 0; i != 6; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(s21_strlen(dest), s21_strlen(src) + 3);
}
END_TEST

START_TEST(s21_strncat_n_le_len) {
  char dest[7] = "abc";
  const char src[] = "defghi";
  s21_strncat(dest, src, 3);
  for (s21_size_t i = 0; i != 6; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(s21_strlen(dest), s21_strlen(src));
}
END_TEST

START_TEST(s21_strncat_n_gr_len) {
  char dest[9] = "abc";
  const char src[] = "defgh";
  s21_strncat(dest, src, 10);
  for (s21_size_t i = 0; i != 8; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(s21_strlen(dest), 8);
}
END_TEST

START_TEST(s21_strncat_n0) {
  char dest[6] = "abcde";
  const char src[] = "12345";
  s21_strncat(dest, src, 0);
  for (s21_size_t i = 0; i != 5; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(s21_strlen(dest), 5);
}
END_TEST

Suite *suite_s21_strncat_test(void) {
  Suite *s = suite_create("s21_strncat_test");
  TCase *tc = tcase_create("s21_strncat_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strncat_n_eq_len_1);
  tcase_add_test(tc, s21_strncat_n_eq_len_2);
  tcase_add_test(tc, s21_strncat_n_le_len);
  tcase_add_test(tc, s21_strncat_n_gr_len);
  tcase_add_test(tc, s21_strncat_n0);

  return s;
}
