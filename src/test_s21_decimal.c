#include <check.h>
#include "s21_decimal.h"

START_TEST(test_s21_add) {
    s21_decimal a = {{1, 0, 0, 0}};
    s21_decimal b = {{2, 0, 0, 0}};
    s21_decimal result, expected = {{3, 0, 0, 0}};
    ck_assert_int_eq(s21_add(a, b, &result), 0);
    ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub) {
    s21_decimal a = {{5, 0, 0, 0}};
    s21_decimal b = {{3, 0, 0, 0}};
    s21_decimal result, expected = {{2, 0, 0, 0}};
    ck_assert_int_eq(s21_sub(a, b, &result), 0);
    ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_is_equal) {
    s21_decimal a = {{5, 0, 0, 0}};
    s21_decimal b = {{5, 0, 0, 0}};
    ck_assert_int_eq(s21_is_equal(a, b), 1);

    s21_decimal c = {{6, 0, 0, 0}};
    ck_assert_int_eq(s21_is_equal(a, c), 0);
}
END_TEST

Suite *s21_decimal_suite(void) {
    Suite *s = suite_create("s21_decimal");

    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_s21_add);
    tcase_add_test(tc_core, test_s21_sub);
    tcase_add_test(tc_core, test_s21_is_equal);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s = s21_decimal_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
