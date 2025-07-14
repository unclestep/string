#include "s21_test.h"

void run_testcase(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  printf("\n");
}

void run_tests(void) {
  Suite *list_cases[] = {suite_s21_memchr_test(),
                         suite_s21_memcmp_test(),
                         suite_s21_memcpy_test(),
                         suite_s21_memset_test(),
                         suite_s21_strncat_test(),
                         suite_s21_strcat_test(),
                         suite_s21_strchr_test(),
                         suite_s21_strncmp_test(),
                         suite_s21_strcmp_test(),
                         suite_s21_strncpy_test(),
                         suite_s21_strcpy_test(),
                         suite_s21_strcspn_test(),
                         suite_s21_strerror_test(),
                         suite_s21_strlen_test(),
                         suite_s21_strpbrk_test(),
                         suite_s21_strrchr_test(),
                         suite_s21_strstr_test(),
                         suite_s21_strtok_test(),
                         suite_s21_sprintf_test(),
                         suite_s21_sscanf_test(),
                         suite_s21_to_upper_test(),
                         suite_s21_to_lower_test(),
                         suite_s21_insert_test(),
                         suite_s21_trim_test(),
                         NULL};

  for (Suite **current_testcase = list_cases; *current_testcase;
       ++current_testcase) {
    run_testcase(*current_testcase);
  }
}

int main(void) {
  run_tests();
  return 0;
}
