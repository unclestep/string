#include "s21_sprintf_test.h"

START_TEST(s21_sprintf_spec_f_basic_positive) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%f %Lf", num1, num2);
  int read2 = sprintf(str2, "%f %Lf", num1, num2);
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
      "% .4f % .4Lf", "%#.0f %#.0Lf", "%015.3f %015.3Lf", "%-20.5f % -20.5Lf"};
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
  double num1 = 123.123456789;
  long double num2 = 123.123456789L;
  int read1 = s21_sprintf(str1, "%f %Lf", num1, num2);
  int read2 = sprintf(str2, "%f %Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_zero) {
  char str1[128];
  char str2[128];
  double num1 = 123.789;
  long double num2 = 123.789L;
  int read1 = s21_sprintf(str1, "%.0f %.0Lf", num1, num2);
  int read2 = sprintf(str2, "%.0f %.0Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_various) {
  char str1[128];
  char str2[128];
  double num1 = 123.123456789;
  long double num2 = 123.123456789L;

  for (int precision = 1; precision <= 10; precision++) {
    char format[32];
    sprintf(format, "%%.%df %%.%dLf", precision, precision);

    int read1 = s21_sprintf(str1, format, num1, num2);
    int read2 = sprintf(str2, format, num1, num2);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_asterisk) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%.*f %.*Lf", 3, num1, 3, num2);
  int read2 = sprintf(str2, "%.*f %.*Lf", 3, num1, 3, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_precision_high) {
  char str1[256];
  char str2[256];
  double num1 = 123.123456789;
  long double num2 = 123.123456789L;
  int read1 = s21_sprintf(str1, "%.15f %.15Lf", num1, num2);
  int read2 = sprintf(str2, "%.15f %.15Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_rounding_up) {
  char str1[128];
  char str2[128];
  double numbers1[] = {123.456789, 0.9999995, -123.456789, -0.9999995};
  long double numbers2[] = {123.456789L, 0.9999995L, -123.456789L, -0.9999995L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.5f %.5Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%.5f %.5Lf", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_rounding_down) {
  char str1[128];
  char str2[128];
  double numbers1[] = {123.123123, 0.1234564, -123.123123, -0.1234564};
  long double numbers2[] = {123.123123L, 0.1234564L, -123.123123L, -0.1234564L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.5f %.5Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%.5f %.5Lf", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_rounding_edge_cases) {
  char str1[128];
  char str2[128];
  double numbers1[] = {0.5, 1.5, 2.5, 3.5, -0.5, -1.5, -2.5, -3.5};
  long double numbers2[] = {0.5L, 1.5L, 2.5L, 3.5L, -0.5L, -1.5L, -2.5L, -3.5L};
  int count = 8;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%.0f %.0Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%.0f %.0Lf", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_plus) {
  char str1[128];
  char str2[128];
  double numbers1[] = {123.456, -123.456, 0.0};
  long double numbers2[] = {123.456L, -123.456L, 0.0L};
  int count = 3;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%+f %+Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%+f %+Lf", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_space) {
  char str1[128];
  char str2[128];
  double numbers1[] = {123.456, -123.456, 0.0};
  long double numbers2[] = {123.456L, -123.456L, 0.0L};
  int count = 3;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "% f % Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "% f % Lf", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_minus) {
  char str1[128];
  char str2[128];
  double num1 = 123.456;
  long double num2 = 123.456L;
  int read1 = s21_sprintf(str1, "%-15f %-15Lf", num1, num2);
  int read2 = sprintf(str2, "%-15f %-15Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_zero) {
  char str1[128];
  char str2[128];
  double numbers1[] = {123.456, -123.456};
  long double numbers2[] = {123.456L, -123.456L};
  int count = 2;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%015f %015Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%015f %015Lf", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_hash) {
  char str1[128];
  char str2[128];
  double numbers1[] = {123.0,      -123.0,  0.0,     1234.5678,
                       -1234.5678, 100.000, -100.000};
  long double numbers2[] = {123.0L,      -123.0L,  0.0L,     1234.5678L,
                            -1234.5678L, 100.000L, -100.000L};
  int count = 7;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%#.0f %#.0Lf", numbers1[i], numbers2[i]);
    int read2 = sprintf(str2, "%#.0f %#.0Lf", numbers1[i], numbers2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_width_larger) {
  char str1[128];
  char str2[128];
  double num1 = 123.456;
  long double num2 = 123.456L;
  int read1 = s21_sprintf(str1, "%20f %20Lf", num1, num2);
  int read2 = sprintf(str2, "%20f %20Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_width_smaller) {
  char str1[128];
  char str2[128];
  double num1 = 123.456;
  long double num2 = 123.456L;
  int read1 = s21_sprintf(str1, "%5f %5Lf", num1, num2);
  int read2 = sprintf(str2, "%5f %5Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_width_asterisk) {
  char str1[128];
  char str2[128];
  double num1 = 123.456;
  long double num2 = 123.456L;
  int read1 = s21_sprintf(str1, "%*f %*Lf", 15, num1, 15, num2);
  int read2 = sprintf(str2, "%*f %*Lf", 15, num1, 15, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_plus_space) {
  char str1[128];
  char str2[128];
  double num1 = 123.456;
  long double num2 = 123.456L;
  int read1 = s21_sprintf(str1, "%+ f %+ Lf", num1, num2);
  int read2 = sprintf(str2, "%+f %+Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_flag_minus_zero) {
  char str1[128];
  char str2[128];
  double num1 = 123.456;
  long double num2 = 123.456L;
  int read1 = s21_sprintf(str1, "%-015f %-015Lf", num1, num2);
  int read2 = sprintf(str2, "%-15f %-15Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_all_flags_combo) {
  char str1[128];
  char str2[128];
  double num1 = 123.0;
  long double num2 = 123.0L;
  int read1 = s21_sprintf(str1, "%+#020.3f %+#020.3Lf", num1, num2);
  int read2 = sprintf(str2, "%+#020.3f %+#020.3Lf", num1, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_width_precision_combo) {
  char str1[128];
  char str2[128];
  double num1 = 123.456789;
  long double num2 = 123.456789L;
  int read1 = s21_sprintf(str1, "%*.*f %*.*Lf", 15, 3, num1, 15, 3, num2);
  int read2 = sprintf(str2, "%*.*f %*.*Lf", 15, 3, num1, 15, 3, num2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_negative_infinity) {
  char str1[512];
  char str2[512];
  double inf1 = -INFINITY;
  long double inf2 = -INFINITY;
  int read1 = s21_sprintf(
      str1, "%f %+f % f %05f %.0f %.10f %Lf %+Lf % Lf %05Lf %.0Lf %.10Lf", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  int read2 = sprintf(
      str2, "%f %+f % f %05f %.0f %.10f %Lf %+Lf % Lf %05Lf %.0Lf %.10Lf", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_positive_infinity) {
  char str1[512];
  char str2[512];
  double inf1 = INFINITY;
  long double inf2 = INFINITY;
  int read1 = s21_sprintf(
      str1, "%f %+f % f %05f %.0f %.10f %Lf %+Lf % Lf %05Lf %.0Lf %.10Lf", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  int read2 = sprintf(
      str2, "%f %+f % f %05f %.0f %.10f %Lf %+Lf % Lf %05Lf %.0Lf %.10Lf", inf1,
      inf1, inf1, inf1, inf1, inf1, inf2, inf2, inf2, inf2, inf2, inf2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_nan) {
  char str1[512];
  char str2[512];
  double nan1 = NAN;
  long double nan2 = NAN;
  int read1 = s21_sprintf(
      str1, "%f %+f % f %05f %.0f %.10f %Lf %+Lf % Lf %05Lf %.0Lf %.10Lf", nan1,
      nan1, nan1, nan1, nan1, nan1, nan2, nan2, nan2, nan2, nan2, nan2);
  int read2 = sprintf(
      str2, "%f %+f % f %05f %.0f %.10f %Lf %+Lf % Lf %05Lf %.0Lf %.10Lf", nan1,
      nan1, nan1, nan1, nan1, nan1, nan2, nan2, nan2, nan2, nan2, nan2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_boundary_values_1) {
  char str1[512];
  char str2[512];
  double values1[] = {DBL_MIN, DBL_MAX, -DBL_MIN, -DBL_MAX};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%f", values1[i]);
    int read2 = sprintf(str2, "%f", values1[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_boundary_values_2_1) {
  char str1[512];
  char str2[512];
  long double values2 = LDBL_MIN;
  int read1 = s21_sprintf(str1, "%Lf", values2);
  int read2 = sprintf(str2, "%Lf", values2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

// START_TEST(s21_sprintf_spec_f_boundary_values_2_2) {
//   char str1[512];
//   char str2[512];
//   long double values2 = LDBL_MAX;
//   int read1 = s21_sprintf(str1, "%Lf", values2);
//   int read2 = sprintf(str2, "%Lf", values2);
//   ck_assert_int_eq(s21_strcmp(str1, str2), 0);
//   ck_assert_int_eq(read1, read2);
// }
// END_TEST

START_TEST(s21_sprintf_spec_f_boundary_values_2_3) {
  char str1[512];
  char str2[512];
  long double values2 = -LDBL_MIN;
  int read1 = s21_sprintf(str1, "%Lf", values2);
  int read2 = sprintf(str2, "%Lf", values2);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

// START_TEST(s21_sprintf_spec_f_boundary_values_2_4) {
//   char str1[512];
//   char str2[512];
//   long double values2 = -LDBL_MAX;
//   int read1 = s21_sprintf(str1, "%Lf", values2);
//   int read2 = sprintf(str2, "%Lf", values2);
//   ck_assert_int_eq(s21_strcmp(str1, str2), 0);
//   ck_assert_int_eq(read1, read2);
// }
// END_TEST

START_TEST(s21_sprintf_spec_f_very_large_1) {
  char str1[128];
  char str2[128];
  double values1[] = {1e+50, -1e+50, 1e+100, -1e+100};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%f", values1[i]);
    int read2 = sprintf(str2, "%f", values1[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_very_large_2) {
  char str1[128];
  char str2[128];
  long double values2[] = {1e+50L, -1e+50L, 1e+100L, -1e+100L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%Lf", values2[i]);
    int read2 = sprintf(str2, "%Lf", values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_near_zero) {
  char str1[128];
  char str2[128];
  double values1[] = {1e-50, -1e-50, 1e-100, -1e-100};
  long double values2[] = {1e-50L, -1e-50L, 1e-100L, -1e-100L};
  int count = 4;

  for (int i = 0; i < count; i++) {
    int read1 = s21_sprintf(str1, "%f %Lf", values1[i], values2[i]);
    int read2 = sprintf(str2, "%f %Lf", values1[i], values2[i]);
    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}
END_TEST

START_TEST(s21_sprintf_spec_f_negative_precision) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%.*f %.*Lf", -5, 123.456, -5, 123.456L);
  int read2 = sprintf(str2, "%.*f %.*Lf", -5, 123.456, -5, 123.456L);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_f_negative_width) {
  char str1[128];
  char str2[128];
  int read1 = s21_sprintf(str1, "%*f %*Lf", -15, 123.456, -15, 123.456L);
  int read2 = sprintf(str2, "%*f %*Lf", -15, 123.456, -15, 123.456L);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

TCase *case_s21_sprintf_f(void) {
  TCase *tc_f = tcase_create("s21_sprintf_f");
  // tcase_set_timeout(tc_f, 30);

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
  tcase_add_test(tc_f, s21_sprintf_spec_f_boundary_values_1);
  tcase_add_test(tc_f, s21_sprintf_spec_f_boundary_values_2_1);
  // tcase_add_test(tc_f, s21_sprintf_spec_f_boundary_values_2_2);
  tcase_add_test(tc_f, s21_sprintf_spec_f_boundary_values_2_3);
  // tcase_add_test(tc_f, s21_sprintf_spec_f_boundary_values_2_4);
  tcase_add_test(tc_f, s21_sprintf_spec_f_very_large_1);
  tcase_add_test(tc_f, s21_sprintf_spec_f_very_large_2);
  tcase_add_test(tc_f, s21_sprintf_spec_f_near_zero);
  tcase_add_test(tc_f, s21_sprintf_spec_f_negative_precision);
  tcase_add_test(tc_f, s21_sprintf_spec_f_negative_width);

  return tc_f;
}
