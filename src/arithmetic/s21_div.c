#include "../main.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    // проверка что указатель не NULL
    if (!result) return -1;
    if (is_zero(value_2)) return 3; // деление на 0

    // обработка знака результата
    int sign = s21_get_sign(value_1) ^ s21_get_sign(value_2);

    // преобразуем в big_decimal
    s21_big_decimal value_1_big, value_2_big, result_big, remainder_big;
    decimal_to_big(value_1, &value_1_big);
    decimal_to_big(value_2, &value_2_big);

    // нормализация scale
    int scale_value_1 = get_scale(value_1);
    int scale_value_2 = get_scale(value_2);
    normalize_big_decimals(&value_1_big, &scale_value_1, &value_2_big, &scale_value_2);

    null_big_decimal(&result_big); // изначально результат = 0

    // получаем целую часть и остаток
    divide_big_decimal(&value_1_big, &value_2_big, &result_big, &remainder_big);

    // сразу начинаем вычислять дробную часть по одной цифре
    int scale = 0;
    while (!is_zero_big_decimal(remainder_big) && scale < 28) {
        multiply_by_10_big_decimal(&remainder_big);

        s21_big_decimal digit, new_remainder;
        divide_big_decimal(&remainder_big, &value_2_big, &digit, &new_remainder);

        // умножаем текущий результат на 10 (добавляем разряд)
        multiply_by_10_big_decimal(&result_big);

        // сразу прибавляем новую цифру (она всегда меньше 10)
        add_big_decimal(&result_big, &digit, &result_big);

        remainder_big = new_remainder;
        scale++;
    }
    int ret = big_to_decimal(result_big, result, scale, sign);
    if (is_zero(*result)) { // чтобы не было -0
        set_sign(result, 0);
    }
    return ret;
}
