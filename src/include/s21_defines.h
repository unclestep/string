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

/* s21_gmp.h */
#define LIMB_SIZE 64
typedef unsigned long long limb_t;

#endif
