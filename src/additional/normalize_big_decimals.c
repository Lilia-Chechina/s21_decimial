#include "../main.h"

void normalize_big_decimals(s21_big_decimal* a, int* scale_a, s21_big_decimal* b, int* scale_b) { // выравниваем порядки
    while (*scale_a < *scale_b) {
        multiply_by_10_big_decimal(a);
        (*scale_a)++;
    }
    while (*scale_b < *scale_a) {
        multiply_by_10_big_decimal(b);
        (*scale_b)++;
    }
}