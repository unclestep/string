#ifndef S21_STRING_TEST_H
#define S21_STRING_TEST_H

#include <check.h>
#include <locale.h>
#include <string.h>

#include "../s21_string.h"
#include "include/s21_bonus_test.h"
#include "include/s21_sprintf_test.h"
#include "include/s21_sscanf_test.h"
#include "include/s21_std_test.h"

void run_testcase(Suite *testcase);
void run_tests(void);

#endif
