#include "s21_std_test.h"

START_TEST(s21_strcat_dest_empty) {
  char dest[6] = "\0";
  const char src[] = "abcde";
  s21_strcat(dest, src);
  for (s21_size_t i = 0; i != 5; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(dest[5], '\0');
  ck_assert_int_eq(s21_strlen(dest), s21_strlen(src));
}
END_TEST

START_TEST(s21_strcat_all_nonempty) {
  char dest[9] = "abcde";
  const char src[] = "fgh";
  s21_strcat(dest, src);
  for (s21_size_t i = 0; i != 8; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(dest[8], '\0');
  ck_assert_int_eq(s21_strlen(dest), 8);
}
END_TEST

START_TEST(s21_strcat_src_empty) {
  char dest[4] = "abc";
  const char src[] = "\0";
  s21_strcat(dest, src);
  for (s21_size_t i = 0; i != 3; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
  ck_assert_int_eq(dest[3], '\0');
  ck_assert_int_eq(s21_strlen(dest), 3);
}
END_TEST

START_TEST(s21_strcat_all_empty) {
  char dest[] = "\0";
  const char src[] = "\0";
  s21_strcat(dest, src);
  ck_assert_int_eq(dest[0], '\0');
  ck_assert_int_eq(s21_strlen(dest), 0);
  ck_assert_int_eq(s21_strlen(dest), s21_strlen(dest));
}
END_TEST

Suite *suite_s21_strcat_test(void) {
  Suite *s = suite_create("s21_strcat_test");
  TCase *tc = tcase_create("s21_strcat_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strcat_dest_empty);
  tcase_add_test(tc, s21_strcat_all_nonempty);
  tcase_add_test(tc, s21_strcat_src_empty);
  tcase_add_test(tc, s21_strcat_all_empty);

  return s;
}
