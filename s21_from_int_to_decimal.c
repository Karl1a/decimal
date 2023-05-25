#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (src < 0) {
    set_bit_to_1_normal_dec(dst, INFO_BIT, INDEX_SIGN);
    src *= -1;
  }
  dst->bits[0] = src;
  return s21_OK;
}