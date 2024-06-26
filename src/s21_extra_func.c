#include "s21_extra_func.h"

int s21_check_bit(unsigned bit, int order) {
  return (bit & (1u << order)) >> order;
}

void s21_set_bit(unsigned *bit, int order, int value) {
  if (value == 1) {
    s21_turn_on_bit(bit, order);
  } else {
    s21_turn_off_bit(bit, order);
  }
}

void s21_turn_on_bit(unsigned *bit, int order) { *bit = *bit | (1 << order); }

void s21_turn_off_bit(unsigned *bit, int order) {
  *bit = *bit & (~(1 << order));
}

int s21_get_scale(unsigned dec) {
  s21_last_bit last_bit;
  last_bit.bits = dec;
  return last_bit.power;
}

void s21_set_scale(unsigned *dec, int power) {
  s21_last_bit last_bit;
  last_bit.bits = *dec;
  last_bit.power = power;
  *dec = last_bit.bits;
}

// void print_bin(unsigned num) {
//   long unsigned int i = 0;
//   char s[sizeof(int) * 8 + 1];
//   while (i < sizeof(int) * 8) {
//     s[i] = num % 2;
//     num /= 2;
//     i++;
//   }
//   for (int j = i - 1; j >= 0; j--) {
//     printf("%d", s[j]);
//   }
// }

int s21_get_sign(unsigned dec) {
  s21_last_bit last_bit;
  last_bit.bits = dec;
  return last_bit.sign;
}

void s21_set_sign(unsigned *dec, int sign) {
  s21_last_bit last_bit;
  last_bit.bits = *dec;
  last_bit.sign = sign;
  *dec = last_bit.bits;
}

int s21_get_big_bit(const s21_big_decimal value, int bit) {
  return s21_check_bit(value.bits[bit / 32], bit % 32);
}

s21_big_decimal s21_big_bit_add(s21_big_decimal value_1,
                                s21_big_decimal value_2) {
  s21_big_decimal result = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int buffer = 0;
  for (int i = 0; i < 15 * 32; i++) {
    int cur_bit_1 = s21_get_big_bit(value_1, i);
    int cur_bit_2 = s21_get_big_bit(value_2, i);
    if (!cur_bit_1 && !cur_bit_2) {  // оба бита нулевые
      s21_set_bit(&result.bits[i / 32], i % 32, buffer);
      if (buffer) {
        buffer = 0;
      }
    } else if (cur_bit_1 != cur_bit_2) {  // биты разные
      s21_set_bit(&result.bits[i / 32], i % 32, !buffer);
      if (buffer) {
        buffer = 1;
      }
    } else {  // оба бита равны 1
      s21_set_bit(&result.bits[i / 32], i % 32, buffer);
      buffer = 1;
    }
  }
  return result;
}

s21_big_decimal s21_big_bit_sub(s21_big_decimal value_1,
                                s21_big_decimal value_2) {
  s21_big_decimal result;
  s21_nullify_big(&result);
  int buffer = 0;
  for (int i = 0; i < 15 * 32; i++) {
    int cur_bit_1 = s21_get_big_bit(value_1, i);
    int cur_bit_2 = s21_get_big_bit(value_2, i);
    if (!cur_bit_1 && !cur_bit_2) {  // оба бита нулевые
      s21_set_bit(&result.bits[i / 32], i % 32, buffer);
    } else if (cur_bit_1 == 1 && cur_bit_2 == 0) {
      s21_set_bit(&result.bits[i / 32], i % 32, !buffer);
      if (buffer) {
        buffer = 0;
      }
    } else if (cur_bit_1 == 0 && cur_bit_2 == 1) {
      s21_set_bit(&result.bits[i / 32], i % 32, !buffer);
      if (!buffer) {
        buffer = 1;
      }
    } else {  // оба бита равны 1
      s21_set_bit(&result.bits[i / 32], i % 32, buffer);
    }
  }
  return result;
}

s21_big_decimal s21_big_bit_mul(s21_big_decimal value_1,
                                s21_big_decimal value_2) {
  s21_big_decimal result = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 15 * 32 + 1; i++) {
    if (s21_get_big_bit(value_2, i)) {
      result = s21_big_bit_add(result, value_1);
    }
    value_1 = s21_left_shif_decimal(value_1, 1);
  }
  return result;
}

