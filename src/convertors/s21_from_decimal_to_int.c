#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) return 1; // Error if NULL is transmitted
  
  s21_truncate(src, &src); // truncate the fractional part
  null_decimal(dst);
  
  int numSign = s21_get_sign(src);
  
  if (src.bits[1] || src.bits[2] || (numSign && src.bits[0] > (uint32_t)INT32_MAX + 1) || 
      (!numSign && src.bits[0] > INT32_MAX)) {
      return 1; // Overflow
  }

  *dst = (int)src.bits[0];
  if (numSign) *dst = -*dst;
  
  return 0;
}