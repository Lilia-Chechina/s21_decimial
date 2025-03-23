#include "main.h"

int main() {

    // тут можно потестить вручную

    // s21_decimal a = {{1, 0, 0, 0}};
    // s21_decimal b = {{999999999, 4294967295, 542101086, 0}};
    // set_scale(&b, 28);

    // printf("%d ", s21_compare(a, b));
    // printf("\na = %.10g (scale = %d)\n", input_a, scale_a);
    // printf("b = %.10g (scale = %d)\n\n", input_b, scale_b);
    // printf("s21_is_equal: %d\n", s21_is_equal(a, b));
    // printf("s21_is_not_equal: %d\n", s21_is_not_equal(a, b));
    // printf("s21_is_less: %d\n", s21_is_less(a, b));
    // printf("s21_is_less_or_equal: %d\n", s21_is_less_or_equal(a, b));
    // printf("s21_is_greater: %d\n", s21_is_greater(a, b));
    // printf("s21_is_greater_or_equal: %d\n", s21_is_greater_or_equal(a, b));

    return 0;
}


////////////////// вспомогательные функции (werlagad) /////////////////
int is_zero(s21_decimal num) { // проверяем, что все три части мантиссы равны 0
    return num.bits[0] == 0 && num.bits[1] == 0 && num.bits[2] == 0;
}

void null_decimal(s21_decimal* num) { // обнуляем все 4 элемента массива bits
    for (int i = 0; i < 4; i++) {
        num->bits[i] = 0;
    }
}

int get_sign(s21_decimal num) { // получаем знак из 31-го бита bits[3]
    return (num.bits[3] >> 31) & 1u;
}

void set_sign(s21_decimal* num, int sign_value) { // устанавливаем или убираем знак в 31-м бите bits[3]
    if (sign_value)
        num->bits[3] |= (1u << 31); // установить бит в 1 (минус)
    else
        num->bits[3] &= ~(1u << 31); // сбросить бит (плюс)
}

int get_scale(s21_decimal num) { // извлекаем scale (биты 16–23 из bits[3])
    return (num.bits[3] >> 16) & 0xFF;
}

void set_scale(s21_decimal* num, int scale_value) {
    num->bits[3] &= ~(0xFF << 16); // сбросим старый scale (маска 0xFF << 16)
    num->bits[3] |= (scale_value & 0xFF) << 16; // запишем новый scale
}

int get_bit(s21_decimal num, int bit) { // получаем конкретный бит от 0 до 95
    int index = bit / 32; // определяем, в каком элементе bits он хранится
    int offset = bit % 32; // определяем позицию внутри этого элемента
    return (num.bits[index] >> offset) & 1u;
}

int get_bit_big_decimal(s21_big_decimal num, int bit) { // также как и get_bit только для bit_decimal
    int index = bit / 32;
    int offset = bit % 32;
    return (num.bits[index] >> offset) & 1u;
}

void set_bit(s21_decimal* num, int bit, unsigned value) { // устанавливаем/сбрасываем конкретный бит (0 или 1)
    int index = bit / 32;
    int offset = bit % 32;
    if (value)
        num->bits[index] |= (1u << offset); // установить бит
    else
        num->bits[index] &= ~(1u << offset); // сбросить бит
}

void shift_left(s21_big_decimal* num) {
    unsigned memory = 0;
    for (int i = 0; i < (int)(sizeof(s21_big_decimal) / sizeof(unsigned)) - 1; ++i) {
        unsigned temp = num->bits[i]; // сохраняем текущий блок
        num->bits[i] <<= 1; // сдвигаем на 1 бит влево
        num->bits[i] |= memory; // подставляем бит-перенос из предыдущего блока
        memory = temp >> (32 - 1); // сохраняем старший бит для следующего блока
    }
}

void multiply_by_10_big_decimal(s21_big_decimal* num) { // x * 10 = x * 8 + x * 2 = x << 3 + x << 1
    s21_big_decimal temp1 = *num;
    s21_big_decimal temp2 = *num;

    for (int i = 0; i < 3; ++i) shift_left(&temp1); // temp1 = num << 3 (умножение на 8)
    shift_left(&temp2); // temp2 = num << 1 (умножение на 2)

    add_big_decimal(&temp1, &temp2, num); // num = temp1 + temp2
}

void add_big_decimal(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result) { // объединяем две структуры, полученные в multiply_by_10_big_decimal
    unsigned memory = 0;
    for (int i = 0; i < 6; i++) {
        uint64_t sum = (uint64_t)a->bits[i] + b->bits[i] + memory; // складываем два uint32 + перенос
        result->bits[i] = (uint32_t)sum; // сохраняем младшие 32 бита результата
        memory = sum >> 32; // сохраняем перенос (старшие биты)
    }
}

void decimal_to_big(s21_decimal src, s21_big_decimal* dest) {
    for (int i = 0; i < 3; i++) {
        dest->bits[i] = src.bits[i]; // копируем мантиссу
    }
    for (int i = 3; i < 6; i++) {
        dest->bits[i] = 0; // старшие 96 бит обнуляем
    }
}

void normalize_big_decimals(s21_big_decimal* a, int* scale_a, s21_big_decimal* b, int* scale_b) {
    while (*scale_a < *scale_b) {
        multiply_by_10_big_decimal(a);
        (*scale_a)++;
    }
    while (*scale_b < *scale_a) {
        multiply_by_10_big_decimal(b);
        (*scale_b)++;
    }
}

///////////////////////// compare (werlagad) /////////////////////////
int s21_compare(s21_decimal a, s21_decimal b) {
    // 0 - a == b; 1 - a > b; -1 - a < b

    // проверяем знак
    int sign_a = get_sign(a);
    int sign_b = get_sign(b);

    if (is_zero(a) && is_zero(b)) { // если два 0
        return 0;
    }

    if (sign_a != sign_b) { // если разные знаки
        return (sign_a == 1) ? -1 : 1;
    }

    // преобразуем в big_decimal
    s21_big_decimal a_big, b_big;
    decimal_to_big(a, &a_big);
    decimal_to_big(b, &b_big);

    // нормализация scale
    int scale_a = get_scale(a);
    int scale_b = get_scale(b);
    normalize_big_decimals(&a_big, &scale_a, &b_big, &scale_b);

    // побитовое сравнение
    int flag = 0;
    for (int i = 191; i >= 0; i--) {
        int bit_a = get_bit_big_decimal(a_big, i);
        int bit_b = get_bit_big_decimal(b_big, i);
        if (bit_a != bit_b) {
            flag = (bit_a > bit_b) ? 1 : -1;
            break;
        }
    }

    if (sign_a == 1) flag *= -1;  // если знак отрицательный, меняем знак результата

    return flag;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
    return s21_compare(a, b) == 0;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b){
    return s21_compare(a, b) != 0;
}

int s21_is_less(s21_decimal a, s21_decimal b) {
    return s21_compare(a, b) == -1;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
    int cmp = s21_compare(a, b);
    return cmp == -1 || cmp == 0;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
    return s21_compare(a, b) == 1;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
    int cmp = s21_compare(a, b);
    return cmp == 1 || cmp == 0;
}
