#include "../main.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
    return s21_compare(a, b) == 0;
}