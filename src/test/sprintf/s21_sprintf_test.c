#include "s21_sprintf_test.h"

Suite *suite_s21_sprintf_test(void) {
  Suite *s = suite_create("s21_sprintf_test");
  suite_add_tcase(s, case_s21_sprintf_c());
  suite_add_tcase(s, case_s21_sprintf_s());
  suite_add_tcase(s, case_s21_sprintf_di());
  suite_add_tcase(s, case_s21_sprintf_o());
  suite_add_tcase(s, case_s21_sprintf_x());
  suite_add_tcase(s, case_s21_sprintf_u());
  suite_add_tcase(s, case_s21_sprintf_f());
  suite_add_tcase(s, case_s21_sprintf_p());

  return s;
}
