#include "../main.h"

void set_scale(s21_decimal* num, int scale_value) {
    num->bits[3] &= ~(0xFF << 16); // сбросим старый scale (маска 0xFF << 16)
    num->bits[3] |= (scale_value & 0xFF) << 16; // запишем новый scale
}