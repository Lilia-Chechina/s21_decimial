#include "../main.h"

int s21_get_rank(s21_decimal value) {
    return value.bits[3] >> 8 & 0xFF;
}