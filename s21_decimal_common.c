#include "s21_decimal.h"

// number of bit
int unsigned bit_number(int unsigned index) { return index / 32; }

// number of the 1/0 at the bit
int unsigned index_number(int unsigned index) { return index % 32; }

// проверка бита - чтобы проверить, что возвращает И бита и 1 (1&0=0 и  1&1=1)
int is_bit_at_index(s21_big_decimal number, int unsigned index) {
  return is_bit(number, bit_number(index), index);
}

int is_bit(s21_big_decimal number, int unsigned bit_number,
           int unsigned index) {
  int unsigned bit = number.bits[bit_number];
  int unsigned position = index_number(index);
  return (bit & (1 << position)) != 0;
}

int is_bit_norm_dec(s21_decimal number, int unsigned bit_number,
                    int unsigned index) {
  int unsigned bit = number.bits[bit_number];
  int unsigned position = index_number(index);
  return (bit & (1 << position)) != 0;
}

// установка бита в 1 - осуществляется через ИЛИ с 1 в этом бите - любой бит с 1
// равен 1
void set_bit_to_1_at_index(s21_big_decimal *number,
                           int unsigned index) {  // установка бита в 1
  return set_bit_to_1(number, bit_number(index), index);
}

// установка бита в 0 - бит переводится в 0, остальные биты  - единицами.
// Сдвигаем единицу на нужную позицию и полностью инверсируем биты
void set_bit_to_0_at_index(s21_big_decimal *number,
                           int unsigned index) {  // установка бита в 0
  return set_bit_to_0(number, bit_number(index), index);
}

// установка бита в 1
void set_bit_to_1(s21_big_decimal *number, int unsigned bit_number,
                  int unsigned index) {
  int unsigned bit = number->bits[bit_number];
  int unsigned position = index_number(index);
  number->bits[bit_number] = bit | (1 << position);
}

void set_bit_to_1_at_index_norm_dec(s21_decimal *number,
                                    int unsigned index) {  // установка бита в 1
  return set_bit_to_1_normal_dec(number, bit_number(index), index);
}

void set_bit_to_1_normal_dec(s21_decimal *number, int unsigned bit_number,
                             int unsigned index) {
  int unsigned bit = number->bits[bit_number];
  int unsigned position = index_number(index);
  number->bits[bit_number] = bit | (1 << position);
}

// установка бита в 0
void set_bit_to_0(s21_big_decimal *number, int unsigned bit_number,
                  int unsigned index) {
  int unsigned bit = number->bits[bit_number];
  int unsigned position = index_number(index);
  number->bits[bit_number] = bit & (~(1 << position));
}

// инверсия бита
void inverse_bit(s21_big_decimal *number, int unsigned bit_number,
                 int unsigned index) {
  int unsigned bit = number->bits[bit_number];
  int unsigned position = index_number(index);
  number->bits[bit_number] = bit ^ (1 << position);
}

// 0 - positive, 1 - negative
int get_sign(s21_big_decimal number) {  // get_sign 31 index at 3 bit
  return is_bit(number, INFO_BIG_BIT, INDEX_SIGN);
}

int get_sign_norm_dec(s21_decimal number) {
  return is_bit_norm_dec(number, INFO_BIT, INDEX_SIGN);
}

void set_sign_1(s21_big_decimal *number) {
  return set_bit_to_1(number, INFO_BIG_BIT, INDEX_SIGN);
}

void set_sign_1_norm_dec(s21_decimal *number) {
  return set_bit_to_1_normal_dec(number, INFO_BIT, INDEX_SIGN);
}

// set positive sign
void set_sign_0(s21_big_decimal *number) {
  return set_bit_to_0(number, INFO_BIG_BIT, INDEX_SIGN);
}

// change sign to opposite
void inverse_sign(s21_big_decimal *number) {
  return inverse_bit(number, INFO_BIG_BIT, INDEX_SIGN);
}

