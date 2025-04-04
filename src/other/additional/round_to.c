#include "../../s21_decimal.h"

void round_to(s21_decimal value, s21_decimal* result, bool to_bigger) {
    int scale = get_scale(value);
    if (scale > 0) {
        s21_big_decimal value_big = { 0 };
        decimal_to_big(value, &value_big);

        while (scale > 0) {        
            int remainder = divide_by_10_big_decimal(&value_big); // cut and remember last bit
            if (remainder > 5) {
                add_1_to_big_decimal(&value_big);
            } else if (to_bigger && remainder == 5) {
                add_1_to_big_decimal(&value_big);
            }
            scale--;
        }

        big_to_decimal(value_big, result, 0, s21_get_sign(value));
    } else {
        s21_copy(value, result);
    }
}