#include "../main.h"

void shift_left(s21_big_decimal* num) { // сдвиг на 1 влево (или *2) (быстрее чем add_big_decimal, так как работаем со сдвигами)
    unsigned memory = 0;
    for (int i = 0; i < (int)(sizeof(s21_big_decimal) / sizeof(unsigned)) - 1; ++i) {
        unsigned temp = num->bits[i]; // сохраняем текущий блок
        num->bits[i] <<= 1; // сдвигаем на 1 бит влево
        num->bits[i] |= memory; // подставляем бит-перенос из предыдущего блока
        memory = temp >> 31; // сохраняем старший бит для следующего блока
    }
}