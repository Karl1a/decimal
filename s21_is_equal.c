#include "s21_decimal.h"

int s21_is_equal(s21_decimal first, s21_decimal second) {
  s21_big_decimal big_first = {{0}};
  s21_big_decimal big_second = {{0}};
  set_info_from_dec_to_big_dec(first, &big_first);
  set_info_from_dec_to_big_dec(second, &big_second);
  do_decimals_with_common_scale(&big_first, &big_second);
  return s21_is_big_equal(big_first, big_second);
}

int s21_is_big_equal(s21_big_decimal big_first, s21_big_decimal big_second) {
  int is_equal = 1;
  if (is_big_decimal_0(big_first) || is_big_decimal_0(big_second)) {
    for (int i = NUMBER_BIG_BITS_191 + 32; i >= 0; --i) {
      if (is_bit_at_index(big_first, i) != is_bit_at_index(big_second, i)) {
        is_equal = 0;
        i = 0;
      }
    }
  }
  return is_equal;
}