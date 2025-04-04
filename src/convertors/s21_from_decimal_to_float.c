#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) return 1;  // Checking the pointer for validity, does the pointer exist?
  double result = 0.0;
  int scale = get_scale(src); 
  result = (double)src.bits[0] + ((double)src.bits[1] * (1ULL << 32)) + ((double)src.bits[2] * (1ULL << 64));

  for (int i = 0; i < scale; i++) {
      result /= 10.0;
  }

  if (s21_get_sign(src)) result = -result;
  *dst = (float)result;

  return 0;
}
