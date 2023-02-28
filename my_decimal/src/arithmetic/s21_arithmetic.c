#include "s21_arithmetic.h"

#include "s21_big_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearDecimal(result);
  int RESULT_CODE = SUCCESS;
  int sign_value1 = getSign(value_1);
  int sign_value2 = getSign(value_2);

  beforeCalculate(&value_1, &value_2);
  if (getExponent(value_1) != getExponent(value_2))
    s21_normalize_pair(&value_1, &value_2);

  if (sign_value1 == sign_value2) {  // if signs are equal - addition
    RESULT_CODE = binaryAddition(value_1, value_2, result);
    setSign(result, sign_value1);
    setExponent(result, getExponent(value_1));
    if (RESULT_CODE) clearDecimal(result);
  } else {  // signs are different - substractions
    if (sign_value1) {
      setSign(&value_1, POSITIVE);
      s21_sub(value_2, value_1, result);
    } else {
      setSign(&value_2, POSITIVE);
      s21_sub(value_1, value_2, result);
    }
  }

  if (!RESULT_CODE) {
    setSignAndExp(result);
    makeNormal(result);
  }

  return RESULT_CODE;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearDecimal(result);
  int RESULT_CODE = SUCCESS;
  int sign_value1 = getSign(value_1);
  int sign_value2 = !getSign(value_2);
  setSign(&value_2, sign_value2);

  beforeCalculate(&value_1, &value_2);
  if (getExponent(value_1) != getExponent(value_2))
    s21_normalize_pair(&value_1, &value_2);

  if (sign_value1 != sign_value2) {  // if signs are different - substraction
    if (s21_is_greater(getModule(value_1), getModule(value_2))) {
      binarySubstraction(value_1, value_2, result);
      setSign(result, sign_value1);
    } else if (s21_is_greater(getModule(value_2), getModule(value_1))) {
      binarySubstraction(value_2, value_1, result);
      setSign(result, sign_value2);
    } else {  // if values are equal substraction = 0
      clearDecimal(result);
    }
    setExponent(result, getExponent(value_1));
  } else {  // signs equal - addition
    RESULT_CODE = s21_add(value_1, value_2, result);
    if (RESULT_CODE) clearDecimal(result);
  }

  if (!RESULT_CODE) {
    setSignAndExp(result);
    makeNormal(result);
  }

  return RESULT_CODE;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) { 
  int RESULT_CODE = 0;
  clearDecimal(result);

  beforeCalculate(&value_1, &value_2);
  s21_big_decimal value1_big = from_decimal_to_big_decimal(value_1);
  s21_big_decimal value2_big = from_decimal_to_big_decimal(value_2);
  s21_big_decimal result_big = {0};

  binaryMultiplicationBig(value1_big, value2_big, &result_big);
  signHandlerBig(value1_big, value2_big, &result_big);
  setExponentBig(&result_big, getExponent(value_1) + getExponent(value_2));
  setSignAndExpBig(&result_big);
  makeNormalBig(&result_big);

  RESULT_CODE = from_big_decimal_to_decimal(result_big, result, 0);
  return RESULT_CODE;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearDecimal(result);
  int RESULT_CODE = SUCCESS;

  if (isEqualZero(value_2)) {
    RESULT_CODE = S21_NAN;
  } else {
    beforeCalculate(&value_1, &value_2);
    if (isEqualUnit(value_2)) {
      *result = value_1;
      signHandler(value_1, value_2, result);
      setExponent(result, 0);
      expHandler(value_1, value_2, result);
    } else if (s21_is_equal(value_1, value_2)) {
      setBit(result, 0, 1);
    } else {
      s21_big_decimal value1_big = from_decimal_to_big_decimal(value_1);
      s21_big_decimal value2_big = from_decimal_to_big_decimal(value_2);
      s21_big_decimal result_big = {0};

      my_div(value1_big, value2_big, &result_big);
      signHandlerBig(value1_big, value2_big, &result_big);
      int exp = getExponent(value_1) - getExponent(value_2);
      RESULT_CODE = from_big_decimal_to_decimal(result_big, result, (exp > 0) ? 28 - exp : 0);
      if (!RESULT_CODE) {
        RESULT_CODE = expHandler(value_1, value_2, result);
        if (!RESULT_CODE) setSignAndExp(result);
      }
    }
  }
  return RESULT_CODE;
}

void s21_mod1(s21_decimal value, s21_decimal *result) {
  clearDecimal(result);

  s21_decimal mult = {{1, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};

  for (int i = getExponent(value); i > 0; i--) {
    binaryMultiplication(mult, ten, &mult);
  }

  *result = int_div(value, mult, &ten);
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearDecimal(result);
  int RESULT_CODE = SUCCESS;

  if (isEqualZero(value_2)) {
    RESULT_CODE = S21_NAN; // или S21_NAN
  } else {
    beforeCalculate(&value_1, &value_2);
    int sign = getSign(value_1);
    setSign(&value_1, 0);
    setSign(&value_2, 0);

    if (s21_is_less(value_1, value_2)) {
      *result = value_1;
      setSign(result, sign);
    } else if (s21_is_not_equal(value_1, value_2)) {
      s21_big_decimal value1_big = from_decimal_to_big_decimal(value_1);
      s21_big_decimal value2_big = from_decimal_to_big_decimal(value_2);
      s21_big_decimal result_big = {0};

      my_div(value1_big, value2_big, &result_big);
      expHandlerBig(value_1, value_2, &result_big);
      
      if (!isEqualZeroBig(result_big)) {
        s21_truncate_big(result_big, &result_big);
        binaryMultiplicationBig(value2_big, result_big, &result_big);
        setExponentBig(&result_big, getExponentBig(value2_big));
        s21_normalize(&value1_big, &result_big);
        binarySubstractionBig(value1_big, result_big, &result_big);
        if (isEqualZeroBig(result_big)) setExponentBig(&result_big, 0);
        from_big_decimal_to_decimal(result_big, result, 0);
        if (!isEqualZero(*result)) setSign(result, sign);
      }
    }
  }

  return RESULT_CODE;
}
