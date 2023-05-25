#include "s21_decimal.h"

int s21_is_greater(s21_decimal first,
                   s21_decimal second) {  // 1 - greater, 0 - not greater
  s21_big_decimal big_first = {{0}};
  s21_big_decimal big_second = {{0}};
  set_info_from_dec_to_big_dec(first, &big_first);
  set_info_from_dec_to_big_dec(second, &big_second);
  do_decimals_with_common_scale(&big_first, &big_second);
  return s21_is_big_greater(big_first, big_second);
}

int s21_is_big_greater(s21_big_decimal big_first, s21_big_decimal big_second) {
  int is_greater = 0;
  int first_scale = get_sign(big_first);
  int second_scale = get_sign(big_second);
  int is_decimals_zero = 0;

  if (!is_big_decimal_0(big_first) &&
      !is_big_decimal_0(big_second)) {  //  1 - оба децимал равны нулю
    is_decimals_zero = 1;
  }

  if ((!first_scale && second_scale) && !is_decimals_zero) {
    is_greater = 1;
  }
  if (first_scale && !second_scale) {
  } else {
    do_decimals_with_common_scale(&big_first, &big_second);
    for (int i = NUMBER_BIG_BITS_191; i >= 0; i--) {
      if (is_bit_at_index(big_first, i) < is_bit_at_index(big_second, i)) {
        if (first_scale) {
          is_greater = 1;
        }
        i = 0;
      } else if (is_bit_at_index(big_first, i) >
                 is_bit_at_index(big_second, i)) {
        is_greater = 1;
        if (first_scale) {
          is_greater = 0;
        }
        i = 0;
      }
    }
  }
  return is_greater;
}
