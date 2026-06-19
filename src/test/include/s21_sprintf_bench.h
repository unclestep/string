#ifndef S21_SPRINTF_BENCH_H
#define S21_SPRINTF_BENCH_H

#ifdef S21_BENCH_SPRINTF

#include <time.h>

void s21_bench_record(const char *spec, int is_libc, const struct timespec *t0,
                      const struct timespec *t1);

#ifdef BENCH_SPEC

#define s21_sprintf(str, ...)                              \
  ({                                                       \
    struct timespec s21_bt0_, s21_bt1_;                    \
    clock_gettime(CLOCK_MONOTONIC, &s21_bt0_);             \
    int s21_bres_ = s21_sprintf(str, __VA_ARGS__);         \
    clock_gettime(CLOCK_MONOTONIC, &s21_bt1_);             \
    s21_bench_record(BENCH_SPEC, 0, &s21_bt0_, &s21_bt1_); \
    s21_bres_;                                             \
  })

#define sprintf(str, ...)                                  \
  ({                                                       \
    struct timespec s21_bt0_, s21_bt1_;                    \
    clock_gettime(CLOCK_MONOTONIC, &s21_bt0_);             \
    int s21_bres_ = sprintf(str, __VA_ARGS__);             \
    clock_gettime(CLOCK_MONOTONIC, &s21_bt1_);             \
    s21_bench_record(BENCH_SPEC, 1, &s21_bt0_, &s21_bt1_); \
    s21_bres_;                                             \
  })

#endif /* BENCH_SPEC */

#endif /* S21_BENCH_SPRINTF */

#endif /* S21_SPRINTF_BENCH_H */
