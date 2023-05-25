#include "s21_decimal.h"

#define INT_NEG_SIGN_SCALE_0 (-2147483648)
#define INT_NEG_SIGN_SCALE_2 (-2147352576)

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = s21_OK;

  s21_big_decimal big_value_1 = {{0}};
  s21_big_decimal big_value_2 = {{0}};
  s21_big_decimal big_result = {{0}};

  set_info_from_dec_to_big_dec(value_1, &big_value_1);
  set_info_from_dec_to_big_dec(value_2, &big_value_2);

  int unsigned sign_value_1 = get_sign(big_value_1);
  int unsigned sign_value_2 = get_sign(big_value_2);

  set_sign_0(&big_value_1);
  set_sign_0(&big_value_2);

  do_decimals_with_common_scale(&big_value_1,
                                &big_value_2);  // normalization!!!
  int unsigned scale = get_scale(big_value_1);

  if (sign_value_1 == sign_value_2) {  // both positive or both negative
    int is_not_subbed = 1;
    if (s21_is_big_equal(big_value_1, big_value_2)) {
      is_not_subbed = 0;
      if (sign_value_1) {
        set_sign_1(&big_result);
      }
    } else {
      if (sign_value_1) {  // both negative - change signs and do common sub
        // with both positive signs -5 -(-3) = -5 + 3 = 3 - 5
        s21_big_decimal temp = {
            {0}};  //нужно поменять местами первое и второе децимлы
        set_info_from_big_dec_to_big_dec(big_value_1, &temp);
        set_info_from_big_dec_to_big_dec(big_value_2, &big_value_1);
        set_info_from_big_dec_to_big_dec(temp, &big_value_2);
      }
    }

    if (is_not_subbed) {
      if (s21_is_big_greater(big_value_1, big_value_2)) {  // 5 - 3
        sub_with_storage_algorithm(big_value_1, big_value_2,
                                   &big_result);  // DO SUB!!!!!!!

      } else {
        sub_with_storage_algorithm(big_value_2, big_value_1, &big_result);
        inverse_sign(&big_result);
      }
    }
  } else {               // different signs
    if (sign_value_1) {  // big  number  is negative, small number is positive
      // -5 - +3 = -(5 + 3)
      set_sign_0(&big_value_1);
      add_with_storage_algorithm(big_value_1, big_value_2, &big_result);
      inverse_sign(&big_result);
    } else {  // big  number  is positive, small number is negative 5 - (-3) =
      // (5 + 3)
      set_sign_0(&big_value_2);
      add_with_storage_algorithm(big_value_1, big_value_2, &big_result);
    }
  }

  set_scale(&big_result, scale);
  status = cast_to_normal_decimal(big_result, result);

  return status;
}

void sub_with_storage_algorithm(s21_big_decimal big_decimal,
                                s21_big_decimal small_decimal,
                                s21_big_decimal *result) {
  for (int unsigned index = 0; index < NUMBER_BIG_BITS_191; index++) {
    int big_number_bit = is_bit_at_index(big_decimal, index);
    int small_number_bit = is_bit_at_index(small_decimal, index);
    if (big_number_bit == small_number_bit) {
      set_bit_to_0_at_index(result, index);
    } else if (big_number_bit && !small_number_bit) {
      set_bit_to_1_at_index(result, index);
    } else {
      set_bit_to_1_at_index(result, index);
      int unsigned inner_step = index + 1;
      for (; !is_bit_at_index(big_decimal, inner_step); inner_step++) {
        set_bit_to_1_at_index(&big_decimal, inner_step);
      }
      set_bit_to_0_at_index(&big_decimal, inner_step);
    }
  }
}
