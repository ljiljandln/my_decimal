#ifndef SRC_CORE_S21_CORE_H_
#define SRC_CORE_S21_CORE_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int bits[4];
} s21_decimal;

#define SUCCESS 0
#define S21_INFINITY 1
#define S21_NEGATIVE_INFINITY 2
#define S21_NAN 3

#define POSITIVE 0
#define NEGATIVE 1

#define EXP_MAX 28
#define EXP_MIN 0
#define EXP_START 16
#define EXP_END 23

#define LAST_BIT0 31
#define LAST_BIT1 63
#define LAST_BIT2 95
#define LAST_BIT3 127
#define LAST_BIT4 159
#define LAST_BIT5 191

#define MAX_INT 4294967295
#define REAL_MAX_INT 2147483647.0f
#define REAL_MIN_INT -2147483648.0f

#define CONVERTATION_SUCCESS 0
#define CONVERTATION_ERROR 1

#define MAX_DECIMAL 79228162514264337593543950335.0f
#define MIN_DECIMAL -79228162514264337593543950335.0f

#define SMALL_FLOAT_VALUE 0.0000000000000000000000000001f

int getBit(s21_decimal value, int position);
int getSign(s21_decimal value);
int getExponent(s21_decimal value);
s21_decimal getModule(s21_decimal value);
void getBitsFromFloat(char *bits, int *exponent, long double result);
int getFloatExponent(float value);
int getDoubleExponent(long double value);

void setSign(s21_decimal *value, int sign);
void setBit(s21_decimal *value, int position, int bit);
void setExponent(s21_decimal *value, int exponent);
void setSignAndExp(s21_decimal *value);
void setBitsFromFloatToDecimal(char *bits, s21_decimal *result);
void makeNormal(s21_decimal *value);
void beforeCalculate(s21_decimal *value_1, s21_decimal *value_2);

void printDecimal(s21_decimal value);
void clearDecimal(s21_decimal *value);
int isEqualZero(s21_decimal value);
int isEqualZeroAll(s21_decimal value);
int isLessWithoutExp(s21_decimal value_1, s21_decimal value_2);
int isEqualUnit(s21_decimal value);
int isOnlyZeroStay(s21_decimal value, int i);
int isEqualNumber(s21_decimal value, unsigned int number);
int s21_from_lld_to_decimal(long long int src, s21_decimal *dst);
int s21_from_decimal_to_long_double(s21_decimal src, long double *dst_d);

void s21_bank_rounding(s21_decimal *value, int n);
int bank_check(int n);

s21_decimal binaryXor(s21_decimal value_1, s21_decimal value_2);
s21_decimal binaryXorAll(s21_decimal value_1, s21_decimal value_2);
s21_decimal binaryAnd(s21_decimal value_1, s21_decimal value_2);
s21_decimal binaryAndAll(s21_decimal value_1, s21_decimal value_2);
s21_decimal binaryNot(s21_decimal value);

void s21_normalize_pair(s21_decimal *value_1, s21_decimal *value_2);

void signHandler(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int expHandler(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void div10(s21_decimal *value);
s21_decimal int_div(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);

int binaryAddition(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
void binarySubstraction(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result);
int binaryMultiplication(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);

int shiftLeft(s21_decimal *value);
void shiftLeftAll(s21_decimal *value);
void shiftRight(s21_decimal *value);

#endif  // SRC_CORE_S21_CORE_H_
