#include "../../s21_decimal.h"

void multiply_by_10_big_decimal(s21_big_decimal* num) { // x * 10 = x * 8 + x * 2 = x << 3 + x << 1
    s21_big_decimal temp1 = *num;
    s21_big_decimal temp2 = *num;

    for (int i = 0; i < 3; ++i) shift_left(&temp1); // temp1 = num << 3 (умножение на 8)
    shift_left(&temp2); // temp2 = num << 1 (умножение на 2)

    add_big_decimal(&temp1, &temp2, num); // num = temp1 + temp2
}