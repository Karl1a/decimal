#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = s21_OK;
  s21_big_decimal big_value_1 = {{0}};
  s21_big_decimal big_value_2 = {{0}};
  s21_big_decimal big_result = {{0}};

  set_info_from_dec_to_big_dec(value_1, &big_value_1);
  set_info_from_dec_to_big_dec(value_2, &big_value_2);

  int sign_value_1 = get_sign(big_value_1);
  int sign_value_2 = get_sign(big_value_2);

  do_decimals_with_common_scale(&big_value_1,
                                &big_value_2);  // normalization!!!

  int unsigned scale = get_scale(big_value_1);

  if (!is_big_decimal_0(big_value_1) &&
      is_big_decimal_0(big_value_2)) {  // первое слагаемое ноль - значит ответ
    // - это второе слагаемое
    set_info_from_big_dec_to_big_dec(big_value_2, &big_result);
  } else if (!is_big_decimal_0(big_value_2) &&
             is_big_decimal_0(big_value_1)) {  // второе слагаемое ноль - значит
    // ответ - это первое слагаемое
    set_info_from_big_dec_to_big_dec(big_value_1, &big_result);
  } else if (sign_value_1 == sign_value_2) {  // both positive or both negative
    add_with_storage_algorithm(big_value_1, big_value_2,
                               &big_result);  // DO ADD!!!!
    if (sign_value_1) {                       // both negative
      set_sign_1(&big_result);
    }
  } else {  // decimal with different signs
    set_sign_0(&big_value_1);
    set_sign_0(&big_value_2);
    if (s21_is_big_greater_or_equal(big_value_1, big_value_2)) {
      sub_with_storage_algorithm(big_value_1, big_value_2, &big_result);
      if (sign_value_1) {
        set_sign_1(&big_result);
      }
    } else {
      sub_with_storage_algorithm(big_value_2, big_value_1, &big_result);
      if (sign_value_2) {
        set_sign_1(&big_result);
      }
    }
  }

  set_scale(&big_result, scale);
  status = cast_to_normal_decimal(big_result, result);

  return status;
}

void add_with_storage_algorithm(s21_big_decimal value_1,
                                s21_big_decimal value_2,
                                s21_big_decimal *result) {
  int storage = 0;
  for (int unsigned i = 0; i < (NUMBER_BIG_BITS_191 + 1); i++) {
    int left_number_bit = is_bit_at_index(value_1, i);
    int right_number_bit = is_bit_at_index(value_2, i);

    if (left_number_bit) {     // left = 1
      if (right_number_bit) {  // left = 1, right = 1
        if (storage) {         // storage = 1
          set_bit_to_1_at_index(result,
                                i);  // 1 + 1 + (1 storage) = 1 (1 storage)
        } else {                     // storage = 0
          set_bit_to_0_at_index(result,
                                i);  // 1 + 1 + (0 storage) = 0 (1 storage)
          storage = 1;
        }
      } else {          // left = 1, right = 0
        if (storage) {  // storage = 1
          set_bit_to_0_at_index(result,
                                i);  // 1 + 0 + (1 storage) = 0 (1 storage)
        } else {                     // storage = 0
          set_bit_to_1_at_index(result,
                                i);  // 1 + 0 + (0 storage) = 1 (0 storage)
        }
      }
    } else {                   // left = 0
      if (right_number_bit) {  // left = 0, right = 1
        if (storage) {         // storage = 1
          set_bit_to_0_at_index(result,
                                i);  // 0 + 1 + (1 storage) = 0 (1 storage)
        } else {                     // storage = 0
          set_bit_to_1_at_index(result,
                                i);  // 0 + 1 + (0 storage) = 1 (0 storage)
        }
      } else {          // left = 0, right = 0
        if (storage) {  // storage = 1
          set_bit_to_1_at_index(result,
                                i);  // 0 + 0 + (1 storage) = 1 (0 storage)
          storage = 0;
        } else {  // storage = 0
          set_bit_to_0_at_index(result,
                                i);  // 0 + 0 + (0 storage) = 0 (0 storage)
        }
      }
    }
  }
}
