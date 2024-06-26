#include <string.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int value, s21_decimal *dec) {
  int return_code = 0;

  if (!dec) {
    return_code = 1;
  }

  if (return_code == 0) {
    s21_nullify(dec);

    int min_flag = 0;
    if (value < 0 && value != INT32_MIN) {
      s21_set_sign(&dec->bits[3], 1);
      value = -value;
    } else if (value == INT32_MIN) {
      s21_set_sign(&dec->bits[3], 1);
      value = -(value + 1);
      min_flag = 1;
    }

    dec->bits[0] = value;
    dec->bits[0] += min_flag;
  }

  return return_code;
}
