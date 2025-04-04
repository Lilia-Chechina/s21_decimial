#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int rank = get_scale(value);

    s21_decimal multiplyer = { { 1, 0, 0, 0 } };
    s21_big_decimal multiplyer_big;
    decimal_to_big(multiplyer, &multiplyer_big);

    for (int i = 0; i < rank; i++) {
        multiply_by_10_big_decimal(&multiplyer_big);
    }

    s21_big_decimal value_big, remainder_big, result_big = { 0 };
    decimal_to_big(value, &value_big);
    divide_big_decimal(&value_big, &multiplyer_big, &result_big, &remainder_big);
    big_to_decimal(result_big, result, 0, 0);

    return 0;
}