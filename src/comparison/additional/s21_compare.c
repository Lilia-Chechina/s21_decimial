#include "../../s21_decimal.h"

int s21_compare(s21_decimal a, s21_decimal b) {
    // 0 - a == b; 1 - a > b; -1 - a < b

    // проверяем знак
    int sign_a = s21_get_sign(a);
    int sign_b = s21_get_sign(b);

    if (is_zero(a) && is_zero(b)) { // если два 0
        return 0;
    }

    if (sign_a != sign_b) { // если разные знаки
        return (sign_a == 1) ? -1 : 1;
    }

    // преобразуем в big_decimal
    s21_big_decimal a_big, b_big;
    decimal_to_big(a, &a_big);
    decimal_to_big(b, &b_big);

    // нормализация scale
    int scale_a = get_scale(a);
    int scale_b = get_scale(b);
    normalize_big_decimals(&a_big, &scale_a, &b_big, &scale_b);

    // побитовое сравнение
    int flag = 0;
    for (int i = 191; i >= 0; i--) {
        int bit_a = get_bit_big_decimal(a_big, i);
        int bit_b = get_bit_big_decimal(b_big, i);
        if (bit_a != bit_b) {
            flag = (bit_a > bit_b) ? 1 : -1;
            break;
        }
    }

    if (sign_a == 1) flag *= -1;  // если знак отрицательный, меняем знак результата

    return flag;
}