#include "s21_decimal.h"

int s21_is_greater(s21_decimal val1, s21_decimal val2) {
  return s21_is_greater_big(s21_convert_to_big(val1), s21_convert_to_big(val2));
}
