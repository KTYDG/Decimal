#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define NEGATIVE 2147483648

// START_TEST(dec_to_int_1) {
//   s21_decimal x = {{150, 13658, 0, NEGATIVE}}; ///2 147 483 647, а это -3 496
//   598. Тест отстойный s21_set_fraction(&x, 3); int y;
//   //s21_from_decimal_to_int(x, &y);
//   ck_assert_int_eq(y, -5866);
// }
// END_TEST

// START_TEST(dec_to_int_2) {
//   s21_decimal x = {{150, 13658, 0, 0}}; /// тест отстой
//   //s21_set_fraction(&x, 3);
//   int y;
//   s21_from_decimal_to_int(x, &y);
//   ck_assert_int_eq(y, 5866);
// }
// END_TEST

// START_TEST(dec_to_int_3) {
//   s21_decimal x = {{150, 13658, 155, 0}};
//   s21_set_fraction(&x, 3);
//   int y = 0;
//   s21_from_decimal_to_int(x, &y);
//   ck_assert_int_eq(y, 0);
// }
// END_TEST

// START_TEST(dec_to_int_4) {
//   s21_decimal x = {{2100000000, 0, 0, 0}};
//   s21_set_fraction(&x, 3);
//   int y;
//   s21_from_decimal_to_int(x, &y);
//   ck_assert_int_eq(y, 2100000000);
// }
// END_TEST

// START_TEST(dec_to_int_5) {
//   s21_decimal x = {{2100000000, 0, 0, NEGATIVE}};
//   s21_set_fraction(&x, 3);
//   int y;
//   s21_from_decimal_to_int(x, &y);
//   ck_assert_int_eq(y, -2100000000);
// }
// END_TEST

// START_TEST(dec_to_int_6) {
//   s21_decimal x = {{3100000000, 0, 0, NEGATIVE}};
//   s21_set_fraction(&x, 3);
//   int y = 0;
//   s21_from_decimal_to_int(x, &y);
//   ck_assert_int_eq(y, 0);
// }

// START_TEST(dec_to_int_7) {
//   s21_decimal x = {{3100000000, 0, 0, 0}};
//   s21_set_fraction(&x, 3);
//   int y;
//   int n1 = s21_from_decimal_to_int(x, &y);
//   ck_assert_int_eq(n1, 1);
// }
// END_TEST

START_TEST(dec_to_int_8) {
  s21_decimal x = {{9, 0, 0, 0}};
  s21_set_fraction(&x, 3);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}
END_TEST

START_TEST(dec_to_int_9) {
  s21_decimal x = {{9, 0, 0, 0}};
  s21_set_fraction(&x, 3);
  int y = s21_from_decimal_to_int(x, NULL);
  ck_assert_int_eq(y, 1);
}
END_TEST

START_TEST(dec_to_int_10) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000110010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int origin = 5;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_11) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000100010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int origin = 3;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_12) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000000000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int origin = 0;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_13) {
  s21_decimal src;
  src.bits[0] = 0b00000001011100111100000111000111;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000001110000000000000000;
  int result = 0;
  int origin = -2;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_14) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000000000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000010000000000000000;
  int result = 0;
  int origin = 0;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

// START_TEST(dec_to_int_15) {
//     s21_decimal src;
//     src.bits[0] = 0b00000000000000000000000000000000;
//     src.bits[1] = 0b10000000000000000000000000000000;
//     src.bits[2] = 0b00000000000000000000000000000000;
//     src.bits[3] = 0b00000000000000000000000000000000;
//     int result = 0;
//     int origin = 0;
//     int origin_error = 0;
//     int my_error = s21_from_decimal_to_int(src, &result);
//     ck_assert_int_eq(origin, result);
//     ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

