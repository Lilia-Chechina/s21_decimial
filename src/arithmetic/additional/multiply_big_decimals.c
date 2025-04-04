#include "../../s21_decimal.h"

void multiply_big_decimals(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result) {
    // временное хранилище результата умножения (не боимся за переполнение, так как сейчас в a и b старшие 92 бита это нули)
    uint64_t temp[6] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            uint64_t mul = (uint64_t)a->bits[i] * b->bits[j]; // перемножаем 32-битные блоки → получаем 64-битный результат

            temp[i + j] += mul; // прибавляем младшие 32 бита к позиции i + j

            // если произошёл перенос (сумма > UINT32_MAX), обрабатываем его (то есть может произойти автоматическое переполнение, которое надо проконтролировать)
            if (temp[i + j] < mul) {
                temp[i + j + 1]++;
            }

            // прибавляем старшие 32 бита результата (так как в result байты хранятся в 32 битах)
            temp[i + j + 1] += temp[i + j] >> 32;
            temp[i + j] &= 0xFFFFFFFF; // оставляем только младшие 32 бита
        }
    }

    // копируем результат в структуру big_decimal
    for (int i = 0; i < 6; i++) {
        result->bits[i] = (uint32_t)temp[i];
    }
}