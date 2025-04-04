#include "../../s21_decimal.h"

int compare_big_decimal(s21_big_decimal *a, s21_big_decimal *b) { // нужно для деления
    for (int i = 191; i >= 0; i--) {
        int bit_a = get_bit_big_decimal(*a, i);
        int bit_b = get_bit_big_decimal(*b, i);

        if (bit_a != bit_b)
            return bit_a > bit_b ? 1 : -1;
    }

    return 0;
}