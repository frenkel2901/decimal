#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = OK;
  if (result) {
    int scale = s21_get_scale(value.bits[3]);
    s21_big_decimal big_val = s21_convert_to_big(value);
    big_val = s21_big_rounding(big_val, scale);
    error = s21_convert_to_dec(big_val, result);
    s21_set_sign(&result->bits[3], s21_get_sign(value.bits[3]));
  } else {
    error = ERROR;
  }
  return error;
}