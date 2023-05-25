#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DEC_SIZE 4
#define BIG_DEC_SIZE 7
#define INFO_BIT 3
#define INFO_BIG_BIT 6
#define NUMBER_BITS_95 95
#define NUMBER_BIG_BITS_191 191

#define INDEX_START_EXP 16
#define INDEX_END_EXP 23
#define INDEX_SIGN 31
#define MAX_SCALE 28

#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL (-79228162514264337593543950335.0F)

typedef struct {
  int unsigned bits
      [DEC_SIZE];  // 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111(96-1)
                   // = 79228162514264337593543950335
} s21_decimal;

typedef struct {
  int unsigned bits[BIG_DEC_SIZE];  // extra 3 bits for main numbers
} s21_big_decimal;

typedef enum {
  s21_OK,
  s21_INF,
  s21_NEG_INF,
  s21_NAN,
} status;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // +
void add_with_storage_algorithm(s21_big_decimal big_decimal,
                                s21_big_decimal small_decimal,
                                s21_big_decimal *result);  // inner function
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // -
void sub_with_storage_algorithm(s21_big_decimal big_decimal,
                                s21_big_decimal small_decimal,
                                s21_big_decimal *result);  // inner function
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // *
void mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // /
void div_with_storage_algorithm(s21_big_decimal value_1,
                                s21_big_decimal value_2,
                                s21_big_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // Mod
void mod_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);           // <
int s21_is_less_or_equal(s21_decimal, s21_decimal);  // <=
int s21_is_greater(s21_decimal, s21_decimal);        // >
int s21_is_big_greater(
    s21_big_decimal big_first,
    s21_big_decimal big_second);  // 1 - greater, 0 - not greater inner function
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  //>=
int s21_is_big_greater_or_equal(s21_big_decimal big_first,
                                s21_big_decimal big_second);
int s21_is_equal(s21_decimal, s21_decimal);  //==
int s21_is_big_equal(s21_big_decimal big_first, s21_big_decimal big_second);
int s21_is_not_equal(s21_decimal, s21_decimal);  // !=

// Convertors
int s21_from_int_to_decimal(int src, s21_decimal *dst);      // Из int
int s21_from_float_to_decimal(float src, s21_decimal *dst);  // Из float
int s21_from_decimal_to_int(s21_decimal src, int *dst);      // В int
int s21_from_decimal_to_float(s21_decimal src, float *dst);  // В float

// Another functions
int s21_floor(s21_decimal value,
              s21_decimal *result);  // Округляет указанное Decimal число до
                                     // ближайшего целого числа в сторону
                                     // отрицательной бесконечности.
int s21_round(
    s21_decimal value,
    s21_decimal *result);  // Округляет Decimal до ближайшего целого числа
int s21_truncate(s21_decimal value,
                 s21_decimal *result);  // Возвращает целые цифры указанного
                                        // Decimal числа; любые дробные цифры
                                        // отбрасываются, включая конечные нули.
int s21_negate(s21_decimal value,
               s21_decimal *result);  // Возвращает результат умножения
                                      // указанного Decimal на -1.

// Common
int unsigned bit_number(
    int unsigned index);  // подается индекс (0-95), по нему возвращется номер
                          // бита, в котором он находится (0-2)
int unsigned index_number(
    int unsigned index);  // подается индекс (0-95), по нему возвращется номер в
                          // бите (0-31)

int is_bit_at_index(
    s21_big_decimal number,
    int unsigned index);  // возвращает значение конкретного индекса в бите (1
                          // или 0). Мы знаем только номер индекса
int is_bit(
    s21_big_decimal number, int unsigned bit_number,
    int unsigned index);  // возвращает значение конкретного индекса в бите (1
                          // или 0). Мы знаем и номер бита, и номер индекса
int is_bit_norm_dec(s21_decimal number, int unsigned bit_number,
                    int unsigned index);

void set_bit_to_1_at_index(
    s21_big_decimal *number,
    int unsigned index);  // установка бита в 1. Мы знаем только номер индекса
void set_bit_to_0_at_index(
    s21_big_decimal *number,
    int unsigned index);  // установка бита в 0. Мы знаем только номер индекса
void set_bit_to_1(s21_big_decimal *number, int unsigned bit_number,
                  int unsigned index);  // установка бита в 1. Мы знаем и номер
                                        // бита, и номер индекса
void set_bit_to_0(s21_big_decimal *number, int unsigned bit_number,
                  int unsigned index);  // установка бита в 0. Мы знаем и номер
                                        // бита, и номер индекса
void set_bit_to_1_normal_dec(s21_decimal *number, int unsigned bit_number,
                             int unsigned index);
void set_sign_1_norm_dec(s21_decimal *number);
void set_bit_to_1_at_index_norm_dec(s21_decimal *number, int unsigned index);

void inverse_bit(
    s21_big_decimal *number, int unsigned bit_number,
    int unsigned index);  // меняет значение бита на противоположный. Мы знаем и
                          // номер бита, и номер индекса

int get_sign(s21_big_decimal number);  // возвращает значение знака (0 -
                                       // положительный, 1 - отрицательный)
int get_sign_norm_dec(s21_decimal number);
void set_sign_0(s21_big_decimal *number);  // задает минус в знак
void set_sign_1(s21_big_decimal *number);  // задает плюс в знак
void inverse_sign(
    s21_big_decimal *number);  // меняет значение знака на противоположный.

int unsigned get_scale(
    s21_big_decimal number);  // возвращает значение степени (степень
                              // используется для определения дробной части)
void set_scale(s21_big_decimal *number,
               int unsigned scale);  // задает новое значение степени
void set_scale_norm_dec(s21_decimal *number, int unsigned scale);

int is_big_decimal_min(s21_big_decimal number);  // 0 - yes, 1 - no
int is_big_decimal_0(s21_big_decimal number);  // проверяет, является ли децимл
                                               // 0 // 0 - yes, 1 - no
int is_big_decimal_abs_1(
    s21_big_decimal
        number);  // проверяет, является ли децимл abs(1) // 0 - yes, 1 - no
int is_bit_0_1_2_full(
    s21_big_decimal
        number);  // // проверяет, заполнены ли единицами первые три бита (0-95)

void do_decimals_with_common_scale(s21_big_decimal *value_1,
                                   s21_big_decimal *value_2);
void erase_zero_scale(s21_big_decimal *number);  // удаляем лишние нули и
                                                 // степень после нормализации
void mul_on_ten(s21_big_decimal *number);  //  умножаем биге децимал на 10
void div_on_ten(s21_big_decimal *number);  // делим биг на 10
unsigned int mod_of_ten(
    s21_big_decimal number);  // взятие остатка от деления на 10
void add_one(s21_big_decimal *number);  // Добавляем +1 к децималу

// result в начале надо обнулить и перенести данные из биг децимл. Сначала
// проверить статус, если инф или нет, то пусть резалт останеться пустым
int cast_to_normal_decimal(
    s21_big_decimal number,
    s21_decimal *result);  // в касте будут проверяться выходы - INF, -INF

void set_info_from_dec_to_big_dec(s21_decimal init_dec,
                                  s21_big_decimal *big_dec);
void set_info_from_big_dec_to_big_dec(s21_big_decimal init_big_dec,
                                      s21_big_decimal *big_dec);
int get_bigger_1(
    s21_big_decimal number);  // return bigger 1 bit at decimal. -1 if decimal
                              // is 0, or index (from 0 ...)
void switch_to_left(s21_big_decimal *number);

void print_decimal_binary(s21_decimal number);

#endif  // SRC_S21_DECIMAL_H_
