#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal first, s21_decimal second) {
  int is_less_or_equal = 0;
  if (s21_is_less(first, second) || s21_is_equal(first, second)) {
    is_less_or_equal = 1;
  }
  return is_less_or_equal;
}