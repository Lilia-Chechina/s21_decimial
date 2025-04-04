#include "../s21_decimal.h"

void set_bit(s21_decimal* num, int bit, unsigned value) { // устанавливаем/сбрасываем конкретный бит (0 или 1)
    int index = bit / 32;
    int offset = bit % 32;
    if (value)
        num->bits[index] |= (1u << offset); // установить бит
    else
        num->bits[index] &= ~(1u << offset); // сбросить бит
}