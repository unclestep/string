#include "../include/s21_std_test.h"

START_TEST(s21_memcpy_dest_empty) {
  char dest[3];
  const char src[] = {'a', 'b', 'c'};
  s21_memcpy(dest, src, 3);
  for (s21_size_t i = 0; i != 3; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
}
END_TEST

START_TEST(s21_memcpy_dest_nonempty) {
  char dest[] = {'x', 'y', 'z', 'd', 'e', 'f'};
  const char src[] = {'a', 'b', 'c'};
  s21_memcpy(dest, src, 3);
  for (s21_size_t i = 0; i != 6; ++i) {
    ck_assert_int_eq(dest[i], 'a' + i);
  }
}
END_TEST

START_TEST(s21_memcpy_max_int) {
  unsigned int dest = 0xFFFF0000;
  const unsigned int src = 0x0000FFFF;
  ck_assert_int_eq(*((unsigned int *)s21_memcpy(&dest, &src, 2)), 0xFFFFFFFF);
}
END_TEST

START_TEST(s21_memcpy_nocpy) {
  int dest = 123456;
  const int src = 654321;
  ck_assert_int_eq(*((int *)s21_memcpy(&dest, &src, 0)), 123456);
}
END_TEST

Suite *suite_s21_memcpy_test(void) {
  Suite *s = suite_create("s21_memcpy_test");
  TCase *tc = tcase_create("s21_memcpy_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_memcpy_dest_empty);
  tcase_add_test(tc, s21_memcpy_dest_nonempty);
  tcase_add_test(tc, s21_memcpy_max_int);
  tcase_add_test(tc, s21_memcpy_nocpy);

  return s;
}
