
#include <stdio.h>

#include "s21_decimal.h"

enum s21_error { OK, INF, N_INF, NAN };
enum s21_result { FALSE, TRUE };

/// @brief Очистка/зануление числа
/// @param number децимал
void s21_clear_big_decimal(big_decimal *number) {
  for (int i = 0; i <= NUMS; i++) {
    // Проставляем везде 0
    number->bits[i] = 0;
  }
}

/// @brief Делает из s21_dec -> big_dec
/// @param src
/// @param dst
void s21_make_bigger(s21_decimal src, big_decimal *dst) {
  src.bits[3] <<= 1;
  src.bits[3] >>= 1;
  int i = 0;
  for (; i < 3; i++) {
    dst->bits[i] = src.bits[i];
  }
  for (; i <= NUMS; i++) {
    dst->bits[i] = 0;
  }
  dst->bits[OPTS] = src.bits[3];
}

/// @brief Делает из big_dec -> s21_dec
/// @param src
/// @param dst
/// @return 0 - конвертация невозможна, 1 - отлично
int s21_make_smaller(big_decimal src, s21_decimal *dst) {
  int rem = 0;
  while (((src.bits[5] > 0 || src.bits[4] > 0 || src.bits[3] > 0) &&
          s21_get_big_fraction(src) > 0) ||
         s21_get_big_fraction(src) > 28) {
    rem = s21_div_ten_nr_big(&src, 1);
  }
  if (rem >= 5) {
    big_decimal one = {{1, 0, 0, 0, 0}};
    s21_add_big_bits(src, one, &src);
  }
  big_decimal copy = src;
  while (s21_get_big_fraction(src) > 0 && !s21_div_ten_nr_big(&copy, 1)) {
    src = copy;
  }
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[OPTS];
  return src.bits[5] > 0 || src.bits[4] > 0 || src.bits[3] > 0 ||
         s21_is_big_empty(src);
}

/// @brief Получение знака числа
/// @param nгmber децимал
/// @return 0 - положительное, 1 - отрицательное
unsigned int s21_get_big_sign(big_decimal number) {
  unsigned int options = number.bits[OPTS];
  options >>= 31;
  return options;
}

/// @brief Проверка на равенство нулю
/// @param number децимал
/// @return 0 - не равен нулю, 1 - равен нулю
int s21_is_big_empty(big_decimal number) {
  int result = 1;
  for (int i = 0; result && i < NUMS; i++) {
    if (number.bits[i] != 0) {
      result = 0;
    }
  }
  return result;
}

/// @brief Получение степени коэффициента масштабирования
/// @param number децимал
/// @return степень коэффициента масштабирования
unsigned int s21_get_big_fraction(big_decimal number) {
  unsigned int options = number.bits[OPTS];
  options <<= 1;
  options >>= 17;
  return options;
}

/// @brief Установка степени коэффициента масштабирования
/// @param number децимал
/// @return степень коэффициента масштабирования
void s21_set_big_fraction(big_decimal *number, unsigned int fraction) {
  fraction <<= 16;
  unsigned int old_fraction = s21_get_big_fraction(*number);
  old_fraction <<= 16;
  unsigned int sign = number->bits[OPTS] - old_fraction;
  number->bits[OPTS] = fraction + sign;
}

/// @brief Равно	==
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @return 0 - FALSE, 1 - TRUE
int s21_is_big_equal(big_decimal value_1, big_decimal value_2) {
  enum s21_result result = TRUE;
  // Если в результате потерялась точность - не равны
  if (s21_get_big_fraction(value_1) != s21_get_big_fraction(value_2)) {
    result = FALSE;
  }
  // Если знаки разные - не равны
  if (s21_get_big_sign(value_1) != s21_get_big_sign(value_1) &&
      !s21_is_big_empty(value_1) && !s21_is_big_empty(value_2)) {
    result = FALSE;
  }
  // если хотя бы одна из 4 частей отличается - не равны
  for (int i = 0; result && i <= NUMS; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      result = FALSE;
    }
  }
  return result;
}

