#include "../../main.h"

void add_1_to_big_decimal(s21_big_decimal* value) { // когда надо просто прибавить 1 создаем минимальный децимал и передаем его в функцию сложения
    s21_big_decimal one = {0};
    one.bits[0] = 1;
    add_big_decimal(value, &one, value);
}