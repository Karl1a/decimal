#include "s21_decimal.h"

int s21_is_less(s21_decimal first, s21_decimal second) {
  int is_less = 0;
  int is_decimals_zero = 0;

  s21_big_decimal big_first = {{0}};
  s21_big_decimal big_second = {{0}};
  set_info_from_dec_to_big_dec(first, &big_first);
  set_info_from_dec_to_big_dec(second, &big_second);

  if (!is_big_decimal_0(big_first) && !is_big_decimal_0(big_second)) {
    is_decimals_zero = 1;
  }

  if (!s21_is_greater(first, second) && !s21_is_equal(first, second) &&
      !is_decimals_zero) {
    is_less = 1;
  }
  return is_less;
}