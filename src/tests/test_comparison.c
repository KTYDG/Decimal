#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define NEGATIVE 2147483648

Suite *s21_suite();

START_TEST(is_not_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_8) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_9) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_10) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_11) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_12) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_13) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, -2147483648}};
  int flag = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(is_not_equal_14) {
  s21_decimal num1 = {{1, 0, 0, -2147483648}};
  s21_decimal num2 = {{1, 0, 0, 0}};
  int flag = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_not_equal_15) {
  s21_decimal num1 = {{3, 2, 1, 0}};
  s21_decimal num2 = {{3, 2, 1, 0}};
  int flag = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(is_not_equal_16) {
  s21_decimal num1 = {{4, 2, 1, 0}};
  s21_decimal num2 = {{3, 2, 1, 0}};
  int flag = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_not_equal_17) {
  s21_decimal num1 = {{4, 2, 1, 65536}};
  s21_decimal num2 = {{4, 2, 1, 0}};
  int flag1 = s21_is_not_equal(num1, num2);
  int flag2 = s21_is_not_equal(num2, num1);
  ck_assert_int_eq(flag1, 1);
  ck_assert_int_eq(flag2, 1);
}
END_TEST

START_TEST(is_not_equal_18) {
  s21_decimal num1 = {{4, 2, 1, 65536}};
  s21_decimal num2 = {{4, 3, 1, 0}};
  int flag1 = s21_is_not_equal(num1, num2);
  int flag2 = s21_is_not_equal(num2, num1);
  ck_assert_int_eq(flag1, 1);
  ck_assert_int_eq(flag2, 1);
}
END_TEST

START_TEST(is_not_equal_19) {
  s21_decimal num1 = {{44, 369, 1687, 65536}};
  s21_decimal num2 = {{44, 369, 1687, 65536}};
  int flag1 = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_not_equal_20) {
  s21_decimal num1 = {{-1, -1, -1, 0}};
  s21_decimal num2 = {{44, 369, 1687, 65536}};
  int flag1 = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

/*---------------------------------- IS EQUAL -------------------*/
START_TEST(is_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_8) {
  s21_decimal x = {{0, 0, 0, NEGATIVE}};
  s21_decimal y = {{1, 0, 0, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_9) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, NEGATIVE}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_10) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, NEGATIVE}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_11) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_12) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_13) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_14) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_15) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_16) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, -2147483648}};
  int flag = s21_is_equal(num1, num2);

  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_equal_17) {
  // Arrange
  s21_decimal num1 = {{0, 0, 0, -2147483648}};
  s21_decimal num2 = {{0, 0, 0, -2147483648}};
  // Act
  int flag = s21_is_equal(num1, num2);
  // Accert
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_equal_18) {
  s21_decimal num1 = {{3345, 2656, 1242, 0}};
  s21_decimal num2 = {{3345, 2656, 1242, 0}};
  int flag = s21_is_equal(num1, num2);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_equal_19) {
  s21_decimal num1 = {{467, 2, 1, 0}};
  s21_decimal num2 = {{3, 234653, 1, 0}};
  int flag = s21_is_equal(num1, num2);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(is_equal_20) {
  s21_decimal num1 = {{4, 2, 1, 589824}};
  s21_decimal num2 = {{4, 2, 1, 0}};
  int flag1 = s21_is_equal(num1, num2);
  int flag2 = s21_is_equal(num2, num1);
  ck_assert_int_eq(flag1, 0);
  ck_assert_int_eq(flag2, 0);
}
END_TEST

START_TEST(is_equal_21) {
  s21_decimal num1 = {{4, 2, 1, 65536}};
  s21_decimal num2 = {{4, 3, 1, 0}};
  int flag1 = s21_is_equal(num1, num2);
  int flag2 = s21_is_equal(num2, num1);
  ck_assert_int_eq(flag1, 0);
  ck_assert_int_eq(flag2, 0);
}
END_TEST

START_TEST(is_equal_22) {
  s21_decimal num1 = {{454, 3269, 16887, 786432}};
  s21_decimal num2 = {{454, 3269, 16887, 786432}};
  int flag1 = s21_is_equal(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_equal_23) {
  s21_decimal num2 = {{-1, -1, -1, 0}};
  s21_decimal num1 = {{44, 369, 1687, 1835008}};
  int flag1 = s21_is_equal(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

/*----------------------------------great-than tests-------------------*/
START_TEST(is_greater_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};
  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_9) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_10) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_11) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_12) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_13) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_14) {
  s21_decimal num1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num2 = {{0, 0, 100, 0}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_greater_15) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, -2147483648}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_greater_16) {
  s21_decimal num1 = {{10, 0, 0, -2147483648}};
  s21_decimal num2 = {{9, 0, 0, -2147483648}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_greater_17) {
  s21_decimal num1 = {{9, 90, 0, -2147483648}};
  s21_decimal num2 = {{10, 100, 0, -2147483648}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_greater_18) {
  s21_decimal num1 = {{10, 11, 12, 0}};
  s21_decimal num2 = {{9, 8, 130, 0}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_greater_19) {
  s21_decimal num1 = {{5, 1, 8, -2146041856}};
  s21_decimal num2 = {{5, 1, 8, -2146238464}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_greater_20) {
  s21_decimal num1 = {{5, 40, 8, -2146238464}};
  s21_decimal num2 = {{500, 1, 3, -2146041856}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_greater_21) {
  s21_decimal num1 = {{10, 11, 12, 65536}};
  s21_decimal num2 = {{9, 8, 13, 65536}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_greater_22) {
  s21_decimal num1 = {{6, 0, 0, 589824}};
  s21_decimal num2 = {{0, 0, 10, 0}};
  int flag1 = s21_is_greater(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

/*---------------------------------- IS LESS -------------------*/
START_TEST(is_less_1) {
  s21_decimal x = {{4294967295, 0, 0, 0}};
  s21_decimal y = {{0, 1, 0, 0}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_less(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_9) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_10) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_11) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_12) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_13) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_14) {
  s21_decimal num1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_less_15) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, -2147483648}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_less_16) {
  s21_decimal num1 = {{10, 0, 0, -2147483648}};
  s21_decimal num2 = {{9, 0, 0, -2147483648}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_less_17) {
  s21_decimal num1 = {{9, 0, 0, -2147483648}};
  s21_decimal num2 = {{10, 0, 0, -2147483648}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_less_18) {
  s21_decimal num1 = {{10, 11, 12, 0}};
  s21_decimal num2 = {{9, 8, 13, 0}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_less_19) {
  s21_decimal num1 = {{500, 1, 3, -2146041856}};
  s21_decimal num2 = {{5, 4, 8, -2146238464}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_less_20) {
  s21_decimal num1 = {{5, 4, 8, -2146238464}};
  s21_decimal num2 = {{500, 1, 3, -2146041856}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST
START_TEST(is_less_21) {
  s21_decimal num1 = {{10, 11, 12, 65536}};
  s21_decimal num2 = {{9, 8, 13, 65536}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_less_22) {
  s21_decimal num1 = {{6, 0, 0, 589824}};
  s21_decimal num2 = {{0, 0, 10, 0}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

/*----------------------------------IS LESS OR EQUAL -----------*/

START_TEST(is_less_or_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_9) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_10) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_11) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_12) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_13) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

/*----------------------------------greater or equal----------*/
START_TEST(is_greater_or_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_9) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_10) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_11) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_12) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_13) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_greater_or_equal_14) {
  s21_decimal num1 = {{6, 0, 0, 589824}};
  s21_decimal num2 = {{6, 0, 0, 589824}};
  int flag1 = s21_is_greater_or_equal(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_greater_or_equal_15) {
  s21_decimal num1 = {{6, 0, 1, 589824}};
  s21_decimal num2 = {{6, 0, 0, 589824}};
  int flag1 = s21_is_greater_or_equal(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_greater_or_equal_16) {
  s21_decimal num1 = {{5, 0, 0, 589824}};
  s21_decimal num2 = {{6, 0, 0, 589824}};
  int flag1 = s21_is_greater_or_equal(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, is_not_equal_1);
  tcase_add_test(tc, is_not_equal_2);
  tcase_add_test(tc, is_not_equal_3);
  tcase_add_test(tc, is_not_equal_4);
  tcase_add_test(tc, is_not_equal_5);
  tcase_add_test(tc, is_not_equal_6);
  tcase_add_test(tc, is_not_equal_7);
  tcase_add_test(tc, is_not_equal_8);
  tcase_add_test(tc, is_not_equal_9);
  tcase_add_test(tc, is_not_equal_10);
  tcase_add_test(tc, is_not_equal_11);
  tcase_add_test(tc, is_not_equal_12);
  tcase_add_test(tc, is_not_equal_13);
  tcase_add_test(tc, is_not_equal_14);
  tcase_add_test(tc, is_not_equal_15);
  tcase_add_test(tc, is_not_equal_16);
  tcase_add_test(tc, is_not_equal_17);
  tcase_add_test(tc, is_not_equal_18);
  tcase_add_test(tc, is_not_equal_19);
  tcase_add_test(tc, is_not_equal_20);

  tcase_add_test(tc, is_equal_1);
  tcase_add_test(tc, is_equal_2);
  tcase_add_test(tc, is_equal_3);
  tcase_add_test(tc, is_equal_4);
  tcase_add_test(tc, is_equal_5);
  tcase_add_test(tc, is_equal_6);
  tcase_add_test(tc, is_equal_7);
  tcase_add_test(tc, is_equal_8);
  tcase_add_test(tc, is_equal_9);
  tcase_add_test(tc, is_equal_10);
  tcase_add_test(tc, is_equal_11);
  tcase_add_test(tc, is_equal_12);
  tcase_add_test(tc, is_equal_13);
  tcase_add_test(tc, is_equal_14);
  tcase_add_test(tc, is_equal_15);
  tcase_add_test(tc, is_equal_16);
  tcase_add_test(tc, is_equal_17);
  tcase_add_test(tc, is_equal_18);
  tcase_add_test(tc, is_equal_19);
  tcase_add_test(tc, is_equal_20);

  tcase_add_test(tc, is_equal_21);
  tcase_add_test(tc, is_equal_22);
  tcase_add_test(tc, is_equal_23);

  tcase_add_test(tc, is_less_22);
  tcase_add_test(tc, is_less_1);
  tcase_add_test(tc, is_less_2);
  tcase_add_test(tc, is_less_3);
  tcase_add_test(tc, is_less_4);
  tcase_add_test(tc, is_less_5);
  tcase_add_test(tc, is_less_6);
  tcase_add_test(tc, is_less_7);
  tcase_add_test(tc, is_less_8);
  tcase_add_test(tc, is_less_9);
  tcase_add_test(tc, is_less_10);
  tcase_add_test(tc, is_less_11);
  tcase_add_test(tc, is_less_12);
  tcase_add_test(tc, is_less_13);
  tcase_add_test(tc, is_less_14);
  tcase_add_test(tc, is_less_15);
  tcase_add_test(tc, is_less_16);
  tcase_add_test(tc, is_less_17);
  tcase_add_test(tc, is_less_18);
  tcase_add_test(tc, is_less_19);
  tcase_add_test(tc, is_less_20);
  tcase_add_test(tc, is_less_21);
  tcase_add_test(tc, is_less_22);

  tcase_add_test(tc, is_greater_1);
  tcase_add_test(tc, is_greater_2);
  tcase_add_test(tc, is_greater_3);
  tcase_add_test(tc, is_greater_4);
  tcase_add_test(tc, is_greater_5);
  tcase_add_test(tc, is_greater_6);
  tcase_add_test(tc, is_greater_7);
  tcase_add_test(tc, is_greater_8);
  tcase_add_test(tc, is_greater_9);
  tcase_add_test(tc, is_greater_10);
  tcase_add_test(tc, is_greater_11);
  tcase_add_test(tc, is_greater_12);
  tcase_add_test(tc, is_greater_13);
  tcase_add_test(tc, is_greater_14);
  tcase_add_test(tc, is_greater_15);
  tcase_add_test(tc, is_greater_16);
  tcase_add_test(tc, is_greater_17);
  tcase_add_test(tc, is_greater_18);
  tcase_add_test(tc, is_greater_19);
  tcase_add_test(tc, is_greater_20);
  tcase_add_test(tc, is_greater_21);
  tcase_add_test(tc, is_greater_22);

  tcase_add_test(tc, is_greater_or_equal_1);
  tcase_add_test(tc, is_greater_or_equal_2);
  tcase_add_test(tc, is_greater_or_equal_3);
  tcase_add_test(tc, is_greater_or_equal_4);
  tcase_add_test(tc, is_greater_or_equal_5);
  tcase_add_test(tc, is_greater_or_equal_6);
  tcase_add_test(tc, is_greater_or_equal_7);
  tcase_add_test(tc, is_greater_or_equal_8);
  tcase_add_test(tc, is_greater_or_equal_9);
  tcase_add_test(tc, is_greater_or_equal_10);
  tcase_add_test(tc, is_greater_or_equal_11);
  tcase_add_test(tc, is_greater_or_equal_12);
  tcase_add_test(tc, is_greater_or_equal_13);
  tcase_add_test(tc, is_greater_or_equal_14);
  tcase_add_test(tc, is_greater_or_equal_15);
  tcase_add_test(tc, is_greater_or_equal_16);

  tcase_add_test(tc, is_less_or_equal_1);
  tcase_add_test(tc, is_less_or_equal_2);
  tcase_add_test(tc, is_less_or_equal_3);
  tcase_add_test(tc, is_less_or_equal_4);
  tcase_add_test(tc, is_less_or_equal_5);
  tcase_add_test(tc, is_less_or_equal_6);
  tcase_add_test(tc, is_less_or_equal_7);
  tcase_add_test(tc, is_less_or_equal_8);
  tcase_add_test(tc, is_less_or_equal_9);
  tcase_add_test(tc, is_less_or_equal_10);
  tcase_add_test(tc, is_less_or_equal_11);
  tcase_add_test(tc, is_less_or_equal_12);
  tcase_add_test(tc, is_less_or_equal_13);

  suite_add_tcase(s, tc);
  return s;
}
int main(void) {
  /* We create variable no_failed to store the number of failed tests: */
  int no_failed = 0;
  /* We declare s as a pointer to a Suite and call on function in order to
   * create and return our test suite: */
  Suite *s = suite_insert();
  /* We pass our newly created test suite to the function srunner_create in
   * order to get a pointer to a test suite runner */
  SRunner *sr = srunner_create(s);
  /* This function will run our test suite and check our assertions, CK_VERBOSE
   * used to show all tests,  use CK_NORMAL instead to see only failed ones: */
  srunner_run_all(sr, CK_NORMAL);
  /* To extract the number of failed tests: */
  no_failed = srunner_ntests_failed(sr);
  /* We free any memory that was allocated due to our runner: */
  srunner_free(sr);
  /* We return if the number of failed tests is 0 else we fail the test run */
  return no_failed == 0 ? 0 : 1;

  /*  for mor information check
  https://www.ccs.neu.edu/home/skotthe/classes/cs5600/fall/2015/labs/intro-check.html
  or https://check.sourceforge.net/doc/doxygen/html/check_8h.html  */
}