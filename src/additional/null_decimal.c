#include "../main.h"

void null_decimal(s21_decimal* num) { // обнуляем все 4 элемента массива bits
    for (int i = 0; i < 4; i++) {
        num->bits[i] = 0;
    }
}