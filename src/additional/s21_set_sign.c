#include "../s21_decimal.h"

void s21_set_sign(s21_decimal* value, bool is_negative) {
    if (is_negative) {
        value->bits[3] |= 1;
    } else {
        value->bits[3] &= ~1;
    }
}