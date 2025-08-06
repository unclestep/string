#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  unsigned a = 1;
  a <<= 32 - 1;
  printf("%u\n", a);
  a >>= 32 - 1;
  printf("%u\n", a);
}
