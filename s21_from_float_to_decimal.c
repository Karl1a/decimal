#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0;
  if (src > MAX_DECIMAL || src < MIN_DECIMAL) {
    res = 1;
  } else if (src != 0.0) {
    unsigned int scale = 0;
    if (src < 0.0) {
      set_bit_to_1_normal_dec(dst, INFO_BIT, INDEX_SIGN);
      src *= -1;
    }

    int check = (int)src;
    for (; !check && scale < MAX_SCALE; check *= 10) {
      scale++;
      check = (int)src;
      src *= 10;
    }

    int i = 0;
    for (; src <= MAX_DECIMAL && scale < 7; i++) {
      src *= 10;
      scale++;
    }
    for (i = 0; src >= powl(10.0, -8) && i < 190; i++) {
      src = (float)floorl(src) / 2;
      if (src - floorl(src) > powl(10.0, -8)) {
        set_bit_to_1_at_index_norm_dec(dst, i);
      }
    }
    set_scale_norm_dec(dst, scale);
  }
  return res;
}
