#include "../s21_decimal.h"

void s21_print_bits(s21_decimal value) {
    for (int i = 0; i < 4; i++) {
        for (int i2 = 31; i2 >= 0; i2--) {
            printf("%d", value.bits[i] >> i2 & 1);
            if (i2 % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n");
    }
}