#include "../s21_decimal.h"

bool s21_get_sign(s21_decimal value) {
    return value.bits[3] & 1;
}