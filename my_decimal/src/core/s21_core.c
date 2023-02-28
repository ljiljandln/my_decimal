#include "s21_core.h"

#include "../arithmetic/s21_arithmetic.h"

int getBit(s21_decimal value, int position) {
  return (value.bits[position / 32] >> (position % 32)) & 1;
}
int getSign(s21_decimal value) { return (value.bits[3] >> 31) & 1U; }
int getExponent(s21_decimal value) {
  int exponent = 0;

  for (int expPos = EXP_START, shift = 0; expPos <= EXP_END;
       expPos++, shift++) {
    if ((value.bits[3] >> expPos) & 1U) {
      exponent |= (1U << shift);
    }
  }

  return exponent;
}
s21_decimal getModule(s21_decimal value) {
  s21_decimal result = value;
  setSign(&result, POSITIVE);
  return result;
}
void getBitsFromFloat(char *bits, int *exponent, long double result) {
  long double result2 = result;
  int k = 0;
  *exponent = 0;
  while (result >= 1.) {
    result /= 10.;
    result2 /= 10.;
    (*exponent)--;
  }

  while (getDoubleExponent(result) != 7 && *exponent <= 27) {
    result *= 10;
    result2 *= 10;
    k = (int)result2;
    result2 -= 1.0 * k;
    (*exponent)++;
  }

  if (getDoubleExponent(result) == 7) {
    result2 *= 10;
    k = (int)result2;
    if (k >= 5) result++;
  }

  while (*exponent < 0) {
    result *= 10;
    (*exponent)++;
  }

  for (int i = 0; result > 0.0; i++) {
    result = floorl(result) / 2.;
    if (result - floorl(result) > 0.0) {
      bits[i] = '1';
    } else {
      bits[i] = '0';
    }
  }
}

int getDoubleExponent(long double value) {
  int exponent = 0;

  while (value >= 1) {
    value /= 10;
    exponent++;
  }
  return exponent;
}

int getFloatExponent(float value) {
  int exponent = 0;

  while (value >= 1) {
    value /= 10;
    exponent++;
  }

  return !exponent ? EXP_MAX : EXP_MAX + 1 - exponent;
}

void setSign(s21_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= (1U << 31);
  } else {
    value->bits[3] &= ~(1UL << 31);
  }
}
void setBit(s21_decimal *value, int position, int bit) {
  if (bit) {
    value->bits[position / 32] |= (1U << (position % 32));
  } else {
    value->bits[position / 32] &= ~(1UL << (position % 32));
  }
}
void setExponent(s21_decimal *value, int exponent) {
  if (exponent >= EXP_MIN && exponent <= EXP_MAX) {
    int sign = getSign(*value);
    value->bits[3] = 0;
    value->bits[3] |= (exponent << EXP_START);
    setSign(value, sign);
  }
}
void setSignAndExp(s21_decimal *value) {
  if (isEqualZero(*value)) {
    setSign(value, POSITIVE);
    setExponent(value, 0);
  }
}
void setBitsFromFloatToDecimal(char *bits, s21_decimal *result) {
  for (int i = strlen(bits) - 1; i != -1; i--) {
    setBit(result, i, bits[i] - 48);
  }
}

void makeNormal(s21_decimal *value) {
  int sign = getSign(*value);
  int exp = getExponent(*value);
  if (exp && !getBit(*value, 0)) {
    s21_decimal ten = {{10, 0, 0, 0}}, tmp_res = {0};
    while (isEqualZero(int_div(*value, ten, &tmp_res)) && exp > 0) {
      exp--;
      *value = tmp_res;
    }
    setExponent(value, exp);
    setSign(value, sign);
  }
}

void beforeCalculate(s21_decimal *value_1, s21_decimal *value_2) {
  setSignAndExp(value_1);
  setSignAndExp(value_2);
  makeNormal(value_1);
  makeNormal(value_2);
}

void printDecimal(s21_decimal value) {
  printf("decimal: ");
  for (int i = 95; i != -1; i--) {
    printf("%d", getBit(value, i));
    if (i == 64 || i == 32) printf(" ");
  }
  printf("\texponent: ");
  for (int i = 31; i != -1; i--) {
    printf("%d", (value.bits[3] >> i % 32) & 1);
  }
  printf("\n");
  printf("int_exponent = %d, int_sign = %d\n\n", getExponent(value),
         getSign(value));
}
void clearDecimal(s21_decimal *value) {
  for (int i = 0; i <= 3; i++) {
    value->bits[i] = 0;
  }
}

