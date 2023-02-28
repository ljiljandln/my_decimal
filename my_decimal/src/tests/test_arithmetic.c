#include "test_core.h"

START_TEST(TEST_ADD_OVERFLOW_POSITIVE) {
  // POSITIVE + POSITIVE
  s21_decimal empty = {0};
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result1 = {0};
  setBit(&value1, LAST_BIT2, 1);
  setBit(&value2, LAST_BIT2, 1);
  int RESULT_CODE = s21_add(value1, value2, &result1);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result1), 1);

  s21_decimal value3 = {0, 0, MAX_INT, 0};
  s21_decimal value4 = {0, 0, MAX_INT, 0};
  s21_decimal result2 = {0};
  RESULT_CODE = s21_add(value3, value4, &result2);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result2), 1);

  s21_decimal value5 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value6 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal result3 = {0};
  RESULT_CODE = s21_add(value5, value6, &result3);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result3), 1);
}
END_TEST
START_TEST(TEST_ADD_OVERFLOW_NEGATIVE) {
  // NEGATIVE + NEGATIVE
  s21_decimal empty = {0};
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result1 = {0};
  setSign(&value1, NEGATIVE);
  setSign(&value2, NEGATIVE);
  setBit(&value1, LAST_BIT2, 1);
  setBit(&value2, LAST_BIT2, 1);
  int RESULT_CODE = s21_add(value1, value2, &result1);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result1), 1);

  s21_decimal value3 = {0, 0, MAX_INT, 0};
  s21_decimal value4 = {0, 0, MAX_INT, 0};
  s21_decimal result2 = {0};
  setSign(&value3, NEGATIVE);
  setSign(&value4, NEGATIVE);
  RESULT_CODE = s21_add(value3, value4, &result2);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result2), 1);

  s21_decimal value5 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value6 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal result3 = {0};
  setSign(&value5, NEGATIVE);
  setSign(&value6, NEGATIVE);
  RESULT_CODE = s21_add(value5, value6, &result3);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result3), 1);
}
END_TEST
START_TEST(TEST_ADD_RANDOM_INT_VALUES) {
  long long int x = getRandomLLD();
  long long int y = getRandomLLD();
  long long int sum = x + y;
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result_test = {0};
  s21_decimal result_add = {0};

  s21_from_lld_to_decimal(sum, &result_test);
  s21_from_lld_to_decimal(x, &value1);
  s21_from_lld_to_decimal(y, &value2);
  int RESULT_CODE = s21_add(value1, value2, &result_add);

  ck_assert_int_eq(RESULT_CODE, SUCCESS);
  ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
}
END_TEST
START_TEST(TEST_ADD_MANUAL_DOUBLE_VALUES1) {
  s21_decimal x = {128491012, 0, 0, 0};
  s21_decimal y = {89023091, 0, 0, 0};
  s21_decimal result_test = {53222403, 3, 0, 0};
  s21_decimal result_add = {0};
  setExponent(&x, 4);
  setExponent(&y, 6);
  setExponent(&result_test, 6);
  int RESULT_CODE = s21_add(x, y, &result_add);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE ADD1   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_add  = ");
  printDecimal(result_add);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_ADD_MANUAL_DOUBLE_VALUES2) {
  s21_decimal x = {MAX_INT, MAX_INT, 0, 0};
  s21_decimal y = {MAX_INT, MAX_INT, 0, 0};
  s21_decimal result_test = {4294867295, MAX_INT, 100000, 0};
  s21_decimal result_add = {0};
  setExponent(&x, 12);
  setExponent(&y, 7);
  setExponent(&result_test, 12);
  int RESULT_CODE = s21_add(x, y, &result_add);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE ADD2   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_add  = ");
  printDecimal(result_add);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_ADD_MANUAL_DOUBLE_VALUES3) {
  s21_decimal x = {18240919, 0, 0, 0};
  s21_decimal y = {283409, 0, 0, 0};
  s21_decimal result_test = {1795751, 0, 0, 0};
  s21_decimal result_add = {0};
  setExponent(&x, 1);
  setExponent(&y, 1);
  setSign(&y, NEGATIVE);
  int RESULT_CODE = s21_add(x, y, &result_add);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE ADD3   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_add  = ");
  printDecimal(result_add);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_ADD_MANUAL_DOUBLE_VALUES4) {
  s21_decimal x = {12489812, 0, 0, 0};
  s21_decimal y = {238124, 0, 0, 0};
  s21_decimal result_test = {11322588, 0, 0, 0};
  s21_decimal result_add = {0};
  setExponent(&x, 3);
  setExponent(&y, 1);
  setExponent(&result_test, 3);
  setSign(&x, NEGATIVE);
  int RESULT_CODE = s21_add(x, y, &result_add);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE ADD4   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_add  = ");
  printDecimal(result_add);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_ADD_MANUAL_DOUBLE_VALUES5) {
  s21_decimal x = {1248918, 18249812, 12488912, 0};
  s21_decimal y = {0, 0, 0, 0};
  s21_decimal result_test = {1248918, 18249812, 12488912, 0};
  s21_decimal result_add = {0};
  int RESULT_CODE = s21_add(x, y, &result_add);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE ADD5   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_add  = ");
  printDecimal(result_add);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
// START_TEST(TEST_ADD_MANUAL_DOUBLE_VALUES1) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_add = {0};
//     int RESULT_CODE = s21_add(x, y, &result_add);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       DOUBLE
//     ADD1                                                      \n");
//     printf("\nresult_test = ");
//     printDecimal(result_test);
//     printf("\nresult_add  = ");
//     printDecimal(result_add);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST
// START_TEST(TEST_ADD_MANUAL_DOUBLE_VALUES1) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_add = {0};
//     int RESULT_CODE = s21_add(x, y, &result_add);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       DOUBLE
//     ADD1                                                      \n");
//     printf("\nresult_test = ");
//     printDecimal(result_test);
//     printf("\nresult_add  = ");
//     printDecimal(result_add);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST
// START_TEST(TEST_ADD_MANUAL_DOUBLE_VALUES1) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_add = {0};
//     int RESULT_CODE = s21_add(x, y, &result_add);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       DOUBLE
//     ADD1                                                      \n");
//     printf("\nresult_test = ");
//     printDecimal(result_test);
//     printf("\nresult_add  = ");
//     printDecimal(result_add);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_add), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST

START_TEST(TEST_SUB_OVERFLOW_POSITIVE) {
  // POSITIVE - NEGATIVE
  s21_decimal empty = {0};
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result1 = {0};
  setSign(&value2, NEGATIVE);
  setBit(&value1, LAST_BIT2, 1);
  setBit(&value2, LAST_BIT2, 1);
  int RESULT_CODE = s21_sub(value1, value2, &result1);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result1), 1);

  s21_decimal value3 = {0, 0, MAX_INT, 0};
  s21_decimal value4 = {0, 0, MAX_INT, 0};
  s21_decimal result2 = {0};
  setSign(&value4, NEGATIVE);
  RESULT_CODE = s21_sub(value3, value4, &result2);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result2), 1);

  s21_decimal value5 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value6 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal result3 = {0};
  setSign(&value6, NEGATIVE);
  RESULT_CODE = s21_sub(value5, value6, &result3);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result3), 1);
}
END_TEST
START_TEST(TEST_SUB_OVERFLOW_NEGATIVE) {
  // NEGATIVE - POSITIVE;
  s21_decimal empty = {0};
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result1 = {0};
  setSign(&value1, NEGATIVE);
  setBit(&value1, LAST_BIT2, 1);
  setBit(&value2, LAST_BIT2, 1);
  int RESULT_CODE = s21_sub(value1, value2, &result1);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result1), 1);

  s21_decimal value3 = {0, 0, MAX_INT, 0};
  s21_decimal value4 = {0, 0, MAX_INT, 0};
  s21_decimal result2 = {0};
  setSign(&value3, NEGATIVE);
  RESULT_CODE = s21_sub(value3, value4, &result2);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result2), 1);

  s21_decimal value5 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value6 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal result3 = {0};
  setSign(&value5, NEGATIVE);
  RESULT_CODE = s21_sub(value5, value6, &result3);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result3), 1);
}
END_TEST
START_TEST(TEST_SUB_RANDOM_INT_VALUES) {
  long long int x = getRandomLLD();
  long long int y = getRandomLLD();
  long long int sub = x - y;
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result_test = {0};
  s21_decimal result_sub = {0};

  s21_from_lld_to_decimal(sub, &result_test);
  s21_from_lld_to_decimal(x, &value1);
  s21_from_lld_to_decimal(y, &value2);
  int RESULT_CODE = s21_sub(value1, value2, &result_sub);

  ck_assert_int_eq(RESULT_CODE, SUCCESS);
  ck_assert_int_eq(s21_is_equal(result_test, result_sub), 1);
}
END_TEST
START_TEST(TEST_SUB_MANUAL_DOUBLE_VALUES1) {
  s21_decimal x = {18240919, 0, 0, 0};
  s21_decimal y = {23498, 0, 0, 0};
  s21_decimal result_test = {2004922601, 5, 0, 0};
  s21_decimal result_sub = {0};
  setExponent(&x, 7);
  setExponent(&y, 1);
  setExponent(&result_test, 7);
  setSign(&result_test, NEGATIVE);
  int RESULT_CODE = s21_sub(x, y, &result_sub);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE SUB1   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_sub  = ");
  printDecimal(result_sub);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_sub), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_SUB_MANUAL_DOUBLE_VALUES2) {
  s21_decimal x = {128498, 12849091, MAX_INT, 0};
  s21_decimal y = {128498, 12849091, MAX_INT, 0};
  s21_decimal result_test = {0, 0, 0, 0};
  s21_decimal result_sub = {0};
  setExponent(&x, 14);
  setExponent(&y, 14);
  int RESULT_CODE = s21_sub(x, y, &result_sub);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE SUB2   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_sub  = ");
  printDecimal(result_sub);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_sub), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_SUB_MANUAL_DOUBLE_VALUES3) {
  s21_decimal x = {1248918, 18249812, 12488912, 0};
  s21_decimal y = {0, 0, 0, 0};
  s21_decimal result_test = {1248918, 18249812, 12488912, 0};
  s21_decimal result_sub = {0};
  int RESULT_CODE = s21_sub(x, y, &result_sub);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE SUB3   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_sub  = ");
  printDecimal(result_sub);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_sub), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_SUB_MANUAL_DOUBLE_VALUES4) {
  s21_decimal x = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal y = {125, 0, 0, 0};
  s21_decimal result_test = {MAX_INT - 1, MAX_INT, MAX_INT, 0};
  s21_decimal result_sub = {0};
  setExponent(&y, 2);
  int RESULT_CODE = s21_sub(x, y, &result_sub);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE SUB4   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_sub  = ");
  printDecimal(result_sub);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_sub), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_SUB_MANUAL_DOUBLE_VALUES5) {
    s21_decimal x = {MAX_INT, MAX_INT, MAX_INT, 0};
    s21_decimal y = {6, 0, 0, 0};
    s21_decimal result_test = {MAX_INT - 1, MAX_INT, MAX_INT, 0};
    s21_decimal result_sub = {0};
    setExponent(&y, 1);
    int RESULT_CODE = s21_sub(x, y, &result_sub);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE SUB5                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_sub  = ");
    printDecimal(result_sub);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_sub), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
