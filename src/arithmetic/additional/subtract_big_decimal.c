#include "../../main.h"

void subtract_big_decimal(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result) {
    unsigned borrow = 0;
    for (int i = 0; i < 6; i++) {
        uint64_t ai = a->bits[i];
        uint64_t bi = b->bits[i] + borrow; // занимаемый десяток у предыдущего числа мы не вычитаем из a->bits[i], а прибавляем к b->bits[i]

        if (ai >= bi) {
            result->bits[i] = (uint32_t)(ai - bi);
            borrow = 0;
        } else { // если надо занимать
            result->bits[i] = (uint32_t)(UINT64_C(1) << 32) + ai - bi; // UINT64_C обязателен, иначе 1 будет представлен в виде 32 битов
            borrow = 1;
        }
    }
}