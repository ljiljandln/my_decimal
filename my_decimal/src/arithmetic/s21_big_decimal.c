#include "s21_big_decimal.h"

s21_big_decimal from_decimal_to_big_decimal(s21_decimal value) {
  s21_big_decimal result = {0};
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value.bits[i];
  }
  result.bits[6] = value.bits[3];
  return result;
}

int getBitBig(s21_big_decimal value, int position) {
  return (value.bits[position / 32] >> (position % 32)) & 1;
}
int getSignBig(s21_big_decimal value) { return (value.bits[6] >> 31) & 1U; }

int getExponentBig(s21_big_decimal value) {
  int exponent = 0;
  for (int expPos = EXP_START, shift = 0; expPos <= EXP_END;
       expPos++, shift++) {
    if ((value.bits[6] >> expPos) & 1U) {
      exponent |= (1U << shift);
    }
  }
  return exponent;
}

void setSignBig(s21_big_decimal *value, int sign) {
  if (sign) {
    value->bits[6] |= (1U << 31);
  } else {
    value->bits[6] &= ~(1UL << 31);
  }
}
void setBitBig(s21_big_decimal *value, int position, int bit) {
  if (bit) {
    value->bits[position / 32] |= (1U << (position % 32));
  } else {
    value->bits[position / 32] &= ~(1UL << (position % 32));
  }
}
void setExponentBig(s21_big_decimal *value, int exponent) {
  if (exponent >= EXP_MIN && exponent <= EXP_MAX_B) {
    int sign = getSignBig(*value);
    value->bits[6] = 0;
    value->bits[6] |= (exponent << EXP_START);
    setSignBig(value, sign);
  }
}

int isEqualZeroBig(s21_big_decimal value) {
  return !value.bits[0] && !value.bits[1] && !value.bits[2] && !value.bits[3] &&
         !value.bits[4] && !value.bits[5];
}
int isEqualZeroAllBig(s21_big_decimal value) {
  return isEqualZeroBig(value) && !value.bits[6];
}

// shifts
int shiftLeftBig(s21_big_decimal *value) {
  int lastBit0 = getBitBig(*value, LAST_BIT0);
  int lastBit1 = getBitBig(*value, LAST_BIT1);
  int lastBit2 = getBitBig(*value, LAST_BIT2);
  int lastBit3 = getBitBig(*value, LAST_BIT3);
  int lastBit4 = getBitBig(*value, LAST_BIT4);
  int lastBit5 = getBitBig(*value, LAST_BIT5);

  for (int i = 0; i < 6; i++) {
    value->bits[i] <<= 1;
  }
  setBitBig(value, LAST_BIT0 + 1, lastBit0);
  setBitBig(value, LAST_BIT1 + 1, lastBit1);
  setBitBig(value, LAST_BIT2 + 1, lastBit2);
  setBitBig(value, LAST_BIT3 + 1, lastBit3);
  setBitBig(value, LAST_BIT4 + 1, lastBit4);

  return lastBit5;  // 1 == overflow; 0 == !overflow
}
void shiftLeftAllBig(s21_big_decimal *value) {
  value->bits[6] <<= 1;
  setBitBig(value, LAST_BIT5 + 1, shiftLeftBig(value));
}
void shiftRightBig(s21_big_decimal *value) {
  int firstBit1 = getBitBig(*value, LAST_BIT0 + 1);
  int firstBit2 = getBitBig(*value, LAST_BIT1 + 1);
  int firstBit3 = getBitBig(*value, LAST_BIT2 + 1);
  int firstBit4 = getBitBig(*value, LAST_BIT3 + 1);
  int firstBit5 = getBitBig(*value, LAST_BIT4 + 1);

  for (int i = 6; i >= 0; i--) {
    value->bits[i] >>= 1;
  }
  setBitBig(value, LAST_BIT5, 0);
  setBitBig(value, LAST_BIT4, firstBit5);
  setBitBig(value, LAST_BIT3, firstBit4);
  setBitBig(value, LAST_BIT2, firstBit3);
  setBitBig(value, LAST_BIT1, firstBit2);
  setBitBig(value, LAST_BIT0, firstBit1);
}

// bit logic
s21_big_decimal binaryXorBig(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_big_decimal result = {0};
  for (int i = 0; i < 6; i++) {
    result.bits[i] = value_1.bits[i] ^ value_2.bits[i];
  }
  return result;
}
s21_big_decimal binaryXorAllBig(s21_big_decimal value_1,
                                s21_big_decimal value_2) {
  s21_big_decimal result = binaryXorBig(value_1, value_2);
  result.bits[6] = value_1.bits[6] ^ value_2.bits[6];
  return result;
}
s21_big_decimal binaryAndBig(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_big_decimal result = {0};
  for (int i = 0; i < 6; i++) {
    result.bits[i] = value_1.bits[i] & value_2.bits[i];
  }
  return result;
}
s21_big_decimal binaryAndAllBig(s21_big_decimal value_1,
                                s21_big_decimal value_2) {
  s21_big_decimal result = binaryAndBig(value_1, value_2);
  result.bits[6] = value_1.bits[6] & value_2.bits[6];
  return result;
}
s21_big_decimal binaryNotBig(s21_big_decimal value) {
  s21_big_decimal result = {0};
  for (int i = 0; i < 6; i++) {
    result.bits[i] = ~value.bits[i];
  }
  return result;
}

