#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_f_basic_positive) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%f %Lf", num1, num2);
  int read2 = sprintf(str2, "%f %Lf", num1, num2);
  printf("str1: %s\nstr2: %s\n\n", str1, str2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_basic_negative) {
  char str1[128];
  char str2[128];
  double num1 = -123.456789;
  long double num2 = -123.456789;
  int read1 = s21_sprintf(str1, "%f %Lf", num1, num2);
  int read2 = sprintf(str2, "%f %Lf", num1, num2);
  printf("str1: %s\nstr2: %s\n\n", str1, str2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_zero) {
  char str1[128];
  char str2[128];
  double num1 = 0;
  long double num2 = 0;
  int read1 = s21_sprintf(str1, "%f %Lf", num1, num2);
  int read2 = sprintf(str2, "%f %Lf", num1, num2);
  printf("s21: %s\n", str1);
  printf("std: %s\n\n", str2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_integer_part_only) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.0, 42.0, 1000.0, -5.0, -999.0};
  long double numbers2[] = {1.0, 42.0, 1000.0, -5.0, -999.0};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%f %Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%f %Lf", numbers1[i], numbers2[i]);
    printf("s21: %s\n", str1);
    printf("std: %s\n\n", str2);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_fractional_part_only) {
  char str1[128];
  char str2[128];
  double numbers1[] = {
      0.1, 0.5, 0.123456, -0.123456, 0.999999, -0.5,
  };
  long double numbers2[] = {
      0.1, 0.5, 0.123456, -0.123456, 0.999999, -0.5,
  };
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%f %Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%f %Lf", numbers1[i], numbers2[i]);
    printf("s21: %s\n", str1);
    printf("std: %s\n\n", str2);
    fflush(stdout);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_mass_test_1) {
  char str1[256];
  char str2[256];

  for (int i = -100; i <= 100; i++) {
    for (int j = 0; j < 10; j++) {
      double num1 = i + j * 0.123456789L;
      long double num2 = i + j * 0.123456789L;
      int read1 = s21_sprintf(str1, "%f %Lf", num1, num2);
      int read2 = sprintf(str2, "%f %Lf", num1, num2);
      printf("s21: %s\n", str1);
      printf("std: %s\n\n", str2);
      fflush(stdout);
      ck_assert_int_eq(s21_strcmp(str1, str2), 0);
      ck_assert_int_eq(read1, read2);
    }
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_mass_test_2) {
  char str1[512];
  char str2[512];

  const char *formats[] = {
      "%f %Lf",       "%.0f %.0Lf",   "%.1f %.1Lf",       "%.3f %.3Lf",
      "%.6f %.6Lf",   "%.10f %.10Lf", "%+f %+Lf",         "% f % Lf",
      "%#f %#Lf",     "%012f %012Lf", "%-15f %-15Lf",     "%+.2f %+.2Lf",
      "% .4f % .4Lf", "%#.0f %#.0Lf", "%015.3f %015.3Lf", "%-20.5f % -20.5Lf "};
  int format_count = sizeof(formats) / sizeof(formats[0]);

  srand(21);

  for (int test = 0; test < 200; test++) {
    double num1;
    long double num2;
    int range_type = rand() % 6;

    switch (range_type) {
      case 0:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1.0;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1.0;
        break;
      case 1:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1000.0;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1000.0;
        break;
      case 2:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 100000000.0;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 100000000.0;
        break;
      case 3:
        num1 = ((double)rand() / RAND_MAX) * 0.001;
        num2 = ((long double)rand() / RAND_MAX) * 0.001;
        break;
      case 4:
        num1 = -((double)rand() / RAND_MAX) * 1000.0;
        num2 = -((long double)rand() / RAND_MAX) * 1000.0;
        break;
      default:
        num1 = ((double)rand() / RAND_MAX - 0.5) * pow(10, rand() % 6);
        num2 = ((long double)rand() / RAND_MAX - 0.5) * pow(10, rand() % 6);
        break;
    }

    const char *format = formats[rand() % format_count];
    int read1 = s21_sprintf(str1, format, num1, num2);
    int read2 = sprintf(str2, format, num1, num2);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_default) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%f", 123.123456789);
  int read2 = sprintf(str2, "%f", 123.123456789);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_zero) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%.0f", 123.789);
  int read2 = sprintf(str2, "%.0f", 123.789);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_various) {
  char str1[128];
  char str2[128];
  double num = 123.123456789;

  for (int precision = 1; precision <= 10; precision++) {
    char format[16];
    sprintf(format, "%%.%df", precision);

    int read1 = s21_sprintf(str1, format, num);
    int read2 = sprintf(str2, format, num);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_asterisk) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%.*f", 3, 123.456789);
  int read2 = sprintf(str2, "%.*f", 3, 123.456789);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_high) {
  char str1[256];
  char str2[256];
  int read1 = s21_sprintf(str1, "%.15f", 123.123456789);
  int read2 = sprintf(str2, "%.15f", 123.123456789);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_rounding_up) {
  char str1[128];
  char str2[128];
  double numbers[] = {123.456789, 0.9999995, -123.456789, -0.9999995};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.5f", numbers[i]);
    int read2 = sprintf(str2, "%.5f", numbers[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_rounding_down) {
  char str1[128];
  char str2[128];
  double numbers[] = {123.123123, 0.1234564, -123.123123, -0.1234564};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.5f", numbers[i]);
    int read2 = sprintf(str2, "%.5f", numbers[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_rounding_edge_cases) {
  char str1[128];
  char str2[128];
  double numbers[] = {0.5, 1.5, 2.5, 3.5, -0.5, -1.5, -2.5, -3.5};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.0f", numbers[i]);
    int read2 = sprintf(str2, "%.0f", numbers[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_plus) {
  char str1[128];
  char str2[128];
  double numbers[] = {123.456, -123.456, 0.0};
  int count = 3;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%+f", numbers[i]);
    int read2 = sprintf(str2, "%+f", numbers[i]);
    printf("s21: %s\n", str1);
    printf("std: %s\n\n", str2);
    fflush(stdout);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_space) {
  char str1[128];
  char str2[128];
  double numbers[] = {123.456, -123.456, 0.0};
  int count = 3;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "% f", numbers[i]);
    int read2 = sprintf(str2, "% f", numbers[i]);
    printf("s21: %s\n", str1);
    printf("std: %s\n\n", str2);
    fflush(stdout);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_minus) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%-15f", 123.456);
  int read2 = sprintf(str2, "%-15f", 123.456);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_zero) {
  char str1[128];
  char str2[128];
  double numbers[] = {123.456, -123.456};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%015f", numbers[i]);
    int read2 = sprintf(str2, "%015f", numbers[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_hash) {
  char str1[128];
  char str2[128];
  double numbers[] = {123.0,      -123.0,  0.0,     1234.5678,
                      -1234.5678, 100.000, -100.000};
  int count = 7;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%#.0f", numbers[i]);
    int read2 = sprintf(str2, "%#.0f", numbers[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_width_larger) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%20f", 123.456);
  int read2 = sprintf(str2, "%20f", 123.456);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_width_smaller) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%5f", 123.456);
  int read2 = sprintf(str2, "%5f", 123.456);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_width_asterisk) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%*f", 15, 123.456);
  int read2 = sprintf(str2, "%*f", 15, 123.456);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_plus_space) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%+ f", 123.456);
  int read2 = sprintf(str2, "%+f", 123.456);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_minus_zero) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%-015f", 123.456);
  int read2 = sprintf(str2, "%-15f", 123.456);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_all_flags_combo) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%+#020.3f", 123.0);
  int read2 = sprintf(str2, "%+#020.3f", 123.0);
  printf("s21: %s\n", str1);
  printf("std: %s\n\n", str2);
  fflush(stdout);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_width_precision_combo) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%*.*f", 15, 3, 123.456789);
  int read2 = sprintf(str2, "%*.*f", 15, 3, 123.456789);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_negative_infinity) {
  char str1[256];
  char str2[256];
  double inf = -INFINITY;
  int read1 = s21_sprintf(str1, "%f %+f % f %05f %.0f %.10f", inf, inf, inf,
                          inf, inf, inf);
  int read2 =
      sprintf(str2, "%f %+f % f %05f %.0f %.10f", inf, inf, inf, inf, inf, inf);
  printf("s21: %s\n", str1);
  printf("std: %s\n\n", str2);
  fflush(stdout);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_positive_infinity) {
  char str1[256];
  char str2[256];
  double inf = INFINITY;
  int read1 = s21_sprintf(str1, "%f %+f % f %05f %.0f %.10f", inf, inf, inf,
                          inf, inf, inf);
  int read2 =
      sprintf(str2, "%f %+f % f %05f %.0f %.10f", inf, inf, inf, inf, inf, inf);
  printf("s21: %s\n", str1);
  printf("std: %s\n\n", str2);
  fflush(stdout);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_nan) {
  char str1[256];
  char str2[256];
  double nan = NAN;
  int read1 = s21_sprintf(str1, "%f %+f % f %05f %.0f %.10f", nan, nan, nan,
                          nan, nan, nan);
  int read2 =
      sprintf(str2, "%f %+f % f %05f %.0f %.10f", nan, nan, nan, nan, nan, nan);
  printf("s21: %s\n", str1);
  printf("std: %s\n\n", str2);
  fflush(stdout);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_boundary_values) {
  char str1[512];
  char str2[512];
  double values[] = {DBL_MIN, DBL_MAX, -DBL_MIN, -DBL_MAX};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%f", values[i]);
    int read2 = sprintf(str2, "%f", values[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_very_large) {
  char str1[128];
  char str2[128];
  double values[] = {1e+50, -1e+50, 1e+100, -1e+100};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%f", values[i]);
    int read2 = sprintf(str2, "%f", values[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_near_zero) {
  char str1[128];
  char str2[128];
  double values[] = {1e-50, -1e-50, 1e-100, -1e-100};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%f", values[i]);
    int read2 = sprintf(str2, "%f", values[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_negative_precision) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%.*f", -5, 123.456);
  int read2 = sprintf(str2, "%.*f", -5, 123.456);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_negative_width) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%*f", -15, 123.456);
  int read2 = sprintf(str2, "%*f", -15, 123.456);
  printf("s21: %s\n", str1);
  printf("std: %s\n\n", str2);
  fflush(stdout);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_f(void) {
  TCase *tc_f = tcase_create("s21_sprintf_f");

  tcase_add_test(tc_f, s21_sprintf_spec_f_basic_positive);
  tcase_add_test(tc_f, s21_sprintf_spec_f_basic_negative);
  tcase_add_test(tc_f, s21_sprintf_spec_f_zero);
  tcase_add_test(tc_f, s21_sprintf_spec_f_integer_part_only);
  tcase_add_test(tc_f, s21_sprintf_spec_f_fractional_part_only);
  tcase_add_test(tc_f, s21_sprintf_spec_f_mass_test_1);
  tcase_add_test(tc_f, s21_sprintf_spec_f_mass_test_2);
  tcase_add_test(tc_f, s21_sprintf_spec_f_precision_default);
  tcase_add_test(tc_f, s21_sprintf_spec_f_precision_zero);
  tcase_add_test(tc_f, s21_sprintf_spec_f_precision_various);
  tcase_add_test(tc_f, s21_sprintf_spec_f_precision_asterisk);
  tcase_add_test(tc_f, s21_sprintf_spec_f_precision_high);
  tcase_add_test(tc_f, s21_sprintf_spec_f_rounding_up);
  tcase_add_test(tc_f, s21_sprintf_spec_f_rounding_down);
  tcase_add_test(tc_f, s21_sprintf_spec_f_rounding_edge_cases);
  tcase_add_test(tc_f, s21_sprintf_spec_f_flag_plus);
  tcase_add_test(tc_f, s21_sprintf_spec_f_flag_space);
  tcase_add_test(tc_f, s21_sprintf_spec_f_flag_minus);
  tcase_add_test(tc_f, s21_sprintf_spec_f_flag_zero);
  tcase_add_test(tc_f, s21_sprintf_spec_f_flag_hash);
  tcase_add_test(tc_f, s21_sprintf_spec_f_width_larger);
  tcase_add_test(tc_f, s21_sprintf_spec_f_width_smaller);
  tcase_add_test(tc_f, s21_sprintf_spec_f_width_asterisk);
  tcase_add_test(tc_f, s21_sprintf_spec_f_flag_plus_space);
  tcase_add_test(tc_f, s21_sprintf_spec_f_flag_minus_zero);
  tcase_add_test(tc_f, s21_sprintf_spec_f_all_flags_combo);
  tcase_add_test(tc_f, s21_sprintf_spec_f_width_precision_combo);
  tcase_add_test(tc_f, s21_sprintf_spec_f_negative_infinity);
  tcase_add_test(tc_f, s21_sprintf_spec_f_positive_infinity);
  tcase_add_test(tc_f, s21_sprintf_spec_f_nan);
  tcase_add_test(tc_f, s21_sprintf_spec_f_boundary_values);
  tcase_add_test(tc_f, s21_sprintf_spec_f_near_zero);
  tcase_add_test(tc_f, s21_sprintf_spec_f_very_large);
  tcase_add_test(tc_f, s21_sprintf_spec_f_negative_precision);
  tcase_add_test(tc_f, s21_sprintf_spec_f_negative_width);

  return tc_f;
}
