#include "s21_decimal.h"

enum s21_error { OK, INF, N_INF, NAN, NIL };
/*
  0 - OK
  1 - INF   - число слишком велико или равно бесконечности
  2 - N_INF - число слишком мало или равно отрицательной бесконечности
  3 - NAN   - деление на 0
*/

/*
  bits[3] содержит коэффициент масштабирования и знак, и состоит из следующих
  частей:

  Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю.
  Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
  указывает степень 10 для разделения целого числа.
  Биты с 24 по 30 не используются и должны быть равны нулю.
  Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный.
*/

/// @brief Сложение	+
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @param result результат оператора
/// @return Код ошибки
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return NIL;
  }
  enum s21_error error_code = OK;
  s21_set_max_fraction(&value_1, &value_2);
  s21_clear_decimal(result);
  s21_set_fraction(result, s21_get_fraction(value_1));
  int negative_1 = value_1.bits[3] >> 31 & 1;
  int negative_2 = value_2.bits[3] >> 31 & 1;
  // Сложение, так как знак значений совпадает
  if (negative_1 == negative_2 && !error_code) {
    int add = s21_add_bits(value_1, value_2, result);
    // Если числа отрицательные, результат тоже отрицательный
    if (negative_1) {
      result->bits[3] |= 1 << 31;
    }
    // если произошло переполнение, выводим код ошибки
    if (add) {
      if (s21_get_fraction(value_1) > 0 && s21_get_fraction(value_2) > 0) {
        int reminder = s21_div_ten(&value_1, 1),
            reminder2 = s21_div_ten(&value_2, 1);
        if (reminder + reminder2 >= 5) {
          s21_decimal one = {{1, 0, 0, 0}};
          s21_add_bits(value_1, one, &value_1);
        }
        error_code = s21_add(value_1, value_2, result);

      } else if (negative_1) {
        error_code = N_INF;
      } else if (!negative_1) {
        error_code = INF;
      }
    }
  } else if (!error_code) {
    // Вычитание, так как знак значений отличается
    // Зануление знака
    value_1.bits[3] &= ~(1 << 31);
    value_2.bits[3] &= ~(1 << 31);
    if (negative_2) {
      error_code = s21_sub(value_1, value_2, result);
    } else {
      error_code = s21_sub(value_2, value_1, result);
    }
  }
  if (s21_is_empty(*result)) {
    s21_clear_decimal(result);
  }
  return error_code;
}

/// @brief Вычитание -
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @param result результат оператора
/// @return Код ошибки
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return NIL;
  }
  enum s21_error error_code = OK;
  s21_set_max_fraction(&value_1, &value_2);
  s21_clear_decimal(result);
  s21_set_fraction(result, s21_get_fraction(value_1));
  int negative_1 = value_1.bits[3] >> 31 & 1;
  int negative_2 = value_2.bits[3] >> 31 & 1;
  // Зануление знака
  value_1.bits[3] &= ~(1 << 31);
  value_2.bits[3] &= ~(1 << 31);
  // Если знаки не совпадают, то это сложение
  if (negative_1 != negative_2 && !error_code) {
    error_code = s21_add(value_1, value_2, result);
    if (negative_1) {
      result->bits[3] |= 1 << 31;
    }
  } else {
    if (s21_is_greater_or_equal(value_1, value_2)) {
      s21_sub_bits(value_1, value_2, result);
      if (negative_1 && !s21_is_empty(*result)) {
        result->bits[3] |= 1 << 31;
      }
      // НЕ УВЕРЕН ЧТО НУЖЕН КОД ОШИБКИ, ОН НЕ СДЕЛАН
    } else if (!error_code) {
      s21_sub_bits(value_2, value_1, result);
      if (!negative_1 && !s21_is_empty(*result)) {
        result->bits[3] |= 1 << 31;
      }
    }
  }
  if (s21_is_empty(*result)) {
    s21_clear_decimal(result);
  }
  return error_code;
}

/// @brief Умножение *
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @param result результат оператора
/// @return Код ошибки
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return NIL;
  }
  enum s21_error error_code = OK;
  s21_clear_decimal(result);
  if (s21_is_empty(value_2) || s21_is_empty(value_1)) {
    return error_code;
  } else {
    int both_sign =
        (value_1.bits[3] >> 31 & 1) == (value_2.bits[3] >> 31 & 1) ? 1 : 0;
    // Зануление знака
    value_1.bits[3] &= ~(1 << 31);
    value_2.bits[3] &= ~(1 << 31);
    big_decimal big1, big2, rbig;
    s21_make_bigger(value_1, &big1);
    s21_make_bigger(value_2, &big2);
    s21_make_bigger(*result, &rbig);

    error_code = s21_mul_big_bits(big1, big2, &rbig);
    // while (error_code != OK && s21_get_big_fraction(big1) > 0 &&
    //        s21_get_big_fraction(big2) > 0) {
    //   if (error_code != OK) {
    //     s21_low_fraction(&big1, &big2);
    //   }
    //   error_code = s21_mul_big_bits(big1, big2, &rbig);
    // }

    if (!error_code) {
      s21_set_big_fraction(
          &rbig, s21_get_big_fraction(big1) + s21_get_big_fraction(big2));
      if (!both_sign) {
        rbig.bits[OPTS] |= 1 << 31;
      }
      if (s21_make_smaller(rbig, result)) {
        if (both_sign) {
          error_code = INF;
        } else {
          error_code = N_INF;
        }
      }
    } else {
      if (both_sign) {
        error_code = INF;
      } else {
        error_code = N_INF;
      }
    }
  }
  return error_code;
}

/// @brief Деление /
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @param result результат оператора
/// @return Код ошибки
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return NIL;
  }
  enum s21_error error_code = OK;
  s21_clear_decimal(result);
  int fraction2 = s21_get_fraction(value_2),
      fraction1 = s21_get_fraction(value_1);
  if (fraction1 >= fraction2) {
    fraction1 -= fraction2;
    fraction2 = 0;
  } else {
    fraction2 -= fraction1;
    fraction1 = 0;
  }
  s21_set_fraction(&value_1, fraction1);
  s21_set_fraction(&value_2, 0);

  if (s21_is_empty(value_2)) {
    error_code = NAN;
  } else {
    big_decimal big1, big2, rbig;
    s21_make_bigger(value_1, &big1);
    s21_make_bigger(value_2, &big2);
    s21_make_bigger(*result, &rbig);
    for (int i = fraction2; i > 0; i--) {
      s21_mul_ten_big(&big1);
    }
    big_decimal copy = big1;
    for (; fraction1 < 31 && !s21_mul_ten_big(&copy); fraction1++) {
      big1 = copy;
    }
    s21_set_big_fraction(&big1, fraction1);
    s21_div_big_bits(big1, big2, &rbig);

    if (s21_make_smaller(rbig, result)) {
      if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
        error_code = INF;
      } else {
        error_code = N_INF;
      }
    }
    // Проверяем одинаковые ли знаки
    if ((value_1.bits[3] >> 31 & 1) != (value_2.bits[3] >> 31 & 1)) {
      result->bits[3] |= 1 << 31;
    }
  }
  return error_code;
}
