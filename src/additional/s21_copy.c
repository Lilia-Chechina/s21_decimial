#include "../s21_decimal.h"

void s21_copy(s21_decimal value, s21_decimal* result) {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    result->bits[3] = value.bits[3];
}