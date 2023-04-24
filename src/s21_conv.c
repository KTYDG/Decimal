#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"

#define S21_DECIMAL_MAX 79228162514264337593543950335.

enum s21_error { OK, ERROR };

/// @brief Из int
/// @param src исходное значение
/// @param dst получаемое значение
/// @return 0 - OK, 1 - ошибка конвертации
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) {
    return ERROR;
  }
  s21_clear_decimal(dst);
  if (src < 0) {
    // Ставим знак отрицательного числа
    dst->bits[3] |= 1 << 31;
    // Инверсия числа и +1 чтоб получить такое же, но положительное
    src = ~src;
    src++;
  }
  dst->bits[0] = src;
  return OK;
}

/// @brief Из float
/// @param src исходное значение
/// @param dst получаемое значение
/// @return 0 - OK, 1 - ошибка конвертации
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  enum s21_error error_code = OK;
  if (dst) {
    s21_clear_decimal(dst);
  } else {
    return ERROR;
  }
  if ((src > 0 && src < 1e-28) || src > S21_DECIMAL_MAX || !dst) {
    error_code = ERROR;
  } else {
    char fl[20] = {0};
    char in[20] = {0};
    int fraction = 0, point = 0;
    sprintf(fl, "%.7g", src);
    for (int i = 0, j = 0; fl[i] != '\0'; i++) {
      if (fl[i] >= '0' && fl[i] <= '9') {
        in[j++] = fl[i];
        if (point) {
          fraction++;
        }
      } else if (fl[i] == '.') {
        point = 1;
      } else if (fl[i] == 'e') {
        sscanf(fl + i + 2, "%d", &fraction);
        if (fl[i + 1] == '+') {
          point = 0;
          fraction -= strlen(in) - 1;
        } else {
          point = 1;
          fraction += strlen(in) - 1;
        }
        break;
      }
    }
    sscanf(in, "%d", &(dst->bits[0]));

    if (point) {
      s21_set_fraction(dst, fraction);
      s21_div_ten(dst, fraction - 28);
      while (dst->bits[0] % 10 == 0) {
        s21_div_ten(dst, 1);
      }
    } else {
      for (int i = 0; i < fraction; i++) {
        s21_mul_ten(dst);
      }
      s21_set_fraction(dst, 0);
    }

    if (src < 0) {
      dst->bits[3] |= 1 << 31;
    }
  }
  return error_code;
}

/// @brief В int
/// @param src исходное значение
/// @param dst получаемое значение
/// @return 0 - OK, 1 - ошибка конвертации
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) {
    return ERROR;
  }
  enum s21_error error_code = OK;
  // Выкидываем дробную часть в помойку
  s21_truncate(src, &src);
  // Если децимал больше 30 бит(1 бит уходит на знак у int), ошибка
  if (src.bits[2] != 0 || src.bits[1] != 0 || ((src.bits[0] >> 31) & 1)) {
    *dst = 0;
    error_code = ERROR;
  } else {
    *dst = src.bits[0];
    // Вставляем знак
    if (s21_get_sign(src)) {
      *dst = -(*dst);
    }
  }
  return error_code;
}

/// @brief В float
/// @param src исходное значение
/// @param dst получаемое значение
/// @return 0 - OK, 1 - ошибка конвертации
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return ERROR;
  }
  int fraction = s21_get_fraction(src);
  long double inc = 1.L;
  long double sum = 0;
  if (s21_is_empty(src)) {
    *dst = 0;
  } else {
    while (fraction) {
      inc *= 0.1L;
      fraction--;
    }
    long double exp = 1L;
    for (int i = 0; i < 3; i++) {
      for (int bit = 0; bit < 32; bit++) {
        if (((src.bits[i] >> bit) & 1)) {
          sum += exp * inc;
        }
        exp *= 2L;
      }
    }
    *dst = (float)sum;
    if (s21_get_sign(src)) {
      *dst = -(*dst);
    }
  }
  return OK;
}
