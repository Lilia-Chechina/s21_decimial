#include "../main.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
    return s21_compare(a, b) == 1;
}