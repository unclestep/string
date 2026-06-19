#ifndef S21_SPRINTF_TEST_H
#define S21_SPRINTF_TEST_H

#ifdef S21_BENCH_SPRINTF
#define _POSIX_C_SOURCE 200809L
#endif

#include <check.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

#include "s21_sprintf.h"
#include "s21_std.h"

#define LOCALE "en_US.UTF-8"

TCase *case_s21_sprintf_c(void);
TCase *case_s21_sprintf_s(void);
TCase *case_s21_sprintf_di(void);
TCase *case_s21_sprintf_o(void);
TCase *case_s21_sprintf_x(void);
TCase *case_s21_sprintf_u(void);
TCase *case_s21_sprintf_f(void);
TCase *case_s21_sprintf_e(void);
TCase *case_s21_sprintf_g(void);
TCase *case_s21_sprintf_n(void);
TCase *case_s21_sprintf_p(void);

Suite *suite_s21_sprintf_test(void);

#endif
