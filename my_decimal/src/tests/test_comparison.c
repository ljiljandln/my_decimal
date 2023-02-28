#include "test_core.h"

START_TEST(test_is_less_true) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_equal) {
  s21_decimal c = {{0, 0, 1, 0}};
  s21_decimal d = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_less(c, d), 0);
}
END_TEST

START_TEST(test_is_less_exp) {
  s21_decimal e = {{1, 1, 1, 1}};
  s21_decimal f = {{1, 1, 1, 1}};
  setExponent(&e, 1);
  ck_assert_int_eq(s21_is_less(e, f), 1);
}
END_TEST

START_TEST(test_is_less_false) {
  s21_decimal g = {{0, 0, 1, 0}};
  s21_decimal h = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(g, h), 0);
}
END_TEST

START_TEST(test_is_less_all_zeroes) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_neg) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  setSign(&a, 1);
  setSign(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_first_neg) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  setSign(&a, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_second_neg) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  setSign(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_another_neg) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  setSign(&a, 1);
  setSign(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_or_equal) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  s21_decimal c = {{0, 0, 1, 0}};
  s21_decimal d = {{0, 0, 1, 0}};
  setExponent(&d, 9);
  ck_assert_int_eq(s21_is_less_or_equal(c, d), 0);

  s21_decimal e = {{0, 0, 0, 0}};
  s21_decimal f = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(e, f), 1);

  s21_decimal g = {{0, 0, 1, 0}};
  s21_decimal h = {{0, 0, 1, 0}};
  setSign(&h, 1);
  ck_assert_int_eq(s21_is_less_or_equal(g, h), 0);
}
END_TEST

START_TEST(test_is_greater_true) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_is_greater_equal) {
  s21_decimal c = {{0, 0, 1, 0}};
  s21_decimal d = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_greater(c, d), 0);
}
END_TEST

START_TEST(test_is_greater_exp) {
  s21_decimal e = {{1, 1, 1, 1}};
  s21_decimal f = {{1, 1, 1, 1}};
  setExponent(&f, 1);
  ck_assert_int_eq(s21_is_greater(e, f), 1);
}
END_TEST

START_TEST(test_is_greater_exp_2) {
  s21_decimal e = {{1, 1, 1, 1}};
  s21_decimal f = {{1, 1, 1, 1}};
  setExponent(&e, 1);
  ck_assert_int_eq(s21_is_greater(e, f), 0);
}
END_TEST

START_TEST(test_is_greater_false) {
  s21_decimal g = {{0, 0, 0, 0}};
  s21_decimal h = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_greater(g, h), 0);
}
END_TEST

START_TEST(test_is_greater_all_zeroes) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_neg) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  setSign(&a, 1);
  setSign(&b, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_is_greater_first_neg) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  setSign(&a, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_second_neg) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  setSign(&b, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_is_greater_another_neg) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  setSign(&a, 1);
  setSign(&b, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_or_equal) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);

  s21_decimal c = {{0, 0, 0, 0}};
  s21_decimal d = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(c, d), 1);

  s21_decimal e = {{0, 0, 1, 0}};
  s21_decimal f = {{0, 0, 1, 0}};
  setExponent(&e, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(e, f), 0);

  s21_decimal g = {{0, 0, 0, 0}};
  s21_decimal h = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(g, h), 0);
}
END_TEST

START_TEST(test_is_equal_exp) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  setExponent(&a, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_true) {
  s21_decimal c = {{0, 23, 0, 0}};
  s21_decimal d = {{0, 23, 0, 0}};
  ck_assert_int_eq(s21_is_equal(c, d), 1);
}
END_TEST

START_TEST(test_is_equal_false) {
  s21_decimal e = {{0, 0, 1, 0}};
  s21_decimal f = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(e, f), 0);
}
END_TEST

START_TEST(test_is_equal_neg_both) {
  s21_decimal g = {{0, 0, 1, 0}};
  s21_decimal h = {{0, 0, 1, 0}};
  setSign(&g, 1);
  setSign(&h, 1);
  ck_assert_int_eq(s21_is_equal(g, h), 1);
}
END_TEST

START_TEST(test_is_equal_all_zeroes) {
  s21_decimal g = {{0, 0, 0, 0}};
  s21_decimal h = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(g, h), 1);
}
END_TEST

START_TEST(test_is_equal_neg_one) {
  s21_decimal g = {{0, 0, 1, 0}};
  s21_decimal h = {{0, 0, 1, 0}};
  setSign(&g, 1);
  ck_assert_int_eq(s21_is_equal(g, h), 0);
}
END_TEST

START_TEST(test_is_equal_exp_both) {
  s21_decimal g = {{0, 0, 1, 0}};
  s21_decimal h = {{0, 0, 1, 0}};
  setExponent(&g, 1);
  setExponent(&h, 1);
  ck_assert_int_eq(s21_is_equal(g, h), 1);
}
END_TEST

START_TEST(test_is_not_equal) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  setExponent(&a, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);

  s21_decimal c = {{0, 23, 0, 0}};
  s21_decimal d = {{0, 23, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(c, d), 0);

  s21_decimal e = {{0, 0, 1, 0}};
  s21_decimal f = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(e, f), 1);

  s21_decimal g = {{0, 0, 0, 0}};
  s21_decimal h = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_not_equal(g, h), 1);
}
END_TEST

Suite *st_comparison(void) {
  Suite *s = suite_create("st_comparison");
  TCase *tc = tcase_create("arithmetic_tc");

  tcase_add_test(tc, test_is_less_true);
  tcase_add_test(tc, test_is_less_equal);
  tcase_add_test(tc, test_is_less_exp);
  tcase_add_test(tc, test_is_less_false);
  tcase_add_test(tc, test_is_less_all_zeroes);
  tcase_add_test(tc, test_is_less_neg);
  tcase_add_test(tc, test_is_less_first_neg);
  tcase_add_test(tc, test_is_less_second_neg);
  tcase_add_test(tc, test_is_less_another_neg);
  tcase_add_test(tc, test_is_less_or_equal);

  tcase_add_test(tc, test_is_greater_true);
  tcase_add_test(tc, test_is_greater_equal);
  tcase_add_test(tc, test_is_greater_exp);
  tcase_add_test(tc, test_is_greater_exp_2);
  tcase_add_test(tc, test_is_greater_false);
  tcase_add_test(tc, test_is_greater_all_zeroes);
  tcase_add_test(tc, test_is_greater_neg);
  tcase_add_test(tc, test_is_greater_first_neg);
  tcase_add_test(tc, test_is_greater_second_neg);
  tcase_add_test(tc, test_is_greater_another_neg);

  tcase_add_test(tc, test_is_greater_or_equal);
  tcase_add_test(tc, test_is_equal_exp);
  tcase_add_test(tc, test_is_equal_true);
  tcase_add_test(tc, test_is_equal_false);
  tcase_add_test(tc, test_is_equal_neg_both);
  tcase_add_test(tc, test_is_equal_all_zeroes);
  tcase_add_test(tc, test_is_equal_neg_one);
  tcase_add_test(tc, test_is_equal_exp_both);
  tcase_add_test(tc, test_is_not_equal);

  suite_add_tcase(s, tc);
  return s;
}