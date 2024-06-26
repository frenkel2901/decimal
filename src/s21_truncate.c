#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = OK;
  if (result) {
    s21_big_decimal big_val = s21_convert_to_big(value);
    s21_big_bit_truncate(big_val, &big_val);
    error = s21_convert_to_dec(big_val, result);
    s21_set_sign(&result->bits[3], s21_get_sign(value.bits[3]));
  } else {
    error = ERROR;
  }
  return error;
}