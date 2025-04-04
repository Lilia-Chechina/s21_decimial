#include "../s21_decimal.h"

int big_to_decimal(s21_big_decimal src, s21_decimal* dest, int scale, int sign) {
    if (src.bits[3] != 0 || src.bits[4] != 0 || src.bits[5] != 0) { // если занято больше 96 бит то делаем банковское округление
        round_bank(&src, &scale);
        if (src.bits[3] != 0 || src.bits[4] != 0 || src.bits[5] != 0) { // если после округления все равно остались лишние биты (когда scale == 0 и занято больше 96 битов)
            null_decimal(dest); // обнуление результата при переполнении
            return (sign == 0) ? 1 : 2;
        }
    }

    null_decimal(dest);
    for (int i = 0; i < 3; i++) { // копируем 96 бит
        dest->bits[i] = src.bits[i];
    }
    set_scale(dest, scale); // устанавливаем порядок
    s21_set_sign(dest, sign); // устанавливаем знак

    return 0;
}
