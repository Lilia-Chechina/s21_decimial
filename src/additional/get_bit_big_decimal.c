#include "../main.h"

int get_bit_big_decimal(s21_big_decimal num, int bit) { // как и get_bit, только для bit_decimal
    int index = bit / 32;
    int offset = bit % 32;
    return (num.bits[index] >> offset) & 1u;
}