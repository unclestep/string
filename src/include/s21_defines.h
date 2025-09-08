#ifndef S21_STRING_DEFINES_H
#define S21_STRING_DEFINES_H

#include <stdint.h>

/* Common */
typedef unsigned long s21_size_t;
#define s21_byte_t unsigned char
#define s21_NULL (void *)0
typedef __uint128_t uint128_t;

#define ONE (uint128_t)1
#define ZERO (uint128_t)0

/* s21_sprintf */
#define LDOUBLE_MANTISSA_BITS 64
#define LDOUBLE_EXPONENT_BITS 15
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
  char *array;
  s21_size_t size;
  s21_size_t alloc;
} sc_t;

/* s21_gmp.h */
#define LIMB_SIZE 64
typedef unsigned long long limb_t;
typedef int mp_size_t;

#endif
