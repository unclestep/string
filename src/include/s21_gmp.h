// #ifndef S21_GMP_H
// #define S21_GMP_H
//
// #include <stdlib.h>
//
// #include "s21_defines.h"
// #include "s21_std.h"
//
// typedef struct BigNum_t {
//   limb_t *num;
//   int e10;
//   int msb;
//   int limbs;
// } BigNum_t;
//
// BigNum_t bignum_add(BigNum_t *add1, BigNum_t *add2);
// BigNum_t bignum_mul(BigNum_t *mul1, BigNum_t *mul2);
//
// static inline int max(int v1, int v2) { return v1 > v2 ? v1 : v2; }
// static inline int min(int v1, int v2) { return v1 < v2 ? v1 : v2; }
//
// static inline void bignum_deepcpy(BigNum_t *dst, BigNum_t *src) {
//   *dst = *src;
//   dst->num = (limb_t *)malloc(sizeof(limb_t) * src->limbs);
//   s21_memcpy(dst->num, src->num, sizeof(limb_t) * src->limbs);
// }
//
// static inline void bignum_clean(BigNum_t *v) {
//   if (v->num) {
//     free(v->num);
//   }
// }
//
// static inline unsigned getbit(BigNum_t *v, int limb, int bit) {
//   return (v->num[limb] >> bit) & ONE;
// }
//
// static inline void setbit(BigNum_t *v, int limb, int bit, uint128_t vbit) {
//   v->num[limb] &= ~(ONE << bit);
//   v->num[limb] |= vbit << bit;
// }
//
// static inline BigNum_t bitshiftr(BigNum_t *v, int shift) {
//   BigNum_t shft = {0};
//   bignum_deepcpy(&shft, v);
//
//   for (int i = 0; i != shift; ++i) {
//     for (int cur_limb = 0; cur_limb != shft.limbs; ++cur_limb) {
//       shft.num[cur_limb] >>= 1;
//       if (cur_limb + 1 < shft.limbs) {
//         setbit(&shft, cur_limb, LIMB_SIZE - 1, getbit(&shft, cur_limb + 1,
//         0));
//       }
//     }
//   }
//
//   return shft;
// }
//
// static inline BigNum_t bitshiftl(BigNum_t *v, int shift) {
//   BigNum_t shft = {0};
//   bignum_deepcpy(&shft, v);
//
//   for (int i = 0; i != shift; ++i) {
//     for (int cur_limb = shft.limbs - 1; cur_limb >= 0; --cur_limb) {
//       shft.num[cur_limb] <<= 1;
//       if (cur_limb - 1 >= 0) {
//         setbit(&shft, cur_limb, 0, getbit(&shft, cur_limb - 1, LIMB_SIZE -
//         1));
//       }
//     }
//   }
//
//   return shft;
// }
//
// static inline void mul2e(BigNum_t *v, const uint128_t m, const int32_t e) {
//   for (s21_size_t v_i = v->msb, m_i = 0; m_i != LIMB_SIZE;
//        ++v_i, ++m_i, ++v->msb) {
//     s21_size_t limb = v_i / LIMB_SIZE;
//     s21_size_t bit = v_i % LIMB_SIZE;
//     v->num[limb] |= ((m >> m_i) & ONE) << bit;
//   }
// }
//
// static inline void mul10(BigNum_t *v) {
//   BigNum_t add1 = bitshiftl(v, 3), add2 = bitshiftl(v, 2);
//   BigNum_t res = bignum_add(&add1, &add2);
//   bignum_clean(v);
//   bignum_clean(&add1);
//   bignum_clean(&add2);
//   *v = res;
// }
//
// // static inline void longdiv2(BigNum_t *m, const int e) {
// //   int e10 = 0;
// //   for (int i = 0; i != decdigits; ++i) {
// //     for () {
// //     }
// //   }
// // }
// //
// // static inline void div2(BigNum_t *q, BigNum_t *r, BigNum_t m, const int e)
// {
// //   *q = 0, *r = 0;
// //
// //   if (e >= 128) {
// //     s21_memset(q, 0, sizeof(uint128_t));
// //     s21_memcpy(r, q, sizeof(uint128_t));
// //   } else {
// //     *q |= m >> e;
// //     *r |= m & ((ONE << e) - 1);
// //   }
// // }
//
// #endif
