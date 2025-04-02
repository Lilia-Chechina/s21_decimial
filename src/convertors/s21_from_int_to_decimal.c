#include "../main.h"

// Maybe later set up 0 and 1 like constants
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (dst == NULL) return 1;  // converting error if NULL is transmitted
    
    null_decimal(dst);  //reset the structure
    if (src < 0) {
      s21_set_sign(dst, 1);
      src = -src;
  }
  dst->bits[0] = (uint32_t)src;  // record the meaning
  return 0;
}