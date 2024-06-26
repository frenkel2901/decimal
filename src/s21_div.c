#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = OK;
  if (!s21_is_dec_zero(value_1) &&
      !s21_is_dec_zero(value_2)) {  // оба значения ненулевые
    s21_big_decimal big_value_1 = s21_convert_to_big(value_1);
    s21_big_decimal big_value_2 = s21_convert_to_big(value_2);
    s21_big_decimal big_result = {0};
    int sign_1 = s21_get_sign(big_value_1.bits[15]);
    int sign_2 = s21_get_sign(big_value_2.bits[15]);
    int scale = s21_get_scale(big_value_1.bits[15]) -
                s21_get_scale(big_value_2.bits[15]);
    if (scale < 0) {  // нормализуем делимое
      big_value_1 = s21_normalize(big_value_1, -scale);
      scale = 0;
    }
    s21_big_decimal remainder =
        s21_big_bit_div(big_value_1, big_value_2, &big_result);
    s21_set_scale(&big_result.bits[15], scale);
    while (!s21_is_big_zero(remainder) &&
           s21_get_scale(big_result.bits[15]) <= 29) {
      scale = s21_get_scale(big_result.bits[15]);
      s21_mul_by_ten_big(&big_result);
      s21_mul_by_ten_big(&remainder);
      s21_big_decimal prom_res;  // промежуточный результат деления
      remainder = s21_big_bit_div(remainder, big_value_2, &prom_res);
      big_result = s21_big_bit_add(big_result, prom_res);
      s21_set_scale(&big_result.bits[15], scale + 1);
    }
    if (sign_1 == sign_2) {
      s21_set_sign(&big_result.bits[15], 0);
    } else {
      s21_set_sign(&big_result.bits[15], 1);
    }
    error_code = s21_convert_to_dec(big_result, result);
  } else if (s21_is_dec_zero(value_2)) {  // делитель равен нулю
    error_code = DIV_BY_ZERO;
  } else {  // делимое равно нулю
    if (result != NULL) {
      s21_nullify(result);
    }
  }
  if (error_code != 0 && result != NULL) {
    s21_nullify(result);
  }
  return error_code;
}