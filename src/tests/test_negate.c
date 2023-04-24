#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

START_TEST(negate_1) {
  s21_decimal num = {{1, 0, 0, 2147483648u}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal num = {{1, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(negate_4) {
  s21_decimal x = {{32444, 100, 343253, -2145976320}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "32444 100 343253 1507328";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(negate_5) {
  s21_decimal x = {{1, 1, 1, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "1 1 1 2148401152";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(negate_6) {
  s21_decimal x = {{0, 0, 0, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "0 0 0 2148401152";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(s21_negate_1) {
  s21_decimal src1, origin, result;
  // src1 = 2.1234;
  src1.bits[0] = 0b00000000000000000101001011110010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001000000000000000000;
  // origin = -2.1234;
  origin.bits[0] = 0b00000000000000000101001011110010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal src1, origin, result;
  // src1 = 457.000001;
  src1.bits[0] = 0b00011011001111010100010001000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = -457.000001;
  origin.bits[0] = 0b00011011001111010100010001000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal src1, origin, result;
  // src1 = 2.000;
  src1.bits[0] = 0b00000000000000000000011111010000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000110000000000000000;
  // origin = -2.000;
  origin.bits[0] = 0b00000000000000000000011111010000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_4) {
  s21_decimal src1, origin, result;
  // src1 = 0.000000000000000000000000000;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000110110000000000000000;
  // origin = 0.000000000000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000110110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_5) {
  s21_decimal src1, origin, result;
  // src1 = -3;
  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  // origin = 3;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_6) {
  s21_decimal src1, origin, result;
  // src1 = 2.222212;
  src1.bits[0] = 0b00000000001000011110100010000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = -2.222212;
  origin.bits[0] = 0b00000000001000011110100010000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_7) {
  s21_decimal src1, origin, result;
  // src1 = 2.22221200000001000;
  src1.bits[0] = 0b00000111100011111010001111101000;
  src1.bits[1] = 0b00000011000101010111110100000001;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000100010000000000000000;
  // origin = -2.22221200000001000;
  origin.bits[0] = 0b00000111100011111010001111101000;
  origin.bits[1] = 0b00000011000101010111110100000001;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000100010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_8) {
  s21_decimal src1, origin, result;
  // src1 = 3.745754741;
  src1.bits[0] = 0b11011111010000111010111001110101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000010010000000000000000;
  // origin = -3.745754741;
  origin.bits[0] = 0b11011111010000111010111001110101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000010010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_9) {
  s21_decimal src1, origin, result;
  // src1 = 2.222212;
  src1.bits[0] = 0b00000000001000011110100010000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  // origin = -2.222212;
  origin.bits[0] = 0b00000000001000011110100010000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_10) {
  s21_decimal src1, origin, result;
  // src1 = -364748;
  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  // origin = 364748;
  origin.bits[0] = 0b00000000000001011001000011001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_11) {
  s21_decimal src1, origin, result;
  // src1 = 987456543210.0;
  src1.bits[0] = 0b00011001111101110000001100100100;
  src1.bits[1] = 0b00000000000000000000100011111011;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  // origin = -987456543210.0;
  origin.bits[0] = 0b00011001111101110000001100100100;
  origin.bits[1] = 0b00000000000000000000100011111011;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_12) {
  s21_decimal src1, origin, result;
  // src1 = -9878798789.5867800;
  src1.bits[0] = 0b11001110100110111101100110011000;
  src1.bits[1] = 0b00000001010111101111011100100110;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001110000000000000000;
  // origin = 9878798789.5867800;
  origin.bits[0] = 0b11001110100110111101100110011000;
  origin.bits[1] = 0b00000001010111101111011100100110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000001110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_13) {
  s21_decimal src1, origin, result;
  // src1 = 9999999999999999999;
  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // origin = -9999999999999999999;
  origin.bits[0] = 0b10001001111001111111111111111111;
  origin.bits[1] = 0b10001010110001110010001100000100;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_14) {
  s21_decimal src1, origin, result;
  // src1 = 18446744073709551615;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // origin = -18446744073709551615;
  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_15) {
  s21_decimal src1, origin, result;
  // src1 = 18446744073709551615.0;
  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  // origin = -18446744073709551615.0;
  origin.bits[0] = 0b11111111111111111111111111110110;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b00000000000000000000000000001001;
  origin.bits[3] = 0b10000000000000010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_16) {
  s21_decimal src1, origin, result;
  // src1 = -796214545.3526545454564545456;
  src1.bits[0] = 0b10111111111111101001001110110000;
  src1.bits[1] = 0b11101010111111101111100111101000;
  src1.bits[2] = 0b00011001101110100010000111100001;
  src1.bits[3] = 0b10000000000100110000000000000000;
  // origin = 796214545.3526545454564545456;
  origin.bits[0] = 0b10111111111111101001001110110000;
  origin.bits[1] = 0b11101010111111101111100111101000;
  origin.bits[2] = 0b00011001101110100010000111100001;
  origin.bits[3] = 0b00000000000100110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_17) {
  s21_decimal src1, origin, result;
  // src1 = -545454512454545.35265454545645;
  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  // origin = 545454512454545.35265454545645;
  origin.bits[0] = 0b10000010111000100101101011101101;
  origin.bits[1] = 0b11111001111010000010010110101101;
  origin.bits[2] = 0b10110000001111101111000010010100;
  origin.bits[3] = 0b00000000000011100000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_18) {
  s21_decimal src1, origin, result;
  // src1 = -7961327845421.843434341378545;
  src1.bits[0] = 0b11110011001100111010100111110001;
  src1.bits[1] = 0b01001011001101011000000011010000;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b10000000000011110000000000000000;
  // origin = 7961327845421.843434341378545;
  origin.bits[0] = 0b11110011001100111010100111110001;
  origin.bits[1] = 0b01001011001101011000000011010000;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_19) {
  s21_decimal src1, origin, result;
  // src1 = 12345677.987654345678987654346;
  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  // origin = -12345677.987654345678987654346;
  origin.bits[0] = 0b10010001000010101111010011001010;
  origin.bits[1] = 0b11000000010001011101010111110010;
  origin.bits[2] = 0b00100111111001000001101100000000;
  origin.bits[3] = 0b10000000000101010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_20) {
  s21_decimal src1, origin, result;
  // src1 = 12345677.987654345678987654346;
  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  // origin = -12345677.987654345678987654346;
  origin.bits[0] = 0b10010001000010101111010011001010;
  origin.bits[1] = 0b11000000010001011101010111110010;
  origin.bits[2] = 0b00100111111001000001101100000000;
  origin.bits[3] = 0b10000000000101010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_21) {
  s21_decimal src1, origin, result;
  // src1 = 87654323456.98765456789876530;
  src1.bits[0] = 0b10110010000010100010111100110010;
  src1.bits[1] = 0b10011001010111000101110110000000;
  src1.bits[2] = 0b00011100010100101001100001111111;
  src1.bits[3] = 0b00000000000100010000000000000000;
  // origin = -87654323456.98765456789876530;
  origin.bits[0] = 0b10110010000010100010111100110010;
  origin.bits[1] = 0b10011001010111000101110110000000;
  origin.bits[2] = 0b00011100010100101001100001111111;
  origin.bits[3] = 0b10000000000100010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_22) {
  s21_decimal src1, origin, result;
  // src1 = -854764561465456456.9876545679;
  src1.bits[0] = 0b11000100000001000100000010001111;
  src1.bits[1] = 0b01000000100100100110001100010101;
  src1.bits[2] = 0b00011011100111100111001001011101;
  src1.bits[3] = 0b10000000000010100000000000000000;
  // origin = 854764561465456456.9876545679;
  origin.bits[0] = 0b11000100000001000100000010001111;
  origin.bits[1] = 0b01000000100100100110001100010101;
  origin.bits[2] = 0b00011011100111100111001001011101;
  origin.bits[3] = 0b00000000000010100000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_23) {
  s21_decimal src1, origin, result;
  // src1 = 79228162514264337593543950335;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // origin = -79228162514264337593543950335;
  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b11111111111111111111111111111111;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_24) {
  s21_decimal src1, origin, result;
  // src1 = -69.1234567;
  src1.bits[0] = 0b00101001001100110110011100000111;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001110000000000000000;
  // origin = 69.1234567;
  origin.bits[0] = 0b00101001001100110110011100000111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000001110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_25) {
  s21_decimal src1, origin, result;
  // src1 = 13436577854.000000000000;
  src1.bits[0] = 0b00100110011110011110000000000000;
  src1.bits[1] = 0b01100101111110011111000000101100;
  src1.bits[2] = 0b00000000000000000000001011011000;
  src1.bits[3] = 0b00000000000011000000000000000000;
  // origin = -13436577854.000000000000;
  origin.bits[0] = 0b00100110011110011110000000000000;
  origin.bits[1] = 0b01100101111110011111000000101100;
  origin.bits[2] = 0b00000000000000000000001011011000;
  origin.bits[3] = 0b10000000000011000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_26) {
  s21_decimal src1, origin, result;
  // src1 = 79228162514264337593543950335;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // origin = -79228162514264337593543950335;
  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b11111111111111111111111111111111;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_27) {
  s21_decimal src1, origin, result;
  // src1 = 79228162514264337593543950335;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // origin = -79228162514264337593543950335;
  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b11111111111111111111111111111111;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_28) {
  s21_decimal src1, origin, result;
  // src1 = 665464545;
  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // origin = -665464545;
  origin.bits[0] = 0b00100111101010100010111011100001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_29) {
  s21_decimal src1, origin, result;
  // src1 = 2.7986531268974139743;
  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  // origin = -2.7986531268974139743;
  origin.bits[0] = 0b11111110100100001101100101011111;
  origin.bits[1] = 0b10000100011001000010000111101000;
  origin.bits[2] = 0b00000000000000000000000000000001;
  origin.bits[3] = 0b10000000000100110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_30) {
  s21_decimal src1, origin, result;
  // src1 = -2156878451.8547640000000000;
  src1.bits[0] = 0b10010011100100010011000000000000;
  src1.bits[1] = 0b00100110110100100010010100001001;
  src1.bits[2] = 0b00000000000100011101011101011110;
  src1.bits[3] = 0b10000000000100000000000000000000;
  // origin = 2156878451.8547640000000000;
  origin.bits[0] = 0b10010011100100010011000000000000;
  origin.bits[1] = 0b00100110110100100010010100001001;
  origin.bits[2] = 0b00000000000100011101011101011110;
  origin.bits[3] = 0b00000000000100000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_31) {
  s21_decimal src1, origin, result;
  // src1 = 0.5456465465486476846545465485;
  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;
  // origin = -0.5456465465486476846545465485;
  origin.bits[0] = 0b00001011000011110111000010001101;
  origin.bits[1] = 0b10010110101100000101100101010001;
  origin.bits[2] = 0b00010001101000010111101110000001;
  origin.bits[3] = 0b10000000000111000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_32) {
  s21_decimal src1, origin, result;
  // src1 = -776890.75455454213415678965898;
  src1.bits[0] = 0b11000010010111101111100010001010;
  src1.bits[1] = 0b01011100000101000111000011011000;
  src1.bits[2] = 0b11111011000001101110010110100011;
  src1.bits[3] = 0b10000000000101110000000000000000;
  // origin = 776890.75455454213415678965898;
  origin.bits[0] = 0b11000010010111101111100010001010;
  origin.bits[1] = 0b01011100000101000111000011011000;
  origin.bits[2] = 0b11111011000001101110010110100011;
  origin.bits[3] = 0b00000000000101110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_33) {
  s21_decimal src1, origin, result;
  // src1 = -732123534337593543950335.12;
  src1.bits[0] = 0b11000011000110111111111110101000;
  src1.bits[1] = 0b10100001110111010100101100101110;
  src1.bits[2] = 0b00000000001111001000111101010001;
  src1.bits[3] = 0b10000000000000100000000000000000;
  // origin = 732123534337593543950335.12;
  origin.bits[0] = 0b11000011000110111111111110101000;
  origin.bits[1] = 0b10100001110111010100101100101110;
  origin.bits[2] = 0b00000000001111001000111101010001;
  origin.bits[3] = 0b00000000000000100000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_34) {
  s21_decimal src1, origin, result;
  // src1 = 675432788976.5424354657687;
  src1.bits[0] = 0b10111110000100011000010110010111;
  src1.bits[1] = 0b11011001001111010001001011000110;
  src1.bits[2] = 0b00000000000001011001011001001000;
  src1.bits[3] = 0b00000000000011010000000000000000;
  // origin = -675432788976.5424354657687;
  origin.bits[0] = 0b10111110000100011000010110010111;
  origin.bits[1] = 0b11011001001111010001001011000110;
  origin.bits[2] = 0b00000000000001011001011001001000;
  origin.bits[3] = 0b10000000000011010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_35) {
  s21_decimal src1, origin, result;
  // src1 = -579895323215489956.67897455465;
  src1.bits[0] = 0b11100110001001011001001101101001;
  src1.bits[1] = 0b00111000110110101110001010110100;
  src1.bits[2] = 0b10111011010111111101000100011110;
  src1.bits[3] = 0b10000000000010110000000000000000;
  // origin = 579895323215489956.67897455465;
  origin.bits[0] = 0b11100110001001011001001101101001;
  origin.bits[1] = 0b00111000110110101110001010110100;
  origin.bits[2] = 0b10111011010111111101000100011110;
  origin.bits[3] = 0b00000000000010110000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_36) {
  s21_decimal src1, origin, result;
  // src1 = 123523543453453453.0;
  src1.bits[0] = 0b01001001011001111111110110000010;
  src1.bits[1] = 0b00010001001001000111000000010101;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  // origin = -123523543453453453.0;
  origin.bits[0] = 0b01001001011001111111110110000010;
  origin.bits[1] = 0b00010001001001000111000000010101;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_37) {
  s21_decimal src1, origin, result;
  // src1 = 31231232456315.0;
  src1.bits[0] = 0b11100001001010100010000011001110;
  src1.bits[1] = 0b00000000000000010001110000001011;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  // origin = -31231232456315.0;
  origin.bits[0] = 0b11100001001010100010000011001110;
  origin.bits[1] = 0b00000000000000010001110000001011;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_38) {
  s21_decimal src1, origin, result;
  // src1 = 78987543557678337.5935439503;
  src1.bits[0] = 0b00111011110001111000001010001111;
  src1.bits[1] = 0b00101001100010100010010001100011;
  src1.bits[2] = 0b00000010100011010101111010100001;
  src1.bits[3] = 0b00000000000010100000000000000000;
  // origin = -78987543557678337.5935439503;
  origin.bits[0] = 0b00111011110001111000001010001111;
  origin.bits[1] = 0b00101001100010100010010001100011;
  origin.bits[2] = 0b00000010100011010101111010100001;
  origin.bits[3] = 0b10000000000010100000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_39) {
  s21_decimal src1, origin, result;
  // src1 = -754567488438.97816770;
  src1.bits[0] = 0b01011010011001011000011011000010;
  src1.bits[1] = 0b00010111001011000011100101001001;
  src1.bits[2] = 0b00000000000000000000000000000100;
  src1.bits[3] = 0b10000000000010000000000000000000;
  // origin = 754567488438.97816770;
  origin.bits[0] = 0b01011010011001011000011011000010;
  origin.bits[1] = 0b00010111001011000011100101001001;
  origin.bits[2] = 0b00000000000000000000000000000100;
  origin.bits[3] = 0b00000000000010000000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_40) {
  s21_decimal src1, origin, result;
  // src1 = -2.514475768684753643;
  src1.bits[0] = 0b10101100110010000011001011101011;
  src1.bits[1] = 0b00100010111001010011011001100011;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  // origin = 2.514475768684753643;
  origin.bits[0] = 0b10101100110010000011001011101011;
  origin.bits[1] = 0b00100010111001010011011001100011;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000100100000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_41) {
  s21_decimal src1, origin, result;
  // src1 = -0.0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  // origin = 0.0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_negate_42) {
  s21_decimal src1, origin, result;
  // src1 = 0.0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  // origin = -0.0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000010000000000000000;
  int check_origin = 0;
  int check = s21_negate(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_4);
  tcase_add_test(tc, negate_5);
  tcase_add_test(tc, negate_6);
  tcase_add_test(tc, s21_negate_1);
  tcase_add_test(tc, s21_negate_2);
  tcase_add_test(tc, s21_negate_3);
  tcase_add_test(tc, s21_negate_4);
  tcase_add_test(tc, s21_negate_5);
  tcase_add_test(tc, s21_negate_6);
  tcase_add_test(tc, s21_negate_7);
  tcase_add_test(tc, s21_negate_8);
  tcase_add_test(tc, s21_negate_9);
  tcase_add_test(tc, s21_negate_10);
  tcase_add_test(tc, s21_negate_11);
  tcase_add_test(tc, s21_negate_12);
  tcase_add_test(tc, s21_negate_13);
  tcase_add_test(tc, s21_negate_14);
  tcase_add_test(tc, s21_negate_15);
  tcase_add_test(tc, s21_negate_16);
  tcase_add_test(tc, s21_negate_17);
  tcase_add_test(tc, s21_negate_18);
  tcase_add_test(tc, s21_negate_19);
  tcase_add_test(tc, s21_negate_20);
  tcase_add_test(tc, s21_negate_21);
  tcase_add_test(tc, s21_negate_22);
  tcase_add_test(tc, s21_negate_23);
  tcase_add_test(tc, s21_negate_24);
  tcase_add_test(tc, s21_negate_25);
  tcase_add_test(tc, s21_negate_26);
  tcase_add_test(tc, s21_negate_27);
  tcase_add_test(tc, s21_negate_28);
  tcase_add_test(tc, s21_negate_29);
  tcase_add_test(tc, s21_negate_30);
  tcase_add_test(tc, s21_negate_31);
  tcase_add_test(tc, s21_negate_32);
  tcase_add_test(tc, s21_negate_33);
  tcase_add_test(tc, s21_negate_34);
  tcase_add_test(tc, s21_negate_35);
  tcase_add_test(tc, s21_negate_36);
  tcase_add_test(tc, s21_negate_37);
  tcase_add_test(tc, s21_negate_38);
  tcase_add_test(tc, s21_negate_39);
  tcase_add_test(tc, s21_negate_40);
  tcase_add_test(tc, s21_negate_41);
  tcase_add_test(tc, s21_negate_42);
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