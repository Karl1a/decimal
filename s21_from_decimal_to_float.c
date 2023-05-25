#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  s21_big_decimal src_big = {{0}};
  set_info_from_dec_to_big_dec(src, &src_big);
  int res = 1;
  if (dst) {
    double tmp = 0;
    for (int i = 0; i < NUMBER_BITS_95 + 1; i++) {
      tmp *= 2;
      if (is_bit_at_index(src_big, NUMBER_BITS_95 - i)) {
        tmp += 1;
      }
    }
    int scale = (int)get_scale(src_big);
    if (scale < MAX_SCALE) {
      if (scale) {
        int scale_int = scale * -1;
        tmp = tmp * pow(10, scale_int);
      }

      if (get_sign(src_big)) {
        tmp *= -1;
      }
      *dst = (float)tmp;
      res = 0;
    }
  }
  return res;
}