#include "../../s21_decimal.h"

int divide_by_10_big_decimal(s21_big_decimal* value) { // деление на 10 для банковского округления
    uint64_t remainder = 0;

    for (int i = 5; i >= 0; i--) {
        uint64_t full = (remainder << 32) | value->bits[i]; // объединяем остаток и текущий блок
        value->bits[i] = (uint32_t)(full / 10); // записываем результат деления
        remainder = full % 10; // сохраняем остаток
    }

    return (int)remainder; // возвращаем остаток от всего деления
}