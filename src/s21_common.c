#include <stdio.h>

#include "s21_decimal.h"

enum s21_error { OK, INF, N_INF, NAN };

/// @brief Очистка/зануление числа
/// @param number децимал
void s21_clear_decimal(s21_decimal *number) {
  for (int i = 0; i < 4; i++) {
    // Проставляем везде 0
    number->bits[i] = 0;
  }
}

/// @brief Проверка на равенство нулю
/// @param number децимал
/// @return 0 - не равен нулю, 1 - равен нулю
int s21_is_empty(s21_decimal number) {
  int result = 0;
  if (number.bits[0] == 0 && number.bits[1] == 0 && number.bits[2] == 0) {
    result = 1;
  }
  return result;
}

/// @brief Получение степени коэффициента масштабирования
/// @param number децимал
/// @return степень коэффициента масштабирования
unsigned int s21_get_fraction(s21_decimal number) {
  unsigned int options = number.bits[3];
  options <<= 1;
  options >>= 17;
  return options;
}

/// @brief Получение знака числа
/// @param nгmber децимал
/// @return 0 - положительное, 1 - отрицательное
unsigned int s21_get_sign(s21_decimal number) {
  unsigned int options = number.bits[3];
  options >>= 31;
  return options;
}

/// @brief Установка степени коэффициента масштабирования
/// @param number децимал
/// @return степень коэффициента масштабирования
void s21_set_fraction(s21_decimal *number, unsigned int fraction) {
  fraction <<= 16;
  unsigned int old_fraction = s21_get_fraction(*number);
  old_fraction <<= 16;
  unsigned int sign = number->bits[3] - old_fraction;
  number->bits[3] = fraction + sign;
}

