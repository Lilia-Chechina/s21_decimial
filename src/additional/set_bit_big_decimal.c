#include "../main.h"

void set_bit_big_decimal(s21_big_decimal* num, int bit, unsigned value) { // как с set_bit, только для big_decimal (используется в делении)
    int index = bit / 32;
    int offset = bit % 32;
    if (value)
        num->bits[index] |= (1u << offset);
    else
        num->bits[index] &= ~(1u << offset);
}