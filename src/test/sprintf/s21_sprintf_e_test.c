#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_e_basic_positive) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%e %Le", num1, num2);
  int read2 = sprintf(str2, "%e %Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_basic_negative) {
  char str1[128];
  char str2[128];
  double num1 = -123.456789;
  long double num2 = -123.456789L;
  int read1 = s21_sprintf(str1, "%e %Le", num1, num2);
  int read2 = sprintf(str2, "%e %Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_zero) {
  char str1[128];
  char str2[128];
  double num1 = 0.0;
  long double num2 = 0.0L;
  int read1 = s21_sprintf(str1, "%e %Le", num1, num2);
  int read2 = sprintf(str2, "%e %Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_uppercase) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%E %LE", num1, num2);
  int read2 = sprintf(str2, "%E %LE", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_different_exponents) {
  char str1[256];
  char str2[256];
  double numbers1[] = {1.23, 12.3, 123.0, 1230.0, 0.123, 0.0123, 0.00123};
  long double numbers2[] = {1.23L,  12.3L,   123.0L,  1230.0L,
                            0.123L, 0.0123L, 0.00123L};
  int count = 7;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%e %Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_positive_exponents) {
  char str1[256];
  char str2[256];
  double numbers1[] = {1e5, 1e10, 1e20, 1.234e15};
  long double numbers2[] = {1e5L, 1e10L, 1e20L, 1.234e15L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%e %Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_negative_exponents) {
  char str1[256];
  char str2[256];
  double numbers1[] = {1e-5, 1e-10, 1e-20, 1.234e-15};
  long double numbers2[] = {1e-5L, 1e-10L, 1e-20L, 1.234e-15L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%e %Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_zero_exponent) {
  char str1[256];
  char str2[256];
  double numbers1[] = {1.0, 2.5, 9.999};
  long double numbers2[] = {1.0L, 2.5L, 9.999L};
  int count = 3;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%e %Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_boundary_exponents) {
  char str1[256];
  char str2[256];
  double numbers1[] = {9.999, 10.0, 10.001, 0.9999, 1.0, 1.0001};
  long double numbers2[] = {9.999L, 10.0L, 10.001L, 0.9999L, 1.0L, 1.0001L};
  int count = 6;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%e %Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_mass_test_1) {
  char str1[256];
  char str2[256];

  for (int i = -50; i <= 50; i += 5) {
    for (int j = 0; j < 5; j++) {
      double num1 = (i + j * 0.123456789) * pow(10, (i % 10) - 5);
      long double num2 = (i + j * 0.123456789L) * pow(10, (i % 10) - 5);
      int read1 = s21_sprintf(str1, "%e %Le", num1, num2);
      int read2 = sprintf(str2, "%e %Le", num1, num2);
      ck_assert_int_eq(s21_strcmp(str1, str2), 0);
      ck_assert_int_eq(read1, read2);
    }
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_mass_test_2) {
  char str1[512];
  char str2[512];

  const char *formats[] = {
      "%e %Le",       "%.0e %.0Le",   "%.1e %.1Le",       "%.3e %.3Le",
      "%.6e %.6Le",   "%.10e %.10Le", "%+e %+Le",         "% e % Le",
      "%#e %#Le",     "%012e %012Le", "%-15e %-15Le",     "%+.2e %+.2Le",
      "% .4e % .4Le", "%#.0e %#.0Le", "%015.3e %015.3Le", "%-20.5e %-20.5Le"};
  int format_count = sizeof(formats) / sizeof(formats[0]);

  srand(21);

  for (int test = 0; test < 200; test++) {
    double num1;
    long double num2;
    int range_type = rand() % 8;

    switch (range_type) {
      case 0:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 10.0;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 10.0;
        break;
      case 1:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1e10;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1e10;
        break;
      case 2:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1e-8;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1e-8;
        break;
      case 3:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1e20;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1e20;
        break;
      case 4:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1e-15;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1e-15;
        break;
      case 5:
        num1 = ((double)rand() / RAND_MAX - 0.5) * pow(10, (rand() % 20) - 10);
        num2 = ((long double)rand() / RAND_MAX - 0.5) *
               pow(10, (rand() % 20) - 10);
        break;
      case 6:
        num1 = ((double)rand() / RAND_MAX) * 1e6;
        num2 = ((long double)rand() / RAND_MAX) * 1e6;
        break;
      default:
        num1 = -((double)rand() / RAND_MAX) * 1e6;
        num2 = -((long double)rand() / RAND_MAX) * 1e6;
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

START_TEST(s21_sprintf_spec_e_precision_default) {
  char str1[128];
  char str2[128];
  double num1 = 123.123456789;
  long double num2 = 123.123456789L;
  int read1 = s21_sprintf(str1, "%e %Le", num1, num2);
  int read2 = sprintf(str2, "%e %Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_precision_zero) {
  char str1[128];
  char str2[128];
  double num1 = 123.789;
  long double num2 = 123.789L;
  int read1 = s21_sprintf(str1, "%.0e %.0Le", num1, num2);
  int read2 = sprintf(str2, "%.0e %.0Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_precision_various) {
  char str1[128];
  char str2[128];
  double num1 = 123.123456789;
  long double num2 = 123.123456789L;

  for (int precision = 1; precision <= 10; precision++) {
    char format[32];
    sprintf(format, "%%.%de %%.%dLe", precision, precision);

    int read1 = s21_sprintf(str1, format, num1, num2);
    int read2 = sprintf(str2, format, num1, num2);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_precision_asterisk) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%.*e %.*Le", 3, num1, 3, num2);
  int read2 = sprintf(str2, "%.*e %.*Le", 3, num1, 3, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_precision_high) {
  char str1[256];
  char str2[256];
  double num1 = 123.123456789;
  long double num2 = 123.123456789L;
  int read1 = s21_sprintf(str1, "%.15e %.15Le", num1, num2);
  int read2 = sprintf(str2, "%.15e %.15Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_rounding_up) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456789e5, 9.9999995e-10, -1.23456789e5,
                       -9.9999995e-10};
  long double numbers2[] = {1.23456789e5L, 9.9999995e-10L, -1.23456789e5L,
                            -9.9999995e-10L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.5e %.5Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%.5e %.5Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_rounding_down) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23123123e5, 1.234564e-10, -1.23123123e5,
                       -1.234564e-10};
  long double numbers2[] = {1.23123123e5L, 1.234564e-10L, -1.23123123e5L,
                            -1.234564e-10L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.5e %.5Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%.5e %.5Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_rounding_edge_cases) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.5e0, 2.5e0, 3.5e0, -1.5e0, -2.5e0, -3.5e0};
  long double numbers2[] = {1.5e0L, 2.5e0L, 3.5e0L, -1.5e0L, -2.5e0L, -3.5e0L};
  int count = 6;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.0e %.0Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%.0e %.0Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_flag_plus) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456e5, -1.23456e5, 0.0};
  long double numbers2[] = {1.23456e5L, -1.23456e5L, 0.0L};
  int count = 3;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%+e %+Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%+e %+Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_flag_space) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456e5, -1.23456e5, 0.0};
  long double numbers2[] = {1.23456e5L, -1.23456e5L, 0.0L};
  int count = 3;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "% e % Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "% e % Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_flag_minus) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456e5;
  long double num2 = 1.23456e5L;
  int read1 = s21_sprintf(str1, "%-20e %-20Le", num1, num2);
  int read2 = sprintf(str2, "%-20e %-20Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_flag_zero) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456e5, -1.23456e5};
  long double numbers2[] = {1.23456e5L, -1.23456e5L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%020e %020Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%020e %020Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_flag_hash) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23e5, -1.23e5, 0.0, 1.0e10, -1.0e10, 1.0e-5, -1.0e-5};
  long double numbers2[] = {1.23e5L,  -1.23e5L, 0.0L,    1.0e10L,
                            -1.0e10L, 1.0e-5L,  -1.0e-5L};
  int count = 7;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%#.0e %#.0Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%#.0e %#.0Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_width_larger) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456e5;
  long double num2 = 1.23456e5L;
  int read1 = s21_sprintf(str1, "%25e %25Le", num1, num2);
  int read2 = sprintf(str2, "%25e %25Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_width_smaller) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456e5;
  long double num2 = 1.23456e5L;
  int read1 = s21_sprintf(str1, "%5e %5Le", num1, num2);
  int read2 = sprintf(str2, "%5e %5Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_width_asterisk) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456e5;
  long double num2 = 1.23456e5L;
  int read1 = s21_sprintf(str1, "%*e %*Le", 20, num1, 20, num2);
  int read2 = sprintf(str2, "%*e %*Le", 20, num1, 20, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_flag_plus_space) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456e5;
  long double num2 = 1.23456e5L;
  int read1 = s21_sprintf(str1, "%+ e %+ Le", num1, num2);
  int read2 = sprintf(str2, "%+e %+Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_flag_minus_zero) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456e5;
  long double num2 = 1.23456e5L;
  int read1 = s21_sprintf(str1, "%-020e %-020Le", num1, num2);
  int read2 = sprintf(str2, "%-20e %-20Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_all_flags_combo) {
  char str1[128];
  char str2[128];
  double num1 = 1.23e5;
  long double num2 = 1.23e5L;
  int read1 = s21_sprintf(str1, "%+#025.3e %+#025.3Le", num1, num2);
  int read2 = sprintf(str2, "%+#025.3e %+#025.3Le", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_width_precision_combo) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456789e5;
  long double num2 = 1.23456789e5L;
  int read1 = s21_sprintf(str1, "%*.*e %*.*Le", 20, 3, num1, 20, 3, num2);
  int read2 = sprintf(str2, "%*.*e %*.*Le", 20, 3, num1, 20, 3, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_case_comparison) {
  char str1[256];
  char str2[256];
  double num1 = 1.23456e10;
  long double num2 = 1.23456e10L;

  int read1 = s21_sprintf(str1, "%e %E %Le %LE", num1, num1, num2, num2);
  int read2 = sprintf(str2, "%e %E %Le %LE", num1, num1, num2, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_mixed_case) {
  char str1[256];
  char str2[256];
  double numbers1[] = {1.23e5, -4.56e-10, 0.0, 9.87e20};
  long double numbers2[] = {1.23e5L, -4.56e-10L, 0.0L, 9.87e20L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %E %Le %LE", numbers1[i], numbers1[i],
                            numbers2[i], numbers2[i]);
    int read2 = sprintf(str2, "%e %E %Le %LE", numbers1[i], numbers1[i],
                        numbers2[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_negative_infinity) {
  char str1[256];
  char str2[256];
  double inf1 = -INFINITY;
  long double inf2 = -INFINITY;
  int read1 = s21_sprintf(
      str1, "%e %+e % e %05e %.0e %.10e %Le %+Le % Le %05Le %.0Le %.10Le", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  int read2 = sprintf(
      str2, "%e %+e % e %05e %.0e %.10e %Le %+Le % Le %05Le %.0Le %.10Le", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_positive_infinity) {
  char str1[256];
  char str2[256];
  double inf1 = INFINITY;
  long double inf2 = INFINITY;
  int read1 = s21_sprintf(
      str1, "%e %+e % e %05e %.0e %.10e %Le %+Le % Le %05Le %.0Le %.10Le", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  int read2 = sprintf(
      str2, "%e %+e % e %05e %.0e %.10e %Le %+Le % Le %05Le %.0Le %.10Le", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_nan) {
  char str1[256];
  char str2[256];
  double nan1 = NAN;
  long double nan2 = NAN;
  int read1 = s21_sprintf(
      str1, "%e %+e % e %05e %.0e %.10e %Le %+Le % Le %05Le %.0Le %.10Le", nan1,
      nan1, nan1, nan1, nan1, nan1, nan2, nan2, nan2, nan2, nan2, nan2);
  int read2 = sprintf(
      str2, "%e %+e % e %05e %.0e %.10e %Le %+Le % Le %05Le %.0Le %.10Le", nan1,
      nan1, nan1, nan1, nan1, nan1, nan2, nan2, nan2, nan2, nan2, nan2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_infinity_case) {
  char str1[256];
  char str2[256];
  double inf1 = INFINITY;
  double ninf1 = -INFINITY;
  long double inf2 = INFINITY;
  long double ninf2 = -INFINITY;

  int read1 = s21_sprintf(str1, "%e %E %Le %LE", inf1, ninf1, inf2, ninf2);
  int read2 = sprintf(str2, "%e %E %Le %LE", inf1, ninf1, inf2, ninf2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_nan_case) {
  char str1[256];
  char str2[256];
  double nan1 = NAN;
  long double nan2 = NAN;

  int read1 = s21_sprintf(str1, "%e %E %Le %LE", nan1, nan1, nan2, nan2);
  int read2 = sprintf(str2, "%e %E %Le %LE", nan1, nan1, nan2, nan2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_boundary_values_1) {
  char str1[512];
  char str2[512];
  double values1[] = {DBL_MIN, DBL_MAX, -DBL_MIN, -DBL_MAX};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e", values1[i]);
    int read2 = sprintf(str2, "%e", values1[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_boundary_values_2) {
  char str1[512];
  char str2[512];
  long double values2[] = {LDBL_MIN, LDBL_MAX, -LDBL_MIN, -LDBL_MAX};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%Le", values2[i]);
    int read2 = sprintf(str2, "%Le", values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_very_large) {
  char str1[128];
  char str2[128];
  double values1[] = {1e+50, -1e+50, 1e+100, -1e+100, 1e+200, -1e+200};
  long double values2[] = {1e+50L,   -1e+50L, 1e+100L,
                           -1e+100L, 1e+200L, -1e+200L};
  int count = 6;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %Le", values1[i], values2[i]);
    int read2 = sprintf(str2, "%e %Le", values1[i], values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_very_small) {
  char str1[128];
  char str2[128];
  double values1[] = {1e-50, -1e-50, 1e-100, -1e-100, 1e-200, -1e-200};
  long double values2[] = {1e-50L,   -1e-50L, 1e-100L,
                           -1e-100L, 1e-200L, -1e-200L};
  int count = 6;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %Le", values1[i], values2[i]);
    int read2 = sprintf(str2, "%e %Le", values1[i], values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_powers_of_ten) {
  char str1[256];
  char str2[256];

  for (int exp = -10; exp <= 10; exp++) {
    double num1 = pow(10.0, exp);
    long double num2 = pow(10.0L, exp);
    int read1 = s21_sprintf(str1, "%e %Le", num1, num2);
    int read2 = sprintf(str2, "%e %Le", num1, num2);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_near_zero) {
  char str1[128];
  char str2[128];
  double values1[] = {1e-300, -1e-300, 1e-307, -1e-307};
  long double values2[] = {1e-300L, -1e-300L, 1e-307L, -1e-307L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%e %Le", values1[i], values2[i]);
    int read2 = sprintf(str2, "%e %Le", values1[i], values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_mantissa_edge_cases) {
  char str1[256];
  char str2[256];
  double numbers1[] = {9.999999e5, 1.000001e5, 9.999999e-5, 1.000001e-5};
  long double numbers2[] = {9.999999e5L, 9.999999e5L, 9.999999e-5L,
                            1.000001e-5L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.5e %.5Le", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%.5e %.5Le", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_e_negative_precision) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456e5;
  long double num2 = 1.23456e5L;
  int read1 = s21_sprintf(str1, "%.*e %.*Le", -5, num1, -5, num2);
  int read2 = sprintf(str2, "%.*e %.*Le", -5, num1, -5, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_e_negative_width) {
  char str1[128];
  char str2[128];
  double num1 = 1.23456e5;
  long double num2 = 1.23456e5L;
  int read1 = s21_sprintf(str1, "%*e %*Le", -20, num1, -20, num2);
  int read2 = sprintf(str2, "%*e %*Le", -20, num1, -20, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_e(void) {
  TCase *tc_e = tcase_create("s21_sprintf_e");

  tcase_add_test(tc_e, s21_sprintf_spec_e_basic_positive);
  tcase_add_test(tc_e, s21_sprintf_spec_e_basic_negative);
  tcase_add_test(tc_e, s21_sprintf_spec_e_zero);
  tcase_add_test(tc_e, s21_sprintf_spec_e_uppercase);
  tcase_add_test(tc_e, s21_sprintf_spec_e_different_exponents);
  tcase_add_test(tc_e, s21_sprintf_spec_e_positive_exponents);
  tcase_add_test(tc_e, s21_sprintf_spec_e_negative_exponents);
  tcase_add_test(tc_e, s21_sprintf_spec_e_zero_exponent);
  tcase_add_test(tc_e, s21_sprintf_spec_e_boundary_exponents);
  tcase_add_test(tc_e, s21_sprintf_spec_e_mass_test_1);
  tcase_add_test(tc_e, s21_sprintf_spec_e_mass_test_2);
  tcase_add_test(tc_e, s21_sprintf_spec_e_precision_default);
  tcase_add_test(tc_e, s21_sprintf_spec_e_precision_zero);
  tcase_add_test(tc_e, s21_sprintf_spec_e_precision_various);
  tcase_add_test(tc_e, s21_sprintf_spec_e_precision_asterisk);
  tcase_add_test(tc_e, s21_sprintf_spec_e_precision_high);
  tcase_add_test(tc_e, s21_sprintf_spec_e_rounding_up);
  tcase_add_test(tc_e, s21_sprintf_spec_e_rounding_down);
  tcase_add_test(tc_e, s21_sprintf_spec_e_rounding_edge_cases);
  tcase_add_test(tc_e, s21_sprintf_spec_e_flag_plus);
  tcase_add_test(tc_e, s21_sprintf_spec_e_flag_space);
  tcase_add_test(tc_e, s21_sprintf_spec_e_flag_minus);
  tcase_add_test(tc_e, s21_sprintf_spec_e_flag_zero);
  tcase_add_test(tc_e, s21_sprintf_spec_e_flag_hash);
  tcase_add_test(tc_e, s21_sprintf_spec_e_width_larger);
  tcase_add_test(tc_e, s21_sprintf_spec_e_width_smaller);
  tcase_add_test(tc_e, s21_sprintf_spec_e_width_asterisk);
  tcase_add_test(tc_e, s21_sprintf_spec_e_flag_plus_space);
  tcase_add_test(tc_e, s21_sprintf_spec_e_flag_minus_zero);
  tcase_add_test(tc_e, s21_sprintf_spec_e_all_flags_combo);
  tcase_add_test(tc_e, s21_sprintf_spec_e_width_precision_combo);
  tcase_add_test(tc_e, s21_sprintf_spec_e_case_comparison);
  tcase_add_test(tc_e, s21_sprintf_spec_e_mixed_case);
  tcase_add_test(tc_e, s21_sprintf_spec_e_negative_infinity);
  tcase_add_test(tc_e, s21_sprintf_spec_e_positive_infinity);
  tcase_add_test(tc_e, s21_sprintf_spec_e_nan);
  tcase_add_test(tc_e, s21_sprintf_spec_e_infinity_case);
  tcase_add_test(tc_e, s21_sprintf_spec_e_nan_case);
  tcase_add_test(tc_e, s21_sprintf_spec_e_boundary_values_1);
  tcase_add_test(tc_e, s21_sprintf_spec_e_boundary_values_2);
  tcase_add_test(tc_e, s21_sprintf_spec_e_very_large);
  tcase_add_test(tc_e, s21_sprintf_spec_e_very_small);
  tcase_add_test(tc_e, s21_sprintf_spec_e_powers_of_ten);
  tcase_add_test(tc_e, s21_sprintf_spec_e_near_zero);
  tcase_add_test(tc_e, s21_sprintf_spec_e_mantissa_edge_cases);
  tcase_add_test(tc_e, s21_sprintf_spec_e_negative_precision);
  tcase_add_test(tc_e, s21_sprintf_spec_e_negative_width);

  return tc_e;
}