int isEqualZero(s21_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}
int isEqualZeroAll(s21_decimal value) {
  return isEqualZero(value) && value.bits[3] == 0;
}
int isLessWithoutExp(s21_decimal value_1, s21_decimal value_2) {
  int RESULT_CODE = 0;
  int bit_value1 = 0;
  int bit_value2 = 0;

  for (int i = LAST_BIT2; i != -1; i--) {
    bit_value1 = getBit(value_1, i);
    bit_value2 = getBit(value_2, i);
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
int isEqualUnit(s21_decimal value) {
  return value.bits[0] == 1 && value.bits[1] == 0 && value.bits[2] == 0;
}
int isOnlyZeroStay(s21_decimal value, int i) {
  int is_all_zero = 1;
  while (i >= 0) {
    if (getBit(value, i)) {
      is_all_zero = 0;
      break;
    }
    i--;
  }
  return is_all_zero;
}
int isEqualNumber(s21_decimal value, unsigned int number) {
  return value.bits[0] == (int)number && value.bits[1] == 0 &&
         value.bits[2] == 0;
}

int s21_from_lld_to_decimal(long long int src, s21_decimal *dst) {
  int RESULT_CODE = CONVERTATION_SUCCESS;

  if (!dst) {
    RESULT_CODE = CONVERTATION_ERROR;
  } else {
    setSign(dst, (src < 0) ? 1 : 0);
    src = llabs(src);
    for (int i = 0; src; i++, src /= 2) {
      setBit(dst, i, src % 2);
    }
  }

  return RESULT_CODE;
}

int s21_from_decimal_to_long_double(s21_decimal src, long double *dst_d) {
  int RESULT_CODE = CONVERTATION_SUCCESS;
  int exp = getExponent(src);
  int sign = getSign(src);
  for (int i = 0; i < 95; i++) {
    *dst_d += getBit(src, i) * powl(2.0, i);
  }
  for (int i = 0; i < exp; i++) {
    *dst_d /= 10.;
  }
  if (sign == 1) {
    *dst_d *= -1.0;
  }

  return RESULT_CODE;
}

void s21_bank_rounding(s21_decimal *value, int n) {
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal hundred = {{100, 0, 0, 0}};
  int sign = getSign(*value);
  int exp = getExponent(*value);
  setSign(value, 0);
  while (n > 0) {
    s21_decimal mod = {0};
    s21_mod(*value, hundred, &mod);
    int m = (127 & mod.bits[0]);
    int_div(*value, ten, value);
    setExponent(value, exp - 1);
    if (bank_check(m)) {
      s21_decimal tmp = *value;
      binaryAddition(tmp, one, value);
      setExponent(value, exp - 1);
    }
    n--;
  }
  setSign(value, sign);
}
int bank_check(int n) {
  int res = 0;
  int mod = n % 10;
  int odd = (n / 10) % 2;
  if (mod > 5 || (mod == 5 && odd)) {
    res = 1;
  }
  return res;
}

// bit logic
s21_decimal binaryXor(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = {0};
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value_1.bits[i] ^ value_2.bits[i];
  }
  return result;
}
s21_decimal binaryXorAll(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = binaryXor(value_1, value_2);
  result.bits[3] = value_1.bits[3] ^ value_2.bits[3];
  return result;
}
s21_decimal binaryAnd(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = {0};
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value_1.bits[i] & value_2.bits[i];
  }
  return result;
}
s21_decimal binaryAndAll(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = binaryAnd(value_1, value_2);
  result.bits[3] = value_1.bits[3] & value_2.bits[3];
  return result;
}
s21_decimal binaryNot(s21_decimal value) {
  s21_decimal result = {0};
  for (int i = 0; i < 3; i++) {
    result.bits[i] = ~value.bits[i];
  }
  return result;
}

void rounding(s21_decimal *value, s21_decimal remainder) {
  s21_decimal five = {{5, 0, 0, 0}}, one = {{1, 0, 0, 0}};
  if (isLessWithoutExp(five, remainder)) {
    binaryAddition(*value, one, value);
  } else if (isEqualNumber(remainder, 5) && getBit(*value, 0)) {
    binaryAddition(*value, one, value);
  }
}

void s21_normalize_pair(s21_decimal *value_1, s21_decimal *value_2) {
  int RESULT_CODE = SUCCESS;

  int e1 = getExponent(*value_1), e2 = getExponent(*value_2);
  int min_exp = e1 < e2 ? e1 : e2;
  int max_exp = e1 > e2 ? e1 : e2;

  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal max_value = (e1 < e2) ? *value_1 : *value_2;
  s21_decimal min_value = (e1 < e2) ? *value_2 : *value_1;

  while (min_exp != max_exp && !RESULT_CODE) {
    s21_decimal tmp = {{0}};
    RESULT_CODE = binaryMultiplication(max_value, ten, &tmp);
    if (!RESULT_CODE) {
      min_exp++;
      max_value = tmp;
    }
  }
  setExponent(&max_value, min_exp);

  while (max_exp != min_exp) {
    s21_decimal tmp = {0};
    s21_decimal remainder = int_div(min_value, ten, &tmp);
    min_value = tmp;
    rounding(&min_value, remainder);
    max_exp--;
  }
  setExponent(&min_value, max_exp);

  if (e1 < e2) {
    *value_1 = max_value;
    *value_2 = min_value;
  } else {
    *value_2 = max_value;
    *value_1 = min_value;
  }
}

void signHandler(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (getSign(value_1) != getSign(value_2)) {
    setSign(result, 1);
  } else {
    setSign(result, 0);
  }
}