// START_TEST(TEST_SUB_MANUAL_DOUBLE_VALUES) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_sub = {0};
//     int RESULT_CODE = s21_sub(x, y, &result_sub);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       DOUBLE
//     SUB1                                                      \n");
//     printf("\nresult_test = ");
//     printDecimal(result_test);
//     printf("\nresult_sub  = ");
//     printDecimal(result_sub);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_sub), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST

START_TEST(TEST_MUL_OVERFLOW_POSITIVE) {
  // POSITIVE * POSITIVE
  s21_decimal empty = {0};
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result1 = {0};
  setBit(&value1, LAST_BIT2, 1);
  setBit(&value2, LAST_BIT2, 1);
  int RESULT_CODE = s21_mul(value1, value2, &result1);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result1), 1);

  s21_decimal value3 = {0, 0, MAX_INT, 0};
  s21_decimal value4 = {0, 0, MAX_INT, 0};
  s21_decimal result2 = {0};
  RESULT_CODE = s21_mul(value3, value4, &result2);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result2), 1);

  s21_decimal value5 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value6 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal result3 = {0};
  RESULT_CODE = s21_mul(value5, value6, &result3);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result3), 1);
}
END_TEST
START_TEST(TEST_MUL_OVERFLOW_NEGATIVE) {
  // POSITIVE * NEGATIVE || NEGATIVE * POSITIVE
  s21_decimal empty = {0};
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result1 = {0};
  setSign(&value2, NEGATIVE);
  setBit(&value1, LAST_BIT2, 1);
  setBit(&value2, LAST_BIT2, 1);
  int RESULT_CODE = s21_mul(value1, value2, &result1);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result1), 1);

  s21_decimal value3 = {0, 0, MAX_INT, 0};
  s21_decimal value4 = {0, 0, MAX_INT, 0};
  s21_decimal result2 = {0};
  setSign(&value4, NEGATIVE);
  RESULT_CODE = s21_mul(value3, value4, &result2);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result2), 1);

  s21_decimal value5 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value6 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal result3 = {0};
  setSign(&value6, NEGATIVE);
  RESULT_CODE = s21_mul(value5, value6, &result3);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result3), 1);

  s21_decimal value7 = {0};
  s21_decimal value8 = {0};
  s21_decimal result4 = {0};
  setSign(&value7, NEGATIVE);
  setBit(&value1, LAST_BIT2, 1);
  setBit(&value2, LAST_BIT2, 1);
  RESULT_CODE = s21_mul(value1, value2, &result4);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result4), 1);

  s21_decimal value9 = {0, 0, MAX_INT, 0};
  s21_decimal value10 = {0, 0, MAX_INT, 0};
  s21_decimal result5 = {0};
  setSign(&value9, NEGATIVE);
  RESULT_CODE = s21_mul(value3, value4, &result5);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result5), 1);

  s21_decimal value11 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value12 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal result6 = {0};
  setSign(&value12, NEGATIVE);
  RESULT_CODE = s21_mul(value5, value6, &result6);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result6), 1);
}
END_TEST
START_TEST(TEST_MUL_RANDOM_INT_VALUES) {
  long long int x = getRandomLLD();
  long long int y = getRandomLLD();
  long long int mult = x * y;
  s21_decimal value1 = {0};
  s21_decimal value2 = {0};
  s21_decimal result_test = {0};
  s21_decimal result_mul = {0};

  s21_from_lld_to_decimal(mult, &result_test);
  s21_from_lld_to_decimal(x, &value1);
  s21_from_lld_to_decimal(y, &value2);
  int RESULT_CODE = s21_mul(value1, value2, &result_mul);

  // printf("x    = %lld\n", x);
  // printf("y    = %lld\n", y);
  // printf("mult = %lld\n", mult);
  // printf("\nresult_test = ");
  // printDecimal(result_test);
  // printf("\nresult_mul  = ");
  // printDecimal(result_mul);
  // printf("RESULT_CODE = %d\n\n", RESULT_CODE);

  ck_assert_int_eq(RESULT_CODE, SUCCESS);
  ck_assert_int_eq(s21_is_equal(result_test, result_mul), 1);
}
END_TEST
START_TEST(TEST_MUL_MANUAL_DOUBLE_VALUES1) {
  s21_decimal x = {1, 0, 0, 0};
  s21_decimal y = {1, 0, 0, 0};
  s21_decimal result_test = {0, 0, 0, 0};
  s21_decimal result_mul = {0};
  setExponent(&x, 28);
  setExponent(&y, 5);
  int RESULT_CODE = s21_mul(x, y, &result_mul);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE MUL1   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_mul  = ");
  printDecimal(result_mul);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mul), 1);
  ck_assert_int_eq(RESULT_CODE, S21_NAN);
}
END_TEST
START_TEST(TEST_MUL_MANUAL_DOUBLE_VALUES2) {
    s21_decimal x = {MAX_INT, MAX_INT, MAX_INT, 0};
    s21_decimal y = {3, 0, 0, 0};
    s21_decimal result_test = {3435973836, 3435973836, 1288490188, 0};
    s21_decimal result_mul = {0};
    setExponent(&x, 15);
    setExponent(&y, 2);
    setExponent(&result_test, 16);
    int RESULT_CODE = s21_mul(x, y, &result_mul);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE MUL2                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_mul  = ");
    printDecimal(result_mul);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_mul), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
