#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t bits[4];
} s21_decimal;

typedef struct {
    uint32_t bits[6];
} s21_big_decimal;

////////////////// вспомогательные функции (werlagad) /////////////////
int is_zero(s21_decimal num);
int is_zero_big_decimal(s21_big_decimal num);
void null_big_decimal(s21_big_decimal* num);
void null_decimal(s21_decimal* num);

int get_sign(s21_decimal num);
void set_sign(s21_decimal* num, int sign_value);

int get_scale(s21_decimal num);
void set_scale(s21_decimal* num, int scale_value);

int get_bit(s21_decimal num, int bit);
int get_bit_big_decimal(s21_big_decimal num, int bit);
void set_bit(s21_decimal* num, int bit, unsigned value);
void set_bit_big_decimal(s21_big_decimal* num, int bit, unsigned value);

void decimal_to_big(s21_decimal src, s21_big_decimal* dest);
int big_to_decimal(s21_big_decimal src, s21_decimal* dest, int scale, int sign);
void shift_left(s21_big_decimal* num);
void round_bank(s21_big_decimal* value, int* scale);
void normalize_big_decimals(s21_big_decimal* a, int* scale_a, s21_big_decimal* b, int* scale_b);

///////////////////////// арифметика (werlagad) /////////////////////////
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

void add_big_decimal(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result);
void subtract_big_decimal(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result);
void multiply_big_decimals(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result);
void multiply_by_10_big_decimal(s21_big_decimal* num);
int divide_big_decimal(s21_big_decimal* a, s21_big_decimal* b, s21_big_decimal* result, s21_big_decimal* remainder);
int divide_by_10_big_decimal(s21_big_decimal* value);
void add_1_to_big_decimal(s21_big_decimal* value);

///////////////////////// сравнения (werlagad) /////////////////////////
int s21_compare(s21_decimal a, s21_decimal b);
int compare_big_decimal(s21_big_decimal *a, s21_big_decimal *b);

int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);

#endif