int unsigned get_scale(s21_big_decimal number) {
  int unsigned scale = 0;
  for (int unsigned index = INDEX_START_EXP, bit_pow = 0; index < INDEX_END_EXP;
       index++, bit_pow++) {
    if (is_bit(number, INFO_BIG_BIT, index)) {
      scale += (int unsigned)pow(2, bit_pow);
    }
  }
  return scale;
}

void set_scale(s21_big_decimal *number, int unsigned scale) {
  int sign = get_sign(*number);
  number->bits[INFO_BIG_BIT] = 0;
  number->bits[INFO_BIG_BIT] =
      number->bits[INFO_BIG_BIT] | (scale << INDEX_START_EXP);
  if (sign) {
    set_sign_1(number);
  }
}

void set_scale_norm_dec(s21_decimal *number, int unsigned scale) {
  int sign = get_sign_norm_dec(*number);
  number->bits[INFO_BIT] = 0;
  number->bits[INFO_BIT] = number->bits[INFO_BIT] | (scale << INDEX_START_EXP);
  if (sign) {
    set_sign_1_norm_dec(number);
  }
}

int is_big_decimal_0(s21_big_decimal number) {  // 0 - yes, 1 - no
  int status = 1;
  int stop_flag = 0;
  for (int unsigned index = 0; index < (NUMBER_BIG_BITS_191 + 1) && !stop_flag;
       index++) {
    if (is_bit_at_index(number, index)) {
      stop_flag = 1;
    }
  }
  if (!stop_flag && get_scale(number) == 0) {
    status = 0;
  }
  return status;
}

int is_big_decimal_abs_1(
    s21_big_decimal
        number) {  // проверяет, является ли децимл abs(1) // 0 - yes, 1 - no
  int status = 1;
  int stop_flag = 0;
  for (int bit = 1; bit < INFO_BIG_BIT && !stop_flag; bit++) {
    if (number.bits[bit] != 0) {
      stop_flag = 1;
    }
  }
  if (number.bits[0] == 1 && !stop_flag) {
    status = 0;
  }
  return status;
}

void do_decimals_with_common_scale(s21_big_decimal *value_1,
                                   s21_big_decimal *value_2) {
  unsigned int scale_1 = get_scale(*value_1);
  unsigned int scale_2 = get_scale(*value_2);
  if (scale_1 != scale_2) {  // проверка на разность степеней
    s21_big_decimal *number_for_normalized = {0};
    unsigned int scale_diff;
    if (scale_1 > scale_2) {
      number_for_normalized = value_2;
      scale_diff = scale_1 - scale_2;
    } else {
      number_for_normalized = value_1;
      scale_diff = scale_2 - scale_1;
    }
    s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
    for (int unsigned i = 0; i < scale_diff;
         i++) {  // если степени разные увеличиваем число в 10 раз на каждый
      // разряд
      mul_big_decimal(*number_for_normalized, ten, number_for_normalized);
    }
    set_scale(number_for_normalized,
              get_scale(*number_for_normalized) +
                  scale_diff);  // задаем степень для нормализованоного числа
  }
}

void erase_zero_scale(s21_big_decimal *number) {
  unsigned int scale = get_scale(*number);
  if (scale) {
    for (unsigned int i = 0; i < scale; i++) {
      s21_big_decimal mod = {0};
      s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
      mod_big_decimal(*number, ten, &mod);
      if (!mod.bits[0]) {
        div_with_storage_algorithm(*number, ten, number);
        set_scale(number, get_scale(*number) - 1);
      }
    }
  }
}

void mul_on_ten(s21_big_decimal *number) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  mul_big_decimal(*number, ten, number);
}

void div_on_ten(s21_big_decimal *number) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  div_with_storage_algorithm(*number, ten, number);
}

void add_one(s21_big_decimal *number) {
  s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
  add_with_storage_algorithm(*number, one, number);
}

unsigned int mod_of_ten(s21_big_decimal number) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal big_result = {0};
  mod_big_decimal(number, ten, &big_result);
  unsigned int result = big_result.bits[0];
  return result;
}