s21_big_decimal s21_left_shif_decimal(s21_big_decimal value, int shift) {
  s21_big_decimal res = value;
  unsigned int buf = 0;
  if (shift > 0) {
    for (int i = 0; i < 15; i++) {
      unsigned int stash = res.bits[i];
      res.bits[i] = stash << shift;
      res.bits[i] |= buf;
      buf = stash >> (32 - shift);
    }
    shift--;
  }
  return res;
}

// int s21_get_big_long_bin(s21_big_decimal value) {
//   int res = 0;
//   for (int i = 15 * 32 - 1; i >= 0 && !res; i--) {
//     if (s21_check_bit(value.bits[i / 32], i % 32)) {
//       res = i;
//     }
//   }
//   return res;
// }

s21_big_decimal s21_normalize(s21_big_decimal value, int shift) {
  s21_big_decimal res = value;
  for (int i = 0; i < shift; i++) {
    s21_mul_by_ten_big(&res);
  }
  int scale = s21_get_scale(value.bits[15]);
  s21_set_scale(&res.bits[15], scale + shift);
  return res;
}

// void print_big_dec(s21_big_decimal value) {
//   printf("%d %d ", s21_get_scale(value.bits[15]),
//   s21_get_sign(value.bits[15])); for (int i = 14; i >= 0; i--) {
//     print_bin(value.bits[i]);
//   }
//   printf("\n");
// }

// void print_dec(s21_decimal value) {
//   printf("%d %d ", s21_get_scale(value.bits[3]),
//   s21_get_sign(value.bits[3])); for (int i = 2; i >= 0; i--) {
//     print_bin(value.bits[i]);
//   }
//   printf("\n");
// }

s21_big_decimal s21_convert_to_big(
    s21_decimal value) {  // Надо еще подумать, как это будет работать.
  s21_big_decimal res = {0};
  res.bits[0] = value.bits[0];
  res.bits[1] = value.bits[1];
  res.bits[2] = value.bits[2];
  res.bits[15] = value.bits[3];
  return res;
}

void s21_normalize_two_big(s21_big_decimal *value1, s21_big_decimal *value2) {
  s21_big_decimal res1 = *value1;
  s21_big_decimal res2 = *value2;
  int scale1 = s21_get_scale(res1.bits[15]);
  int scale2 = s21_get_scale(res2.bits[15]);
  if (scale1 > scale2) {
    res2 = s21_normalize(res2, scale1 - scale2);
  } else if (scale1 < scale2) {
    res1 = s21_normalize(res1, scale2 - scale1);
  }
  *value1 = res1;
  *value2 = res2;
}

int s21_is_greater_big(s21_big_decimal val1, s21_big_decimal val2) {
  int res = FALSE;
  int sign1 = s21_get_sign(val1.bits[15]);
  int sign2 = s21_get_sign(val2.bits[15]);
  s21_normalize_two_big(&val1, &val2);
  if (!(s21_is_big_zero(val1) && s21_is_big_zero(val2))) {
    if (sign1 == sign2 && sign1 == 0) {
      if (s21_first_bigger_bit(val1, val2) > 0) {
        res = TRUE;
      }
    } else if (sign1 == sign2 && sign1 == 1) {
      if (s21_first_bigger_bit(val1, val2) < 0) {
        res = TRUE;
      }
    } else if (sign1 < sign2) {
      res = TRUE;
    }
  }
  return res;
}

int s21_is_equal_big(s21_big_decimal val1, s21_big_decimal val2) {
  int res = TRUE;
  int sign1 = s21_get_sign(val1.bits[15]);
  int sign2 = s21_get_sign(val2.bits[15]);
  s21_normalize_two_big(&val1, &val2);
  if (!(s21_is_big_zero(val1) && s21_is_big_zero(val2))) {
    if (sign1 == sign2) {
      if (s21_first_bigger_bit(val1, val2) != 0) {
        res = FALSE;
      }
    } else {
      res = FALSE;
    }
  }
  return res;
}