START_TEST(dec_to_int_16) {
  s21_decimal src;
  src.bits[0] = 0b00000011111000110110011011000111;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000001010000000000000000;
  int result = 0;
  int origin = 652;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_17) {
  s21_decimal src;
  src.bits[0] = 0b00011101101010010010000100011011;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000010000000000000000000;
  int result = 0;
  int origin = 4;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_18) {
  s21_decimal src;
  src.bits[0] = 0b10000111010110110010011111110011;
  src.bits[1] = 0b00000000000000000000000000000001;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000100000000000000000;
  int result = 0;
  int origin = 65658654;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_19) {
  s21_decimal src;
  src.bits[0] = 0b00010101101111011001110101001110;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000110000000000000000;
  int result = 0;
  int origin = -364748;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_20) {
  s21_decimal src;
  src.bits[0] = 0b01101000011010011010001100101111;
  src.bits[1] = 0b00000000000000000001001000010011;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000011010000000000000000;
  int result = 0;
  int origin = 1;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_21) {
  s21_decimal src;
  src.bits[0] = 0b00010110010010101110101011000000;
  src.bits[1] = 0b00000000000000000000100011111100;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000010110000000000000000;
  int result = 0;
  int origin = -98;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_22) {
  s21_decimal src;
  src.bits[0] = 0b00111011100110101100100111111001;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int origin = 99999999;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_23) {
  s21_decimal src;
  src.bits[0] = 0b11001010011010010001110011000010;
  src.bits[1] = 0b10011001110101001010110100100110;
  src.bits[2] = 0b10110000001111100010111010011101;
  src.bits[3] = 0b10000000000101110000000000000000;
  int result = 0;
  int origin = -545445;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_24) {
  s21_decimal src;
  src.bits[0] = 0b11101010011100001110100101000111;
  src.bits[1] = 0b10100010011001110000111100001010;
  src.bits[2] = 0b10110000001111101111000100010000;
  src.bits[3] = 0b00000000000101100000000000000000;
  int result = 0;
  int origin = 5454545;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_25) {
  s21_decimal src;
  src.bits[0] = 0b11101010001011100110110001010100;
  src.bits[1] = 0b00100111000110111110101011111001;
  src.bits[2] = 0b00011001101111000001110101101001;
  src.bits[3] = 0b00000000000101000000000000000000;
  int result = 0;
  int origin = 79645421;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_26) {
  s21_decimal src;
  src.bits[0] = 0b10010001000010101111010011001010;
  src.bits[1] = 0b11000000010001011101010111110010;
  src.bits[2] = 0b00100111111001000001101100000000;
  src.bits[3] = 0b00000000000101010000000000000000;
  int result = 0;
  int origin = 12345677;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_27) {
  s21_decimal src;
  src.bits[0] = 0b10010001000010101111010011001010;
  src.bits[1] = 0b11000000010001011101010111110010;
  src.bits[2] = 0b00100111111001000001101100000000;
  src.bits[3] = 0b10000000000101010000000000000000;
  int result = 0;
  int origin = -12345677;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_28) {
  s21_decimal src;
  src.bits[0] = 0b10011100101100011101000110000101;
  src.bits[1] = 0b01100001100101011101011101110110;
  src.bits[2] = 0b00000000000000000000000011101010;
  src.bits[3] = 0b00000000000100000000000000000000;
  int result = 0;
  int origin = 432356;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_29) {
  s21_decimal src;
  src.bits[0] = 0b01100001011111010111001111001001;
  src.bits[1] = 0b00000000100111100100000111010001;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000010010000000000000000;
  int result = 0;
  int origin = 44545413;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_30) {
  s21_decimal src;
  src.bits[0] = 0b01011100000110001011011001101010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000000000000000000000;
  int result = 0;
  int origin = -1545123434;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

// START_TEST(dec_to_int_31) {
//     s21_decimal src;
//     src.bits[0] = 0b00000000000000000000000000000000;
//     src.bits[1] = 0b00000000000000000000000000000000;
//     src.bits[2] = 0b10000000000000000000000000000000;
//     src.bits[3] = 0b10000000000000000000000000000000;
//     int result = 0;
//     int origin = 0;
//     int origin_error = 1;
//     int my_error = s21_from_decimal_to_int(src, &result);
//     ck_assert_int_eq(origin, result);
//     ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

START_TEST(dec_to_int_32) {
  s21_decimal src;
  src.bits[0] = 0b10101001101110110110011111111111;
  src.bits[1] = 0b00001010111111101100000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000011000000000000000000;
  int result = 0;
  int origin = 792281;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST

START_TEST(dec_to_int_33) {
  s21_decimal src;
  src.bits[0] = 0b11111110100100001101100101011111;
  src.bits[1] = 0b10000100011001000010000111101000;
  src.bits[2] = 0b00000000000000000000000000000001;
  src.bits[3] = 0b00000000000100110000000000000000;
  int result = 0;
  int origin = 2;
  int origin_error = 0;
  int my_error = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(origin, result);
  ck_assert_int_eq(origin_error, my_error);
}
END_TEST
START_TEST(dec_to_int_34) {
  int inp = 0;
  s21_decimal var1 = {{0, 0, 0, 0}};
  int res = 0;
  int error = s21_from_decimal_to_int(var1, &inp);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res, inp);
}
END_TEST

START_TEST(dec_to_int_35) {
  int inp = 0;
  s21_decimal var1 = {{2147483647, 0, 0, 0}};
  int res = 2147483647;
  int error = s21_from_decimal_to_int(var1, &inp);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res, inp);
}
END_TEST

