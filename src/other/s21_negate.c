#include "../main.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    if (s21_get_sign(value)) {
        s21_set_sign(result, false);
    } else {
        s21_set_sign(result, true);
    }
    return 0;
}