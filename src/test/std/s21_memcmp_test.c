#include "../s21_test.h"

Suite *suite_s21_memcmp_test(void) {
  Suite *s = suite_create("s21_memcmp_test");
  TCase *tc = tcase_create("s21_memcmp_test");
  suite_add_tcase(s, tc);

  return s;
}
