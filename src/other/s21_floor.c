#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    round_to(value, result, false);
    return 0;
}