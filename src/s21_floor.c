#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = OK;
  if (result) {
    s21_big_decimal big_val = s21_convert_to_big(value);
    s21_big_decimal rest = s21_big_bit_truncate(big_val, &big_val);
    if (s21_get_sign(value.bits[3]) && !s21_is_big_zero(rest)) {
      s21_big_decimal unos = {0};
      unos.bits[0] = 1;
      big_val = s21_big_bit_add(big_val, unos);
    }
    error = s21_convert_to_dec(big_val, result);
    s21_set_sign(&result->bits[3], s21_get_sign(value.bits[3]));
  } else {
    error = ERROR;
  }
  return error;
}