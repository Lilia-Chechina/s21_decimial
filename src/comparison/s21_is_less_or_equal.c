#include "../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
    int cmp = s21_compare(a, b);
    return cmp == -1 || cmp == 0;
}