void div10(s21_decimal *value) {
  int exp = getExponent(*value), sign = getSign(*value);
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal remainder = int_div(*value, ten, value);
  rounding(value, remainder);
  setExponent(value, exp - 1);
  setSign(value, sign);
}

int expHandler(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int RESULT_CODE = SUCCESS;
  int new_exponent = getExponent(value_1) + getExponent(*result) - getExponent(value_2);

  if (new_exponent > 28) {
    while (new_exponent > 28) {
      new_exponent--;
      div10(result);
      if (isEqualZero(*result)) {
        RESULT_CODE = 3;
        clearDecimal(result);
        break;
      }
    }
  }
  setExponent(result, (new_exponent >= 0) ? new_exponent : 0);

  if (new_exponent < 0) {
    new_exponent = - new_exponent;
    s21_decimal ten = {{10, 0, 0, 0}};
    while (new_exponent--) {
      s21_decimal tmp = {0};
      RESULT_CODE = s21_mul(*result, ten, &tmp);
      if (RESULT_CODE) {
        clearDecimal(result);
        break;
      }
      *result = tmp;
    }
  }
  return RESULT_CODE;
}
s21_decimal int_div(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  clearDecimal(result);
  int i = LAST_BIT2;
  while (!getBit(value_1, i) && i > 0) {
    i--;
  }
  s21_decimal tmp = {{getBit(value_1, i), 0, 0, 0}};

  while (i > 0) {
    while (isLessWithoutExp(tmp, value_2) && i-- > 0) {
      shiftLeft(&tmp);
      setBit(&tmp, 0, getBit(value_1, i));
      shiftLeft(result);
    }

    if (i != -1) {
      binarySubstraction(tmp, value_2, &tmp);
      setBit(result, 0, 1);
      if (isEqualZero(tmp) && isOnlyZeroStay(value_1, i - 1)) {
        for (int j = i - 1; j >= 0; j--) shiftLeft(result);
        break;
      }
    }
  }
  return tmp;  // remainder
}

// bit arithmetic
int binaryAddition(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int RESULT_CODE = SUCCESS, sign = getSign(value_1);

  while (!isEqualZero(value_2) && !RESULT_CODE) {
    s21_decimal temp = binaryAnd(value_1, value_2);
    value_1 = binaryXor(value_1, value_2);
    RESULT_CODE = shiftLeft(&temp);
    value_2 = temp;
  }

  *result = value_1;
  if (RESULT_CODE && sign) {
    RESULT_CODE = S21_NEGATIVE_INFINITY;
  }

  return RESULT_CODE;
}
void binarySubstraction(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result) {
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal negative_value_2 = {0};
  binaryAddition(binaryNot(value_2), one, &negative_value_2);

  while (!isEqualZeroAll(negative_value_2)) {
    s21_decimal temp = binaryAndAll(value_1, negative_value_2);
    value_1 = binaryXorAll(value_1, negative_value_2);
    shiftLeftAll(&temp);
    negative_value_2 = temp;
  }
  setBit(&value_1, LAST_BIT2 + 1, 0);

  *result = value_1;
}
int binaryMultiplication(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result) {
  int RESULT_CODE = SUCCESS;
  s21_decimal tmp = {0};

  while (!isEqualZero(value_2) && !RESULT_CODE) {
    if (getBit(value_2, 0)) {
      RESULT_CODE = binaryAddition(value_1, tmp, &tmp);
      if (RESULT_CODE) break;
    }
    RESULT_CODE = shiftLeft(&value_1);
    shiftRight(&value_2);
  }

  if (RESULT_CODE && (getSign(value_1) != getSign(value_2))) {
    RESULT_CODE = S21_NEGATIVE_INFINITY;
  }

  *result = tmp;

  return RESULT_CODE;
}

// shifts
int shiftLeft(s21_decimal *value) {
  int lastBit0 = getBit(*value, LAST_BIT0);
  int lastBit1 = getBit(*value, LAST_BIT1);
  int lastBit2 = getBit(*value, LAST_BIT2);

  for (int i = 0; i < 3; i++) {
    value->bits[i] <<= 1;
  }
  setBit(value, LAST_BIT0 + 1, lastBit0);
  setBit(value, LAST_BIT1 + 1, lastBit1);

  return lastBit2;  // 1 == overflow; 0 == !overflow
}
void shiftLeftAll(s21_decimal *value) {
  value->bits[3] <<= 1;
  setBit(value, LAST_BIT2 + 1, shiftLeft(value));
}
void shiftRight(s21_decimal *value) {
  int firstBit1 = getBit(*value, LAST_BIT0 + 1);
  int firstBit2 = getBit(*value, LAST_BIT1 + 1);

  for (int i = 3; i >= 0; i--) {
    value->bits[i] >>= 1;
  }
  setBit(value, LAST_BIT2, 0);
  setBit(value, LAST_BIT1, firstBit2);
  setBit(value, LAST_BIT0, firstBit1);
}
