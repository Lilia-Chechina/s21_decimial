#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    // проверка что указатель не NULL
    if (!result) return -1;

    // проверка на знак
    int sign_value_1 = s21_get_sign(value_1);
    int sign_value_2 = s21_get_sign(value_2);

    if (sign_value_1 != sign_value_2) { // если знаки разные, то это вычитание
        if (sign_value_1 == 1) { // вычитаем отрицательное
            s21_set_sign(&value_1, 0);
            return s21_sub(value_2, value_1, result);
        } else {
            s21_set_sign(&value_2, 0);
            return s21_sub(value_1, value_2, result);
        }
    }

    // преобразуем в big_decimal
    s21_big_decimal value_1_big, value_2_big, result_big;
    decimal_to_big(value_1, &value_1_big);
    decimal_to_big(value_2, &value_2_big);

    // нормализация scale
    int scale_value_1 = get_scale(value_1);
    int scale_value_2 = get_scale(value_2);
    normalize_big_decimals(&value_1_big, &scale_value_1, &value_2_big, &scale_value_2);

    // складываем побайтово в big_decimal
    add_big_decimal(&value_1_big, &value_2_big, &result_big);

    // преобразуем в decimal (используем банковское округление)
    int ret = big_to_decimal(result_big, result, scale_value_1, sign_value_1);
    if (is_zero(*result)) { // чтобы не было -0
        s21_set_sign(result, 0);
    }
    return ret;
}
