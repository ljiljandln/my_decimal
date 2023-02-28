#include "s21_comparison.h"

// возвращает 1, если первый децимал меньше второго
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int is_less = 0;
  if (isEqualZero(value_1) && isEqualZero(value_2)) {
    is_less = 0;
  } else {
    if (getSign(value_1) && !getSign(value_2)) {
      is_less = 1;
    } else if (!getSign(value_1) && getSign(value_2)) {
      is_less = 0;
    } else {
      s21_normalize_pair(&value_1, &value_2);
      for (int i = 95; i >= 0; i--) {
        if (getBit(value_1, i) && !getBit(value_2, i)) {
          if (getSign(value_1)) {
            is_less = 1;
            break;
          } else {
            is_less = 0;
            break;
          }
        } else if (!getBit(value_1, i) && getBit(value_2, i)) {
          if (getSign(value_1)) {
            is_less = 0;
            break;
          } else {
            is_less = 1;
            break;
          }
        }
      }
    }
  }
  return is_less;
}

// возвращает 1, если первый децимал меньше или равен второму
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

// возвращает 1, если первый децимал больше второго
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_2, value_1);
}

// возвращает 1, если первый децимал больше или равен второму
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

// возвращает 1, если первый децимал равен второму
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return value_1.bits[0] == value_2.bits[0] &&
         value_1.bits[1] == value_2.bits[1] &&
         value_1.bits[2] == value_2.bits[2] &&
         value_1.bits[3] == value_2.bits[3];
}

// возвращает 1, если первый децимал не равен второму
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
