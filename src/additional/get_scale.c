#include "../s21_decimal.h"

int get_scale(s21_decimal value) {
    return value.bits[3] >> 8 & 0xFF;
}