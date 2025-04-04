#include "../s21_decimal.h"

void round_bank(s21_big_decimal* value, int* scale) {
    while ((value->bits[3] != 0 || value->bits[4] != 0 || value->bits[5] != 0) && *scale > 0) { // пока используется больше 96 бит или scale != 0
        (*scale)--;
        int remainder = divide_by_10_big_decimal(value); // отсекаем и запоминаем последний бит
        if (remainder > 5) { // если больше 5 ++
            add_1_to_big_decimal(value);
        } else if (remainder == 5) {
            if (value->bits[0] & 1u) { // если равно 5 и при этом бит перед ним четный ++
                add_1_to_big_decimal(value);
            }
        }
    }
}