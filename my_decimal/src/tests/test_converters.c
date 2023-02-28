#include "test_core.h"

/*START_TEST(decimal_float_test_1) {
  float a = -12432414.2342342f;
  float result = 0.0f;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_float(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_float_eq(a, result);
}
END_TEST

START_TEST(decimal_float_test_2) {
  float a = 0.1234567f;
  float result;
  s21_decimal b;
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_float(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_float_eq(a, result);
}
END_TEST

START_TEST(decimal_float_test_3) {
  float a = SMALL_FLOAT_VALUE;
  float result = 0.0f;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_float(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_float_eq(a, result);
}
END_TEST

START_TEST(decimal_float_test_4) {
  float a = 0.00000000000000000000000000001f;
  float result = 0.0f;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
  code = s21_from_decimal_to_float(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_float_eq(0.0f, result);
}
END_TEST

START_TEST(decimal_float_test_5) {
  float a = -0.0000000f;
  float result = 0.0f;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_float(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_float_eq(a, result);
}
END_TEST

START_TEST(decimal_float_test_6) {
  float a = 0.0000000f;
  float result = 0.0f;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_float(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_float_eq(a, result);
}
END_TEST

#START_TEST(decimal_float_test_7) {
#    float a =  79228162514264337593543950336.0f;
#    s21_decimal b = {0};
#    int code = 0;
#    code = s21_from_float_to_decimal(a, &b);
#    ck_assert_int_eq(code, CONVERTATION_ERROR);
#} END_TEST
*/

/*START_TEST(decimal_float_test_8) {
  float a = 123456700000000000000.0f;
  float result = 0.0f;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_float(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_float_eq(a, result);
}
END_TEST

START_TEST(decimal_float_test_9) {
  float a = 123123.0f;
  s21_decimal *b = NULL;
  int code = 0;
  code = s21_from_float_to_decimal(a, b);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
}
END_TEST

START_TEST(decimal_float_test_10) {
  float a = 123.0f;
  float *result = NULL;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_float(b, result);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
}
END_TEST

START_TEST(decimal_float_test_11) {
  float a = 1.0 / 0.0;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
}
END_TEST

START_TEST(decimal_float_test_12) {
  float a = -1.0 / 0.0;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
}
END_TEST

START_TEST(decimal_float_test_13) {
  float a = 5.0f;
  int code = 0;
  code = s21_from_float_to_decimal(a, NULL);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
}
END_TEST

START_TEST(decimal_int_test_1) {
  int a = 50;
  int result = 0;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_int_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_int(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_int_eq(a, result);
}
END_TEST

START_TEST(decimal_int_test_2) {
  int a = 2147483647;
  int result = 0;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_int_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_int(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_int_eq(a, result);
}
END_TEST

START_TEST(decimal_int_test_3) {
  int a = -2147483648;
  int result = 0;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_int_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_int(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_int_eq(a, result);
}
END_TEST

START_TEST(decimal_int_test_4) {
  int a = 0;
  int result;
  s21_decimal b;
  int code = 0;
  code = s21_from_int_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_int(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_int_eq(a, result);
}
END_TEST

START_TEST(decimal_int_test_5) {
  float a = 123.123;
  int a1 = 123;
  int result = 0;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_int(b, &result);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  ck_assert_int_eq(a1, result);
}
END_TEST

START_TEST(decimal_int_test_6) {
  float a = 123131425462264624624.324f;
  int result = 0;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_int(b, &result);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
}
END_TEST

START_TEST(decimal_int_test_7) {
  int a = 24;
  s21_decimal *b = NULL;
  int code = 0;
  code = s21_from_int_to_decimal(a, b);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
}
END_TEST

START_TEST(decimal_int_test_8) {
  int a = 0;
  int *result = NULL;
  s21_decimal b = {0};
  int code = 0;
  code = s21_from_int_to_decimal(a, &b);
  ck_assert_int_eq(code, CONVERTATION_SUCCESS);
  code = s21_from_decimal_to_int(b, result);
  ck_assert_int_eq(code, CONVERTATION_ERROR);
}
END_TEST

Suite *st_converters(void) {
  Suite *s = suite_create("st_converters");
  TCase *tc = tcase_create("converters_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, decimal_float_test_1);
  tcase_add_test(tc, decimal_float_test_2);
  tcase_add_test(tc, decimal_float_test_3);
  tcase_add_test(tc, decimal_float_test_4);
  tcase_add_test(tc, decimal_float_test_5);
  tcase_add_test(tc, decimal_float_test_6);
  // tcase_add_test(tc, decimal_float_test_7);
  tcase_add_test(tc, decimal_float_test_8);
  tcase_add_test(tc, decimal_float_test_9);
  tcase_add_test(tc, decimal_float_test_10);
  tcase_add_test(tc, decimal_float_test_11);
  tcase_add_test(tc, decimal_float_test_12);
  tcase_add_test(tc, decimal_float_test_13);
  tcase_add_test(tc, decimal_int_test_1);
  tcase_add_test(tc, decimal_int_test_2);
  tcase_add_test(tc, decimal_int_test_3);
  tcase_add_test(tc, decimal_int_test_4);
  tcase_add_test(tc, decimal_int_test_5);
  tcase_add_test(tc, decimal_int_test_6);
  tcase_add_test(tc, decimal_int_test_7);
  tcase_add_test(tc, decimal_int_test_8);
  return s;
}*/