int binaryAdditionBig(s21_big_decimal value_1, s21_big_decimal value_2,
                      s21_big_decimal *result) {
  int RESULT_CODE = 0;
  while (!isEqualZeroBig(value_2) && !RESULT_CODE) {
    s21_big_decimal temp = binaryAndBig(value_1, value_2);
    value_1 = binaryXorBig(value_1, value_2);
    RESULT_CODE = shiftLeftBig(&temp);
    value_2 = temp;
  }

  *result = value_1;

  return RESULT_CODE;
}
void binarySubstractionBig(s21_big_decimal value_1, s21_big_decimal value_2,
                           s21_big_decimal *result) {
  s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal negative_value_2 = {0};
  binaryAdditionBig(binaryNotBig(value_2), one, &negative_value_2);

  while (!isEqualZeroAllBig(negative_value_2)) {
    s21_big_decimal temp = binaryAndAllBig(value_1, negative_value_2);
    value_1 = binaryXorAllBig(value_1, negative_value_2);
    shiftLeftAllBig(&temp);
    negative_value_2 = temp;
  }
  setBitBig(&value_1, LAST_BIT5 + 1, 0);
  *result = value_1;
}
int binaryMultiplicationBig(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result) {
  int RESULT_CODE = 0;
  s21_big_decimal tmp = {0};

  while (!isEqualZeroBig(value_2) && !RESULT_CODE) {
    if (getBitBig(value_2, 0)) {
      RESULT_CODE = binaryAdditionBig(value_1, tmp, &tmp);
      if (RESULT_CODE) break;
    }
    RESULT_CODE = shiftLeftBig(&value_1);
    shiftRightBig(&value_2);
  }
  *result = tmp;

  return RESULT_CODE;
}

void setSignAndExpBig(s21_big_decimal *value) {
  if (isEqualZeroBig(*value)) {
    setSignBig(value, 0);
    setExponentBig(value, 0);
  }
}

int isLessWithoutExpBig(s21_big_decimal value_1, s21_big_decimal value_2) {
  int RESULT_CODE = 0;
  int bit_value1 = 0;
  int bit_value2 = 0;

  for (int i = LAST_BIT5; i != -1; i--) {
    bit_value1 = getBitBig(value_1, i);
    bit_value2 = getBitBig(value_2, i);
    if (bit_value1 > bit_value2) {
      RESULT_CODE = 0;
      break;
    } else if (bit_value1 < bit_value2) {
      RESULT_CODE = 1;
      break;
    }
  }

  return RESULT_CODE;
}

int isOnlyZeroStayBig(s21_big_decimal value, int i) {
  int is_all_zero = 1;
  while (i >= 0) {
    if (getBitBig(value, i)) {
      is_all_zero = 0;
      break;
    }
    i--;
  }
  return is_all_zero;
}

void clearDecimalBig(s21_big_decimal *value) {
  for (int i = 0; i <= 6; i++) {
    value->bits[i] = 0;
  }
}

s21_big_decimal int_div_big(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result) {
  clearDecimalBig(result);
  int i = LAST_BIT5;
  while (!getBitBig(value_1, i) && i > 0) {
    i--;
  }
  s21_big_decimal tmp = {{getBitBig(value_1, i), 0, 0, 0, 0, 0, 0}};

  while (i > 0) {
    while (isLessWithoutExpBig(tmp, value_2) && i-- > 0) {
      shiftLeftBig(&tmp);
      setBitBig(&tmp, 0, getBitBig(value_1, i));
      shiftLeftBig(result);
    }

    if (i != -1) {
      binarySubstractionBig(tmp, value_2, &tmp);
      setBitBig(result, 0, 1);
      if (isEqualZeroBig(tmp) && isOnlyZeroStayBig(value_1, i - 1)) {
        for (int j = i - 1; j >= 0; j--) shiftLeftBig(result);
        break;
      }
    }
  }
  return tmp;  // remainder
}

int isEqualNumberBig(s21_big_decimal value, unsigned int number) {
  return value.bits[0] == (int)number && !value.bits[1] && !value.bits[2] &&
         !value.bits[3] && !value.bits[4] && !value.bits[5];
}

void roundingBig(s21_big_decimal *value, s21_big_decimal remainder) {
  s21_big_decimal five = {{5, 0, 0, 0, 0, 0, 0}}, one = {{1, 0, 0, 0, 0, 0, 0}};
  if (isLessWithoutExpBig(five, remainder)) {
    binaryAdditionBig(*value, one, value);
  } else if (isEqualNumberBig(remainder, 5) && getBitBig(*value, 0)) {
    binaryAdditionBig(*value, one, value);
  }
}

void div_10(s21_big_decimal *value) {
  int exp = getExponentBig(*value), sign = getSignBig(*value);
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal remainder = int_div_big(*value, ten, value);
  roundingBig(value, remainder);
  setExponentBig(value, exp - 1);
  setSignBig(value, sign);
}

