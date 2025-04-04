#include "../s21_decimal.h"

void null_big_decimal(s21_big_decimal* num) { // обнуляем
    for (int i = 0; i < 6; i++) num->bits[i] = 0;
}