// @brief Больше	>
/// @param value_1 первое значение
/// @param value_2 второе значение
/// @return 0 - FALSE, 1 - TRUE
int s21_is_big_greater(big_decimal value_1, big_decimal value_2) {
  enum s21_result result = TRUE;
  int negative_1 = s21_get_big_sign(value_1);
  int negative_2 = s21_get_big_sign(value_2);
  int stop = 1;
  if (s21_is_big_equal(value_1, value_2)) {
    // Если числа равны - ложь
    result = FALSE;
  } else if (negative_1 && !negative_2) {
    // Если первое отрицательное, второе положительно - ложь
    result = FALSE;
  } else if (negative_1 == negative_2) {
    // Если знаки равны, сравниваем остальное
    // if (!s21_set_max_big_fraction(&value_1, &value_2)) {
    for (int i = NUMS; stop && i >= 0; i--) {
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
int s21_is_big_greater_or_equal(big_decimal value_1, big_decimal value_2) {
  enum s21_result result = TRUE;
  if (!s21_is_big_equal(value_1, value_2)) {
    result = s21_is_big_greater(value_1, value_2);
  }
  return result;
}

/// @brief Смещает биты числа вправо(УМЕНЬШЕНИЕ ЧИСЛА)
/// @param number децимал
/// @param offset смещение
void s21_offset_big_right(big_decimal *number, int offset) {
  for (int i = 0; i <= NUMS; i++) {
    int stop = 1;
    for (int bit = 0; stop && bit < 32; bit++) {
      if (i == 0 || (offset - bit) <= 0) {
        number->bits[i] >>= offset;
        stop = 0;
      } else {
        number->bits[i - 1] ^=
            (-((number->bits[i] >> bit) & 1) ^ number->bits[i - 1]) &
            (1 << (32 - offset + bit));
      }
    }
  }
}

/// @brief Смещает биты числа влево(УВЕЛИЧЕНИЕ ЧИСЛА)
/// @param number децимал
/// @param offset смещение
void s21_offset_big_left(big_decimal *number, int offset) {
  for (int i = NUMS; i >= 0; i--) {
    int stop = 1;
    for (int bit = 31; stop && bit >= 0; bit--) {
      if (i == NUMS || (bit + offset) <= 31) {
        number->bits[i] <<= offset;
        stop = 0;
      } else {
        number->bits[i + 1] ^=
            (-((number->bits[i] >> bit) & 1) ^ number->bits[i + 1]) &
            (1 << (bit + offset - 32));
      }
    }
  }
}

/// @brief Сложение двух
/// @param v1 первый
/// @param v2 второй
/// @param r результат сложения
/// @return есть ли переполнение
int s21_add_big_bits(big_decimal v1, big_decimal v2, big_decimal *r) {
  int add = 0;
  s21_clear_big_decimal(r);

  for (int i = 0; i <= NUMS; i++) {
    for (int bit = 0; bit < 32; bit++) {
      // Если оба бита равны 0 или 1, то оставим 0
      if (((v1.bits[i] >> bit) & 1) == ((v2.bits[i] >> bit) & 1)) {
        // Если прошлое сложение битов было с избытком, ставим 1
        if (add) {
          r->bits[i] |= 1 << bit;
          // Убираем избыток
          add = 0;
        }
        // Если оба бита равны единице, ставим избыток
        if (((v1.bits[i] >> bit) & 1) == 1) {
          add = 1;
        }
      } else {
        // Если оба бита разные, ставим 1
        r->bits[i] |= 1 << bit;
        // Если прошлое сложение битов было с избытком, ставим 0
        if (add) {
          r->bits[i] &= ~(1 << bit);
          // Избыток оставляем
        }
      }
    }
  }
  return add;
}

/// @brief Вычитание двух децималов
/// @param v1 первый
/// @param v2 второй
/// @param r результат вычитания
void s21_sub_big_bits(big_decimal v1, big_decimal v2, big_decimal *r) {
  int borrow = 0;
  s21_clear_big_decimal(r);

  for (int i = 0; i <= NUMS; i++) {
    for (int bit = 0; bit < 32; bit++) {
      // Если оба бита равны 0 или 1, то оставим 0
      if (((v1.bits[i] >> bit) & 1) == ((v2.bits[i] >> bit) & 1)) {
        // Если прошлое вычитание битов было с займом, ставим 1
        if (borrow) {
          r->bits[i] |= 1 << bit;
        }
      } else {
        // Если оба бита разные, ставим 1
        r->bits[i] |= 1 << bit;
        // Если прошлое вычитание битов было с займом, ставим 0
        if (borrow) {
          r->bits[i] &= ~(1 << bit);
          // Если бит v1 == 1, займ убрать
          if ((v1.bits[i] >> bit) & 1) {
            borrow = 0;
          }
        }
        // Если бит v1 == 0, займ взять
        if (!((v1.bits[i] >> bit) & 1)) {
          borrow = 1;
        }
      }
    }
  }
}

/// @brief Умножение двух децималов
/// @param v1 первый
/// @param v2 второй
/// @param r результат умножения
/// @return код ошибки
int s21_mul_big_bits(big_decimal v1, big_decimal v2, big_decimal *r) {
  enum s21_error error_code = OK;
  s21_clear_big_decimal(r);

  int num_is_inf = 0;
  int both_sign = s21_get_big_sign(v1) == s21_get_big_sign(v2) ? 1 : 0;

  for (int i = 0; !error_code && i <= NUMS; i++) {
    for (int bit = 0; !error_code && bit < 32; bit++) {
      if (((v1.bits[i] >> bit) & 1) == 1) {
        error_code = s21_add_big_bits(*r, v2, r);
        if (!both_sign && num_is_inf) {
          error_code = N_INF;
        } else if (num_is_inf) {
          error_code = INF;
        }
      }
      if (((v2.bits[NUMS] >> 31) & 1) == 1) {
        num_is_inf = 1;
      }
      s21_offset_big_left(&v2, 1);
    }
  }
  return error_code;
}

/// @brief Деление двух децималов
/// @param v1 первый
/// @param v2 второй
/// @param r результат умножения
/// @return децимал - остаток от деления
big_decimal s21_div_big_bits(big_decimal v1, big_decimal v2, big_decimal *r) {
  s21_clear_big_decimal(r);

  int max = 0;
  for (; max < 32 * OPTS; max++) {
    if ((v2.bits[NUMS] >> 31) & 1) {
      break;
    }
    s21_offset_big_left(&v2, 1);
  }
  for (int i = 0; i < max; i++) {
    if (s21_is_big_greater_or_equal(v1, v2)) {
      s21_sub_big_bits(v1, v2, &v1);
      r->bits[0] |= 1 << 0;
    }
    s21_offset_big_right(&v2, 1);
    s21_offset_big_left(r, 1);
  }
  if (s21_is_big_greater_or_equal(v1, v2)) {
    s21_sub_big_bits(v1, v2, &v1);
    r->bits[0] |= 1 << 0;
  }
  s21_set_big_fraction(r, s21_get_big_fraction(v1));
  return v1;
}

/// @brief Увеличивает незначащие нули в точность на 1
/// @param value децимал
/// @return код ошибки
int s21_mul_ten_big(big_decimal *value) {
  // Например превратить число 123,123 -> 123,1230
  big_decimal ten = {{10, 0, 0, 0}};
  int fraction = s21_get_big_fraction(*value);

  if (fraction > 0) {
    s21_set_big_fraction(value, fraction - 1);
  }

  return s21_mul_big_bits(*value, ten, value);
}

/// @brief Уменьшает точность на times-раз и НЕ проводит округление
/// @param value децимал
/// @param times-раз делить
/// @return остаток
int s21_div_ten_nr_big(big_decimal *value, int times) {
  // Например превратить число 123,129 -> 123,13 (times = 1)

  big_decimal ten = {{10, 0, 0, 0, 0}};
  unsigned int fraction = s21_get_big_fraction(*value);
  unsigned int value_options = value->bits[OPTS];
  value->bits[OPTS] = 0;
  big_decimal reminder;
  s21_clear_big_decimal(&reminder);
  reminder.bits[OPTS] = 0;

  while (times-- > 0) {
    fraction--;
    reminder = s21_div_big_bits(*value, ten, value);
  }
  value->bits[OPTS] = value_options;
  s21_set_big_fraction(value, fraction);
  return reminder.bits[0];
}

// /// @brief Уменьшает точность на times-раз и проводит округление
// /// @param value децимал
// /// @param times-раз делить
// /// @return остаток
// int s21_div_ten_big(big_decimal *value, int times) {
//   // Например превратить число 123,129 -> 123,13 (times = 1)

//   int reminder = s21_div_ten_nr_big(value, times);
//   if (reminder >= 5) {
//     big_decimal one = {{1, 0, 0, 0, 0}};
//     s21_add_big_bits(*value, one, value);
//     reminder -= 5;
//   }
//   return reminder;
// }

// void b_big(big_decimal d) {
//   if (s21_get_big_sign(d)) {
//     printf("NEGATIVE::");
//   } else {
//     printf("POSITIVE::");
//   }
//   printf("fraction:%2d::", s21_get_big_fraction(d));
//   for (int i = NUMS; i >= 0; i--) {
//     bits(d.bits[i]);
//   }
//   printf("\n");
// }
