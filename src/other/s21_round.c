#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    round_to(value, result, true);
    return 0;
}