#include "../main.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    // проверка что указатель не NULL
    if (!result) return -1;

    // обработка знака результата
    int sign_result = s21_get_sign(value_1) ^ s21_get_sign(value_2); // исключающее или

    // преобразуем в big_decimal
    s21_big_decimal value_1_big, value_2_big, result_big;
    decimal_to_big(value_1, &value_1_big);
    decimal_to_big(value_2, &value_2_big);

    // складываем порядки
    int scale = get_scale(value_1) + get_scale(value_2);

    // перемножаем побайтово в big_decimal
    multiply_big_decimals(&value_1_big, &value_2_big, &result_big);

    // преобразуем в decimal (используем банковское округление)
    int ret = big_to_decimal(result_big, result, scale, sign_result);
    if (is_zero(*result)) { // чтобы не было -0
        set_sign(result, 0);
    }
    return ret;
}
