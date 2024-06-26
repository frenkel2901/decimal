#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = OK;
  /*Конвертирую значения в биг*/
  s21_big_decimal big_value_1 = s21_convert_to_big(value_1);
  s21_big_decimal big_value_2 = s21_convert_to_big(value_2);
  /*Узнаю знаки*/
  int sign_1 = s21_get_sign(big_value_1.bits[15]);
  int sign_2 = s21_get_sign(big_value_2.bits[15]);
  /*Нормализую значения*/
  s21_normalize_two_big(&big_value_1, &big_value_2);
  s21_big_decimal big_result = {0};
  /*Узнаю степень*/
  int scale = s21_get_scale(big_value_1.bits[15]);
  if (sign_1 == sign_2) {  // Оба знака одинаковые
    if (s21_is_greater_or_equal_big(s21_big_bit_abs(big_value_1),
                                    s21_big_bit_abs(big_value_2))) {
      big_result = s21_big_bit_sub(big_value_1, big_value_2);
      /*Выставляю в результате знак*/
      s21_set_sign(&big_result.bits[15], sign_1);
    } else {
      big_result = s21_big_bit_sub(big_value_2, big_value_1);
      /*Выставляю в результате знак*/
      s21_set_sign(&big_result.bits[15], !sign_2);
    }
  } else {  // Знаки разные
    big_result = s21_big_bit_add(big_value_1, big_value_2);
    /*Выставляю в результате знак*/
    s21_set_sign(&big_result.bits[15], sign_1);
  }
  /*Возвращаю степень*/
  s21_set_scale(&big_result.bits[15], scale);
  error_code = s21_convert_to_dec(big_result, result);
  if (error_code != 0 && result != NULL) {
    s21_nullify(result);
  }
  return error_code;
}