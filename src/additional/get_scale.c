#include "../main.h"

int get_scale(s21_decimal num) { // извлекаем scale (биты 16–23 из bits[3])
    return (num.bits[3] >> 16) & 0xFF;
}