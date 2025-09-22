#ifndef S21_STRING_DEFINES_H
#define S21_STRING_DEFINES_H

#include <stdbool.h>

/* Common */
typedef unsigned long s21_size_t;
#define s21_byte_t unsigned char
#define s21_NULL (void *)0
typedef __uint128_t uint128_t;

#define ONE (uint128_t)1
#define ZERO (uint128_t)0

#define LOG10_2 0.30102999566

/* s21_sprintf */
#if defined(__APPLE__)
#define LDOUBLE_MANTISSA_BITS 52
#define LDOUBLE_EXPONENT_BITS 11
#define LDOUBLE_EXPLICIT_LEADING_BIT 0

#elif defined(__linux__) && (defined(__x86_64__) || defined(__amd64__))
#define LDOUBLE_MANTISSA_BITS 64
#define LDOUBLE_EXPONENT_BITS 15
#define LDOUBLE_EXPLICIT_LEADING_BIT 1

#elif defined(__linux__) && defined(__aarch64__)
#define LDOUBLE_MANTISSA_BITS 112
#define LDOUBLE_EXPONENT_BITS 15
#define LDOUBLE_EXPLICIT_LEADING_BIT 0
#endif

#define DOUBLE_MANTISSA_BITS 52
#define DOUBLE_EXPONENT_BITS 11

typedef struct conv_t {
  bool minus;
  bool plus;
  bool space;
  bool hash;
  bool zero;
  int wid;
  int prec;
  int len;
  int spec;
} conv_t;

/* Size Char */
typedef struct sc_t {
  char *d;
  s21_size_t size;
  s21_size_t alloc;
} sc_t;

/* s21_gmp.h */
#define LIMB_SIZE 64
typedef unsigned long long limb_t;
typedef int mp_size_t;

typedef struct mpz_t {
  limb_t *d;       /* Pointer to the number */
  mp_size_t size;  /* Actual number of used limbs */
  mp_size_t alloc; /* Number of allocated limbs */
} mpz_t;

typedef struct mpf_t {
  mpz_t man; /* Mantissa */
  int exp;   /* Exponent */
  int fig;   /* Figures of number */
} mpf_t;

#endif