int cast_to_normal_decimal(s21_big_decimal big_result, s21_decimal *result) {
  int status = s21_OK;
  int sign = get_sign(big_result);
  unsigned int inf = 0;
  unsigned int scale = get_scale(big_result);
  if (scale > 28) {
    for (int unsigned i = 0; i < scale - 28; i++) {
      div_on_ten(&big_result);
      set_scale(&big_result, get_scale(big_result) - 1);
    }
    scale = 28;
  }

  if (!is_big_decimal_0(big_result)) {
    erase_zero_scale(&big_result);
  }

  if (scale) {
    for (int i = INFO_BIG_BIT - 1; i >= INFO_BIT; i--) {
      if (big_result.bits[i]) {
        for (unsigned int j = 0; j < scale; ++j) {
          if (j == scale - 1) {
            inf = inf + 10 * mod_of_ten(big_result);
          }
          if (j == scale - 2) {
            inf = mod_of_ten(big_result);
          }
          div_on_ten(&big_result);
          set_scale(&big_result, get_scale(big_result) - 1);
          if (!big_result.bits[i]) {
            j = scale;
            i = INFO_BIT;
          }
        }
      }
    }
  }
  if (inf > 50) {
    add_one(&big_result);
  }

  for (int i = INFO_BIT; i < INFO_BIG_BIT; i++) {
    if (big_result.bits[i]) {
      if (sign) {
        status = s21_NEG_INF;
      } else {
        status = s21_INF;
      }
    }
  }

  if (!status) {
    for (int bit = 0; bit < INFO_BIT; bit++) {
      result->bits[bit] = big_result.bits[bit];
    }
    result->bits[INFO_BIT] = big_result.bits[INFO_BIG_BIT];
  }
  return status;
}

void set_info_from_dec_to_big_dec(s21_decimal init_dec,
                                  s21_big_decimal *big_dec) {
  for (int unsigned bit = 0; bit < INFO_BIT; bit++) {
    big_dec->bits[bit] = init_dec.bits[bit];
    big_dec->bits[INFO_BIT + bit] = 0;
  }
  big_dec->bits[6] = init_dec.bits[INFO_BIT];
}

void set_info_from_big_dec_to_big_dec(s21_big_decimal init_big_dec,
                                      s21_big_decimal *big_dec) {
  for (int unsigned bit = 0; bit < BIG_DEC_SIZE; bit++) {
    big_dec->bits[bit] = init_big_dec.bits[bit];
  }
}

int get_bigger_1(
    s21_big_decimal number) {  // return bigger 1 bit at decimal. -1 if decimal
  // is 0, or index (from 0 ...)
  int stop_flag = 0;
  int index = NUMBER_BIG_BITS_191;
  while (index >= 0 && !stop_flag) {
    if (is_bit_at_index(number, index)) {
      stop_flag = 1;
    } else {
      index--;
    }
  }
  if (!stop_flag) index = -1;  // -1 if decimal is 0
  return index;
}

void switch_to_left(
    s21_big_decimal *number) {  // switch to 1 bit to left (mult *2)
  s21_big_decimal temp = {0};
  for (int unsigned index = 0; index < NUMBER_BIG_BITS_191 - 1; index++) {
    if (is_bit_at_index(*number, index)) {
      set_bit_to_1_at_index(&temp, index + 1);
    } else {
      set_bit_to_0_at_index(&temp, index + 1);
    }
  }
  temp.bits[INFO_BIG_BIT] = number->bits[INFO_BIG_BIT];
  set_info_from_big_dec_to_big_dec(temp, number);
}

void print_decimal_binary(s21_decimal number) {
  for (int unsigned index = 0; index < NUMBER_BITS_95 + 1 + 32; index++) {
    if (index % 32 == 0 && index != 0) {
      printf(" ");
    }
    int unsigned bit = number.bits[bit_number(index)];
    int unsigned position = index_number(index);
    if ((bit & (1 << position)) != 0) {
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");

  printf("bit[0] %ud\n", number.bits[0]);
  printf("bit[1] %ud\n", number.bits[1]);
  printf("bit[2] %ud\n", number.bits[2]);
  printf("bit[3] %ud\n", number.bits[3]);
  printf("\n");
}