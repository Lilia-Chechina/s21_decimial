#include "../../s21_decimal.h"

void add_big_decimal(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result) { // складываем две структуры
    unsigned memory = 0;
    for (int i = 0; i < 6; i++) {
        uint64_t sum = (uint64_t)a->bits[i] + b->bits[i] + memory; // складываем два uint32 + перенос
        result->bits[i] = (uint32_t)sum; // сохраняем младшие 32 бита результата
        memory = sum >> 32; // сохраняем перенос (старшие биты)
    }
}