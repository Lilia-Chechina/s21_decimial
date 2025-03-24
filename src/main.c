#include "main.h"

int main() {

    // тут можно потестить вручную
    // float fa = 1.00000006f;
    // float fb = 1.00000007f;
    // printf("float: %d\n", fa == fb);
    // s21_decimal a = {{100000006, 0, 0, 0}};
    // s21_decimal b = {{100000007, 0, 0, 0}};
    // set_scale(&a, 8); // 1.00000006
    // set_scale(&b, 8); // 1.00000007

    // printf("decimal: %d\n", s21_is_equal(a, b));

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


    // s21_decimal a = {{5000000, 0, 0, 0}};
    // s21_decimal b = {{7000000, 0, 0, 0}};
    // set_scale(&a, 7);
    // set_scale(&b, 7);
    // s21_decimal result;

    // int status = s21_add(a, b, &result);

    // printf("Status: %d\n", status);
    // printf("Result bits: {%u, %u, %u, %u}\n", result.bits[0], result.bits[1], result.bits[2], result.bits[3]);
    // printf("Scale: %d\n", get_scale(result));
    // printf("Sign: %d\n", get_sign(result));

    // float fa = 0.5f;
    // float fb = 0.7f;
    // printf("float: %.10g + %.10g = %.10g\n", fa, fb, fa + fb);

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

void decimal_to_big(s21_decimal src, s21_big_decimal* dest) {
    for (int i = 0; i < 3; i++) {
        dest->bits[i] = src.bits[i]; // копируем мантиссу
    }
    for (int i = 3; i < 6; i++) {
        dest->bits[i] = 0; // старшие 96 бит обнуляем
    }
}

int big_to_decimal(s21_big_decimal src, s21_decimal* dest, int scale, int sign) {
    if (src.bits[3] != 0 || src.bits[4] != 0 || src.bits[5] != 0) { // если занято больше 96 бит то делаем банковское округление
        round_bank(&src, &scale);
        if (src.bits[3] != 0 || src.bits[4] != 0 || src.bits[5] != 0) { // если после округления все равно остались лишние биты (когда scale == 0 и занято больше 96 битов)
            return (sign == 0) ? 1 : 2;
        }
    }

    for (int i = 0; i < 3; i++) { // копируем 96 бит
        dest->bits[i] = src.bits[i];
    }
    set_scale(dest, scale); // устанавливаем порядок
    set_sign(dest, sign); // устанавливаем знак

    return 0;
}

void shift_left(s21_big_decimal* num) { // сдвиг на 1 влево (или *2) (быстрее чем add_big_decimal, так как работаем со сдвигами)
    unsigned memory = 0;
    for (int i = 0; i < (int)(sizeof(s21_big_decimal) / sizeof(unsigned)) - 1; ++i) {
        unsigned temp = num->bits[i]; // сохраняем текущий блок
        num->bits[i] <<= 1; // сдвигаем на 1 бит влево
        num->bits[i] |= memory; // подставляем бит-перенос из предыдущего блока
        memory = temp >> 31; // сохраняем старший бит для следующего блока
    }
}

void round_bank(s21_big_decimal* value, int* scale) {
    while ((value->bits[3] != 0 || value->bits[4] != 0 || value->bits[5] != 0) && *scale > 0) { // пока используется больше 96 бит или scale != 0
        (*scale)--;
        int remainder = divide_by_10_big_decimal(value); // отсекаем и запоминаем последний бит
        if (remainder > 5) { // если больше 5 ++
            add_1_to_big_decimal(value);
        } else if (remainder == 5) {
            if (value->bits[0] & 1u) { // если равно 5 и при этом бит перед ним четный ++
                add_1_to_big_decimal(value);
            }
        }
    }
}

void normalize_big_decimals(s21_big_decimal* a, int* scale_a, s21_big_decimal* b, int* scale_b) { // выравниваем порядки
    while (*scale_a < *scale_b) {
        multiply_by_10_big_decimal(a);
        (*scale_a)++;
    }
    while (*scale_b < *scale_a) {
        multiply_by_10_big_decimal(b);
        (*scale_b)++;
    }
}

///////////////////////// арифметика (werlagad) /////////////////////////
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    // проверка что указатель не NULL
    if (!result) return 1;

    // проверка на знак
    int sign_value_1 = get_sign(value_1);
    // int sign_value_2 = get_sign(value_2);

    // if (sign_value_1 != sign_value_2) { // если знаки разные, то это вычитание
    //     if (sign_value_1 == 1) { // вычитаем отрицательное
    //         set_sign(&value_1, 0);
    //         return s21_sub(value_2, value_1, result);
    //     } else {
    //         set_sign(&value_2, 0);
    //         return s21_sub(value_1, value_2, result);
    //     }
    // }

    // преобразуем в big_decimal
    s21_big_decimal value_1_big, value_2_big, result_big;
    decimal_to_big(value_1, &value_1_big);
    decimal_to_big(value_2, &value_2_big);

    // нормализация scale
    int scale_value_1 = get_scale(value_1);
    int scale_value_2 = get_scale(value_2);
    normalize_big_decimals(&value_1_big, &scale_value_1, &value_2_big, &scale_value_2);

    // складываем побайтово в big_decimal
    add_big_decimal(&value_1_big, &value_2_big, &result_big);

    // преобразуем в decimal (используем банковское округление)
    return big_to_decimal(result_big, result, scale_value_1, sign_value_1);
}

// int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

// }

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

// }

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

// }

void add_big_decimal(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result) { // складываем две структуры
    unsigned memory = 0;
    for (int i = 0; i < 6; i++) {
        uint64_t sum = (uint64_t)a->bits[i] + b->bits[i] + memory; // складываем два uint32 + перенос
        result->bits[i] = (uint32_t)sum; // сохраняем младшие 32 бита результата
        memory = sum >> 32; // сохраняем перенос (старшие биты)
    }
}

void multiply_by_10_big_decimal(s21_big_decimal* num) { // x * 10 = x * 8 + x * 2 = x << 3 + x << 1
    s21_big_decimal temp1 = *num;
    s21_big_decimal temp2 = *num;

    for (int i = 0; i < 3; ++i) shift_left(&temp1); // temp1 = num << 3 (умножение на 8)
    shift_left(&temp2); // temp2 = num << 1 (умножение на 2)

    add_big_decimal(&temp1, &temp2, num); // num = temp1 + temp2
}

int divide_by_10_big_decimal(s21_big_decimal* value) { // деление на 10 для банковского округления
    uint64_t remainder = 0;

    for (int i = 5; i >= 0; i--) {
        uint64_t full = (remainder << 32) | value->bits[i]; // объединяем остаток и текущий блок
        value->bits[i] = (uint32_t)(full / 10); // записываем результат деления
        remainder = full % 10; // сохраняем остаток
    }

    return (int)remainder; // возвращаем остаток от всего деления
}

void add_1_to_big_decimal(s21_big_decimal* value) { // когда надо просто прибавить 1 создаем минимальный децимал и передаем его в функцию сложения
    s21_big_decimal one = {0};
    one.bits[0] = 1;
    add_big_decimal(value, &one, value);
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