void makeNormalBig(s21_big_decimal *value) {
  int exp = getExponentBig(*value);
  int sign = getSignBig(*value);
  if (exp && !getBitBig(*value, 0)) {
    s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}}, tmp_res = {0};
    while (isEqualZeroBig(int_div_big(*value, ten, &tmp_res)) && exp > 0) {
      exp--;
      *value = tmp_res;
    }
    setExponentBig(value, exp);
    setSignBig(value, sign);
  }
}

void my_div(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result) {
  s21_big_decimal tmp =
      int_div_big(value_1, value_2, result);
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};

  if (!isEqualZeroBig(tmp)) {
    int exp = 0;
    int code = {SUCCESS}, code1 = code, code2 = code;
    s21_big_decimal tmp_res = *result;

    while (!isEqualZeroBig(tmp) && exp < 56 && !code && !code1 && !code2) {
      int counter = 0;
      while (isLessWithoutExpBig(tmp, value_2) && exp < 56 && !code && !code1) {
        code = binaryMultiplicationBig(tmp, ten, &tmp);
        exp++;
        counter++;
        code1 = binaryMultiplicationBig(tmp_res, ten, &tmp_res);
      }
      s21_big_decimal r = {0};
      tmp = int_div_big(tmp, value_2, &r);
      code2 = binaryAdditionBig(tmp_res, r, &tmp_res);
      if (code || code1 || code2) {
        exp -= counter;
        break;
      } else
        *result = tmp_res;
    }

    setExponentBig(result, exp);
  }
}

int from_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result,
                                int exp) {
  int RESULT_CODE = 0;
  if (value.bits[3] || value.bits[4] || value.bits[5]) {
    if (!exp) {
      while ((value.bits[3] || value.bits[4] || value.bits[5]) &&
             getExponentBig(value)) {
        div_10(&value);
      }
    } else {
      while ((value.bits[3] || value.bits[4] || value.bits[5]) ||
             getExponentBig(value) > exp) {
        div_10(&value);
      }
    }
  }
  if (value.bits[3] || value.bits[4] || value.bits[5]) {
    RESULT_CODE = getSignBig(value) ? 2 : 1;
    clearDecimalBig(&value);
  } else if (getExponentBig(value) > 28) {
    while (getExponentBig(value) > 28) {
      div_10(&value);
      if (isEqualZeroBig(value)) {
        RESULT_CODE = 3;
        clearDecimalBig(&value);
        break;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    result->bits[i] = value.bits[i];
  }
  result->bits[3] = value.bits[6];
  return RESULT_CODE;
}

void signHandlerBig(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
  if (getSignBig(value_1) != getSignBig(value_2)) {
    setSignBig(result, 1);
  } else {
    setSignBig(result, 0);
  }
}

void expHandlerBig(s21_decimal value_1, s21_decimal value_2,
                   s21_big_decimal *result) {
  int new_exponent =
      getExponent(value_1) + getExponentBig(*result) - getExponent(value_2);
  setExponentBig(result, (new_exponent >= 0) ? new_exponent : 0);

  if (new_exponent < 0) {
    new_exponent = -new_exponent;
    s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
    while (new_exponent--) {
      binaryMultiplicationBig(*result, ten, result);
    }
  }
}

int s21_truncate_big(s21_big_decimal value, s21_big_decimal *result) {
  memset(result, 0, sizeof(*result));
  int res = 0;
  int sign = getSignBig(value);
  setSignBig(&value, 0);
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  int exp = getExponentBig(value);
  value.bits[6] = 0;
  if (!exp) {
    *result = value;
  } else {
    while (exp--) {
      int_div_big(value, ten, result);
      value = *result;
    }
  }
  setSignBig(result, sign);
  return res;
}

void s21_normalize(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  int RESULT_CODE = SUCCESS;

  int e1 = getExponentBig(*value_1), e2 = getExponentBig(*value_2);
  int min_exp = e1 < e2 ? e1 : e2;
  int max_exp = e1 > e2 ? e1 : e2;

  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal max_value = (e1 < e2) ? *value_1 : *value_2;
  s21_big_decimal min_value = (e1 < e2) ? *value_2 : *value_1;

  while (min_exp != max_exp && !RESULT_CODE) {
    s21_big_decimal tmp = {{0}};
    RESULT_CODE = binaryMultiplicationBig(max_value, ten, &tmp);
    if (!RESULT_CODE) {
      min_exp++;
      max_value = tmp;
    }
  }
  setExponentBig(&max_value, min_exp);
  
  while (max_exp != min_exp) {
    s21_big_decimal tmp = {0};
    s21_big_decimal remainder = int_div_big(min_value, ten, &tmp);
    min_value = tmp;
    roundingBig(&min_value, remainder);
    max_exp--;
  }
  setExponentBig(&min_value, max_exp);

  if (e1 < e2) {
    *value_1 = max_value;
    *value_2 = min_value;
  }
  else {
    *value_2 = max_value;
    *value_1 = min_value;
  }
}