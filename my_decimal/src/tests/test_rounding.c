#include "test_core.h"

START_TEST(test_negate) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  s21_decimal c = {{1, 1, 1, 0}};
  s21_negate(a, &c);
  setSign(&b, 1);
  ck_assert_int_eq(s21_is_equal(c, b), 1);
}
END_TEST

START_TEST(test_negate_neg) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  s21_decimal c = {{1, 1, 1, 0}};
  setSign(&a, 1);
  s21_negate(a, &c);
  ck_assert_int_eq(s21_is_equal(c, b), 1);
}
END_TEST

START_TEST(test_truncate) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{105, 0, 0, 0}};
  s21_decimal res = {0};
  setExponent(&b, 1);
  s21_truncate(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{1055, 0, 0, 0}};
  s21_decimal res = {0};
  setExponent(&b, 2);
  s21_truncate(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_truncate_no_exp) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  s21_decimal res = {0};
  s21_truncate(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_floor) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{15, 0, 0, 0}};
  s21_decimal res = {0};
  setExponent(&b, 1);
  s21_floor(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_floor_neg) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{15, 0, 0, 0}};
  s21_decimal res = {0};
  setSign(&a, 1);
  setSign(&b, 1);
  setExponent(&b, 1);
  s21_floor(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_floor_neg_zero) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{20, 0, 0, 0}};
  s21_decimal res = {0};
  setSign(&a, 1);
  setSign(&b, 1);
  setExponent(&b, 1);
  s21_floor(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_round) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{14, 0, 0, 0}};
  s21_decimal res = {0};
  setExponent(&b, 1);
  s21_round(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_round_2) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{19, 0, 0, 0}};
  s21_decimal res = {0};
  setExponent(&b, 1);
  s21_round(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_round_neg) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{19, 0, 0, 0}};
  s21_decimal res = {0};
  setSign(&a, 1);
  setSign(&b, 1);
  setExponent(&b, 1);
  s21_round(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_round_neg_2) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{14, 0, 0, 0}};
  s21_decimal res = {0};
  setSign(&a, 1);
  setSign(&b, 1);
  setExponent(&b, 1);
  s21_round(b, &res);
  ck_assert_int_eq(s21_is_equal(a, res), 1);
}
END_TEST

START_TEST(test_bank) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{15, 0, 0, 0}};
  setExponent(&b, 1);
  s21_bank_rounding(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_bank_2) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{24, 0, 0, 0}};
  setExponent(&b, 1);
  s21_bank_rounding(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

Suite *st_rounding(void) {
  Suite *s = suite_create("st_rounding");
  TCase *tc = tcase_create("rounding_tc");

  tcase_add_test(tc, test_truncate);
  tcase_add_test(tc, test_truncate_2);
  tcase_add_test(tc, test_truncate_no_exp);
  tcase_add_test(tc, test_floor);
  tcase_add_test(tc, test_floor_neg);
  tcase_add_test(tc, test_floor_neg_zero);
  tcase_add_test(tc, test_round);
  tcase_add_test(tc, test_round_2);
  tcase_add_test(tc, test_round_neg);
  tcase_add_test(tc, test_round_neg_2);
  tcase_add_test(tc, test_negate);
  tcase_add_test(tc, test_negate_neg);
  tcase_add_test(tc, test_bank);
  tcase_add_test(tc, test_bank_2);

  suite_add_tcase(s, tc);
  return s;
}