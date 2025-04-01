#include "../main.h"

int is_zero_big_decimal(s21_big_decimal num) { // как is_zero, только с big_decimal
    for (int i = 0; i < 6; i++)
        if (num.bits[i] != 0) return 0;
    return 1;
}