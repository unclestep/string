#include "s21_sprintf_bench.h"

#ifdef S21_BENCH_SPRINTF

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char spec[8];
  double *samples[2]; /* [0] = s21_sprintf, [1] = libc sprintf */
  size_t count[2];
  size_t cap[2];
} bench_entry_t;

static bench_entry_t *entries = NULL;
static size_t entries_count = 0;
static size_t entries_cap = 0;
static int report_registered = 0;

static void push_sample(bench_entry_t *e, int is_libc, double ns) {
  size_t idx = is_libc ? 1 : 0;
  if (e->count[idx] == e->cap[idx]) {
    e->cap[idx] = e->cap[idx] ? e->cap[idx] * 2 : 64;
    e->samples[idx] = realloc(e->samples[idx], e->cap[idx] * sizeof(double));
  }
  e->samples[idx][e->count[idx]++] = ns;
}

static bench_entry_t *find_or_create(const char *spec) {
  for (size_t i = 0; i < entries_count; ++i) {
    if (strcmp(entries[i].spec, spec) == 0) return &entries[i];
  }
  if (entries_count == entries_cap) {
    entries_cap = entries_cap ? entries_cap * 2 : 16;
    entries = realloc(entries, entries_cap * sizeof(bench_entry_t));
  }
  bench_entry_t *e = &entries[entries_count++];
  memset(e, 0, sizeof(*e));
  strncpy(e->spec, spec, sizeof(e->spec) - 1);
  return e;
}

static int cmp_double(const void *a, const void *b) {
  double da = *(const double *)a;
  double db = *(const double *)b;
  return (da > db) - (da < db);
}

static double mean_of(const double *arr, size_t n) {
  double sum = 0;
  for (size_t i = 0; i < n; ++i) sum += arr[i];
  return n ? sum / (double)n : 0.0;
}

static double percentile95_of(const double *arr, size_t n) {
  if (n == 0) return 0.0;
  double *copy = malloc(n * sizeof(double));
  memcpy(copy, arr, n * sizeof(double));
  qsort(copy, n, sizeof(double), cmp_double);
  size_t idx = (size_t)ceil(0.95 * (double)n);
  if (idx == 0) idx = 1;
  if (idx > n) idx = n;
  double result = copy[idx - 1];
  free(copy);
  return result;
}

static void s21_bench_print_report(void) {
  printf("\n## sprintf benchmark (nanoseconds per call)\n\n");
  printf(
      "| Specifier | Samples | s21_sprintf avg | s21_sprintf p95 | "
      "sprintf avg | sprintf p95 |\n");
  printf("|---|---|---|---|---|---|\n");
  for (size_t i = 0; i < entries_count; ++i) {
    bench_entry_t *e = &entries[i];
    double s21_avg = mean_of(e->samples[0], e->count[0]);
    double s21_p95 = percentile95_of(e->samples[0], e->count[0]);
    double libc_avg = mean_of(e->samples[1], e->count[1]);
    double libc_p95 = percentile95_of(e->samples[1], e->count[1]);
    printf("| %%%s | %zu | %.1f | %.1f | %.1f | %.1f |\n", e->spec, e->count[0],
           s21_avg, s21_p95, libc_avg, libc_p95);
  }
  printf("\n");
}

void s21_bench_record(const char *spec, int is_libc, const struct timespec *t0,
                      const struct timespec *t1) {
  if (!report_registered) {
    atexit(s21_bench_print_report);
    report_registered = 1;
  }
  double ns = (double)(t1->tv_sec - t0->tv_sec) * 1e9 +
              (double)(t1->tv_nsec - t0->tv_nsec);
  bench_entry_t *e = find_or_create(spec);
  push_sample(e, is_libc, ns);
}

#endif /* S21_BENCH_SPRINTF */
