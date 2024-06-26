#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = OK;
  if (result) {
    s21_nullify(result);
    *result = value;
    s21_set_sign(&result->bits[3], !s21_get_sign(result->bits[3]));
  } else {
    error = ERROR;
  }
  return error;
}