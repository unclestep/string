#include "../s21_test.h"

Suite *suite_s21_memset_test(void) {
  Suite *s = suite_create("s21_memset_test");
  TCase *tc = tcase_create("s21_memset_test");
  suite_add_tcase(s, tc);

  return s;
}
