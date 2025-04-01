#include "../../main.h"

int divide_big_decimal(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result, s21_big_decimal* remainder) { // ищем наибольшее q, при котором верно: b * 2**q <= a
    s21_big_decimal current_b, prev_b;
    s21_big_decimal temp_a = *a;

    while (compare_big_decimal(&temp_a, b) >= 0) { // пока делимое больше делителя
        int q = 0; // степень двойки
        current_b = *b; // для запоминания промежуточного результата

        do {
            prev_b = current_b;  // запоминаем предыдущий
            shift_left(&current_b);  // умножаем на 2
            q++; // повышаем степень двойки
        } while (compare_big_decimal(&current_b, &temp_a) <= 0); // do-while, потому что надо гарантированно выполнить хотя бы одну итерацию

        // используем prev_b вместо сдвига вправо
        s21_big_decimal temp_result = {0};
        set_bit_big_decimal(&temp_result, q - 1, 1); // result += 2**(q - 1)
        add_big_decimal(result, &temp_result, result); // обновляем result

        subtract_big_decimal(&temp_a, &prev_b, &temp_a); // вычитаем найденное значение из текущего остатка
    }

    *remainder = temp_a;

    return 0;
}