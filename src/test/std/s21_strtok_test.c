#include "../include/s21_std_test.h"

START_TEST(s21_strtok_all_delims) {
  char str1[] = "1234567890";
  char str2[] = "1234567890";
  const char *delim = "1234567890";

  ck_assert_ptr_eq(s21_strtok(str1, delim), strtok(str2, delim));
  ck_assert_int_eq(*str1, *str2);

  for (s21_size_t i = 1; i <= 3; ++i) {
    ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
    ck_assert_ptr_eq(strtok(s21_NULL, delim), s21_NULL);
  }

  ck_assert_ptr_eq(s21_strtok(str1, "abcdef"), str1);
  ck_assert_ptr_eq(s21_strtok(s21_NULL, "abcdef"), s21_NULL);
  ck_assert_ptr_eq(strtok(str2, "abcdef"), str2);
  ck_assert_ptr_eq(strtok(s21_NULL, "abcdef"), s21_NULL);
}
END_TEST

START_TEST(s21_strtok_no_delims) {
  char str1[] = "abcdefghijklmn";
  char str2[] = "abcdefghijklmn";
  const char *delim = "1234567890";

  ck_assert_ptr_eq(s21_strtok(str1, delim), str1);
  ck_assert_ptr_eq(strtok(str2, delim), str2);

  for (s21_size_t i = 1; i <= 3; ++i) {
    ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
    ck_assert_ptr_eq(strtok(s21_NULL, delim), s21_NULL);
  }
}
END_TEST

START_TEST(s21_strtok_3_tokens) {
  char str1[] = "abc@de!f";
  char str2[] = "abc@de!f";
  const char *delim = "!@";

  ck_assert_ptr_eq(s21_strtok(str1, delim), str1);
  ck_assert_int_eq(*(str1 + 3), '\0');
  ck_assert_ptr_eq(strtok(str2, delim), str2);
  ck_assert_int_eq(*(str2 + 3), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), str1 + 4);
  ck_assert_int_eq(*(str1 + 6), '\0');
  ck_assert_ptr_eq(strtok(s21_NULL, delim), str2 + 4);
  ck_assert_int_eq(*(str2 + 6), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), str1 + 7);
  ck_assert_ptr_eq(strtok(s21_NULL, delim), str2 + 7);

  for (s21_size_t i = 1; i <= 3; ++i) {
    ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
    ck_assert_ptr_eq(strtok(s21_NULL, delim), s21_NULL);
  }
}
END_TEST

START_TEST(s21_strtok_del_first_end) {
  char str1[] = "$abcdef@";
  char str2[] = "$abcdef@";
  const char *delim = "$@";

  ck_assert_ptr_eq(s21_strtok(str1, delim), str1 + 1);
  ck_assert_int_eq(*(str1 + 0), '$');
  ck_assert_ptr_eq(strtok(str2, delim), str2 + 1);
  ck_assert_int_eq(*(str2 + 0), '$');

  ck_assert_int_eq(*(str1 + 7), '\0');
  ck_assert_int_eq(*(str2 + 7), '\0');

  for (s21_size_t i = 1; i <= 3; ++i) {
    ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
    ck_assert_ptr_eq(strtok(s21_NULL, delim), s21_NULL);
  }
}
END_TEST

START_TEST(s21_strtok_del_twice_and_more) {
  const char *delim = "!@#$^*-";

  char str1[] = "@#abc$$$de!@#*f-ghijklmn!@#$^*-";

  ck_assert_ptr_eq(s21_strtok(str1, delim), str1 + 2);
  ck_assert_int_eq(*str1, '@');
  ck_assert_int_eq(*(str1 + 1), '#');
  ck_assert_int_eq(*(str1 + 5), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), str1 + 8);
  ck_assert_int_eq(*(str1 + 6), '$');
  ck_assert_int_eq(*(str1 + 7), '$');
  ck_assert_int_eq(*(str1 + 10), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), str1 + 14);
  ck_assert_int_eq(*(str1 + 11), '@');
  ck_assert_int_eq(*(str1 + 12), '#');
  ck_assert_int_eq(*(str1 + 13), '*');
  ck_assert_int_eq(*(str1 + 15), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), str1 + 16);
  ck_assert_int_eq(*(str1 + 24), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
  ck_assert_int_eq(*(str1 + 25), '@');
  ck_assert_int_eq(*(str1 + 26), '#');
  ck_assert_int_eq(*(str1 + 27), '$');
  ck_assert_int_eq(*(str1 + 28), '^');
  ck_assert_int_eq(*(str1 + 29), '*');
  ck_assert_int_eq(*(str1 + 30), '-');

  for (s21_size_t i = 30; i <= 32; ++i) {
    ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
  }

  char str2[] = "@#abc$$$de!@#*f-ghijklmn!@#$^*-";

  ck_assert_ptr_eq(strtok(str2, delim), str2 + 2);
  ck_assert_int_eq(*str2, '@');
  ck_assert_int_eq(*(str2 + 1), '#');
  ck_assert_int_eq(*(str2 + 5), '\0');

  ck_assert_ptr_eq(strtok(s21_NULL, delim), str2 + 8);
  ck_assert_int_eq(*(str2 + 6), '$');
  ck_assert_int_eq(*(str2 + 7), '$');
  ck_assert_int_eq(*(str2 + 10), '\0');

  ck_assert_ptr_eq(strtok(s21_NULL, delim), str2 + 14);
  ck_assert_int_eq(*(str2 + 11), '@');
  ck_assert_int_eq(*(str2 + 12), '#');
  ck_assert_int_eq(*(str2 + 13), '*');
  ck_assert_int_eq(*(str2 + 15), '\0');

  ck_assert_ptr_eq(strtok(s21_NULL, delim), str2 + 16);
  ck_assert_int_eq(*(str2 + 24), '\0');

  ck_assert_ptr_eq(strtok(s21_NULL, delim), s21_NULL);
  ck_assert_int_eq(*(str2 + 25), '@');
  ck_assert_int_eq(*(str2 + 26), '#');
  ck_assert_int_eq(*(str2 + 27), '$');
  ck_assert_int_eq(*(str2 + 28), '^');
  ck_assert_int_eq(*(str2 + 29), '*');
  ck_assert_int_eq(*(str2 + 30), '-');

  for (size_t i = 30; i <= 32; ++i) {
    ck_assert_ptr_eq(strtok(s21_NULL, delim), s21_NULL);
  }
}
END_TEST

