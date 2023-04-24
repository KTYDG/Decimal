#include "s21_decimal.h"

enum s21_error { OK, ERROR };

/// @brief Округляет указанное Decimal число до ближайшего целого числа в
/// сторону отрицательной бесконечности.
/// @param value исходное значение
/// @param result получаемое значение
/// @return 0 - OK, 1 - ошибка вычисления
int s21_floor(s21_decimal value, s21_decimal *result) {
  enum s21_error error_code = ERROR;
  s21_decimal one = {{1, 0, 0, 0}}, temp = {{0, 0, 0, 0}};

  if (result && s21_get_fraction(value) < 29) {
    error_code = OK;
    if (s21_get_sign(value)) {
      error_code = s21_truncate(value, &temp);
      error_code = s21_sub(temp, one, result);
    } else {
      error_code = s21_truncate(value, result);
    }
  }
  return error_code;
}

/// @brief Округляет Decimal до ближайшего целого числа.
/// @param value исходное значение
/// @param result получаемое значение
/// @return 0 - OK, 1 - ошибка вычисления
int s21_round(s21_decimal value, s21_decimal *result) {
  enum s21_error error_code = ERROR;
  if (result && s21_get_fraction(value) < 29) {
    error_code = OK;
    s21_div_ten(&value, s21_get_fraction(value));
    *result = value;
  }
  return error_code;
}

/// @brief Возвращает целые цифры указанного Decimal числа;
/// любые дробные цифры отбрасываются, включая конечные нули.
/// @param value исходное значение
/// @param result получаемое значение
/// @return 0 - OK, 1 - ошибка вычисления
int s21_truncate(s21_decimal value, s21_decimal *result) {
  enum s21_error error_code = ERROR;
  if (result && s21_get_fraction(value) < 29) {
    error_code = OK;
    int fraction = s21_get_fraction(value);

    while (fraction > 0) {
      s21_decimal ten = {{10, 0, 0, 0}};
      s21_decimal value_copy = value;
      value_copy.bits[3] = 0;

      s21_set_fraction(&value, (fraction--) - 1);

      if (!s21_is_empty(value_copy)) {
        s21_div_bits(value_copy, ten, &value);
      }
    }
    *result = value;
  }
  return error_code;
}

/// @brief Возвращает результат умножения указанного Decimal на -1.
/// @param value исходное значение
/// @param result получаемое значение
/// @return 0 - OK, 1 - ошибка вычисления
int s21_negate(s21_decimal value, s21_decimal *result) {
  enum s21_error error_code = ERROR;
  if (result && s21_get_fraction(value) < 29) {
    error_code = OK;
    value.bits[3] ^= 1 << 31;
    *result = value;
  }
  return error_code;
}