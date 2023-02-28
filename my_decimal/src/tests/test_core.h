#ifndef SRC_TESTS_TEST_CORE_H_
#define SRC_TESTS_TEST_CORE_H_

#include <check.h>
#include <time.h>

#include "../s21_decimal.h"

Suite *st_arithmetic(void);
Suite *st_comparison(void);
// Suite *st_converters(void);
Suite *st_rounding(void);

long long int getRandomLLD();
double getRandomDouble();

#endif  // SRC_TESTS_TEST_CORE_H_
