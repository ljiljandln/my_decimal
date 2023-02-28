#ifndef SRC_ARITHMETIC_S21_BIG_DECIMAL_H_
#define SRC_ARITHMETIC_S21_BIG_DECIMAL_H_

#define LAST_BIT3 127
#define LAST_BIT4 159
#define LAST_BIT5 191

#define EXP_MAX_B 57

#include "../s21_decimal.h"

typedef struct {
  int bits[7];
} s21_big_decimal;

s21_big_decimal from_decimal_to_big_decimal(s21_decimal value);
int getBitBig(s21_big_decimal value, int position);
int getSignBig(s21_big_decimal value);
int getExponentBig(s21_big_decimal value);
void setSignBig(s21_big_decimal *value, int sign);
void setBitBig(s21_big_decimal *value, int position, int bit);
void setExponentBig(s21_big_decimal *value, int exponent);
int isEqualZeroBig(s21_big_decimal value);
int isEqualZeroAllBig(s21_big_decimal value);
int shiftLeftBig(s21_big_decimal *value);
void shiftLeftAllBig(s21_big_decimal *value);
void shiftRightBig(s21_big_decimal *value);
s21_big_decimal binaryXorBig(s21_big_decimal value_1, s21_big_decimal value_2);
s21_big_decimal binaryXorAllBig(s21_big_decimal value_1,
                                s21_big_decimal value_2);
s21_big_decimal binaryAndBig(s21_big_decimal value_1, s21_big_decimal value_2);
s21_big_decimal binaryAndAllBig(s21_big_decimal value_1,
                                s21_big_decimal value_2);
s21_big_decimal binaryNotBig(s21_big_decimal value);
int binaryAdditionBig(s21_big_decimal value_1, s21_big_decimal value_2,
                      s21_big_decimal *result);
void binarySubstractionBig(s21_big_decimal value_1, s21_big_decimal value_2,
                           s21_big_decimal *result);
int binaryMultiplicationBig(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result);
void setSignAndExpBig(s21_big_decimal *value);
int isLessWithoutExpBig(s21_big_decimal value_1, s21_big_decimal value_2);
int isOnlyZeroStayBig(s21_big_decimal value, int i);
void clearDecimalBig(s21_big_decimal *value);
s21_big_decimal int_div_big(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result);
int isEqualNumberBig(s21_big_decimal value, unsigned int number);
void roundingBig(s21_big_decimal *value, s21_big_decimal remainder);
void div_10(s21_big_decimal *value);
void makeNormalBig(s21_big_decimal *value);
void printDecimalBig(s21_big_decimal value);
void my_div(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result);
int from_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result,
                                int exp);
void signHandlerBig(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
void expHandlerBig(s21_decimal value_1, s21_decimal value_2,
                   s21_big_decimal *result);
int s21_truncate_big(s21_big_decimal value, s21_big_decimal *result);
void s21_normalize(s21_big_decimal *value_1, s21_big_decimal *value_2);

#endif  // SRC_ARITHMETIC_S21_BIG_DECIMAL_H_
