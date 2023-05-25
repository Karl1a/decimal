#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status;
  s21_big_decimal big_value_1 = {{0}};
  s21_big_decimal big_value_2 = {{0}};
  s21_big_decimal big_result = {{0}};
  set_info_from_dec_to_big_dec(value_1, &big_value_1);
  set_info_from_dec_to_big_dec(value_2, &big_value_2);
  if (!is_big_decimal_0(big_value_2)) {
    status = s21_NAN;
  } else {
    do_decimals_with_common_scale(&big_value_1, &big_value_2);
    mod_big_decimal(big_value_1, big_value_2, &big_result);
    status = cast_to_normal_decimal(big_result, result);
    result->bits[3] = big_value_1.bits[6];
  }
  return status;
}

void mod_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  s21_big_decimal big_value_result = {{0}};
  div_with_storage_algorithm(value_1, value_2, &big_value_result);

  s21_big_decimal mul_big_value_result = {{0}};
  mul_big_decimal(value_2, big_value_result, &mul_big_value_result);

  sub_with_storage_algorithm(value_1, mul_big_value_result, result);
}