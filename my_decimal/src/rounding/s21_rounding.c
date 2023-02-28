#include "s21_rounding.h"

// 0 - OK
// 1 - ошибка вычисления

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result) {
  memset(result, 0, sizeof(*result));
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal mod = {0};
  s21_mod1(value, &mod);
  s21_truncate(value, result);
  if (getSign(value) && s21_is_not_equal(mod, zero)) {
    binaryAddition(*result, one, result);
  }
  setSign(result, getSign(value));
  return 0;
}

// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result) {
  memset(result, 0, sizeof(*result));
  s21_decimal mod = {0};
  s21_decimal half = {{5, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  setExponent(&half, 1);
  s21_mod(value, one, &mod);
  setSign(&mod, 0);
  s21_truncate(value, result);
  if (s21_is_greater_or_equal(mod, half)) {
    binaryAddition(*result, one, result);
  }
  setSign(result, getSign(value));
  return 0;
}

// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result) {
  memset(result, 0, sizeof(*result));
  int sign = getSign(value);
  int exp = getExponent(value);
  s21_decimal ten = {{10, 0, 0, 0}};
  setSign(&value, 0);
  value.bits[3] = 0;
  if (!exp) {
    *result = value;
  } else {
    while (exp--) {
      int_div(value, ten, result);
      value = *result;
    }
  }
  setSign(result, sign);
  return 0;
}

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result) {
  int new_sign = !(getSign(value));
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  setSign(result, new_sign);
  return 0;
}
