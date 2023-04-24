#include "s21_decimal.h"

enum s21_result { FALSE, TRUE };

/// @brief Меньше	<
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @return 0 - FALSE, 1 - TRUE
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_greater_or_equal(value_1, value_2);
}

/// @brief Меньше или равно	<=
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @return 0 - FALSE, 1 - TRUE
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_greater(value_1, value_2);
}

/// @brief Больше	>
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @return 0 - FALSE, 1 - TRUE
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  enum s21_result result = TRUE;
  int negative_1 = value_1.bits[3] >> 31 & 1;
  int negative_2 = value_2.bits[3] >> 31 & 1;
  int stop = 1;
  if (s21_is_equal(value_1, value_2)) {
    // Если числа равны - ложь
    result = FALSE;
  } else if (negative_1 && !negative_2) {
    // Если первое отрицательное, второе положительно - ложь
    result = FALSE;
  } else if (negative_1 == negative_2) {
    // Если знаки равны, сравниваем остальное
    if (!s21_set_max_fraction(&value_1, &value_2)) {
      for (int i = 2; stop && i >= 0; i--) {
        for (int bit = 31; stop && bit >= 0; bit--) {
          if (((value_1.bits[i] >> bit) & 1) == 1 &&
              ((value_2.bits[i] >> bit) & 1) == 0) {
            stop = !stop;
          } else if (((value_2.bits[i] >> bit) & 1) == 1 &&
                     ((value_1.bits[i] >> bit) & 1) == 0) {
            result = FALSE;
            stop = !stop;
          }
        }
      }
    }

    if (negative_1) {
      result = !result;
    }
  }
  return result;
}

/// @brief Больше или равно	>=
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @return 0 - FALSE, 1 - TRUE
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  enum s21_result result = TRUE;
  if (!s21_is_equal(value_1, value_2)) {
    result = s21_is_greater(value_1, value_2);
  }
  return result;
}

/// @brief Равно	==
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @return 0 - FALSE, 1 - TRUE
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  enum s21_result result = TRUE;
  // Если в результате потерялась точность - не равны
  if (s21_set_max_fraction(&value_1, &value_2)) {
    result = FALSE;
  }
  // Если знаки разные - не равны
  if (s21_get_sign(value_1) != s21_get_sign(value_2) &&
      !s21_is_empty(value_1) && !s21_is_empty(value_2)) {
    result = FALSE;
  }
  // если хотя бы одна из 3 частей отличается - не равны
  for (int i = 0; result && i < 3; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      result = FALSE;
    }
  }
  return result;
}

/// @brief Не равно	!=
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @return 0 - FALSE, 1 - TRUE
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  // Обратный результат равенства
  return !s21_is_equal(value_1, value_2);
}