START_TEST(TEST_MUL_MANUAL_DOUBLE_VALUES3) {
    s21_decimal x = {2, 0, 0, 0};
    s21_decimal y = {5, 0, 0, 0};
    s21_decimal result_test = {1, 0, 0, 0};
    s21_decimal result_mul = {0};
    setExponent(&y, 1);
    int RESULT_CODE = s21_mul(x, y, &result_mul);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE MUL3                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_mul  = ");
    printDecimal(result_mul);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_mul), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
START_TEST(TEST_MUL_MANUAL_DOUBLE_VALUES4) {
    s21_decimal x = {123481284, 20934124, 45, 0};
    s21_decimal y = {0, 0, 0, 0};
    s21_decimal result_test = {0, 0, 0, 0};
    s21_decimal result_mul = {0};
    setExponent(&x, 19);
    setExponent(&y, 5);
    int RESULT_CODE = s21_mul(x, y, &result_mul);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE MUL4                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_mul  = ");
    printDecimal(result_mul);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_mul), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
// START_TEST(TEST_MUL_MANUAL_DOUBLE_VALUES) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_mul = {0};
//     int RESULT_CODE = s21_mul(x, y, &result_mul);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       DOUBLE MUL1                                                      \n");
//     printf("\nresult_test = ");
//     printDecimal(result_test);
//     printf("\nresult_mul  = ");
//     printDecimal(result_mul);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_mul), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST

