#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status;
  s21_big_decimal big_value_1 = {{0}};
  s21_big_decimal big_value_2 = {{0}};
  set_info_from_dec_to_big_dec(value_1, &big_value_1);
  set_info_from_dec_to_big_dec(value_2, &big_value_2);
  s21_big_decimal big_result = {{0}};
  if (!is_big_decimal_0(big_value_2)) {
    status = s21_NAN;
  } else {
    do_decimals_with_common_scale(&big_value_1, &big_value_2);
    unsigned int sign_value_1 = get_sign(big_value_1);
    unsigned int sign_value_2 = get_sign(big_value_2);
    s21_big_decimal mod_of_number = {{0}};
    mod_big_decimal(big_value_1, big_value_2, &mod_of_number);
    div_with_storage_algorithm(big_value_1, big_value_2, &big_result);
    while (is_big_decimal_0(mod_of_number) && get_scale(big_result) < 28) {
      mul_on_ten(&mod_of_number);
      mul_on_ten(&big_result);
      set_scale(&big_result, get_scale(big_result) + 1);
      s21_big_decimal div_of_mod = {{0}};
      div_with_storage_algorithm(mod_of_number, big_value_2, &div_of_mod);
      add_with_storage_algorithm(big_result, div_of_mod, &big_result);
      mod_big_decimal(mod_of_number, big_value_2, &mod_of_number);
    }
    if (sign_value_1 == sign_value_2) {
      set_sign_0(&big_result);
    } else {
      set_sign_1(&big_result);
    }
    status = cast_to_normal_decimal(big_result, result);
  }
  return status;
}

void div_with_storage_algorithm(s21_big_decimal value_1,
                                s21_big_decimal value_2,
                                s21_big_decimal *result) {
  s21_big_decimal temp = {{0}};
  value_1.bits[6] = 0;
  value_2.bits[6] = 0;
  int index = get_bigger_1(value_1);
  for (; index >= 0; index--) {
    int bit = is_bit_at_index(value_1, index);
    if (bit) {
      set_bit_to_1_at_index(&temp, 0);
    } else {
      set_bit_to_0_at_index(&temp, 0);
    }
    if (s21_is_big_greater_or_equal(temp, value_2)) {
      set_bit_to_1_at_index(result, index);
      sub_with_storage_algorithm(temp, value_2, &temp);
    } else {
      set_bit_to_0_at_index(result, index);
    }
    switch_to_left(&temp);
  }
}