START_TEST(s21_strtok_use_twice) {
  const char *delim = "!@#$^*-";

  char str1[] = "@#abc$$$de!@#*f-ghijklmn!@#$^*-";

  ck_assert_ptr_eq(s21_strtok(str1, delim), str1 + 2);
  ck_assert_int_eq(*str1, '@');
  ck_assert_int_eq(*(str1 + 1), '#');
  ck_assert_int_eq(*(str1 + 5), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), str1 + 8);
  ck_assert_int_eq(*(str1 + 6), '$');
  ck_assert_int_eq(*(str1 + 7), '$');
  ck_assert_int_eq(*(str1 + 10), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), str1 + 14);
  ck_assert_int_eq(*(str1 + 11), '@');
  ck_assert_int_eq(*(str1 + 12), '#');
  ck_assert_int_eq(*(str1 + 13), '*');
  ck_assert_int_eq(*(str1 + 15), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), str1 + 16);
  ck_assert_int_eq(*(str1 + 24), '\0');

  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
  ck_assert_int_eq(*(str1 + 25), '@');
  ck_assert_int_eq(*(str1 + 26), '#');
  ck_assert_int_eq(*(str1 + 27), '$');
  ck_assert_int_eq(*(str1 + 28), '^');
  ck_assert_int_eq(*(str1 + 29), '*');
  ck_assert_int_eq(*(str1 + 30), '-');

  for (s21_size_t i = 30; i <= 32; ++i) {
    ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
  }

  char str11[] = "$abcdef@";

  ck_assert_ptr_eq(s21_strtok(str11, delim), str11 + 1);
  ck_assert_int_eq(*(str11 + 0), '$');
  ck_assert_int_eq(*(str11 + 7), '\0');

  for (s21_size_t i = 1; i <= 3; ++i) {
    ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
  }

  char str2[] = "@#abc$$$de!@#*f-ghijklmn!@#$^*-";

  ck_assert_ptr_eq(strtok(str2, delim), str2 + 2);
  ck_assert_int_eq(*str2, '@');
  ck_assert_int_eq(*(str2 + 1), '#');
  ck_assert_int_eq(*(str2 + 5), '\0');

  ck_assert_ptr_eq(strtok(s21_NULL, delim), str2 + 8);
  ck_assert_int_eq(*(str2 + 6), '$');
  ck_assert_int_eq(*(str2 + 7), '$');
  ck_assert_int_eq(*(str2 + 10), '\0');

  ck_assert_ptr_eq(strtok(s21_NULL, delim), str2 + 14);
  ck_assert_int_eq(*(str2 + 11), '@');
  ck_assert_int_eq(*(str2 + 12), '#');
  ck_assert_int_eq(*(str2 + 13), '*');
  ck_assert_int_eq(*(str2 + 15), '\0');

  ck_assert_ptr_eq(strtok(s21_NULL, delim), str2 + 16);
  ck_assert_int_eq(*(str2 + 24), '\0');

  ck_assert_ptr_eq(strtok(s21_NULL, delim), s21_NULL);
  ck_assert_int_eq(*(str2 + 25), '@');
  ck_assert_int_eq(*(str2 + 26), '#');
  ck_assert_int_eq(*(str2 + 27), '$');
  ck_assert_int_eq(*(str2 + 28), '^');
  ck_assert_int_eq(*(str2 + 29), '*');
  ck_assert_int_eq(*(str2 + 30), '-');

  for (size_t i = 30; i <= 32; ++i) {
    ck_assert_ptr_eq(strtok(s21_NULL, delim), s21_NULL);
  }

  char str22[] = "$abcdef@";

  ck_assert_ptr_eq(strtok(str22, delim), str22 + 1);
  ck_assert_int_eq(*(str22 + 0), '$');
  ck_assert_int_eq(*(str22 + 7), '\0');

  for (s21_size_t i = 1; i <= 3; ++i) {
    ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), s21_NULL);
  }
}
END_TEST

Suite *suite_s21_strtok_test(void) {
  Suite *s = suite_create("s21_strtok_test");
  TCase *tc = tcase_create("s21_strtok_test");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_strtok_all_delims);
  tcase_add_test(tc, s21_strtok_no_delims);
  tcase_add_test(tc, s21_strtok_3_tokens);
  tcase_add_test(tc, s21_strtok_del_first_end);
  tcase_add_test(tc, s21_strtok_del_twice_and_more);
  tcase_add_test(tc, s21_strtok_use_twice);

  return s;
}