START_TEST(TEST_DIV_OVERFLOW_POSITIVE) {
  // (POSITIVE / POSITIVE) && VALUE1 != VALUE2
  s21_decimal empty = {0};
  s21_decimal value1 = {0};
  s21_decimal value2 = {5, 0, 0, 0};
  s21_decimal result1 = {0};
  setBit(&value1, LAST_BIT2, 1);
  setExponent(&value2, 1);
  int RESULT_CODE = s21_div(value1, value2, &result1);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result1), 1);

  s21_decimal value3 = {0, 0, MAX_INT, 0};
  s21_decimal value4 = {5, 0, 0, 0};
  s21_decimal result2 = {0};
  setExponent(&value4, 1);
  RESULT_CODE = s21_div(value1, value2, &result2);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result2), 1);

  s21_decimal value5 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value6 = {5, 0, 0, 0};
  s21_decimal result3 = {0};
  setExponent(&value6, 1);
  RESULT_CODE = s21_div(value1, value2, &result3);
  ck_assert_int_eq(RESULT_CODE, S21_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result3), 1);
}
END_TEST
START_TEST(TEST_DIV_OVERFLOW_NEGATIVE) {
  // (POSITIVE / NEGATIVE || NEGATIVE / POSITIVE) && VALUE1 != VALUE2
  s21_decimal empty = {0};
  s21_decimal value1 = {0};
  s21_decimal value2 = {5, 0, 0, 0};
  s21_decimal result1 = {0};
  setBit(&value1, LAST_BIT2, 1);
  setExponent(&value2, 1);
  setSign(&value2, NEGATIVE);
  int RESULT_CODE = s21_div(value1, value2, &result1);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result1), 1);

  s21_decimal value3 = {0, 0, MAX_INT, 0};
  s21_decimal value4 = {5, 0, 0, 0};
  s21_decimal result2 = {0};
  setExponent(&value4, 1);
  setSign(&value4, NEGATIVE);
  RESULT_CODE = s21_div(value1, value2, &result2);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result2), 1);

  s21_decimal value5 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value6 = {5, 0, 0, 0};
  s21_decimal result3 = {0};
  setExponent(&value6, 1);
  setSign(&value6, NEGATIVE);
  RESULT_CODE = s21_div(value1, value2, &result3);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result3), 1);

  s21_decimal value7 = {0};
  s21_decimal value8 = {5, 0, 0, 0};
  s21_decimal result4 = {0};
  setBit(&value1, LAST_BIT2, 1);
  setExponent(&value8, 1);
  setSign(&value7, NEGATIVE);
  RESULT_CODE = s21_div(value1, value2, &result4);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result4), 1);

  s21_decimal value9 = {0, 0, MAX_INT, 0};
  s21_decimal value10 = {5, 0, 0, 0};
  s21_decimal result5 = {0};
  setExponent(&value10, 1);
  setSign(&value9, NEGATIVE);
  RESULT_CODE = s21_div(value1, value2, &result5);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result5), 1);

  s21_decimal value11 = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal value12 = {5, 0, 0, 0};
  s21_decimal result6 = {0};
  setExponent(&value12, 1);
  setSign(&value11, NEGATIVE);
  RESULT_CODE = s21_div(value1, value2, &result6);
  ck_assert_int_eq(RESULT_CODE, S21_NEGATIVE_INFINITY);
  ck_assert_int_eq(s21_is_equal(empty, result6), 1);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_INT_VALUES1) {
  s21_decimal x = {9812357, 0, 0, 0};
  s21_decimal y = {4, 0, 0, 0};
  s21_decimal result_test = {245308925, 0, 0, 0};
  s21_decimal result_div = {0};
  setExponent(&result_test, 2);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       INT DIV1      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);

  s21_decimal x2 = {9812357, 0, 0, 0};
  s21_decimal y2 = {4, 0, 0, 0};
  s21_decimal result_test2 = {245308925, 0, 0, 0};
  s21_decimal result_div2 = {0};
  setExponent(&result_test2, 2);
  setSign(&x2, NEGATIVE);
  setSign(&result_test2, NEGATIVE);
  RESULT_CODE = s21_div(x2, y2, &result_div2);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV2      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test2);
  printf("\nresult_div  = ");
  printDecimal(result_div2);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test2, result_div2), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);

  s21_decimal x3 = {9812357, 0, 0, 0};
  s21_decimal y3 = {4, 0, 0, 0};
  s21_decimal result_test3 = {245308925, 0, 0, 0};
  s21_decimal result_div3 = {0};
  setExponent(&result_test3, 2);
  setSign(&y3, NEGATIVE);
  setSign(&result_test3, NEGATIVE);
  RESULT_CODE = s21_div(x3, y3, &result_div3);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV3      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test3);
  printf("\nresult_div  = ");
  printDecimal(result_div3);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test3, result_div3), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);

  s21_decimal x4 = {9812357, 0, 0, 0};
  s21_decimal y4 = {0, 0, 0, 0};
  s21_decimal result_test4 = {0, 0, 0, 0};
  s21_decimal result_div4 = {0};
  RESULT_CODE = s21_div(x4, y4, &result_div4);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV4      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test4);
  printf("\nresult_div  = ");
  printDecimal(result_div4);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test4, result_div4), 1);
  ck_assert_int_eq(RESULT_CODE, S21_NAN);

  s21_decimal x5 = {9812357, 0, 0, 0};
  s21_decimal y5 = {1, 0, 0, 0};
  s21_decimal result_test5 = {9812357, 0, 0, 0};
  s21_decimal result_div5 = {0};
  RESULT_CODE = s21_div(x5, y5, &result_div5);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV5      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test5);
  printf("\nresult_div  = ");
  printDecimal(result_div5);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test5, result_div5), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);

  s21_decimal x6 = {9812357, 0, 0, 0};
  s21_decimal y6 = {1, 0, 0, 0};
  s21_decimal result_test6 = {9812357, 0, 0, 0};
  s21_decimal result_div6 = {0};
  setSign(&x6, NEGATIVE);
  setSign(&result_test6, NEGATIVE);
  RESULT_CODE = s21_div(x6, y6, &result_div6);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV6      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test6);
  printf("\nresult_div  = ");
  printDecimal(result_div6);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test6, result_div6), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);

  s21_decimal x7 = {MAX_INT, MAX_INT, 0, 0};
  s21_decimal y7 = {5, 0, 0, 0};
  s21_decimal result_test7 = {858993459, 858993459, 0, 0};
  s21_decimal result_div7 = {0};
  RESULT_CODE = s21_div(x7, y7, &result_div7);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV7      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test7);
  printf("\nresult_div  = ");
  printDecimal(result_div7);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test7, result_div7), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);

  s21_decimal x8 = {MAX_INT, MAX_INT, 0, 0};
  s21_decimal y8 = {MAX_INT, MAX_INT, 0, 0};
  s21_decimal result_test8 = {1, 0, 0, 0};
  s21_decimal result_div8 = {0};
  RESULT_CODE = s21_div(x8, y8, &result_div8);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV8      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test8);
  printf("\nresult_div  = ");
  printDecimal(result_div8);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test8, result_div8), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_INT_VALUES2) {
  s21_decimal x = {1, 0, 0, 0};
  s21_decimal y = {20, 0, 0, 0};
  s21_decimal result_test = {5, 0, 0, 0};
  s21_decimal result_div = {0};
  setExponent(&result_test, 2);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV9      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_INT_VALUES3) {
  s21_decimal x = {1, 0, 0, 0};
  s21_decimal y = {50, 0, 0, 0};
  s21_decimal result_test = {2, 0, 0, 0};
  s21_decimal result_div = {0};
  setExponent(&result_test, 2);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV10     "
      "                                                 \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_INT_VALUES4) {
  s21_decimal x = {MAX_INT, MAX_INT, MAX_INT, 0};
  s21_decimal y = {3, 0, 0, 0};
  s21_decimal result_test = {1431655765, 1431655765, 1431655765, 0};
  s21_decimal result_div = {0};
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n==================================================================="
      "================================================\n");
  printf(
      "                                                       INT DIV11     "
      "                                                 \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
// START_TEST(TEST_DIV_MANUAL_INT_VALUES) {
//   s21_decimal x = {0, 0, 0, 0};
//   s21_decimal y = {0, 0, 0, 0};
//   s21_decimal result_test = {0, 0, 0, 0};
//   s21_decimal result_div = {0};
//   int RESULT_CODE = s21_div(x, y, &result_div);
//   printf(
//       "\n==================================================================="
//       "================================================\n");
//   printf(
//       "                                                       INT DIV10     "
//       "                                                 \n");
//   printf("\nresult_test = ");
//   printDecimal(result_test);
//   printf("\nresult_div  = ");
//   printDecimal(result_div);
//   printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//   printf(
//       "====================================================================="
//       "==============================================\n");
//   ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
//   ck_assert_int_eq(RESULT_CODE, SUCCESS);
// }
// END_TEST
// START_TEST(TEST_DIV_MANUAL_INT_VALUES) {
//   s21_decimal x = {0, 0, 0, 0};
//   s21_decimal y = {0, 0, 0, 0};
//   s21_decimal result_test = {0, 0, 0, 0};
//   s21_decimal result_div = {0};
//   int RESULT_CODE = s21_div(x, y, &result_div);
//   printf(
//       "\n==================================================================="
//       "================================================\n");
//   printf(
//       "                                                       INT DIV10     "
//       "                                                 \n");
//   printf("\nresult_test = ");
//   printDecimal(result_test);
//   printf("\nresult_div  = ");
//   printDecimal(result_div);
//   printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//   printf(
//       "====================================================================="
//       "==============================================\n");
//   ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
//   ck_assert_int_eq(RESULT_CODE, SUCCESS);
// }
// END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES1) {
  s21_decimal x = {1124891289, 0, 0, 0};
  s21_decimal y = {38490023, 0, 0, 0};
  s21_decimal result_test = {3630516643, 4115887026, 158431910, 0};
  s21_decimal result_div = {0};
  setExponent(&x, 4);
  setExponent(&y, 2);
  setExponent(&result_test, 28);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV1   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES2) {
  s21_decimal x = {4, 0, 0, 0};
  s21_decimal y = {5, 0, 0, 0};
  s21_decimal result_test = {8, 0, 0, 0};
  s21_decimal result_div = {0};
  setExponent(&result_test, 1);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV2   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES3) {
  s21_decimal x = {10000, 0, 0, 0};
  s21_decimal y = {10, 0, 0, 0};
  s21_decimal result_test = {1, 0, 0, 0};
  s21_decimal result_div = {0};
  setExponent(&x, 3);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV3   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES4) {
  s21_decimal x = {1, 0, 0, 0};
  s21_decimal y = {1, 0, 0, 0};
  s21_decimal result_test = {1, 0, 0, 0};
  s21_decimal result_div = {0};
  setSign(&x, NEGATIVE);
  setSign(&y, NEGATIVE);
  setExponent(&x, 28);
  setExponent(&y, 28);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV4   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES5) {
  s21_decimal x = {1, 0, 0, 0};
  s21_decimal y = {1, 0, 0, 0};
  s21_decimal result_test = {1, 0, 0, 0};
  s21_decimal result_div = {0};
  setSign(&x, NEGATIVE);
  setSign(&result_test, NEGATIVE);
  setExponent(&x, 28);
  setExponent(&y, 28);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV5   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES6) {
  s21_decimal x = {12897420, 0, 0, 0};
  s21_decimal y = {5, 0, 0, 0};
  s21_decimal result_test = {2579484, 0, 0, 0};
  s21_decimal result_div = {0};
  setExponent(&x, 3);
  setExponent(&result_test, 3);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV6   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES7) {
  s21_decimal x = {19884210, 0, 0, 0};
  s21_decimal y = {5, 0, 0, 0};
  s21_decimal result_test = {1113714336, 9, 0, 0};
  s21_decimal result_div = {0};
  setExponent(&y, 4);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV7   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES8) {
  s21_decimal x = {12481294, 1812489, 1824918, 0};
  s21_decimal y = {0, 0, 0, 0};
  s21_decimal result_test = {0, 0, 0, 0};
  s21_decimal result_div = {0};
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV8  "
      "                                                    \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, S21_NAN);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES9) {
  s21_decimal x = {28450, 102409, 12480912, 0};
  s21_decimal y = {1, 0, 0, 0};
  s21_decimal result_test = {28450, 102409, 12480912, 0};
  s21_decimal result_div = {0};
  setExponent(&x, 1);
  setExponent(&y, 1);
  int RESULT_CODE = s21_div(x, y, &result_div);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE DIV9   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_div);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES10) {
    s21_decimal x = {6, 0, 0, 0};
    s21_decimal y = {7, 0, 0, 0};
    s21_decimal result_test = {2070787803, 3961501925, 464658073, 0};
    s21_decimal result_div = {0};
    setExponent(&x, 1);
    setExponent(&y, 1);
    setExponent(&result_test, 28);
    int RESULT_CODE = s21_div(x, y, &result_div);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE DIV10                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_div  = ");
    printDecimal(result_div);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES11) {
    s21_decimal x = {1, 0, 0, 0};
    s21_decimal y = {5, 0, 0, 0};
    s21_decimal result_test = {2, 0, 0, 0};
    s21_decimal result_div = {0};
    setExponent(&x, 27);
    setExponent(&y, 28);
    int RESULT_CODE = s21_div(x, y, &result_div);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE DIV11                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_div  = ");
    printDecimal(result_div);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
// START_TEST(TEST_DIV_MANUAL_DOUBLE_VALUES) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_div = {0};
//     int RESULT_CODE = s21_div(x, y, &result_div);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       DOUBLE
//     DIV3                                                      \n");
//     printf("\nresult_test = ");
//     printDecimal(result_test);
//     printf("\nresult_div  = ");
//     printDecimal(result_div);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_div), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST

START_TEST(TEST_MOD_MANUAL_INT_VALUES1) {
  s21_decimal x = {1248124, 0, 0, 0};
  s21_decimal y = {1248124, 0, 0, 0};
  s21_decimal result_test = {0, 0, 0, 0};
  s21_decimal result_mod = {0};
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       INT MOD1      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_INT_VALUES2) {
  s21_decimal x = {181249, 0, 0, 0};
  s21_decimal y = {45, 0, 0, 0};
  s21_decimal result_test = {34, 0, 0, 0};
  s21_decimal result_mod = {0};
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       INT MOD2      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_INT_VALUES3) {
  s21_decimal x = {5, 0, 0, 0};
  s21_decimal y = {4, 0, 0, 0};
  s21_decimal result_test = {1, 0, 0, 0};
  s21_decimal result_mod = {0};
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       INT MOD3      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_INT_VALUES4) {
  s21_decimal x = {1, 0, 0, 0};
  s21_decimal y = {1, 0, 0, 0};
  s21_decimal result_test = {0, 0, 0, 0};
  s21_decimal result_mod = {0};
  setSign(&x, NEGATIVE);
  setSign(&y, NEGATIVE);
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       INT MOD4      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_INT_VALUES5) {
  s21_decimal x = {83284, 0, 0, 0};
  s21_decimal y = {5, 0, 0, 0};
  s21_decimal result_test = {4, 0, 0, 0};
  s21_decimal result_mod = {0};
  setSign(&x, NEGATIVE);
  setSign(&result_test, NEGATIVE);
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       INT MOD5      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_INT_VALUES6) {
  s21_decimal x = {83284, 0, 0, 0};
  s21_decimal y = {5, 0, 0, 0};
  s21_decimal result_test = {4, 0, 0, 0};
  s21_decimal result_mod = {0};
  setSign(&y, NEGATIVE);
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       INT MOD6      "
      "                                                \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_div  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
// START_TEST(TEST_MOD_MANUAL_INT_VALUES) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_mod = {0};
//     int RESULT_CODE = s21_mod(x, y, &result_mod);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       INT MOD1
//     \n"); printf("\nresult_test = "); printDecimal(result_test);
//     printf("\nresult_div  = ");
//     printDecimal(result_mod);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST
// START_TEST(TEST_MOD_MANUAL_INT_VALUES) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_mod = {0};
//     int RESULT_CODE = s21_mod(x, y, &result_mod);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       INT MOD1
//     \n"); printf("\nresult_test = "); printDecimal(result_test);
//     printf("\nresult_div  = ");
//     printDecimal(result_mod);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST
// START_TEST(TEST_MOD_MANUAL_INT_VALUES) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_mod = {0};
//     int RESULT_CODE = s21_mod(x, y, &result_mod);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       INT MOD1
//     \n"); printf("\nresult_test = "); printDecimal(result_test);
//     printf("\nresult_div  = ");
//     printDecimal(result_mod);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST
// START_TEST(TEST_MOD_MANUAL_INT_VALUES) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_mod = {0};
//     int RESULT_CODE = s21_mod(x, y, &result_mod);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       INT MOD1
//     \n"); printf("\nresult_test = "); printDecimal(result_test);
//     printf("\nresult_div  = ");
//     printDecimal(result_mod);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST
START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES1) {
  s21_decimal x = {19220, 0, 0, 0};
  s21_decimal y = {961, 0, 0, 0};
  s21_decimal result_test = {0, 0, 0, 0};
  s21_decimal result_mod = {0};
  setExponent(&x, 2);
  setExponent(&y, 1);
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE MOD1   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_mod  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES2) {
  s21_decimal x = {9, 0, 0, 0};
  s21_decimal y = {4, 0, 0, 0};
  s21_decimal result_test = {1, 0, 0, 0};
  s21_decimal result_mod = {0};
  setExponent(&x, 10);
  setExponent(&y, 10);
  setExponent(&result_test, 10);
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE MOD2   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_mod  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES3) {
  s21_decimal x = {23598, 12894, 23589124, 0};
  s21_decimal y = {0, 0, 0, 0};
  s21_decimal result_test = {0, 0, 0, 0};
  s21_decimal result_mod = {0};
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE MOD3   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_mod  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, S21_NAN);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES4) {
  s21_decimal x = {12481824, 1230940, 234, 0};
  s21_decimal y = {1, 0, 0, 0};
  s21_decimal result_test = {0, 0, 0, 0};
  s21_decimal result_mod = {0};
  setExponent(&x, 1);
  setExponent(&y, 1);
  int RESULT_CODE = s21_mod(x, y, &result_mod);
  printf(
      "\n\n\n\n============================================================="
      "======================================================\n");
  printf(
      "                                                       DOUBLE MOD4   "
      "                                                   \n");
  printf("\nresult_test = ");
  printDecimal(result_test);
  printf("\nresult_mod  = ");
  printDecimal(result_mod);
  printf("RESULT_CODE = %d\n\n", RESULT_CODE);
  printf(
      "====================================================================="
      "==============================================\n");
  ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES5) {
    s21_decimal x = {62, 0, 0, 0};
    s21_decimal y = {4, 0, 0, 0};
    s21_decimal result_test = {22, 0, 0, 0};
    s21_decimal result_mod = {0};
    setExponent(&x, 1);
    setExponent(&result_test, 1);
    int RESULT_CODE = s21_mod(x, y, &result_mod);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE MOD5                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_mod  = ");
    printDecimal(result_mod);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES6) {
    s21_decimal x = {MAX_INT, MAX_INT, MAX_INT, 0};
    s21_decimal y = {33, 0, 0, 0};
    s21_decimal result_test = {3, 0, 0, 0};
    s21_decimal result_mod = {0};
    setExponent(&y, 1);
    setExponent(&result_test, 1);
    int RESULT_CODE = s21_mod(x, y, &result_mod);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE MOD6                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_mod  = ");
    printDecimal(result_mod);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES7) {
    s21_decimal x = {4, 0, 0, 0};
    s21_decimal y = {2, 0, 0, 0};
    s21_decimal result_test = {0, 0, 0, 0};
    s21_decimal result_mod = {0};
    setExponent(&y, 2);
    int RESULT_CODE = s21_mod(x, y, &result_mod);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE MOD7                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_mod  = ");
    printDecimal(result_mod);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES8) {
    s21_decimal x = {0, MAX_INT, MAX_INT, 0};
    s21_decimal y = {1, 0, 0, 0};
    s21_decimal result_test = {0, 0, 0, 0};
    s21_decimal result_mod = {0};
    setExponent(&y, 3);
    int RESULT_CODE = s21_mod(x, y, &result_mod);
    printf("\n\n\n\n===================================================================================================================\n");
    printf("                                                       DOUBLE MOD8                                                      \n");
    printf("\nresult_test = ");
    printDecimal(result_test);
    printf("\nresult_mod  = ");
    printDecimal(result_mod);
    printf("RESULT_CODE = %d\n\n", RESULT_CODE);
    printf("===================================================================================================================\n");
    ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
    ck_assert_int_eq(RESULT_CODE, SUCCESS);
} END_TEST
// START_TEST(TEST_MOD_MANUAL_DOUBLE_VALUES) {
//     s21_decimal x = {0, 0, 0, 0};
//     s21_decimal y = {0, 0, 0, 0};
//     s21_decimal result_test = {0, 0, 0, 0};
//     s21_decimal result_mod = {0};
//     int RESULT_CODE = s21_mod(x, y, &result_mod);
//     printf("\n\n\n\n===================================================================================================================\n");
//     printf("                                                       DOUBLE
//     MOD1                                                      \n");
//     printf("\nresult_test = ");
//     printDecimal(result_test);
//     printf("\nresult_mod  = ");
//     printDecimal(result_mod);
//     printf("RESULT_CODE = %d\n\n", RESULT_CODE);
//     printf("===================================================================================================================\n");
//     ck_assert_int_eq(s21_is_equal(result_test, result_mod), 1);
//     ck_assert_int_eq(RESULT_CODE, SUCCESS);
// } END_TEST

