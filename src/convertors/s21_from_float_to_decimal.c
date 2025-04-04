#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL || src != src || (src + 1 == src) || (src - 1 == src)) return 1; //  Checking for Nan and Inf
  
  null_decimal(dst);  // so that there is no garbage in memory
  if ((src > -1e-28 && src < 1e-28) || src > 7.922816e28 || src < -7.922816e28) return 1; // range
  
  int sign = (src < 0);
  if (sign) src = -src;
  
  int exponent = 0;
  while (src >= 10.0f) {
      src /= 10.0f;
      exponent++;
  }
  while (src > 0.0f && src < 1.0f) {
      src *= 10.0f;
      exponent--;
  }
  
  s21_big_decimal big;
  null_big_decimal(&big);
  
  for (int i = 0; i < 7; i++) {
      int digit = (int)src;
      src = (src - digit) * 10.0f;
      multiply_by_10_big_decimal(&big);
      big.bits[0] += digit;
  }
  
  int scale = 7 - exponent;
  round_bank(&big, &scale);
  
  return big_to_decimal(big, dst, scale, sign);
}