int s21_is_less_big(s21_big_decimal val1, s21_big_decimal val2) {
  int res = FALSE;
  if (!s21_is_greater_big(val1, val2) && !s21_is_equal_big(val1, val2)) {
    res = TRUE;
  }
  return res;
}

int s21_is_less_or_equal_big(s21_big_decimal val1, s21_big_decimal val2) {
  return !s21_is_greater_big(val1, val2);
}

int s21_is_greater_or_equal_big(s21_big_decimal val1, s21_big_decimal val2) {
  int res = FALSE;
  if (s21_is_greater_big(val1, val2) || s21_is_equal_big(val1, val2)) {
    res = TRUE;
  }
  return res;
}

int s21_is_not_equal_big(s21_big_decimal val1, s21_big_decimal val2) {
  return !s21_is_equal_big(val1, val2);
}

int s21_first_bigger_bit(s21_big_decimal val1, s21_big_decimal val2) {
  int res = 0;
  for (int i = 15 * 32 - 1; i >= 0 && res == 0; i--) {
    if (s21_check_bit(val1.bits[i / 32], i % 32) >
        s21_check_bit(val2.bits[i / 32], i % 32)) {
      res = 1;
    } else if (s21_check_bit(val1.bits[i / 32], i % 32) <
               s21_check_bit(val2.bits[i / 32], i % 32)) {
      res = -1;
    }
  }
  return res;
}

int s21_is_dec_zero(s21_decimal val) {
  int res = TRUE;
  for (int i = 0; i < 3 && res; i++) {
    if (val.bits[i] != 0) {
      res = FALSE;
    }
  }
  return res;
}

int s21_is_big_zero(s21_big_decimal val) {
  int res = TRUE;
  for (int i = 0; i < 15 && res; i++) {
    if (val.bits[i] != 0) {
      res = FALSE;
    }
  }
  return res;
}

void s21_nullify(s21_decimal *num) {
  num->bits[0] = 0;
  num->bits[1] = 0;
  num->bits[2] = 0;
  num->bits[3] = 0;
}

void s21_nullify_big(s21_big_decimal *num) {
  for (int i = 0; i < 16; i++) {
    num->bits[i] = 0;
  }
}

s21_big_decimal s21_big_bit_div(s21_big_decimal value_1,
                                s21_big_decimal value_2, s21_big_decimal *res) {
  s21_set_scale(&value_1.bits[15], 0);
  s21_set_scale(&value_2.bits[15], 0);
  s21_set_sign(&value_1.bits[15], 0);
  s21_set_sign(&value_2.bits[15], 0);
  s21_big_decimal rest = value_1;
  int curr_shift = 0;
  s21_nullify_big(res);
  while (s21_is_greater_or_equal_big(rest, value_2)) {
    curr_shift = 0;
    s21_big_decimal buff = value_2;
    s21_big_decimal buff_next = s21_left_shif_decimal(buff, 1);
    s21_set_scale(&buff_next.bits[15], 0);
    while (s21_is_greater_or_equal_big(rest, buff_next)) {
      buff = buff_next;
      buff_next = s21_left_shif_decimal(buff, 1);
      s21_set_scale(&buff_next.bits[15], 0);
      curr_shift++;
    }
    rest = s21_big_bit_sub(rest, buff);
    s21_set_bit(&res->bits[curr_shift / 32], curr_shift % 32, 1);
  }
  return rest;
}

s21_big_decimal s21_big_bit_truncate(s21_big_decimal val,
                                     s21_big_decimal *res) {
  s21_nullify_big(res);
  *res = val;
  s21_big_decimal rest = {0}, dec_del = {0};
  dec_del.bits[0] = 10;
  int scale = s21_get_scale(val.bits[15]);
  s21_set_sign(&val.bits[15], 0);
  if (scale > 0) {
    dec_del = s21_normalize(dec_del, scale - 1);
    rest = s21_big_bit_div(val, dec_del, res);
  }
  return rest;
}

// int s21_len_big_bit(s21_big_decimal val) {
//   int res = 0;
//   for (int i = 15 * 32; i > 0 && !res; i--) {
//     if (s21_check_bit(val.bits[i / 32], i % 32)) {
//       res = i;
//     }
//   }
//   return res;
// }