START_TEST(dec_to_int_36) {
  int inp = 0;
  s21_decimal var1 = {{2147483648, 0, 0, 0}};
  int error = s21_from_decimal_to_int(var1, &inp);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dec_to_int_37) {
  int inp = 0;
  s21_decimal var1 = {{2147483647, 0, 0, 2147483648}};
  int res = -2147483647;
  int error = s21_from_decimal_to_int(var1, &inp);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res, inp);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  // tcase_add_test(tc, dec_to_int_1);
  // tcase_add_test(tc, dec_to_int_2);
  // tcase_add_test(tc, dec_to_int_3);
  // tcase_add_test(tc, dec_to_int_4);
  // tcase_add_test(tc, dec_to_int_5);
  // tcase_add_test(tc, dec_to_int_6);
  // tcase_add_test(tc, dec_to_int_7);
  tcase_add_test(tc, dec_to_int_8);
  tcase_add_test(tc, dec_to_int_9);
  tcase_add_test(tc, dec_to_int_10);
  tcase_add_test(tc, dec_to_int_11);
  tcase_add_test(tc, dec_to_int_12);
  tcase_add_test(tc, dec_to_int_13);
  tcase_add_test(tc, dec_to_int_14);
  // tcase_add_test(tc, dec_to_int_15);
  tcase_add_test(tc, dec_to_int_16);
  tcase_add_test(tc, dec_to_int_17);
  tcase_add_test(tc, dec_to_int_18);
  tcase_add_test(tc, dec_to_int_19);
  tcase_add_test(tc, dec_to_int_20);
  tcase_add_test(tc, dec_to_int_21);
  tcase_add_test(tc, dec_to_int_22);
  tcase_add_test(tc, dec_to_int_23);
  tcase_add_test(tc, dec_to_int_24);
  tcase_add_test(tc, dec_to_int_25);
  tcase_add_test(tc, dec_to_int_26);
  tcase_add_test(tc, dec_to_int_27);
  tcase_add_test(tc, dec_to_int_28);
  tcase_add_test(tc, dec_to_int_29);
  tcase_add_test(tc, dec_to_int_30);
  // tcase_add_test(tc, dec_to_int_31);
  tcase_add_test(tc, dec_to_int_32);
  tcase_add_test(tc, dec_to_int_33);
  tcase_add_test(tc, dec_to_int_34);
  tcase_add_test(tc, dec_to_int_35);
  tcase_add_test(tc, dec_to_int_36);
  tcase_add_test(tc, dec_to_int_37);
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