/// @brief Смещает биты числа вправо(УМЕНЬШЕНИЕ ЧИСЛА)
/// @param number децимал
/// @param offset смещение
void s21_offset_right(s21_decimal *number, int offset) {
  for (int i = 0; i < 3; i++) {
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
void s21_offset_left(s21_decimal *number, int offset) {
  for (int i = 2; i >= 0; i--) {
    int stop = 1;
    for (int bit = 31; stop && bit >= 0; bit--) {
      if (i == 2 || (bit + offset) <= 31) {
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

/// @brief Устанавливает максимальную мантиссу числам
/// @param v1 первый децимал
/// @param v2 второй децимал
/// @return остаток от округления при переполнении
int s21_set_max_fraction(s21_decimal *v1, s21_decimal *v2) {
  int fraction_1 = s21_get_fraction(*v1);
  int fraction_2 = s21_get_fraction(*v2);
  int fraction_n = fraction_1;
  int max = fraction_1 > fraction_2 ? fraction_1 - fraction_2
                                    : fraction_2 - fraction_1;
  int reminder = 0;

  // Увеличиваем мантиссу у числа, насколько это возможно
  if (fraction_1 > fraction_2) {
    fraction_n = fraction_2;
    s21_decimal copy = *v2;
    for (int i = 0; !s21_mul_ten(&copy) && i < max; i++) {
      *v2 = copy;
      fraction_n++;
    }
    reminder = s21_div_ten(v1, fraction_1 - fraction_n);
  } else if (fraction_1 < fraction_2) {
    fraction_n = fraction_1;
    s21_decimal copy = *v1;
    for (int i = 0; !s21_mul_ten(&copy) && i < max; i++) {
      *v1 = copy;
      fraction_n++;
    }
    reminder = s21_div_ten(v2, fraction_2 - fraction_n);
  }
  return reminder;
}

/// @brief Сложение двух
/// @param v1 первый
/// @param v2 второй
/// @param r результат сложения
/// @return есть ли переполнение
int s21_add_bits(s21_decimal v1, s21_decimal v2, s21_decimal *r) {
  int add = 0;
  r->bits[0] = 0;
  r->bits[1] = 0;
  r->bits[2] = 0;
  for (int i = 0; i < 3; i++) {
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
void s21_sub_bits(s21_decimal v1, s21_decimal v2, s21_decimal *r) {
  int borrow = 0;
  r->bits[0] = 0;
  r->bits[1] = 0;
  r->bits[2] = 0;

  for (int i = 0; i < 3; i++) {
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
  // return borrow;
}

/// @brief Умножение двух децималов
/// @param v1 первый
/// @param v2 второй
/// @param r результат умножения
/// @return код ошибки
int s21_mul_bits(s21_decimal v1, s21_decimal v2, s21_decimal *r) {
  enum s21_error error_code = OK;
  r->bits[0] = 0;
  r->bits[1] = 0;
  r->bits[2] = 0;

  int num_is_inf = 0;
  int both_sign = (v1.bits[3] >> 31 & 1) == (v2.bits[3] >> 31 & 1) ? 1 : 0;

  for (int i = 0; !error_code && i < 3; i++) {
    for (int bit = 0; !error_code && bit < 32; bit++) {
      if (((v1.bits[i] >> bit) & 1) == 1) {
        error_code = s21_add_bits(*r, v2, r);
        if (!both_sign && num_is_inf) {
          error_code = N_INF;
        } else if (num_is_inf) {
          error_code = INF;
        }
      }
      if (((v2.bits[2] >> 31) & 1) == 1) {
        num_is_inf = 1;
      }
      s21_offset_left(&v2, 1);
    }
  }
  return error_code;
}

/// @brief Деление двух децималов
/// @param v1 первый
/// @param v2 второй
/// @param r результат умножения
/// @return децимал - остаток от деления
s21_decimal s21_div_bits(s21_decimal v1, s21_decimal v2, s21_decimal *r) {
  r->bits[0] = 0;
  r->bits[1] = 0;
  r->bits[2] = 0;

  if (!s21_is_empty(v1) && s21_is_greater_or_equal(v1, v2)) {
    int max = 0;
    for (; max < 96; max++) {
      if ((v2.bits[2] >> 31) & 1) {
        break;
      }
      s21_offset_left(&v2, 1);
    }
    for (int i = 0; i < max; i++) {
      if (s21_is_greater_or_equal(v1, v2)) {
        s21_sub_bits(v1, v2, &v1);
        r->bits[0] |= 1 << 0;
      }
      s21_offset_right(&v2, 1);
      s21_offset_left(r, 1);
    }
    if (s21_is_greater_or_equal(v1, v2)) {
      s21_sub_bits(v1, v2, &v1);
      r->bits[0] |= 1 << 0;
    }
  }
  return v1;
}

/// @brief Уменьшает точность на times-раз и проводит округление
/// @param value децимал
/// @param times-раз делить на 10
/// @return остаток
int s21_div_ten(s21_decimal *value, int times) {
  // Например превратить число 123,129 -> 123,13 (times = 1)

  s21_decimal ten = {{10, 0, 0, 0}};
  unsigned int fraction = s21_get_fraction(*value);
  unsigned int value_options = value->bits[3];
  value->bits[3] = 0;
  s21_decimal reminder;
  s21_clear_decimal(&reminder);

  while (times-- > 0) {
    fraction--;
    reminder = s21_div_bits(*value, ten, value);
  }
  value->bits[3] = value_options;
  s21_set_fraction(value, fraction);
  if (reminder.bits[0] >= 5) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_add_bits(*value, one, value);
    reminder.bits[0] = 0;
  }
  return reminder.bits[0];
}

/// @brief Увеличивает незначащие нули в точность на 1
/// @param value децимал
/// @return код ошибки
int s21_mul_ten(s21_decimal *value) {
  // Например превратить число 123,123 -> 123,1230
  s21_decimal ten = {{10, 0, 0, 0}};
  int fraction = s21_get_fraction(*value);

  s21_set_fraction(value, fraction + 1);

  return s21_mul_bits(*value, ten, value);
}

// void bits(unsigned int a) {
//   // anna i;
//   // memcpy(&i, &a, sizeof(int));
//   char buffer[33] = {0};
//   char *p = buffer + 32;
//   unsigned long long tmp = a;
//   for (int i = 0; i < 32; ++i) {
//     *(--p) = (tmp & 0x1) + '0';
//     tmp >>= 1;
//   }
//   printf("%s ", buffer);
// }

// void b(s21_decimal d) {
//   if (s21_get_sign(d)) {
//     printf("NEGATIVE :: ");
//   } else {
//     printf("POSITIVE :: ");
//   }
//   printf("fraction: %2d :: ", s21_get_fraction(d));
//   for (int i = 2; i >= 0; i--) {
//     bits(d.bits[i]);
//   }
//   printf("\n");
// }