int s21_convert_to_dec(s21_big_decimal val, s21_decimal *res) {
  int error_code = OK;
  int len_after_dot = 0;
  int sign = s21_get_sign(val.bits[15]);
  s21_big_decimal rest = {0};
  if (res != NULL) {
    s21_nullify(res);
  }
  int scale = s21_get_scale(val.bits[15]);
  if (scale > 28) {
    len_after_dot = scale - 28;
    s21_set_scale(&val.bits[15], len_after_dot);
    rest = s21_big_bit_truncate(val, &val);
    // if (s21_is_big_zero(val) && !s21_is_big_zero(rest)) {
    //   error_code = TOO_SMALL;
    // }
    s21_set_scale(&rest.bits[15], len_after_dot - 1);
    s21_big_bit_truncate(rest, &rest);
    scale = 28;
  }
  while (scale >= 0 && (s21_check_extra_bit(val))) {
    rest = s21_div_by_ten_big(&val);
    scale -= 1;
  }
  val = s21_big_bank_rounding(val, rest, 1);
  if (scale < 0 || s21_check_extra_bit(val)) {
    if (sign || (s21_is_big_zero(val) && !s21_is_big_zero(rest))) {
      error_code = TOO_SMALL;
    } else {
      error_code = TOO_BIG;
    }
  } else if (error_code == OK && res != NULL) {
    res->bits[0] = val.bits[0];
    res->bits[1] = val.bits[1];
    res->bits[2] = val.bits[2];
    s21_set_scale(&res->bits[3], scale);
    s21_set_sign(&res->bits[3], sign);
  }
  return error_code;
}

s21_big_decimal s21_big_bit_abs(s21_big_decimal val) {
  s21_set_sign(&val.bits[15], 0);
  return val;
}

s21_big_decimal s21_big_rounding(s21_big_decimal val, int scale) {
  s21_big_decimal buff = s21_big_bit_truncate(val, &val);
  s21_big_decimal zeros = {0};
  zeros.bits[0] = 5;
  zeros = s21_normalize(zeros, scale);
  s21_set_scale(&zeros.bits[15], 1);
  if (s21_is_greater_or_equal_big(buff, zeros)) {
    s21_big_decimal ones = {0};
    ones.bits[0] = 1;
    val = s21_big_bit_add(val, ones);
  }
  return val;
}

s21_big_decimal s21_big_bank_rounding(s21_big_decimal val, s21_big_decimal rest,
                                      int scale) {
  s21_big_decimal zeros = {0};
  zeros.bits[0] = 5;
  zeros = s21_normalize(zeros, scale);
  s21_set_scale(&zeros.bits[15], 1);
  if (s21_is_greater_big(rest, zeros)) {
    s21_big_decimal ones = {0};
    ones.bits[0] = 1;
    val = s21_big_bit_add(val, ones);
  } else if (s21_is_equal_big(rest, zeros)) {
    if (s21_get_big_bit(val, 0)) {
      s21_big_decimal ones = {0};
      ones.bits[0] = 1;
      val = s21_big_bit_add(val, ones);
    }
  }
  return val;
}

int s21_check_extra_bit(s21_big_decimal val) {
  int res = 0;
  for (int i = 3; i < 14 && !res; i++) {
    if (val.bits[i] != 0) {
      res = 1;
    }
  }
  return res;
}

s21_big_decimal s21_div_by_ten_big(s21_big_decimal *result) {
  unsigned long long overflow = 0;
  s21_big_decimal res = {0};
  for (int i = 6; i >= 0; i--) {
    unsigned long long save = (overflow << 32) | result->bits[i];
    result->bits[i] = (save / 10);
    overflow = save % 10;
  }
  res.bits[0] = overflow;
  return res;
}

void s21_mul_by_ten_big(s21_big_decimal *result) {
  s21_big_decimal shift3 = *result;
  s21_big_decimal shift1 = *result;

  shift3 = s21_left_shif_decimal(shift3, 3);
  shift1 = s21_left_shif_decimal(shift1, 1);

  *result = s21_big_bit_add(shift1, shift3);
}