#include "../main.h"

int get_bit(s21_decimal num, int bit) { // получаем конкретный бит от 0 до 95
    int index = bit / 32; // определяем, в каком элементе bits он хранится
    int offset = bit % 32; // определяем позицию внутри этого элемента
    return (num.bits[index] >> offset) & 1u;
}