#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_g_basic_decimal) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 12.3456, 123.456, 0.123456, 0.0123456};
  long double numbers2[] = {1.23456L, 12.3456L, 123.456L, 0.123456L,
                            0.0123456L};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%g %Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_basic_exponential) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456e-5, 1.23456e10, 0.00001, 1000000};
  long double numbers2[] = {1.23456e-5L, 1.23456e10L, 0.00001L, 1000000L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%g %Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_zero) {
  char str1[128];
  char str2[128];
  double num1 = 0.0;
  long double num2 = 0.0L;
  int read1 = s21_sprintf(str1, "%g %Lg", num1, num2);
  int read2 = sprintf(str2, "%g %Lg", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_g_uppercase) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%G %LG", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%G %LG", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_boundary_transitions) {
  char str1[256];
  char str2[256];
  double numbers1[] = {
      0.0001, 0.00009999, 0.000001, 1000000, 999999, 100000,
  };
  long double numbers2[] = {0.0001L,  0.00009999L, 0.000001L,
                            1000000L, 999999L,     100000L};
  int count = 6;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%g %Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_precision_boundaries) {
  char str1[256];
  char str2[256];
  double num1 = 123456.789;
  long double num2 = 123456.789L;

  for (int precision = 1; precision <= 8; precision++) {
    char format[32];
    sprintf(format, "%%.%dg %%.%dLg", precision, precision);

    int read1 = s21_sprintf(str1, format, num1, num2);
    int read2 = sprintf(str2, format, num1, num2);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_powers_of_ten_boundaries) {
  char str1[256];
  char str2[256];

  for (int exp = -6; exp <= 6; exp++) {
    double num1 = pow(10.0, exp);
    long double num2 = pow(10.0L, exp);

    int read1 = s21_sprintf(str1, "%g %Lg", num1, num2);
    int read2 = sprintf(str2, "%g %Lg", num1, num2);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_trailing_zeros) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.230000, 123.000, 0.100000, 1.000};
  long double numbers2[] = {1.230000L, 123.000L, 0.100000L, 1.000L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%g %Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_flag_hash) {
  char str1[128];
  char str2[128];
  double numbers1[] = {123.000, 1.000, 0.100000, 1230000};
  long double numbers2[] = {123.000L, 1.000L, 0.100000L, 1230000L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%#g %#Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%#g %#Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_integer_like) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.0, 42.0, 1000.0, -5.0, -999.0};
  long double numbers2[] = {1.0L, 42.0L, 1000.0L, -5.0L, -999.0L};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%g %Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_precision_default) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%g %Lg", num1, num2);
  int read2 = sprintf(str2, "%g %Lg", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_g_precision_zero) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.7, 12.7, 123.7, 0.7};
  long double numbers2[] = {1.7L, 12.7L, 123.7L, 0.7L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.0g %.0Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%.0g %.0Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_precision_various) {
  char str1[128];
  char str2[128];
  double num1 = 123456.789;
  long double num2 = 123456.789L;

  for (int precision = 1; precision <= 10; precision++) {
    char format[32];
    sprintf(format, "%%.%dg %%.%dLg", precision, precision);

    int read1 = s21_sprintf(str1, format, num1, num2);
    int read2 = sprintf(str2, format, num1, num2);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_precision_asterisk) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%.*g %.*Lg", 4, num1, 4, num2);
  int read2 = sprintf(str2, "%.*g %.*Lg", 4, num1, 4, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_g_mass_test_1) {
  char str1[256];
  char str2[256];

  for (int i = -30; i <= 30; i += 3) {
    for (int j = 0; j < 3; j++) {
      double num1 = (i + j * 0.123456789) * pow(10, (i % 8) - 4);
      long double num2 = (i + j * 0.123456789L) * pow(10, (i % 8) - 4);
      int read1 = s21_sprintf(str1, "%g %Lg", num1, num2);
      int read2 = sprintf(str2, "%g %Lg", num1, num2);
      ck_assert_int_eq(s21_strcmp(str1, str2), 0);
      ck_assert_int_eq(read1, read2);
    }
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_mass_test_2) {
  char str1[512];
  char str2[512];

  const char *formats[] = {
      "%g %Lg",       "%.0g %.0Lg",   "%.1g %.1Lg",       "%.3g %.3Lg",
      "%.6g %.6Lg",   "%.10g %.10Lg", "%+g %+Lg",         "% g % Lg",
      "%#g %#Lg",     "%012g %012Lg", "%-15g %-15Lg",     "%+.2g %+.2Lg",
      "% .4g % .4Lg", "%#.0g %#.0Lg", "%015.3g %015.3Lg", "%-20.5g %-20.5Lg"};
  int format_count = sizeof(formats) / sizeof(formats[0]);

  srand(21);

  for (int test = 0; test < 200; test++) {
    double num1;
    long double num2;
    int range_type = rand() % 10;

    switch (range_type) {
      case 0:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1000.0;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1000.0;
        break;
      case 1:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1e10;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1e10;
        break;
      case 2:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1e-6;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1e-6;
        break;
      case 3:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 0.0001;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 0.0001;
        break;
      case 4:
        num1 = (double)(rand() % 10000);
        num2 = (long double)(rand() % 10000);
        break;
      case 5:
        num1 = ((double)(rand() % 1000)) + 0.10000;
        num2 = ((long double)(rand() % 1000)) + 0.10000L;
        break;
      case 6:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1e20;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1e20;
        break;
      case 7:
        num1 = ((double)rand() / RAND_MAX - 0.5) * 1e-15;
        num2 = ((long double)rand() / RAND_MAX - 0.5) * 1e-15;
        break;
      case 8:
        num1 = ((double)rand() / RAND_MAX) * 1e3;
        num2 = ((long double)rand() / RAND_MAX) * 1e3;
        break;
      default:
        num1 = -((double)rand() / RAND_MAX) * 1e3;
        num2 = -((long double)rand() / RAND_MAX) * 1e3;
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

START_TEST(s21_sprintf_spec_g_flag_plus) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, -1.23456, 0.0, 1.23456e10, -1.23456e10};
  long double numbers2[] = {1.23456L, -1.23456L, 0.0L, 1.23456e10L,
                            -1.23456e10L};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%+g %+Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%+g %+Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_flag_space) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, -1.23456, 0.0, 1.23456e10, -1.23456e10};
  long double numbers2[] = {1.23456L, -1.23456L, 0.0L, 1.23456e10L,
                            -1.23456e10L};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "% g % Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "% g % Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_flag_minus) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%-15g %-15Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%-15g %-15Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_flag_zero) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, -1.23456, 1.23456e10, -1.23456e10};
  long double numbers2[] = {1.23456L, -1.23456L, 1.23456e10L, -1.23456e10L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%015g %015Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%015g %015Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_width_larger) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%20g %20Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%20g %20Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_width_asterisk) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%*g %*Lg", 15, numbers1[i], 15, numbers2[i]);
    int read2 = sprintf(str2, "%*g %*Lg", 15, numbers1[i], 15, numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_flag_plus_space) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%+ g %+ Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%+g %+Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_flag_minus_zero) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%-015g %-015Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%-15g %-15Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_all_flags_combo) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23000, 1.23000e10};  // Для проверки флага #
  long double numbers2[] = {1.23000L, 1.23000e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 =
        s21_sprintf(str1, "%+#015.3g %+#015.3Lg", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%+#015.3g %+#015.3Lg", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_width_precision_combo) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456789, 1.23456789e10};
  long double numbers2[] = {1.23456789L, 1.23456789e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%*.*g %*.*Lg", 15, 4, numbers1[i], 15, 4,
                            numbers2[i]);
    int read2 =
        sprintf(str2, "%*.*g %*.*Lg", 15, 4, numbers1[i], 15, 4, numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_case_comparison) {
  char str1[256];
  char str2[256];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %G %Lg %LG", numbers1[i], numbers1[i],
                            numbers2[i], numbers2[i]);
    int read2 = sprintf(str2, "%g %G %Lg %LG", numbers1[i], numbers1[i],
                        numbers2[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_mixed_case) {
  char str1[256];
  char str2[256];
  double numbers1[] = {1.23, -4.56e-10, 0.0, 9.87e20, 123.000};
  long double numbers2[] = {1.23L, -4.56e-10L, 0.0L, 9.87e20L, 123.000L};
  int count = 5;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %G %Lg %LG", numbers1[i], numbers1[i],
                            numbers2[i], numbers2[i]);
    int read2 = sprintf(str2, "%g %G %Lg %LG", numbers1[i], numbers1[i],
                        numbers2[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_negative_infinity) {
  char str1[512];
  char str2[512];
  double inf1 = -INFINITY;
  long double inf2 = -INFINITY;
  int read1 = s21_sprintf(
      str1, "%g %+g % g %05g %.0g %.10g %Lg %+Lg % Lg %05Lg %.0Lg %.10Lg", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  int read2 = sprintf(
      str2, "%g %+g % g %05g %.0g %.10g %Lg %+Lg % Lg %05Lg %.0Lg %.10Lg", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_g_positive_infinity) {
  char str1[512];
  char str2[512];
  double inf1 = INFINITY;
  long double inf2 = INFINITY;
  int read1 = s21_sprintf(
      str1, "%g %+g % g %05g %.0g %.10g %Lg %+Lg % Lg %05Lg %.0Lg %.10Lg", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  int read2 = sprintf(
      str2, "%g %+g % g %05g %.0g %.10g %Lg %+Lg % Lg %05Lg %.0Lg %.10Lg", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_g_nan) {
  char str1[512];
  char str2[512];
  double nan1 = NAN;
  long double nan2 = NAN;
  int read1 = s21_sprintf(
      str1, "%g %+g % g %05g %.0g %.10g %Lg %+Lg % Lg %05Lg %.0Lg %.10Lg", nan1,
      nan1, nan1, nan1, nan1, nan1, nan2, nan2, nan2, nan2, nan2, nan2);
  int read2 = sprintf(
      str2, "%g %+g % g %05g %.0g %.10g %Lg %+Lg % Lg %05Lg %.0Lg %.10Lg", nan1,
      nan1, nan1, nan1, nan1, nan1, nan2, nan2, nan2, nan2, nan2, nan2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_g_infinity_case) {
  char str1[256];
  char str2[256];
  double inf1 = INFINITY;
  double ninf1 = -INFINITY;
  long double inf2 = INFINITY;
  long double ninf2 = -INFINITY;

  int read1 = s21_sprintf(str1, "%g %G %Lg %LG", inf1, ninf1, inf2, ninf2);
  int read2 = sprintf(str2, "%g %G %Lg %LG", inf1, ninf1, inf2, ninf2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_g_nan_case) {
  char str1[256];
  char str2[256];
  double nan1 = NAN;
  long double nan2 = NAN;

  int read1 = s21_sprintf(str1, "%g %G %Lg %LG", nan1, nan1, nan2, nan2);
  int read2 = sprintf(str2, "%g %G %Lg %LG", nan1, nan1, nan2, nan2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_g_boundary_values_1) {
  char str1[512];
  char str2[512];
  double values1[] = {DBL_MIN, DBL_MAX, -DBL_MIN, -DBL_MAX};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g", values1[i]);
    int read2 = sprintf(str2, "%g", values1[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_boundary_values_2_1) {
  char str1[512];
  char str2[512];
  long double values2 = LDBL_MIN;
  int read1 = s21_sprintf(str1, "%Lg", values2);
  int read2 = sprintf(str2, "%Lg", values2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

// START_TEST(s21_sprintf_spec_g_boundary_values_2_2) {
//   char str1[512];
//   char str2[512];
//   long double values2 = LDBL_MAX;
//   int read1 = s21_sprintf(str1, "%Lg", values2);
//   int read2 = sprintf(str2, "%Lg", values2);
//   ck_assert_int_eq(s21_strcmp(str1, str2), 0);
//   ck_assert_int_eq(read1, read2);
// }
// END_TEST

START_TEST(s21_sprintf_spec_g_boundary_values_2_3) {
  char str1[512];
  char str2[512];
  long double values2 = -LDBL_MIN;
  int read1 = s21_sprintf(str1, "%Lg", values2);
  int read2 = sprintf(str2, "%Lg", values2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

// START_TEST(s21_sprintf_spec_g_boundary_values_2_4) {
//   char str1[512];
//   char str2[512];
//   long double values2 = -LDBL_MAX;
//   int read1 = s21_sprintf(str1, "%Lg", values2);
//   int read2 = sprintf(str2, "%Lg", values2);
//   ck_assert_int_eq(s21_strcmp(str1, str2), 0);
//   ck_assert_int_eq(read1, read2);
// }
// END_TEST

START_TEST(s21_sprintf_spec_g_very_large) {
  char str1[128];
  char str2[128];
  double values1[] = {1e+50, -1e+50, 1e+100, -1e+100, 1e+200, -1e+200};
  long double values2[] = {1e+50L,   -1e+50L, 1e+100L,
                           -1e+100L, 1e+200L, -1e+200L};
  int count = 6;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", values1[i], values2[i]);
    int read2 = sprintf(str2, "%g %Lg", values1[i], values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_very_small) {
  char str1[128];
  char str2[128];
  double values1[] = {1e-50, -1e-50, 1e-100, -1e-100, 1e-200, -1e-200};
  long double values2[] = {1e-50L,   -1e-50L, 1e-100L,
                           -1e-100L, 1e-200L, -1e-200L};
  int count = 6;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", values1[i], values2[i]);
    int read2 = sprintf(str2, "%g %Lg", values1[i], values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_near_zero) {
  char str1[128];
  char str2[128];
  double values1[] = {1e-300, -1e-300, 1e-307, -1e-307};
  long double values2[] = {1e-300L, -1e-300L, 1e-307L, -1e-307L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", values1[i], values2[i]);
    int read2 = sprintf(str2, "%g %Lg", values1[i], values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_format_selection) {
  char str1[256];
  char str2[256];

  /* %f */
  double decimal_numbers1[] = {1.23, 12.34, 123.4, 0.123, 0.0123};
  long double decimal_numbers2[] = {1.23L, 12.34L, 123.4L, 0.123L, 0.0123L};
  /* %e */
  double exp_numbers1[] = {0.000012, 1234567, 1.23e-10, 1.23e15};
  long double exp_numbers2[] = {0.000012L, 1234567L, 1.23e-10L, 1.23e15L};

  for (int i = 0; i < 5; i++) {
    int read1 =
        s21_sprintf(str1, "%g %Lg", decimal_numbers1[i], decimal_numbers2[i]);
    int read2 =
        sprintf(str2, "%g %Lg", decimal_numbers1[i], decimal_numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }

  for (int i = 0; i < 4; i++) {
    int read1 = s21_sprintf(str1, "%g %Lg", exp_numbers1[i], exp_numbers2[i]);
    int read2 = sprintf(str2, "%g %Lg", exp_numbers1[i], exp_numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_negative_precision) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 =
        s21_sprintf(str1, "%.*g %.*Lg", -5, numbers1[i], -5, numbers2[i]);
    int read2 = sprintf(str2, "%.*g %.*Lg", -5, numbers1[i], -5, numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_g_negative_width) {
  char str1[128];
  char str2[128];
  double numbers1[] = {1.23456, 1.23456e10};
  long double numbers2[] = {1.23456L, 1.23456e10L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 =
        s21_sprintf(str1, "%*g %*Lg", -20, numbers1[i], -20, numbers2[i]);
    int read2 = sprintf(str2, "%*g %*Lg", -20, numbers1[i], -20, numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

TCase *case_s21_sprintf_g(void) {
  TCase *tc_g = tcase_create("s21_sprintf_g");
  // tcase_set_timeout(tc_g, 30);

  tcase_add_test(tc_g, s21_sprintf_spec_g_basic_decimal);
  tcase_add_test(tc_g, s21_sprintf_spec_g_basic_exponential);
  tcase_add_test(tc_g, s21_sprintf_spec_g_zero);
  tcase_add_test(tc_g, s21_sprintf_spec_g_uppercase);
  tcase_add_test(tc_g, s21_sprintf_spec_g_boundary_transitions);
  tcase_add_test(tc_g, s21_sprintf_spec_g_precision_boundaries);
  tcase_add_test(tc_g, s21_sprintf_spec_g_powers_of_ten_boundaries);
  tcase_add_test(tc_g, s21_sprintf_spec_g_trailing_zeros);
  tcase_add_test(tc_g, s21_sprintf_spec_g_flag_hash);
  tcase_add_test(tc_g, s21_sprintf_spec_g_integer_like);
  tcase_add_test(tc_g, s21_sprintf_spec_g_precision_default);
  tcase_add_test(tc_g, s21_sprintf_spec_g_precision_zero);
  tcase_add_test(tc_g, s21_sprintf_spec_g_precision_various);
  tcase_add_test(tc_g, s21_sprintf_spec_g_precision_asterisk);
  tcase_add_test(tc_g, s21_sprintf_spec_g_mass_test_1);
  tcase_add_test(tc_g, s21_sprintf_spec_g_mass_test_2);
  tcase_add_test(tc_g, s21_sprintf_spec_g_flag_plus);
  tcase_add_test(tc_g, s21_sprintf_spec_g_flag_space);
  tcase_add_test(tc_g, s21_sprintf_spec_g_flag_minus);
  tcase_add_test(tc_g, s21_sprintf_spec_g_flag_zero);
  tcase_add_test(tc_g, s21_sprintf_spec_g_width_larger);
  tcase_add_test(tc_g, s21_sprintf_spec_g_width_asterisk);
  tcase_add_test(tc_g, s21_sprintf_spec_g_flag_plus_space);
  tcase_add_test(tc_g, s21_sprintf_spec_g_flag_minus_zero);
  tcase_add_test(tc_g, s21_sprintf_spec_g_all_flags_combo);
  tcase_add_test(tc_g, s21_sprintf_spec_g_width_precision_combo);
  tcase_add_test(tc_g, s21_sprintf_spec_g_case_comparison);
  tcase_add_test(tc_g, s21_sprintf_spec_g_mixed_case);
  tcase_add_test(tc_g, s21_sprintf_spec_g_negative_infinity);
  tcase_add_test(tc_g, s21_sprintf_spec_g_positive_infinity);
  tcase_add_test(tc_g, s21_sprintf_spec_g_nan);
  tcase_add_test(tc_g, s21_sprintf_spec_g_infinity_case);
  tcase_add_test(tc_g, s21_sprintf_spec_g_nan_case);
  tcase_add_test(tc_g, s21_sprintf_spec_g_boundary_values_1);
  tcase_add_test(tc_g, s21_sprintf_spec_g_boundary_values_2_1);
  // tcase_add_test(tc_g, s21_sprintf_spec_g_boundary_values_2_2);
  tcase_add_test(tc_g, s21_sprintf_spec_g_boundary_values_2_3);
  // tcase_add_test(tc_g, s21_sprintf_spec_g_boundary_values_2_4);
  tcase_add_test(tc_g, s21_sprintf_spec_g_very_large);
  tcase_add_test(tc_g, s21_sprintf_spec_g_very_small);
  tcase_add_test(tc_g, s21_sprintf_spec_g_near_zero);
  tcase_add_test(tc_g, s21_sprintf_spec_g_format_selection);
  tcase_add_test(tc_g, s21_sprintf_spec_g_negative_precision);
  tcase_add_test(tc_g, s21_sprintf_spec_g_negative_width);

  return tc_g;
}
