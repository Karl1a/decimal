#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal first, s21_decimal second) {
  s21_big_decimal big_first = {{0}};
  s21_big_decimal big_second = {{0}};
  set_info_from_dec_to_big_dec(first, &big_first);
  set_info_from_dec_to_big_dec(second, &big_second);
  return s21_is_big_greater_or_equal(big_first, big_second);
}

int s21_is_big_greater_or_equal(s21_big_decimal big_first,
                                s21_big_decimal big_second) {
  int is_greater_or_equal = 0;
  if (s21_is_big_greater(big_first, big_second) ||
      s21_is_big_equal(big_first, big_second)) {
    is_greater_or_equal = 1;
  }
  return is_greater_or_equal;
}