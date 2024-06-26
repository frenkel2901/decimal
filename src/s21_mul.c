#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = OK;
  /*Сначала проверить множители на ноль*/
  if (!s21_is_dec_zero(value_1) && !s21_is_dec_zero(value_2)) {
    s21_big_decimal big_result = {0};
    /*Конвертирую значения в биг*/
    s21_big_decimal big_value_1 = s21_convert_to_big(value_1);
    s21_big_decimal big_value_2 = s21_convert_to_big(value_2);
    int sign_1 = s21_get_sign(big_value_1.bits[15]);
    int sign_2 = s21_get_sign(big_value_2.bits[15]);
    big_result = s21_big_bit_mul(big_value_1, big_value_2);
    if (sign_1 == sign_2) {
      /*Выставляю в результате знак "+"*/
      s21_set_sign(&big_result.bits[15], 0);
    } else {
      /*Выставляю в результате знак "-"*/
      s21_set_sign(&big_result.bits[15], 1);
    }
    /*Подсчёт степени*/
    s21_set_scale(&big_result.bits[15],
                  s21_get_scale(big_value_1.bits[15]) +
                      s21_get_scale(big_value_2.bits[15]));
    error_code = s21_convert_to_dec(big_result, result);
    if (error_code != 0 && result != NULL) {
      s21_nullify(result);
    }
  } else {
    if (result != NULL) {
      s21_nullify(result);
    }
  }
  return error_code;
}