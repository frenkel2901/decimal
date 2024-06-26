#include <math.h>
#include <string.h>

#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int return_code = 0;

  if (!dst) {
    return_code = 1;
  } else {
    int coefficient = s21_get_sign(src.bits[3]);
    int power = s21_get_scale(src.bits[3]);
    double value = 0;

    for (int i = 95; i >= 0; i--) {
      if (s21_check_bit(src.bits[i / 32], i % 32)) value += pow(2, i);
    }

    if (coefficient == 0) {
      *dst = (float)(value / pow(10, power));
    } else {
      *dst = (float)(value / pow(10, power) * -1);
    }
  }

  return return_code;
}
