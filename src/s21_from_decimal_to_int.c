#include <math.h>

#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_code = 0;

  if (!dst) {
    return_code = 1;
  } else {
    int coefficient = s21_get_sign(src.bits[3]);
    unsigned value = 0;

    s21_truncate(src, &src);

    if (src.bits[1] > 0 || src.bits[2] > 0 ||
        (coefficient == 0 && src.bits[0] > 2147483647) ||
        (coefficient == 1 && src.bits[0] > 2147483648)) {
      return_code = 1;
    } else

      for (int i = 31; i >= 0; i--) {
        if (s21_check_bit(src.bits[i / 32], i % 32)) value += pow(2, i);
      }

    if (coefficient == 0) {
      *dst = value;
    } else {
      *dst = -value;
    }
  }

  return return_code;
}
