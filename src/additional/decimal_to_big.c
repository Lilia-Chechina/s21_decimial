#include "../s21_decimal.h"

void decimal_to_big(s21_decimal src, s21_big_decimal* dest) {
    for (int i = 0; i < 3; i++) {
        dest->bits[i] = src.bits[i]; // копируем мантиссу
    }
    for (int i = 3; i < 6; i++) {
        dest->bits[i] = 0; // старшие 96 бит обнуляем
    }
}