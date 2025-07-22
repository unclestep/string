#include <limits.h>
#include <unistd.h>

#include "../s21_test.h"

#define LOCALE "en_US.UTF-8"

START_TEST(s21_sprintf_spec_c_default_char_1) {
  char c = 'a';
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%c", c);
  int read2 = sprintf(str2, "%c", c);

  ck_assert_int_eq(s21_strcmp(str1, "a"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_default_char_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "a %.10c c %.c e %.-c g", 'b', 'd', 'f');
  int read2 = sprintf(str2, "a %c c %c e %c g", 'b', 'd', 'f');

  ck_assert_int_eq(s21_strcmp(str1, "a b c d e f g"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_1) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc", 'z');
  int read2 = sprintf(str2, "%lc", 'z');

  ck_assert_int_eq(s21_strcmp(str1, "z"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_2) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc", L'ß');
  int read2 = sprintf(str2, "%lc", L'ß');

  ck_assert_int_eq(s21_strcmp(str1, "ß"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_3) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc", L'水');
  int read2 = sprintf(str2, "%lc", L'水');

  ck_assert_int_eq(s21_strcmp(str1, "水"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_4) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc", L'🍌');
  int read2 = sprintf(str2, "%lc", L'🍌');

  ck_assert_int_eq(s21_strcmp(str1, "🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_wide_char_all) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lc%lc%lc%lc", 'z', L'ß', L'水', L'🍌');
  int read2 = sprintf(str2, "%lc%lc%lc%lc", 'z', L'ß', L'水', L'🍌');

  ck_assert_int_eq(s21_strcmp(str1, "zß水🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5c", 'a');
  int read2 = sprintf(str2, "%5c", 'a');

  ck_assert_int_eq(s21_strcmp(str1, "    a"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5c", 'a');
  int read2 = sprintf(str2, "%-5c", 'a');

  ck_assert_int_eq(s21_strcmp(str1, "a    "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5c%-5c", 'a', 'b');
  int read2 = sprintf(str2, "%5c%-5c", 'a', 'b');

  ck_assert_int_eq(s21_strcmp(str1, "    ab    "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_4) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5lc%5lc%5lc%5lc", 'z', L'ß', L'水', L'🍌');
  int read2 = sprintf(str2, "%5lc%5lc%5lc%5lc", 'z', L'ß', L'水', L'🍌');

  ck_assert_int_eq(s21_strcmp(str1, "    z   ß  水 🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_flag_and_wid_5) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 =
      s21_sprintf(str1, "%-5lc%-5lc%-5lc%-5lc", 'z', L'ß', L'水', L'🍌');
  int read2 = sprintf(str2, "%-5lc%-5lc%-5lc%-5lc", 'z', L'ß', L'水', L'🍌');

  ck_assert_int_eq(s21_strcmp(str1, "z    ß   水  🍌 "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_memory_alloc_wid_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%256c", 'a');
  int read2 = sprintf(str2, "%256c", 'a');

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_memory_alloc_wid_2) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%-256c", 'a');
  int read2 = sprintf(str2, "%-256c", 'a');

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_must_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05c", '1');
  int read2 = sprintf(str2, "%5c", '1');

  ck_assert_int_eq(s21_strcmp(str1, "    1"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_empty_char) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%cdef", '\0');
  int read2 = sprintf(str2, "abc%cdef", '\0');

  ck_assert_int_eq(s21_strcmp(str1, "abc"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_empty_char_wid) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%3cdef", '\0');
  int read2 = sprintf(str2, "abc%3cdef", '\0');

  ck_assert_int_eq(s21_strcmp(str1, "abc  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_empty_wchar) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%lcdef", L'\0');
  int read2 = sprintf(str2, "abc%lcdef", L'\0');

  ck_assert_int_eq(s21_strcmp(str1, "abc"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_c_empty_wchar_wid) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%3lcdef", L'\0');
  int read2 = sprintf(str2, "abc%3lcdef", L'\0');

  ck_assert_int_eq(s21_strcmp(str1, "abc  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

// /* SPECIFIER S */

START_TEST(s21_sprintf_spec_s_default_one_string) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%s", "abcdef");
  int read2 = sprintf(str2, "%s", "abcdef");

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_default_many_strings) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%s%s %s  %s%s", "ab", "cd", "ef", "\0", "gh");
  int read2 = sprintf(str2, "%s%s %s  %s%s", "ab", "cd", "ef", "\0", "gh");

  ck_assert_int_eq(s21_strcmp(str1, "abcd ef  gh"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_one_string_1) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls", L"abcdef");
  int read2 = sprintf(str2, "%ls", L"abcdef");

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_one_string_2) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls", L"Привет");
  int read2 = sprintf(str2, "%ls", L"Привет");

  ck_assert_int_eq(s21_strcmp(str1, "Привет"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_one_string_3) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls", L"水是生命之源");
  int read2 = sprintf(str2, "%ls", L"水是生命之源");

  ck_assert_int_eq(s21_strcmp(str1, "水是生命之源"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_one_string_4) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls", L"🍌🍇🍆🍑🍒🍓🌽");
  int read2 = sprintf(str2, "%ls", L"🍌🍇🍆🍑🍒🍓🌽");

  ck_assert_int_eq(s21_strcmp(str1, "🍌🍇🍆🍑🍒🍓🌽"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_many_strings) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls%ls%ls%ls%ls", L"🍌🍇🍆🍑🍒🍓🌽", L"Привет",
                          L"水是生命之源", L"", L"abcdef");
  int read2 = sprintf(str2, "%ls%ls%ls%ls%ls", L"🍌🍇🍆🍑🍒🍓🌽", L"Привет",
                      L"水是生命之源", L"", L"abcdef");

  ck_assert_int_eq(s21_strcmp(str1, "🍌🍇🍆🍑🍒🍓🌽Привет水是生命之源abcdef"),
                   0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_default_one_string) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.s", "abcdef");
  int read2 = sprintf(str2, "%.s", "abcdef");

  ck_assert_int_eq(s21_strcmp(str1, "\0"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_default_many_strings_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%s%.s%s", "ab", "cd", "ef");
  int read2 = sprintf(str2, "%s%.s%s", "ab", "cd", "ef");

  ck_assert_int_eq(s21_strcmp(str1, "abef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_default_many_strings_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.1s%.3s%.5s%.7s", "abcdef", "123456",
                          "ghijkl", "000000");
  int read2 =
      sprintf(str2, "%.1s%.3s%.5s%.7s", "abcdef", "123456", "ghijkl", "000000");

  ck_assert_int_eq(s21_strcmp(str1, "a123ghijk000000"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_default_many_strings_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%3.1s%5.3s%7.5s%9.7s", "abcdef", "123456",
                          "ghijkl", "000000");
  int read2 = sprintf(str2, "%3.1s%5.3s%7.5s%9.7s", "abcdef", "123456",
                      "ghijkl", "000000");

  ck_assert_int_eq(s21_strcmp(str1, "  a  123  ghijk   000000"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_wide_one_string) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.ls", L"🍌🍇🍆🍑🍒🍓");
  int read2 = sprintf(str2, "%.ls", L"🍌🍇🍆🍑🍒🍓");

  ck_assert_int_eq(s21_strcmp(str1, "\0"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_wide_many_strings_1) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ls%.ls%ls", L"🍌🍇", L"🍆🍑", L"🍒🍓");
  int read2 = sprintf(str2, "%ls%.ls%ls", L"🍌🍇", L"🍆🍑", L"🍒🍓");

  ck_assert_int_eq(s21_strcmp(str1, "🍌🍇🍒🍓"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_wide_many_strings_2) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.1ls%.3ls%.5ls%.7ls", L"abc", L"Привет",
                          L"水是生命之源", L"🍌🍇🍒🍓");
  int read2 = sprintf(str2, "%.1ls%.3ls%.5ls%.7ls", L"abc", L"Привет",
                      L"水是生命之源", L"🍌🍇🍒🍓");

  ck_assert_int_eq(s21_strcmp(str1, "aП水🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_prec_wide_many_strings_width) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%3.1ls%5.3ls%7.5ls%9.7ls", L"abc", L"Привет",
                          L"水是生命之源", L"🍌🍇🍒🍓");
  int read2 = sprintf(str2, "%3.1ls%5.3ls%7.5ls%9.7ls", L"abc", L"Привет",
                      L"水是生命之源", L"🍌🍇🍒🍓");

  ck_assert_int_eq(s21_strcmp(str1, "  a   П    水     🍌"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_default_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5s", "abc");
  int read2 = sprintf(str2, "%5s", "abc");

  ck_assert_int_eq(s21_strcmp(str1, "  abc"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_default_width_flag) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5s", "abc");
  int read2 = sprintf(str2, "%-5s", "abc");

  ck_assert_int_eq(s21_strcmp(str1, "abc  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_default_width_flag_many) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5s%-5s", "abc", "def");
  int read2 = sprintf(str2, "%5s%-5s", "abc", "def");

  ck_assert_int_eq(s21_strcmp(str1, "  abcdef  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_width_many) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 =
      s21_sprintf(str1, "%7ls%7ls%7ls%7ls", L"az", L"αß", L"水是", L"🍌🌽");
  int read2 = sprintf(str2, "%7ls%7ls%7ls%7ls", L"az", L"αß", L"水是", L"🍌🌽");

  ck_assert_int_eq(s21_strcmp(str1, "     az   αß 水是🍌🌽"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_wide_width_flag_many) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 =
      s21_sprintf(str1, "%-7ls%-7ls%-7ls%-7ls", L"az", L"αß", L"水是", L"🍌🌽");
  int read2 =
      sprintf(str2, "%-7ls%-7ls%-7ls%-7ls", L"az", L"αß", L"水是", L"🍌🌽");

  ck_assert_int_eq(s21_strcmp(str1, "az     αß   水是 🍌🌽"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_realloc_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%256s", "abcdef");
  int read2 = sprintf(str2, "%256s", "abcdef");

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_realloc_2) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%-256s", "abcdef");
  int read2 = sprintf(str2, "%-256s", "abcdef");

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_must_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%07s", "123456");
  int read2 = sprintf(str2, "%7s", "123456");

  ck_assert_int_eq(s21_strcmp(str1, " 123456"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_empty_default) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%sdef", "\0");
  int read2 = sprintf(str2, "abc%sdef", "\0");

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_empty_default_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%3sdef", "\0");
  int read2 = sprintf(str2, "abc%3sdef", "\0");

  ck_assert_int_eq(s21_strcmp(str1, "abc   def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_empty_wide) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%lsdef", L"\0");
  int read2 = sprintf(str2, "abc%lsdef", L"\0");

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

START_TEST(s21_sprintf_spec_s_empty_wide_width) {
  setlocale(LC_ALL, LOCALE);
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%3lsdef", L"\0");
  int read2 = sprintf(str2, "abc%3lsdef", L"\0");

  ck_assert_int_eq(s21_strcmp(str1, "abc   def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}
END_TEST

/* SPECIFIERS DI */

START_TEST(s21_sprintf_spec_di_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-d", 21);
  int read2 = sprintf(str2, "%-d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+d", 21);
  int read2 = sprintf(str2, "%+d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "+21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_flags_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% d", 21);
  int read2 = sprintf(str2, "% d", 21);

  ck_assert_int_eq(s21_strcmp(str1, " 21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_flags_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% +d", 21);
  int read2 = sprintf(str2, "%+d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "+21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_flags_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% +d", -21);
  int read2 = sprintf(str2, "%+d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_width_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5d", 21);
  int read2 = sprintf(str2, "%5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_width_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5d", -21);
  int read2 = sprintf(str2, "%5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "  -21"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05d", 21);
  int read2 = sprintf(str2, "%05d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05d", -21);
  int read2 = sprintf(str2, "%05d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-0021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_width_flags_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5d", 21);
  int read2 = sprintf(str2, "%-5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "21   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_width_flags_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5d", -21);
  int read2 = sprintf(str2, "%-5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-21  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-05d", -21);
  int read2 = sprintf(str2, "%-5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-21  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5d", 21);
  int read2 = sprintf(str2, "%.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5d", -21);
  int read2 = sprintf(str2, "%.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_zero_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%.ddef", 0);
  int read2 = sprintf(str2, "abc%.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_zero_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%5.ddef", 0);
  int read2 = sprintf(str2, "abc%5.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_zero_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5.ddef", 0);
  int read2 = sprintf(str2, "abc%-5.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_zero_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%+.ddef", 0);
  int read2 = sprintf(str2, "abc%+.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc+def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_zero_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc% .ddef", 0);
  int read2 = sprintf(str2, "abc% .ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_zero_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%05.ddef", 0);
  int read2 = sprintf(str2, "abc%5.ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_zero_7) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%+ddef", 0);
  int read2 = sprintf(str2, "abc%+ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc+0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_zero_8) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5ddef", 0);
  int read2 = sprintf(str2, "abc%-5ddef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0    def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_flags) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+.5d", 21);
  int read2 = sprintf(str2, "%+.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "+00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5d", 21);
  int read2 = sprintf(str2, "%8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5d", -21);
  int read2 = sprintf(str2, "%8.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "  -00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5d", 21);
  int read2 = sprintf(str2, "%-8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00021   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5d", -21);
  int read2 = sprintf(str2, "%-8.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "-00021  "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5d", 21);
  int read2 = sprintf(str2, "%8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5d", -21);
  int read2 = sprintf(str2, "%8.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "  -00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "% 8.5d", 21);
  int read2 = sprintf(str2, "% 8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+8.5d", 21);
  int read2 = sprintf(str2, "%+8.5d", 21);

  ck_assert_int_eq(s21_strcmp(str1, "  +00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_unwork_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%+8.5d", -21);
  int read2 = sprintf(str2, "%+8.5d", -21);

  ck_assert_int_eq(s21_strcmp(str1, "  -00021"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_extreme_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%+256.128d", INT_MAX);
  int read2 = sprintf(str2, "%+256.128d", INT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_width_flags_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5d", INT_MIN);
  int read2 = sprintf(str2, "%8.5d", INT_MIN);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_hlen_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hd", SHRT_MAX);
  int read2 = sprintf(str2, "%hd", SHRT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "32767"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_hlen_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hd", UINT_MAX);
  int read2 = sprintf(str2, "%hd", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "-1"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_hlen_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hd", 0x12345678);
  int read2 = sprintf(str2, "%hd", 0x12345678);

  ck_assert_int_eq(s21_strcmp(str1, "22136"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_di_prec_llen) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ld", LONG_MAX);
  int read2 = sprintf(str2, "%ld", LONG_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "9223372036854775807"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

/* SPECIFIER O */

START_TEST(s21_sprintf_spec_o_default) {
  char str1[128];
  char str2[128];

  for (unsigned i = 0; i <= 12345; ++i) {
    int read1 = s21_sprintf(str1, "%o", i);
    int read2 = sprintf(str2, "%o", i);

    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}

START_TEST(s21_sprintf_spec_o_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-o", 21);
  int read2 = sprintf(str2, "%-o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "25"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#o", 21);
  int read2 = sprintf(str2, "%#o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5o", 21);
  int read2 = sprintf(str2, "%5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   25"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05o", 21);
  int read2 = sprintf(str2, "%05o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5o", 21);
  int read2 = sprintf(str2, "%-5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "25   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-05o", 21);
  int read2 = sprintf(str2, "%-5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "25   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5o", 21);
  int read2 = sprintf(str2, "%.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%.odef", 0);
  int read2 = sprintf(str2, "abc%.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%5.odef", 0);
  int read2 = sprintf(str2, "abc%5.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5.odef", 0);
  int read2 = sprintf(str2, "abc%-5.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#.odef", 0);
  int read2 = sprintf(str2, "abc%#.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#5.odef", 0);
  int read2 = sprintf(str2, "abc%#5.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc    0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%0#5.0odef", 0);
  int read2 = sprintf(str2, "abc%#5.odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc    0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_7) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#-5.0odef", 0);
  int read2 = sprintf(str2, "abc%#-5.0odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0    def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_8) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#odef", 0);
  int read2 = sprintf(str2, "abc%#odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_zero_9) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#8.5odef", 0);
  int read2 = sprintf(str2, "abc%#8.5odef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc   00000def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_hash_extreme_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#.3o", 123);
  int read2 = sprintf(str2, "%#.3o", 123);

  ck_assert_int_eq(s21_strcmp(str1, "0173"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_hash_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#o", 1);
  int read2 = sprintf(str2, "%#o", 1);

  ck_assert_int_eq(s21_strcmp(str1, "01"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_hash_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%0#6.5o", 21);
  int read2 = sprintf(str2, "%#6.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, " 00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5o", 21);
  int read2 = sprintf(str2, "%8.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_width_flags) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5o", 21);
  int read2 = sprintf(str2, "%-8.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00025   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5o", 21);
  int read2 = sprintf(str2, "%8.5o", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00025"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%256.128o", UINT_MAX);
  int read2 = sprintf(str2, "%256.128o", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%3.3o", 64);
  int read2 = sprintf(str2, "%3.3o", 64);

  ck_assert_int_eq(s21_strcmp(str1, "100"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5.4o", 64);
  int read2 = sprintf(str2, "%5.4o", 64);

  ck_assert_int_eq(s21_strcmp(str1, " 0100"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5.4o", 64);
  int read2 = sprintf(str2, "%-5.4o", 64);

  ck_assert_int_eq(s21_strcmp(str1, "0100 "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_width_flags_extreme_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05.8o", UINT_MAX);
  int read2 = sprintf(str2, "%5.4o", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "37777777777"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_hlen_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ho", USHRT_MAX);
  int read2 = sprintf(str2, "%ho", USHRT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "177777"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_hlen_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ho", UINT_MAX);
  int read2 = sprintf(str2, "%ho", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "177777"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_hlen_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%ho", 0x12345678);
  int read2 = sprintf(str2, "%ho", 0x12345678);

  ck_assert_int_eq(s21_strcmp(str1, "53170"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_o_prec_llen) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lo", LONG_MAX);
  int read2 = sprintf(str2, "%lo", LONG_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "777777777777777777777"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

/* SPECIFIER xX */

START_TEST(s21_sprintf_spec_xX_default) {
  char str1[128];
  char str2[128];

  for (unsigned i = 0; i <= 12345; ++i) {
    int read1 = s21_sprintf(str1, "%x", i);
    int read2 = sprintf(str2, "%x", i);

    ck_assert_int_eq(s21_strcmp(str1, str2), 0);
    ck_assert_int_eq(read1, read2);
  }
}

START_TEST(s21_sprintf_spec_xX_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-x", 21);
  int read2 = sprintf(str2, "%-x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "15"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#x", 21);
  int read2 = sprintf(str2, "%#x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "0x15"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%5x", 21);
  int read2 = sprintf(str2, "%5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   15"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_width_flags_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%05x", 21);
  int read2 = sprintf(str2, "%05x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_width_flags_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-5x", 21);
  int read2 = sprintf(str2, "%-5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "15   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-05x", 21);
  int read2 = sprintf(str2, "%-5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "15   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%.5x", 21);
  int read2 = sprintf(str2, "%.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%.xdef", 0);
  int read2 = sprintf(str2, "abc%.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%5.xdef", 0);
  int read2 = sprintf(str2, "abc%5.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%-5.xdef", 0);
  int read2 = sprintf(str2, "abc%-5.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#.xdef", 0);
  int read2 = sprintf(str2, "abc%#.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abcdef"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#5.xdef", 0);
  int read2 = sprintf(str2, "abc%#5.xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%0#5.0xdef", 0);
  int read2 = sprintf(str2, "abc%#5.0xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_7) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#-5.0xdef", 0);
  int read2 = sprintf(str2, "abc%#-5.0xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc     def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_8) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#Xdef", 0);
  int read2 = sprintf(str2, "abc%#Xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc0def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_zero_9) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "abc%#8.5Xdef", 0);
  int read2 = sprintf(str2, "abc%#8.5Xdef", 0);

  ck_assert_int_eq(s21_strcmp(str1, "abc   00000def"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_hash_extreme_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#.3x", 123);
  int read2 = sprintf(str2, "%#.3x", 123);

  ck_assert_int_eq(s21_strcmp(str1, "0x07b"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_hash_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-#6.3X", 123);
  int read2 = sprintf(str2, "%-#6.3X", 123);

  ck_assert_int_eq(s21_strcmp(str1, "0X07B "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_hash_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%0#8.5x", 21);
  int read2 = sprintf(str2, "%#8.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, " 0x00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%8.5x", 21);
  int read2 = sprintf(str2, "%8.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width_flags) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-8.5x", 21);
  int read2 = sprintf(str2, "%-8.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "00015   "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width_flags_unwork) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%08.5x", 21);
  int read2 = sprintf(str2, "%8.5x", 21);

  ck_assert_int_eq(s21_strcmp(str1, "   00015"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_1) {
  char str1[512];
  char str2[512];

  int read1 = s21_sprintf(str1, "%156.128x", UINT_MAX);
  int read2 = sprintf(str2, "%156.128x", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%2.2x", 153);
  int read2 = sprintf(str2, "%2.2x", 153);

  ck_assert_int_eq(s21_strcmp(str1, "99"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%4.3x", 153);
  int read2 = sprintf(str2, "%4.3x", 153);

  ck_assert_int_eq(s21_strcmp(str1, " 099"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_4) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%-4.3x", 153);
  int read2 = sprintf(str2, "%-4.3x", 153);

  ck_assert_int_eq(s21_strcmp(str1, "099 "), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_5) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%X", 11259375);
  int read2 = sprintf(str2, "%X", 11259375);

  ck_assert_int_eq(s21_strcmp(str1, "ABCDEF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_width_flags_extreme_6) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%#10.8X", UINT_MAX);
  int read2 = sprintf(str2, "%#10.8X", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "0XFFFFFFFF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_hlen_1) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hX", USHRT_MAX);
  int read2 = sprintf(str2, "%hX", USHRT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "FFFF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_hlen_2) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hX", UINT_MAX);
  int read2 = sprintf(str2, "%hX", UINT_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "FFFF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_hlen_3) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%hx", 0x12345678);
  int read2 = sprintf(str2, "%hx", 0x12345678);

  ck_assert_int_eq(s21_strcmp(str1, "5678"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

START_TEST(s21_sprintf_spec_xX_prec_llen) {
  char str1[128];
  char str2[128];

  int read1 = s21_sprintf(str1, "%lX", ULONG_MAX);
  int read2 = sprintf(str2, "%lX", ULONG_MAX);

  ck_assert_int_eq(s21_strcmp(str1, "FFFFFFFFFFFFFFFF"), 0);
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
  ck_assert_int_eq(read1, read2);
}

Suite *suite_s21_sprintf_test(void) {
  Suite *s = suite_create("s21_sprintf_test");

  TCase *tc_c = tcase_create("s21_sprintf_test_c");
  suite_add_tcase(s, tc_c);
  tcase_add_test(tc_c, s21_sprintf_spec_c_default_char_1);
  tcase_add_test(tc_c, s21_sprintf_spec_c_default_char_2);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_1);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_2);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_3);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_4);
  tcase_add_test(tc_c, s21_sprintf_spec_c_wide_char_all);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_1);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_2);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_3);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_4);
  tcase_add_test(tc_c, s21_sprintf_spec_c_flag_and_wid_5);
  tcase_add_test(tc_c, s21_sprintf_spec_c_memory_alloc_wid_1);
  tcase_add_test(tc_c, s21_sprintf_spec_c_memory_alloc_wid_2);
  tcase_add_test(tc_c, s21_sprintf_spec_c_must_unwork);
  tcase_add_test(tc_c, s21_sprintf_spec_c_empty_char);
  tcase_add_test(tc_c, s21_sprintf_spec_c_empty_char_wid);
  tcase_add_test(tc_c, s21_sprintf_spec_c_empty_wchar);
  tcase_add_test(tc_c, s21_sprintf_spec_c_empty_wchar_wid);

  TCase *tc_s = tcase_create("s21_sprintf_test_s");
  suite_add_tcase(s, tc_s);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_one_string);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_many_strings);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_one_string_1);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_one_string_2);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_one_string_3);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_one_string_4);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_many_strings);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_default_one_string);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_default_many_strings_1);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_default_many_strings_2);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_default_many_strings_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_wide_one_string);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_wide_many_strings_1);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_wide_many_strings_2);
  tcase_add_test(tc_s, s21_sprintf_spec_s_prec_wide_many_strings_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_width_flag);
  tcase_add_test(tc_s, s21_sprintf_spec_s_default_width_flag_many);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_width_many);
  tcase_add_test(tc_s, s21_sprintf_spec_s_wide_width_flag_many);
  tcase_add_test(tc_s, s21_sprintf_spec_s_realloc_1);
  tcase_add_test(tc_s, s21_sprintf_spec_s_realloc_2);
  tcase_add_test(tc_s, s21_sprintf_spec_s_must_unwork);
  tcase_add_test(tc_s, s21_sprintf_spec_s_empty_default);
  tcase_add_test(tc_s, s21_sprintf_spec_s_empty_default_width);
  tcase_add_test(tc_s, s21_sprintf_spec_s_empty_wide);
  tcase_add_test(tc_s, s21_sprintf_spec_s_empty_wide_width);

  TCase *tc_di = tcase_create("s21_sprintf_test_di");
  suite_add_tcase(s, tc_di);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_4);
  tcase_add_test(tc_di, s21_sprintf_spec_di_flags_5);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_4);
  tcase_add_test(tc_di, s21_sprintf_spec_di_width_flags_unwork);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_4);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_5);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_6);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_7);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_zero_8);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_flags);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_4);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_unwork_5);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_extreme_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_width_flags_extreme_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_hlen_1);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_hlen_2);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_hlen_3);
  tcase_add_test(tc_di, s21_sprintf_spec_di_prec_llen);

  TCase *tc_o = tcase_create("s21_sprintf_test_o");
  suite_add_tcase(s, tc_o);
  tcase_add_test(tc_o, s21_sprintf_spec_o_default);
  tcase_add_test(tc_o, s21_sprintf_spec_o_flags_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_flags_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_width);
  tcase_add_test(tc_o, s21_sprintf_spec_o_width_flags_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_width_flags_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_width_flags_unwork);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_3);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_4);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_5);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_6);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_7);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_8);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_zero_9);
  tcase_add_test(tc_o, s21_sprintf_spec_o_hash_extreme_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_hash_extreme_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_hash_unwork);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_unwork);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_3);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_4);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_width_flags_extreme_5);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_hlen_1);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_hlen_2);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_hlen_3);
  tcase_add_test(tc_o, s21_sprintf_spec_o_prec_llen);

  TCase *tc_xX = tcase_create("s21_sprintf_test_xX");
  suite_add_tcase(s, tc_xX);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_default);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_flags_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_flags_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_width);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_width_flags_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_width_flags_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_width_flags_unwork);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_3);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_4);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_5);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_6);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_7);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_8);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_zero_9);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_hash_extreme_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_hash_extreme_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_hash_unwork);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_unwork);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_3);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_4);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_5);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_width_flags_extreme_6);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_hlen_1);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_hlen_2);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_hlen_3);
  tcase_add_test(tc_xX, s21_sprintf_spec_xX_prec_llen);

  return s;
}
