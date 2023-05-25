#include "s21_decimal.h"
int s21_negate(s21_decimal value, s21_decimal *dst) {
  s21_big_decimal value_big = {{0}};
  set_info_from_dec_to_big_dec(value, &value_big);
  int res = 0;
  unsigned int scale = get_scale(value_big);
  if (scale > MAX_SCALE) {
    res = 1;
  } else if (value.bits[INFO_BIT] != 0) {
    if (get_sign(value_big)) {
      set_sign_0(&value_big);
    } else {
      set_sign_1(&value_big);
    }
    *dst = value;
    dst->bits[INFO_BIT] = value_big.bits[INFO_BIG_BIT];
  } else {
    *dst = value;
  }
  return res;
}
