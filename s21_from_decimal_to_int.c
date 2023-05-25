#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_big_decimal src_big = {{0}};
  set_info_from_dec_to_big_dec(src, &src_big);
  int res = 0;
  unsigned int scale = get_scale(src_big);
  if (scale < MAX_SCALE) {
    if (src_big.bits[1] == 0 && src_big.bits[2] == 0) {
      *dst = (int)src.bits[0];
      if (scale) {
        int scale_int = (int)scale * -1;
        *dst = (int)(*dst * pow(10, scale_int));
      }
      if (get_sign(src_big)) {
        *dst *= -1;
      }
    } else
      res = 1;
  } else
    res = 1;
  return res;
}