#include <stdint.h>
#include <stdio.h>
#include <string.h>

void print_bits(uint64_t bits, int mbits, int ebits) {
  uint32_t bias = (1ULL << (ebits - 1)) - 1;
  uint32_t sign = (bits >> (mbits + ebits)) & 1;
  uint32_t exponent = bits >> mbits & ((1ULL << ebits) - 1);
  uint64_t mantissa = bits & ((1ULL << mbits) - 1);

  printf("%u ", sign);

  for (int i = ebits - 1; i >= 0; --i) {
    printf("%u", (exponent >> i) & 1);
  }
  printf(" ");

  for (int i = mbits - 1; i >= 0; --i) {
    printf("%llu", (mantissa >> i) & 1);
  }
  printf("\n");
}

int main(void) {
  uint64_t bits1 = 0;
  uint64_t bits2 = 0;

  float a = 1234567.123;
  memcpy(&bits1, &a, sizeof(float));
  double b = (double)a;
  memcpy(&bits2, &b, sizeof(double));

  print_bits(bits1, 23, 8);
  print_bits(bits2, 52, 11);

  printf("%.1024Lf", (long double)0.11);
}
