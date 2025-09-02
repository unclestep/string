// #include "../include/s21_gmp.h"
//
// BigNum_t bignum_add(BigNum_t *add1, BigNum_t *add2) {
//   BigNum_t res = {0};
//
//   BigNum_t *gr = add1->limbs > add2->limbs ? add1 : add2;
//   BigNum_t *le = add1->limbs < add2->limbs ? add1 : add2;
//
//   res.num = (limb_t *)malloc(gr->limbs * sizeof(limb_t));
//
//   unsigned carry = 0;
//   int msb = 0;
//
//   for (int cur_limb = 0; cur_limb != le->limbs; ++cur_limb) {
//     for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
//       unsigned b1 = getbit(add1, cur_limb, cur_bit);
//       unsigned b2 = getbit(add2, cur_limb, cur_bit);
//
//       unsigned sum = b1 + b2 + carry;
//       carry = (sum > 1) ? 1 : 0;
//       unsigned bit_to_set = sum == 1 || sum == 3 ? 1 : 0;
//
//       setbit(&res, cur_limb, cur_bit, bit_to_set);
//
//       if (bit_to_set == 1) {
//         msb = cur_limb * LIMB_SIZE + cur_bit;
//       }
//     }
//   }
//
//   for (int cur_limb = le->limbs; cur_limb != gr->limbs; ++cur_limb) {
//     for (int cur_bit = 0; cur_bit != LIMB_SIZE; ++cur_bit) {
//       unsigned sum = getbit(gr, cur_limb, cur_bit) + carry;
//       carry = (sum > 1) ? 1 : 0;
//       unsigned bit_to_set = sum == 1 ? 1 : 0;
//
//       setbit(&res, cur_limb, cur_bit, bit_to_set);
//
//       if (bit_to_set == 1) {
//         msb = cur_limb * LIMB_SIZE + cur_bit;
//       }
//     }
//   }
//
//   res.msb = msb;
//   res.limbs = gr->limbs;
//
//   return res;
// }
