#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define NEGATIVE 2147483648

START_TEST(from_d_to_f_0) {
  float inp = 1. / 0.;
  s21_decimal out;
  int error = s21_from_float_to_decimal(inp, &out);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

END_TEST
START_TEST(from_d_to_f_1) {
  float result = 0;
  s21_decimal target = {{0x00000002, 0, 0, 0}};
  float answer = 2;
  int error = s21_from_decimal_to_float(target, &result);
  ck_assert_float_eq(result, answer);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_d_to_f_2) {
  s21_decimal target = {{0x00000C8C, 0, 0, 0x80010000}};
  float answer = -321.2;
  float result = 0;
  int error = s21_from_decimal_to_float(target, &result);
  ck_assert_float_eq(result, answer);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_d_to_f_3) {
  s21_decimal target = {{0x00000C8C, 0, 0, 0x00010000}};
  float answer = 321.2;
  float result = 0;
  int error = s21_from_decimal_to_float(target, &result);
  ck_assert_float_eq(result, answer);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_d_to_f_4) {
  float answer = 3.478075E-10;
  s21_decimal target = {{0x0035123B, 0x00000000, 0x00000000, 0x00100000}};
  float result = 0;
  int error = s21_from_decimal_to_float(target, &result);
  ck_assert_float_eq(result, answer);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_d_to_f_5) {
  float answer = -4.057507E-11;
  s21_decimal target = {{0x003DE9A3, 0x00000000, 0x00000000, 0x80110000}};
  float result = 0;
  int error = s21_from_decimal_to_float(target, &result);
  ck_assert_float_eq(result, answer);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_d_to_f_6) {
  float answer = 0.003;
  s21_decimal target = {{0x00000003, 0, 0, 0x00030000}};
  float result = 0;
  int error = s21_from_decimal_to_float(target, &result);
  ck_assert_float_eq(result, answer);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_d_to_f_7) {
  s21_decimal number;
  // decimal: 2.0
  // float: 2
  // int: 1073741824
  number.bits[0] = 0b00000000000000000000000000010100;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000010000000000000000;
  int result_int = 1073741824;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_8) {
  s21_decimal number;
  // decimal: -0.8
  // float: -0.8
  // int: -1085485875
  number.bits[0] = 0b00000000000000000000000000001000;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b10000000000000010000000000000000;
  int result_int = -1085485875;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_9) {
  s21_decimal number;
  // decimal: 0
  // float: 0
  // int: 0
  number.bits[0] = 0b00000000000000000000000000000000;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 0;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_10) {
  s21_decimal number;
  // decimal: 1
  // float: 1
  // int: 1065353216
  number.bits[0] = 0b00000000000000000000000000000001;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 1065353216;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_11) {
  s21_decimal number;
  // decimal: 0.0
  // float: 0
  // int: -2147483648
  number.bits[0] = 0b00000000000000000000000000000000;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b10000000000000010000000000000000;
  int result_int = 0;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_12) {
  s21_decimal number;
  // decimal: -1.75
  // float: -1.75
  // int: -1075838976
  number.bits[0] = 0b00000000000000000000000010101111;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b10000000000000100000000000000000;
  int result_int = -1075838976;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_13) {
  s21_decimal number;
  // decimal: 6521
  // float: 6521
  // int: 1170982912
  number.bits[0] = 0b00000000000000000001100101111001;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 1170982912;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_14) {
  s21_decimal number;
  // decimal: 4
  // float: 4
  // int: 1082130432
  number.bits[0] = 0b00000000000000000000000000000100;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 1082130432;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_15) {
  s21_decimal number;
  // decimal: 65658654
  // float: 6.565866E+07
  // int: 1283094472
  number.bits[0] = 0b00000011111010011101111100011110;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 1283094472;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_16) {
  s21_decimal number;
  // decimal: -364748
  // float: -364748
  // int: -927852160
  number.bits[0] = 0b00000000000001011001000011001100;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b10000000000000000000000000000000;
  int result_int = -927852160;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_17) {
  s21_decimal number;
  // decimal: 0.003
  // float: 0.003
  // int: 994352038
  number.bits[0] = 0b00000000000000000000000000000011;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000110000000000000000;
  int result_int = 994352038;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_18) {
  s21_decimal number;
  // decimal: -9878798789
  // float: -9.878798E+09
  // int: -804047712
  number.bits[0] = 0b01001100110100101000000111000101;
  number.bits[1] = 0b00000000000000000000000000000010;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b10000000000000000000000000000000;
  int result_int = -804047712;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_19) {
  s21_decimal number;
  // decimal: 9959999999999999999
  // float: 9.96E+18
  // int: 1594505479
  number.bits[0] = 0b11001010111000111111111111111111;
  number.bits[1] = 0b10001010001110010000011100111010;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 1594505479;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_20) {
  s21_decimal number;
  // decimal: 18446744073709551615
  // float: 1.844674E+19
  // int: 1602224128
  number.bits[0] = 0b11111111111111111111111111111111;
  number.bits[1] = 0b11111111111111111111111111111111;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 1602224128;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_21) {
  s21_decimal number;
  // decimal: -5454545545352456454545645464
  // float: -5.454546E+27
  // int: -309526744
  number.bits[0] = 0b10001000100000001001111110011000;
  number.bits[1] = 0b10000010011101100000001010011001;
  number.bits[2] = 0b00010001100111111110010011110010;
  number.bits[3] = 0b10000000000000000000000000000000;
  int result_int = -309526744;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_22) {
  s21_decimal number;
  // decimal: 79228162514264337593543950335
  // float: 7.922816E+28
  // int: 1870659584
  number.bits[0] = 0b11111111111111111111111111111111;
  number.bits[1] = 0b11111111111111111111111111111111;
  number.bits[2] = 0b11111111111111111111111111111111;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 1870659584;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_23) {
  s21_decimal number;
  // decimal: 1234.5677987654345678987654346
  // float: 1234.568
  // int: 1150964267
  number.bits[0] = 0b10010001000010101111010011001010;
  number.bits[1] = 0b11000000010001011101010111110010;
  number.bits[2] = 0b00100111111001000001101100000000;
  number.bits[3] = 0b00000000000110010000000000000000;
  int result_int = 1150964267;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_24) {
  s21_decimal number;
  // decimal: -123458677.98765434567898765435
  // float: -1.234587E+08
  // int: -856982897
  number.bits[0] = 0b10111001000000010001100001111011;
  number.bits[1] = 0b01101110100110001001011011101100;
  number.bits[2] = 0b00100111111001000100001100110010;
  number.bits[3] = 0b10000000000101000000000000000000;
  int result_int = -856982897;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_25) {
  s21_decimal number;
  // decimal: 123445677.98765434567898765435
  // float: 1.234457E+08
  // int: 1290499126
  number.bits[0] = 0b00110100100000010001100001111011;
  number.bits[1] = 0b01001010011100100010011000011110;
  number.bits[2] = 0b00100111111000110010111111101001;
  number.bits[3] = 0b00000000000101000000000000000000;
  int result_int = 1290499126;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_26) {
  s21_decimal number;
  // decimal: -12345677.987654533456789876543
  // float: -1.234568E+07
  // int: -885235378
  number.bits[0] = 0b11111110001111011010111100111111;
  number.bits[1] = 0b11000000010001101000000010111010;
  number.bits[2] = 0b00100111111001000001101100000000;
  number.bits[3] = 0b10000000000101010000000000000000;
  int result_int = -885235378;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_27) {
  s21_decimal number;
  // decimal: 0.0000000000000000001
  // float: 1E-19
  // int: 535567946
  number.bits[0] = 0b00000000000000000000000000000001;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000100110000000000000000;
  int result_int = 535567946;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_28) {
  s21_decimal number;
  // decimal: 0.0000000000000000000000000001
  // float: 1E-28
  // int: 285050806
  number.bits[0] = 0b00000000000000000000000000000001;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000111000000000000000000;
  int result_int = 285050806;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_29) {
  s21_decimal number;
  // decimal: 0.0000000000000000000000000000
  // float: 0
  // int: -2147483648
  number.bits[0] = 0b00000000000000000000000000000000;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b10000000000111000000000000000000;
  int result_int = 0;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_30) {
  s21_decimal number;
  // decimal: -79228162514264337593543950335
  // float: -7.922816E+28
  // int: -276824064
  number.bits[0] = 0b11111111111111111111111111111111;
  number.bits[1] = 0b11111111111111111111111111111111;
  number.bits[2] = 0b11111111111111111111111111111111;
  number.bits[3] = 0b10000000000000000000000000000000;
  int result_int = -276824064;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_31) {
  s21_decimal number;
  // decimal: -792.28162514264337593543950335
  // float: -792.2816
  // int: -1002040826
  number.bits[0] = 0b11111111111111111111111111111111;
  number.bits[1] = 0b11111111111111111111111111111111;
  number.bits[2] = 0b11111111111111111111111111111111;
  number.bits[3] = 0b10000000000110100000000000000000;
  int result_int = -1002040826;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_32) {
  s21_decimal number;
  // decimal: -79228162514264337593543950335
  // float: -7.922816E+28
  // int: -276824064
  number.bits[0] = 0b11111111111111111111111111111111;
  number.bits[1] = 0b11111111111111111111111111111111;
  number.bits[2] = 0b11111111111111111111111111111111;
  number.bits[3] = 0b10000000000000000000000000000000;
  int result_int = -276824064;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_33) {
  s21_decimal number;
  // decimal: 2.7986531268974139743
  // float: 2.798653
  // int: 1077091618
  number.bits[0] = 0b11111110100100001101100101011111;
  number.bits[1] = 0b10000100011001000010000111101000;
  number.bits[2] = 0b00000000000000000000000000000001;
  number.bits[3] = 0b00000000000100110000000000000000;
  int result_int = 1077091618;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_34) {
  s21_decimal number;
  // decimal: 5.4564654654864768465454654846
  // float: 5.456465
  // int: 1085184861
  number.bits[0] = 0b01101110100110100110010101111110;
  number.bits[1] = 0b11100010111000110111110100101010;
  number.bits[2] = 0b10110000010011101101001100001111;
  number.bits[3] = 0b00000000000111000000000000000000;
  int result_int = 1085184861;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_35) {
  s21_decimal number;
  // decimal: -79228162514264337593543950330
  // float: -7.922816E+28
  // int: -276824064
  number.bits[0] = 0b11111111111111111111111111111010;
  number.bits[1] = 0b11111111111111111111111111111111;
  number.bits[2] = 0b11111111111111111111111111111111;
  number.bits[3] = 0b10000000000000000000000000000000;
  int result_int = -276824064;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_36) {
  s21_decimal number;
  // decimal: 32323465785678987654
  // float: 3.232346E+19
  // int: 1608534530
  number.bits[0] = 0b00000000111000111000000110000110;
  number.bits[1] = 0b11000000100101000000010011100000;
  number.bits[2] = 0b00000000000000000000000000000001;
  number.bits[3] = 0b00000000000000000000000000000000;
  int result_int = 1608534530;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_37) {
  s21_decimal number;
  // decimal: -784510454.7989898652154545652
  // float: -7.845105E+08
  // int: -834991432
  number.bits[0] = 0b00110101111110110100010111110100;
  number.bits[1] = 0b10110111000111111011101111011100;
  number.bits[2] = 0b00011001010110010101000110000001;
  number.bits[3] = 0b10000000000100110000000000000000;
  int result_int = -834991432;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_38) {
  s21_decimal number;
  // decimal: 0.324524
  // float: 0.324524
  // int: 1051076610
  number.bits[0] = 0b00000000000001001111001110101100;
  number.bits[1] = 0b00000000000000000000000000000000;
  number.bits[2] = 0b00000000000000000000000000000000;
  number.bits[3] = 0b00000000000001100000000000000000;
  int result_int = 1051076610;
  int result_error = 0;
  float my_float;
  int my_error = s21_from_decimal_to_float(number, &my_float);
  int my_int = *(int *)(void *)&my_float;
  ck_assert_int_eq(result_int, my_int);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(from_d_to_f_39) {
  s21_decimal x = {{15008, 0, 0, 0}};
  s21_set_fraction(&x, 3);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = 15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_d_to_f_40) {
  s21_decimal x = {{15008, 0, 0, NEGATIVE}};
  s21_set_fraction(&x, 3);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_d_to_f_41) {
  s21_decimal x = {{15008, 0, 0, NEGATIVE}};
  s21_set_fraction(&x, 3);
  float res1 = 0;
  int n1 = s21_from_decimal_to_float(x, NULL);
  float res2 = 0;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(from_d_to_f_42) {
  s21_decimal x = {{1505345008, 0, 0, NEGATIVE}};
  s21_set_fraction(&x, 3);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -1505345.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, from_d_to_f_0);
  tcase_add_test(tc, from_d_to_f_1);
  tcase_add_test(tc, from_d_to_f_2);
  tcase_add_test(tc, from_d_to_f_3);
  tcase_add_test(tc, from_d_to_f_4);
  tcase_add_test(tc, from_d_to_f_5);
  tcase_add_test(tc, from_d_to_f_7);
  tcase_add_test(tc, from_d_to_f_6);
  tcase_add_test(tc, from_d_to_f_7);
  tcase_add_test(tc, from_d_to_f_8);
  tcase_add_test(tc, from_d_to_f_9);
  tcase_add_test(tc, from_d_to_f_10);
  tcase_add_test(tc, from_d_to_f_11);
  tcase_add_test(tc, from_d_to_f_12);
  tcase_add_test(tc, from_d_to_f_13);
  tcase_add_test(tc, from_d_to_f_14);
  tcase_add_test(tc, from_d_to_f_15);
  tcase_add_test(tc, from_d_to_f_16);
  tcase_add_test(tc, from_d_to_f_17);
  tcase_add_test(tc, from_d_to_f_18);
  tcase_add_test(tc, from_d_to_f_19);
  tcase_add_test(tc, from_d_to_f_20);
  tcase_add_test(tc, from_d_to_f_21);
  tcase_add_test(tc, from_d_to_f_22);
  tcase_add_test(tc, from_d_to_f_23);
  tcase_add_test(tc, from_d_to_f_24);
  tcase_add_test(tc, from_d_to_f_25);
  tcase_add_test(tc, from_d_to_f_26);
  tcase_add_test(tc, from_d_to_f_27);
  tcase_add_test(tc, from_d_to_f_28);
  tcase_add_test(tc, from_d_to_f_29);
  tcase_add_test(tc, from_d_to_f_30);
  tcase_add_test(tc, from_d_to_f_31);
  tcase_add_test(tc, from_d_to_f_32);
  tcase_add_test(tc, from_d_to_f_33);
  tcase_add_test(tc, from_d_to_f_34);
  tcase_add_test(tc, from_d_to_f_35);
  tcase_add_test(tc, from_d_to_f_36);
  tcase_add_test(tc, from_d_to_f_37);
  tcase_add_test(tc, from_d_to_f_38);
  tcase_add_test(tc, from_d_to_f_39);
  tcase_add_test(tc, from_d_to_f_40);
  tcase_add_test(tc, from_d_to_f_41);
  tcase_add_test(tc, from_d_to_f_42);

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
