#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int res = 0;
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal value_big = {{0}};
  s21_big_decimal temp = {{0}};
  s21_big_decimal mod = {{0}};
  set_info_from_dec_to_big_dec(value, &value_big);
  unsigned int scale = get_scale(value_big);
  if (scale > MAX_SCALE)
    res = 1;
  else {
    if (scale) {
      while (scale != 1) {
        div_with_storage_algorithm(value_big, ten, &temp);
        scale--;
        value_big.bits[0] = temp.bits[0];
        value_big.bits[1] = temp.bits[1];
        value_big.bits[2] = temp.bits[2];
      }
      mod_big_decimal(value_big, ten, &mod);
      if (mod.bits[0] >= 5) {
        div_with_storage_algorithm(value_big, ten, &temp);
        value_big.bits[0] = temp.bits[0];
        value_big.bits[1] = temp.bits[1];
        value_big.bits[2] = temp.bits[2];
        value_big.bits[0] += 1;
      } else {
        div_with_storage_algorithm(value_big, ten, &temp);
        value_big.bits[0] = temp.bits[0];
        value_big.bits[1] = temp.bits[1];
        value_big.bits[2] = temp.bits[2];
      }
      if (get_sign(value_big)) {
        set_bit_to_1_normal_dec(result, INFO_BIT, INDEX_SIGN);
      }
      result->bits[0] = value_big.bits[0];
    } else {
      for (int x = 0; x < 4; x++) result->bits[x] = value.bits[x];
    }
  }
  return res;
}
