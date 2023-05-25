#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = s21_OK;
  ;
  s21_big_decimal big_value_1 = {{0}};
  s21_big_decimal big_value_2 = {{0}};
  s21_big_decimal big_result = {{0}};

  set_info_from_dec_to_big_dec(value_1, &big_value_1);
  set_info_from_dec_to_big_dec(value_2, &big_value_2);

  mul_big_decimal(big_value_1, big_value_2, &big_result);

  status = cast_to_normal_decimal(big_result, result);  // anti normalization
  return status;
}

void mul_big_decimal(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                     s21_big_decimal *big_result) {
  int is_mul_done = 1;
  int sign_value_1 = get_sign(big_value_1);
  int sign_value_2 = get_sign(big_value_2);
  int unsigned scale_1 = get_scale(big_value_1);
  int unsigned scale_2 = get_scale(big_value_2);

  if ((!is_big_decimal_0(big_value_1)) ||
      (!is_big_decimal_0(big_value_2))) {  // 0
    is_mul_done = 0;
  } else if (!is_big_decimal_abs_1(big_value_1)) {  // first is abs(1)
    set_info_from_big_dec_to_big_dec(big_value_2, big_result);
    is_mul_done = 0;
  } else if (!is_big_decimal_abs_1(big_value_2)) {  // second is abs(1)
    set_info_from_big_dec_to_big_dec(big_value_1, big_result);
    is_mul_done = 0;
  }

  if (is_mul_done) {
    int real_size_value_2 = get_bigger_1(big_value_2);

    s21_big_decimal storage_big_decimal = {{0}};

    if (is_bit_at_index(big_value_2, 0)) {
      set_info_from_big_dec_to_big_dec(big_value_1, big_result);
    } else {
      set_info_from_big_dec_to_big_dec(storage_big_decimal, big_result);
    }

    for (int i = 1; i <= real_size_value_2; i++) {
      set_info_from_big_dec_to_big_dec(*big_result, &storage_big_decimal);
      switch_to_left(&big_value_1);
      if (is_bit_at_index(big_value_2, i)) {
        add_with_storage_algorithm(storage_big_decimal, big_value_1,
                                   big_result);
      } else {
        s21_big_decimal nul_big_dec = {{0}};
        add_with_storage_algorithm(storage_big_decimal, nul_big_dec,
                                   big_result);
      }
    }
  }

  if (sign_value_1 == sign_value_2) {
    set_sign_0(big_result);
  } else {
    set_sign_1(big_result);
  }
  set_scale(big_result, scale_1 + scale_2);  // TO DO if scale > 28
}