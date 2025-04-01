#include "../main.h"

int is_zero(s21_decimal num) { // проверяем, что все три части мантиссы равны 0
    return num.bits[0] == 0 && num.bits[1] == 0 && num.bits[2] == 0;
}