Suite *st_arithmetic(void) {
  Suite *s = suite_create("st_arithmetic");
  TCase *tc = tcase_create("arithmetic_tc");

  tcase_add_test(tc, TEST_ADD_OVERFLOW_POSITIVE);
  tcase_add_test(tc, TEST_ADD_OVERFLOW_NEGATIVE);
  tcase_add_loop_test(tc, TEST_ADD_RANDOM_INT_VALUES, 0, 100);
  tcase_add_test(tc, TEST_ADD_MANUAL_DOUBLE_VALUES1);
  tcase_add_test(tc, TEST_ADD_MANUAL_DOUBLE_VALUES2);
  tcase_add_test(tc, TEST_ADD_MANUAL_DOUBLE_VALUES3);
  tcase_add_test(tc, TEST_ADD_MANUAL_DOUBLE_VALUES4);
  tcase_add_test(tc, TEST_ADD_MANUAL_DOUBLE_VALUES5);

  tcase_add_test(tc, TEST_SUB_OVERFLOW_POSITIVE);
  tcase_add_test(tc, TEST_SUB_OVERFLOW_NEGATIVE);
  tcase_add_loop_test(tc, TEST_SUB_RANDOM_INT_VALUES, 0, 100);
  tcase_add_test(tc, TEST_SUB_MANUAL_DOUBLE_VALUES1);
  tcase_add_test(tc, TEST_SUB_MANUAL_DOUBLE_VALUES2);
  tcase_add_test(tc, TEST_SUB_MANUAL_DOUBLE_VALUES3);
  tcase_add_test(tc, TEST_SUB_MANUAL_DOUBLE_VALUES4);
  tcase_add_test(tc, TEST_SUB_MANUAL_DOUBLE_VALUES5);

  tcase_add_test(tc, TEST_MUL_OVERFLOW_POSITIVE);
  tcase_add_test(tc, TEST_MUL_OVERFLOW_NEGATIVE);
  tcase_add_test(tc, TEST_MUL_RANDOM_INT_VALUES);
  tcase_add_test(tc, TEST_MUL_MANUAL_DOUBLE_VALUES1);
  tcase_add_test(tc, TEST_MUL_MANUAL_DOUBLE_VALUES2);
  tcase_add_test(tc, TEST_MUL_MANUAL_DOUBLE_VALUES3);
  tcase_add_test(tc, TEST_MUL_MANUAL_DOUBLE_VALUES4);

  tcase_add_test(tc, TEST_DIV_OVERFLOW_POSITIVE);
  tcase_add_test(tc, TEST_DIV_OVERFLOW_NEGATIVE);
  tcase_add_test(tc, TEST_DIV_MANUAL_INT_VALUES1);
  tcase_add_test(tc, TEST_DIV_MANUAL_INT_VALUES2);
  tcase_add_test(tc, TEST_DIV_MANUAL_INT_VALUES3);
  tcase_add_test(tc, TEST_DIV_MANUAL_INT_VALUES4);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES1);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES2);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES3);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES4);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES5);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES6);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES7);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES8);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES9);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES10);
  tcase_add_test(tc, TEST_DIV_MANUAL_DOUBLE_VALUES11);

  tcase_add_test(tc, TEST_MOD_MANUAL_INT_VALUES1);
  tcase_add_test(tc, TEST_MOD_MANUAL_INT_VALUES2);
  tcase_add_test(tc, TEST_MOD_MANUAL_INT_VALUES3);
  tcase_add_test(tc, TEST_MOD_MANUAL_INT_VALUES4);
  tcase_add_test(tc, TEST_MOD_MANUAL_INT_VALUES5);
  tcase_add_test(tc, TEST_MOD_MANUAL_INT_VALUES6);
  tcase_add_test(tc, TEST_MOD_MANUAL_DOUBLE_VALUES1);
  tcase_add_test(tc, TEST_MOD_MANUAL_DOUBLE_VALUES2);
  tcase_add_test(tc, TEST_MOD_MANUAL_DOUBLE_VALUES3);
  tcase_add_test(tc, TEST_MOD_MANUAL_DOUBLE_VALUES4);
  tcase_add_test(tc, TEST_MOD_MANUAL_DOUBLE_VALUES5);
  tcase_add_test(tc, TEST_MOD_MANUAL_DOUBLE_VALUES6);
  tcase_add_test(tc, TEST_MOD_MANUAL_DOUBLE_VALUES7);
  tcase_add_test(tc, TEST_MOD_MANUAL_DOUBLE_VALUES8);

  suite_add_tcase(s, tc);
  return s;
}