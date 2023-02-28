#include "s21_converters.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int RESULT_CODE = CONVERTATION_SUCCESS;

  if (src <= MIN_DECIMAL || src >= MAX_DECIMAL ||
      ((!isnormal(src) || fabs(src) < SMALL_FLOAT_VALUE) && src != 0.000000f) ||
      !dst) {
    RESULT_CODE = CONVERTATION_ERROR;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    setSign(dst, (src < 0) ? 1 : 0);
    src = fabs(src);
    char bits[256] = {0};
    int exponent = 0;
    getBitsFromFloat(bits, &exponent, src);
    setBitsFromFloatToDecimal(bits, dst);
    setExponent(dst, exponent);
  }

  // if (dst != NULL && getBit(*dst, 96)) {
  //     RESULT_CODE = CONVERTATION_ERROR;
  //     clearDecimal(dst);
  // }

  if (fabs(src) < SMALL_FLOAT_VALUE) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
  }

  return RESULT_CODE;
}
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int RESULT_CODE = CONVERTATION_SUCCESS;

  if (!dst) {
    RESULT_CODE = CONVERTATION_ERROR;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    setSign(dst, (src < 0) ? 1 : 0);
    dst->bits[0] = abs(src);
  }

  return RESULT_CODE;
}
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int RESULT_CODE = CONVERTATION_SUCCESS;
  long double dst_d = 0.0;
  if (!dst) {
    RESULT_CODE = CONVERTATION_ERROR;
  } else {
    *dst = 0;
  }
  if (RESULT_CODE == CONVERTATION_SUCCESS) {
    RESULT_CODE = s21_from_decimal_to_long_double(src, &dst_d);
  }
  if (RESULT_CODE == CONVERTATION_SUCCESS) {
    if (dst_d > REAL_MAX_INT) {
      RESULT_CODE = CONVERTATION_ERROR;
    } else {
      *dst = (int)dst_d;
    }
  }
  return RESULT_CODE;
}
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  long double dst_d = 0.0;
  int RESULT_CODE = CONVERTATION_SUCCESS;
  if (!dst) {
    RESULT_CODE = CONVERTATION_ERROR;
  } else {
    *dst = 0.000000000f;
  }
  if (RESULT_CODE == CONVERTATION_SUCCESS) {
    int exp = getExponent(src);
    int sign = getSign(src);
    for (int i = 0; i < 95; i++) {
      dst_d += getBit(src, i) * powl(2.0, i);
    }
    for (int i = 0; i < exp; i++) {
      dst_d /= 10.;
    }
    if (sign == 1) {
      dst_d *= -1.0;
    }

    *dst = (float)dst_d;
  }
  return RESULT_CODE;
}
