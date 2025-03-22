#include <stdio.h>
#include <stdbool.h>

typedef struct {
    __uint32_t bits[4];
} s21_decimal;

void s21_print_bits(s21_decimal value) {
    for (int i = 0; i < 4; i++) {
        for (int i2 = 32 - 1; i2 >= 0; i2--) {
            printf("%d", (value.bits[i] >> i2) & 1);
            if (i2 % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void s21_set_sign(s21_decimal* value, bool sign) {
    if (sign) {
        value->bits[3] |= 1;
    } else {
        value->bits[3] &= ~1;
    }
}

bool s21_get_sign(s21_decimal value) {
    return value.bits[3] & 1;
}

int s21_get_rank(s21_decimal value) {
    return value.bits[3] >> 8 & 0xFF;
}