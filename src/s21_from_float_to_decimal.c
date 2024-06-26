#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

void get_float(char *str, int *power, int *length, int *float_str);

int s21_from_float_to_decimal(float src, s21_decimal *dec) {
  int return_code = 0;
  if (!dec || (0 < fabsf(src) && fabsf(src) < 1e-28) || isnan(src) ||
      isinf(src) || 79228162514264337593543950335.f < src) {
    return_code = 1;
  } else {
    char str[200] = {0};
    int power, float_str, length = 0;
    s21_nullify(dec);
    if (src < 0) {
      s21_set_sign(&dec->bits[3], 1);
    }
    sprintf(str, "%.7g", src);
    get_float(str, &power, &length, &float_str);
    if (28 < abs(power) + length) {
      memset(str, 0, 128);
      sprintf(str, "%.*e", 29 - abs(power), src);
      get_float(str, &power, &length, &float_str);
    }
    int integer_value = abs(atoi(str));
    for (int i = 0; i < length; ++i) {
      integer_value *= 10;
    }
    integer_value += float_str;
    if (power < 0) {
      s21_set_scale(&dec->bits[3], abs(power) + length);
    } else if (!power) {
      s21_set_scale(&dec->bits[3], length);
    }
    for (int i = 0; integer_value; ++i, integer_value /= 2) {
      if (integer_value % 2) {
        s21_set_bit(&dec->bits[i / 32], i, 1);
      }
    }
    if (0 < power - length) {
      s21_decimal s21_mul_by_10 = {{10, 0, 0, 0}};
      for (int i = 0; i < power - length; ++i) {
        return_code = s21_mul(*dec, s21_mul_by_10, dec);
      }
    }
  }
  return return_code;
}

void get_float(char *str, int *power, int *length, int *float_str) {
  char *dot = strchr(str, '.');
  char *exponenta = strchr(str, 'e');

  *power = 0;
  *float_str = 0;
  *length = 0;

  if (exponenta) {
    *exponenta++ = '\0';
    *power = atoi(exponenta);
  }

  if (dot) {
    *dot++ = '\0';
    *length = strlen(dot);
    *float_str = atoi(dot);
  }
}
