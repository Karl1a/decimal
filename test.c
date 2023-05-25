#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

// convertor site
// https://www.rapidtables.com/convert/number/binary-to-decimal.html
#define MAX_AT_NUMBER_BIT 4294967295
#define NEG_SIGN_SCALE_0 \
  2147483648  // 0x80000000(hex) - 10000000000000000000000000000000
#define POS_SIGN_SCALE_1 \
  65536  // 0x10000 (hex)  - 00000000000000010000000000000000
#define POS_SIGN_SCALE_2 \
  131072  // 0x20000 (hex)  - 00000000000000100000000000000000
#define POS_SIGN_SCALE_4 \
  262144  // 0x40000 (hex)  - 00000000000001000000000000000000
#define POS_SIGN_SCALE_28 \
  1835008  // 0x1C0000(hex)  - 00000000000111000000000000000000
#define NEG_SIGN_SCALE_1 \
  2147549184  // 0x80010000 (hex) - 10000000000000010000000000000000
#define NEG_SIGN_SCALE_2 \
  2147614720  // 0x80020000 (hex) - 10000000000000100000000000000000
#define NEG_SIGN_SCALE_28 \
  2149318656  // 0x801C0000(hex) - 10000000000111000000000000000000

#define INT_NEG_SIGN_SCALE_0 (-2147483648)
#define INT_NEG_SIGN_SCALE_2 (-2147352576)
#define INT_NEG_SIGN_SCALE_4 (-2147221504)
/*
 Testing c#
 https://learn.microsoft.com/ru-ru/dotnet/api/system.decimal?view=net-7.0 -
 methods https://www.programiz.com/csharp-programming/online-compiler/ online
 compiler

 Comment to test:
 create decimal: Decimal(Int32, Int32, Int32, Boolean, Byte)
 decimal left = new decimal(-1, -1, -1, false, 0);  // this is max
 decimal left = new decimal(-1, -1, -1, true, 0);  // this is min
 decimal right = new decimal(0, 0, 0, false, 0); // this is 0
 to print
 Console.WriteLine (res.ToString());
 */

// add

// Test 0: -0 + (-0)
START_TEST(s21_add_neg_0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 0. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      bit0 value is 0
      bit1 value is 0
      bit2 value is 0
      bit3 value is -2147483648
   */
}

END_TEST

// Test 1: 0 + 0
START_TEST(s21_add_0_0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 1. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }

  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 2: 0 + 1
START_TEST(s21_add_0_1_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 2. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      1
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 3: 1 + 0
START_TEST(s21_add_1_0_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 3. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      0
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 4: 1 + 1
START_TEST(s21_add_1_1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 4. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 2);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      1
      2
      for bit0 value is 2
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 5: 1 + (-1)
START_TEST(s21_add_1_neg1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 5. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      -1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 6: (-1) + 1
START_TEST(s21_add_neg1_1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 6. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 7: (-1) + (-1)
START_TEST(s21_add_neg1_neg1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 7. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 2);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      -1
      -2
      for bit0 value is 2
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 8: 1 + 1 - second bit
START_TEST(s21_add_second_bit_1_1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 8. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 2);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      4294967296
      8589934592
      for bit0 value is 0
      for bit1 value is 2
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 9: 1 + (-1) - second bit
START_TEST(s21_add_second_bit_1_neg1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 9. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      -4294967296
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 10: (-1) + 1 - second bit
START_TEST(s21_add_second_bit_neg1_1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 10. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      4294967296
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 11: (-1) + (-1) - second bit
START_TEST(s21_add_second_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 11. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 2);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      -4294967296
      -8589934592
      for bit0 value is 0
      for bit1 value is 2
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 12: 1 + 1 - third bit
START_TEST(s21_add_third_bit_1_1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 12. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 2);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      18446744073709551616
      36893488147419103232
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 2
      for bit3 value is 0
   */
}

END_TEST

// Test 13: 1 + (-1) - third bit
START_TEST(s21_add_third_bit_1_neg1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 13. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      -18446744073709551616
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 14: (-1) + 1 - third bit
START_TEST(s21_add_third_bit_neg1_1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 14. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      18446744073709551616
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 15: (-1) + (-1) - third bit
START_TEST(s21_add_third_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 15. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 2);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      -18446744073709551616
      -36893488147419103232
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 2
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 16: max + 0
START_TEST(s21_add_max_0_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 16. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 17: max + 1 = INFINITY
START_TEST(s21_add_max_1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 17. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      1
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 18: max + (-1)
START_TEST(s21_add_max_neg1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 18. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -1
      79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 19: max + max = INFINITY
START_TEST(s21_add_max_max_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 19. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      79228162514264337593543950335
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 20: min + 0
START_TEST(s21_add_min_0_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 20. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 21: min + 1
START_TEST(s21_add_min_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 21. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      1
      -79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 22: min + (-1) = -INFINITY
START_TEST(s21_add_min_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 22. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      -1
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 23: max + (-min) = 0
START_TEST(s21_add_max_min_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 23. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -79228162514264337593543950335
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 24: 1.23 + 1.45 - common scale
START_TEST(s21_add_common_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 24. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 268);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      1.45
      2.68
      for bit0 value is 268
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 25: 1.23+ (-1.45) - common scale
START_TEST(s21_add_common_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 25. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 22);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      -1.45
      -0.22
      for bit0 value is 22
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 26: (-1.23) + 1.45 - common scale
START_TEST(s21_add_common_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 26. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 22);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      1.45
      -0.22
      for bit0 value is 22
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 27: (-1.23) + (-1.45) - common scale
START_TEST(s21_add_common_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 27. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 268);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      -1.45
      -2.68
      for bit0 value is 268
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 28: 12.3 + 1.45 - different scale
START_TEST(s21_add_different_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 28. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1375);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      1.45
      13.75
      for bit0 value is 1375
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 29: 12.3 + (-1.45) - different scale
START_TEST(s21_add_different_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 29. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1085);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      -1.45
      10.85
      for bit0 value is 1085
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 30: (-12.3) + 1.45 - different scale
START_TEST(s21_add_different_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 30. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1085);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      1.45
      -10.85
      for bit0 value is 1085
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 31: (-12.3) + (-1.45) - different scale
START_TEST(s21_add_different_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 31. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1375);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      -1.45
      -13.75
      for bit0 value is 1375
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 32: 7.9228162514264337593543950335 + 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_add_max_scale_1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 32. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 858993459);
  ck_assert_int_eq((int)result.bits[1], 858993459);
  ck_assert_int_eq((int)result.bits[2], 858993459);
  ck_assert_int_eq((int)result.bits[3], 1769472);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      7.9228162514264337593543950335
      15.845632502852867518708790067
      for bit0 value is 858993459
      for bit1 value is 858993459
      for bit2 value is 858993459
      for bit3 value is 1769472
   */
}

END_TEST

// Test 33: 7.9228162514264337593543950335 + (-7.9228162514264337593543950335) -
// max scale
START_TEST(s21_add_max_scale_1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 33. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 1835008);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      7.9228162514264337593543950335
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 1835008
      0
   */
}

END_TEST

// Test 34: (-7.9228162514264337593543950335) + 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_add_max_scale_neg1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 34. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], -2145648640);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      -7.9228162514264337593543950335
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2145648640
   */
}

END_TEST

// Test 35: (-7.9228162514264337593543950335) +
// (-7.9228162514264337593543950335) - max scale
START_TEST(s21_add_max_scale_neg1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 35. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 858993459);
  ck_assert_int_eq((int)result.bits[1], 858993459);
  ck_assert_int_eq((int)result.bits[2], 858993459);
  ck_assert_int_eq((int)result.bits[3], -2145714176);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      -7.9228162514264337593543950335
      -15.845632502852867518708790067
      for bit0 value is 858993459
      for bit1 value is 858993459
      for bit2 value is 858993459
      for bit3 value is -2145714176
   */
}

END_TEST

// Test 36: number + number
START_TEST(s21_add_number_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_add(left, right, &result);
      printf("Add test 36. Status is %d, Result %d + %d is \n", status, i, j);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], i + j);
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      ck_assert_int_eq((int)result.bits[3], 0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Add(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          2
          2
          4
          for bit0 value is 4
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 37: number + (-number)
START_TEST(s21_add_number_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_add(left, right, &result);
      printf("Add test 37. Status is %d, Result %d + %d is \n", status, i, j);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], abs(i - j));
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      if (i >= j) {
        ck_assert_int_eq((int)result.bits[3], 0);
      } else {
        ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
      }
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(3, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Add(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          2
          -3
          0
          for bit0 value is 1
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 38: (-number) + number
START_TEST(s21_add_negnumber_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_add(left, right, &result);
      printf("Add test 38. Status is %d, Result %d + %d is \n", status, i, j);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], abs(i - j));
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      if (i < j) {
        ck_assert_int_eq((int)result.bits[3], 0);
      } else {
        ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
      }
      ck_assert_int_eq(status, 0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Add(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          2
          0
          for bit0 value is 0
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 39: (-number) + (-number)
START_TEST(s21_add_negnumber_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_add(left, right, &result);
      printf("Add test 39. Status is %d, Result %d + %d is \n", status, i, j);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], i + j);
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Add(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          -2
          -4
          for bit0 value is 4
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 40: max + 0.11
START_TEST(s21_add_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 40. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.11
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 41: max + 0.99
START_TEST(s21_add_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 41. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.99
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 42: almost max + 0.11
START_TEST(s21_add_almost_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 42. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.11
      79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 43: almost max + 0.99
START_TEST(s21_add_almost_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 43. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.99
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 44: min + 0.11
START_TEST(s21_add_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 44. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.11
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 45: min + 0.99
START_TEST(s21_add_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 45. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.99
      -79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 46: almost min + 0.11
START_TEST(s21_add_almost_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 46. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.11
      -79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 47: almost min + 0.99
START_TEST(s21_add_almost_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 47. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -3);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.99
      -79228162514264337593543950333
      for bit0 value is -3
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 48: -0 + 0
START_TEST(s21_add_neg0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 48. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 49: 0 + (-0)
START_TEST(s21_add_0_neg0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Add test 49. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Add(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// sub
//  Test 0: -0 - (-0)
START_TEST(s21_sub_neg_0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 0. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 1: 0 - 0
START_TEST(s21_sub_0_0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 1. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 2: 0 - 1
START_TEST(s21_sub_0_1_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 2. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      1
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 3: 1 - 0
START_TEST(s21_sub_1_0_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 3. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      0
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 4: 1 - 1
START_TEST(s21_sub_1_1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 4. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 5: 1 - (-1)
START_TEST(s21_sub_1_neg1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 5. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 2);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      -1
      2
      for bit0 value is 2
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 6: (-1) - 1
START_TEST(s21_sub_neg1_1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 6. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 2);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      1
      -2
      for bit0 value is 2
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 7: (-1) - (-1)
START_TEST(s21_sub_neg1_neg1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 7. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      -1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 8: 1 - 1 - second bit
START_TEST(s21_sub_second_bit_1_1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 8. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      4294967296
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 9: 1 - (-1) - second bit
START_TEST(s21_sub_second_bit_1_neg1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 9. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 2);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      -4294967296
      8589934592
      for bit0 value is 0
      for bit1 value is 2
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 10: (-1) - 1 - second bit
START_TEST(s21_sub_second_bit_neg1_1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 10. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 2);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      4294967296
      -8589934592
      for bit0 value is 0
      for bit1 value is 2
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 11: (-1) - (-1) - second bit
START_TEST(s21_sub_second_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 11. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      -4294967296
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 12: 1 - 1 - third bit
START_TEST(s21_sub_third_bit_1_1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 12. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      18446744073709551616
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 13: 1 - (-1) - third bit
START_TEST(s21_sub_third_bit_1_neg1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 13. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 2);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      -18446744073709551616
      36893488147419103232
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 2
      for bit3 value is 0
   */
}

END_TEST

// Test 14: (-1) - 1 - third bit
START_TEST(s21_sub_third_bit_neg1_1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 14. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 2);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      18446744073709551616
      -36893488147419103232
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 2
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 15: (-1) - (-1) - third bit
START_TEST(s21_sub_third_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 15. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      -18446744073709551616
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 16: max - 0
START_TEST(s21_sub_max_0_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 16. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 17: max - 1
START_TEST(s21_sub_max_1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 17. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      1
      79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 18: max - (-1) = INFINITY
START_TEST(s21_sub_max_neg1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 18. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq(status, 1);

  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -1
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 19: max - max
START_TEST(s21_sub_max_max_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 19. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      79228162514264337593543950335
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 20: min - 0
START_TEST(s21_sub_min_0_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 20. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 21: min - 1 = -INFINITY
START_TEST(s21_sub_min_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 21. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      1
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 22: min - (-1)
START_TEST(s21_sub_min_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 22. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);

  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      -1
      -79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 23: max - (-min) = INFINITY
START_TEST(s21_sub_max_min_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 23. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -79228162514264337593543950335
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 24: 1.23 - 1.45 - common scale
START_TEST(s21_sub_common_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 24. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 22);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      1.45
      -0.22
      for bit0 value is 22
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 25: 1.23 - (-1.45) - common scale
START_TEST(s21_sub_common_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 25. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 268);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      -1.45
      2.68
      for bit0 value is 268
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 26: (-1.23) - 1.45 - common scale
START_TEST(s21_sub_common_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 26. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 268);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      1.45
      -2.68
      for bit0 value is 268
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 27: (-1.23) - (-1.45) - common scale
START_TEST(s21_sub_common_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 27. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 22);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      -1.45
      0.22
      for bit0 value is 22
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 28: 12.3 - 1.45 - different scale
START_TEST(s21_sub_different_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 28. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1085);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      1.45
      10.85
      for bit0 value is 1085
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 29: 12.3 - (-1.45) - different scale
START_TEST(s21_sub_different_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 29. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1375);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      -1.45
      13.75
      for bit0 value is 1375
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 30: (-12.3) - 1.45 - different scale
START_TEST(s21_sub_different_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 30. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1375);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      1.45
      -13.75
      for bit0 value is 1375
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 31: (-12.3) - (-1.45) - different scale
START_TEST(s21_sub_different_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 31. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1085);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      -1.45
      -10.85
      for bit0 value is 1085
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 32: 7.9228162514264337593543950335 - 7.9228162514264337593543950335 -
// max scale
START_TEST(
    s21_sub_max_scale_1_1_test) {  // тест падает на этапе антинормализации
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 32. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 1835008);
  ck_assert_int_eq(status, 0);

  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      7.9228162514264337593543950335
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 1835008
   */
}

END_TEST

// Test 33: 7.9228162514264337593543950335 - (-7.9228162514264337593543950335) -
// max scale
START_TEST(s21_sub_max_scale_1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 33. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 858993459);
  ck_assert_int_eq((int)result.bits[1], 858993459);
  ck_assert_int_eq((int)result.bits[2], 858993459);
  ck_assert_int_eq((int)result.bits[3], 1769472);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      7.9228162514264337593543950335
      15.845632502852867518708790067
      for bit0 value is 858993459
      for bit1 value is 858993459
      for bit2 value is 858993459
      for bit3 value is 1769472
   */
}

END_TEST

// Test 34: (-7.9228162514264337593543950335) - 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_sub_max_scale_neg1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 34. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 858993459);
  ck_assert_int_eq((int)result.bits[1], 858993459);
  ck_assert_int_eq((int)result.bits[2], 858993459);
  ck_assert_int_eq((int)result.bits[3], -2145714176);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      -7.9228162514264337593543950335
      -15.845632502852867518708790067
      for bit0 value is 858993459
      for bit1 value is 858993459
      for bit2 value is 858993459
      for bit3 value is -2145714176
   */
}

END_TEST

// Test 35: (-7.9228162514264337593543950335) -
// (-7.9228162514264337593543950335) - max scale
START_TEST(s21_sub_max_scale_neg1_neg1_test) {  // тест падает на этапе
                                                // антинормализации
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 35. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], -2145648640);
  ck_assert_int_eq(status, 0);

  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      -7.9228162514264337593543950335
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2145648640
   */
}

END_TEST

// Test 36: number - number
START_TEST(s21_sub_number_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_sub(left, right, &result);
      printf("Test sub 36. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], abs(i - j));
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      if (j > i) {
        ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
      } else {
        ck_assert_int_eq((int)result.bits[3], 0);
      }
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(3, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Subtract(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          2
          3
          -1
          for bit0 value is 1
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 37: number - (-number)
START_TEST(s21_sub_number_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_sub(left, right, &result);
      printf("Test sub 37. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], abs(i + j));
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      ck_assert_int_eq((int)result.bits[3], 0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Subtract(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          2
          -2
          4
          for bit0 value is 4
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 38: (-number) - number
START_TEST(s21_sub_negnumber_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_sub(left, right, &result);
      printf("Test sub 38. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], abs(i + j));
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Subtract(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          2
          -4
          for bit0 value is 4
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 39: (-number) - (-number)
START_TEST(s21_sub_negnumber_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_sub(left, right, &result);
      printf("Test sub 39. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], abs(i - j));
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      if (i >= j) {
        ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
      } else {
        ck_assert_int_eq((int)result.bits[3], 0);
      }
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(3, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Subtract(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          -3
          0
          for bit0 value is 1
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 40: max - 0.11
START_TEST(s21_sub_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Test sub 40. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.11
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 41: max - 0.99
START_TEST(s21_sub_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 41. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.99
      79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 42: almost max - 0.11
START_TEST(s21_sub_almost_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Test sub 42. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.11
      79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 43: almost max - 0.99
START_TEST(s21_sub_almost_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 43. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -3);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.99
      79228162514264337593543950333
      for bit0 value is -3
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 44: min - 0.11
START_TEST(s21_sub_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Test sub 44. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.11
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 45: min - 0.99
START_TEST(s21_sub_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 45. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.99
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 46: almost min - 0.11
START_TEST(s21_sub_almost_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Test sub 46. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -2);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.11
      -79228162514264337593543950334
      for bit0 value is -2
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 47: almost min - 0.99
START_TEST(s21_sub_almost_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 47. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.99
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 48: -0 - 0
START_TEST(s21_sub_neg0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Test sub 48. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 49: 0 - (-0)
START_TEST(s21_sub_0_neg0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_add(left, right, &result);
  printf("Test sub 49. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 50: 123 - 1.13 - common scale
START_TEST(s21_sub_15_113_test) {
  s21_decimal left = {{123, 0, 0, 0}};
  s21_decimal right = {{113, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_sub(left, right, &result);
  printf("Test sub 50. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 12187);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(113, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Subtract(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      123
      1.13
      121.87
      for bit0 value is 12187
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// mul

// Test 0: -0 * (-0)
START_TEST(s21_mul_neg_0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 0. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 1: 0 * 0
START_TEST(s21_mul_0_0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 1. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 2: 0 * 1
START_TEST(s21_mul_0_1_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 2. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 3: 1 * 0
START_TEST(s21_mul_1_0_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 3. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 4: 1 * 1
START_TEST(s21_mul_1_1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 4. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      1
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 5: 1 * (-1)
START_TEST(s21_mul_1_neg1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 5. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      -1
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 6: (-1) * 1
START_TEST(s21_mul_neg1_1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 6. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      1
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 7: (-1) * (-1)
START_TEST(s21_mul_neg1_neg1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 7. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      -1
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 8: 1 * 1 - second bit
START_TEST(s21_mul_second_bit_1_1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 8. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      4294967296
      18446744073709551616
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 1
      for bit3 value is 0
   */
}

END_TEST

// Test 9: 1 * (-1) - second bit
START_TEST(s21_mul_second_bit_1_neg1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 9. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      -4294967296
      -18446744073709551616
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 10: (-1) * 1 - second bit
START_TEST(s21_mul_second_bit_neg1_1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 10. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
       4294967296
      -18446744073709551616
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 11: (-1) * (-1) - second bit
START_TEST(s21_mul_second_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 11. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      -4294967296
      18446744073709551616
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 1
      for bit3 value is 0
   */
}

END_TEST

// Test 12: 1 * 1 = INFINITY - third bit
START_TEST(s21_mul_third_bit_1_1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 12. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      18446744073709551616
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 13: 1 * (-1) = - INFINITY - third bit
START_TEST(s21_mul_third_bit_1_neg1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 13. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      -18446744073709551616
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 14: (-1) * 1 = - INFINITY - third bit
START_TEST(s21_mul_third_bit_neg1_1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 14. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      18446744073709551616
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 15: (-1) * (-1) = INFINITY - third bit
START_TEST(s21_mul_third_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 15. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      -18446744073709551616
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 16: max * 0
START_TEST(s21_mul_max_0_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 16. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 17: max * 1
START_TEST(s21_mul_max_1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 17. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      1
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 18: max * (-1)
START_TEST(s21_mul_max_neg1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 18. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -1
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 19: max * max = INFINITY
START_TEST(s21_mul_max_max_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 19. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      79228162514264337593543950335
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 20: min * 0
START_TEST(s21_mul_min_0_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 20. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 21: min * 1
START_TEST(s21_mul_min_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 21. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      1
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 22: min * (-1)
START_TEST(s21_mul_min_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 22. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      -1
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 23: max * (-min) = 0
START_TEST(s21_mul_max_min_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 23. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -79228162514264337593543950335
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 24: 1.23 * 1.45 - common scale
START_TEST(s21_mul_common_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 24. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 17835);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_4);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      1.45
      1.7835
      for bit0 value is 17835
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 262144
   */
}

END_TEST

// Test 25: 1.23 * (-1.45) - common scale
START_TEST(s21_mul_common_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 25. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 17835);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_4);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      -1.45
      -1.7835
      for bit0 value is 17835
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147221504
   */
}

END_TEST

// Test 26: (-1.23) * 1.45 - common scale
START_TEST(s21_mul_common_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 26. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 17835);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_4);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      1.45
      -1.7835
      for bit0 value is 17835
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147221504
   */
}

END_TEST

// Test 27: (-1.23) * (-1.45) - common scale
START_TEST(s21_mul_common_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 27. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 17835);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_4);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      -1.45
      1.7835
      for bit0 value is 17835
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 262144
   */
}

END_TEST

// Test 28: 12.3 * 1.45 - different scale
START_TEST(s21_mul_different_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 28. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 17835);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 196608);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      1.45
      17.835
      for bit0 value is 17835
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 196608
   */
}

END_TEST

// Test 29: 12.3 * (-1.45) - different scale
START_TEST(s21_mul_different_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 29. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 17835);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], -2147287040);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      -1.45
      -17.835
      for bit0 value is 17835
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147287040
   */
}

END_TEST

// Test 30: (-12.3) * 1.45 - different scale
START_TEST(s21_mul_different_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 30. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 17835);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], -2147287040);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      1.45
      -17.835
      for bit0 value is 17835
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147287040
   */
}

END_TEST

// Test 31: (-12.3) * (-1.45) - different scale
START_TEST(s21_mul_different_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 31. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 17835);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 196608);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      -1.45
      17.835
      for bit0 value is 17835
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 196608
   */
}

END_TEST

// Test 32: 7.9228162514264337593543950335 * 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_mul_max_scale_1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 32. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 158262358);
  ck_assert_int_eq((int)result.bits[1], 899300158);
  ck_assert_int_eq((int)result.bits[2], -892143627);
  ck_assert_int_eq((int)result.bits[3], 1769472);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      7.9228162514264337593543950335
      62.771017353866807638357894230
      for bit0 value is 158262358
      for bit1 value is 899300158
      for bit2 value is -892143627
      for bit3 value is 1769472
   */
}

END_TEST

// Test 33: 7.9228162514264337593543950335 * (-7.9228162514264337593543950335) -
// max scale
START_TEST(s21_mul_max_scale_1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 33. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 158262358);
  ck_assert_int_eq((int)result.bits[1], 899300158);
  ck_assert_int_eq((int)result.bits[2], -892143627);
  ck_assert_int_eq((int)result.bits[3], -2145714176);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      7.9228162514264337593543950335
      -62.771017353866807638357894230
      for bit0 value is 158262358
      for bit1 value is 899300158
      for bit2 value is -892143627
      for bit3 value is -2145714176
   */
}

END_TEST

// Test 34: (-7.9228162514264337593543950335) * 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_mul_max_scale_neg1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 34. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 158262358);
  ck_assert_int_eq((int)result.bits[1], 899300158);
  ck_assert_int_eq((int)result.bits[2], -892143627);
  ck_assert_int_eq((int)result.bits[3], -2145714176);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      -7.9228162514264337593543950335
      -62.771017353866807638357894230
      for bit0 value is 158262358
      for bit1 value is 899300158
      for bit2 value is -892143627
      for bit3 value is -2145714176
   */
}

END_TEST

// Test 35: (-7.9228162514264337593543950335) *
// (-7.9228162514264337593543950335) - max scale
START_TEST(s21_mul_max_scale_neg1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 35. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 158262358);
  ck_assert_int_eq((int)result.bits[1], 899300158);
  ck_assert_int_eq((int)result.bits[2], -892143627);
  ck_assert_int_eq((int)result.bits[3], 1769472);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      -7.9228162514264337593543950335
      62.771017353866807638357894230
      for bit0 value is 158262358
      for bit1 value is 899300158
      for bit2 value is -892143627
      for bit3 value is 1769472
   */
}

END_TEST

// Test 36: number * number
START_TEST(s21_mul_number_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_mul(left, right, &result);
      printf("Test mul 36. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], i * j);
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      ck_assert_int_eq((int)result.bits[3], 0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Multiply(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          2
          2
          4
          for bit0 value is 4
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 37: number * (-number)
START_TEST(s21_mul_number_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_mul(left, right, &result);
      printf("Test mul 37. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], i * j);
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Multiply(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          2
          -2
          -4
          for bit0 value is 4
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 38: (-number) * number
START_TEST(s21_mul_negnumber_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_mul(left, right, &result);
      printf("Test mul 38. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], i * j);
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Multiply(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          2
          -4
          for bit0 value is 4
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 39: (-number) * (-number)
START_TEST(s21_mul_negnumber_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_mul(left, right, &result);
      printf("Test mul 39. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq((int)result.bits[0], i * j);
      ck_assert_int_eq((int)result.bits[1], 0);
      ck_assert_int_eq((int)result.bits[2], 0);
      ck_assert_int_eq((int)result.bits[3], 0);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Multiply(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          -2
          4
          for bit0 value is 4
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 40: max * 0.11
START_TEST(s21_mul_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 40. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1030792151);
  ck_assert_int_eq((int)result.bits[1], -1889785611);
  ck_assert_int_eq((int)result.bits[2], 472446402);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.11
      8715097876569077135289834537
      for bit0 value is -1030792151
      for bit1 value is -1889785611
      for bit2 value is 472446402
      for bit3 value is 0
   */
}

END_TEST

// Test 41: max * 0.99
START_TEST(s21_mul_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 41. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -687194768);
  ck_assert_int_eq((int)result.bits[1], 171798691);
  ck_assert_int_eq((int)result.bits[2], -42949673);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.99
      78435880889121694217608510832
      for bit0 value is -687194768
      for bit1 value is 171798691
      for bit2 value is -42949673
      for bit3 value is 0
   */
}

END_TEST

// Test 42: almost max * 0.11
START_TEST(s21_mul_almost_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 42. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1030792151);
  ck_assert_int_eq((int)result.bits[1], -1889785611);
  ck_assert_int_eq((int)result.bits[2], 472446402);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.11
      8715097876569077135289834537
      for bit0 value is -1030792151
      for bit1 value is -1889785611
      for bit2 value is 472446402
      for bit3 value is 0
   */
}

END_TEST

// Test 43: almost max * 0.99
START_TEST(s21_mul_almost_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 43. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -687194769);
  ck_assert_int_eq((int)result.bits[1], 171798691);
  ck_assert_int_eq((int)result.bits[2], -42949673);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.99
      78435880889121694217608510831
      for bit0 value is -687194769
      for bit1 value is 171798691
      for bit2 value is -42949673
      for bit3 value is 0
   */
}

END_TEST

// Test 44: min * 0.11
START_TEST(s21_mul_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 44. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1030792151);
  ck_assert_int_eq((int)result.bits[1], -1889785611);
  ck_assert_int_eq((int)result.bits[2], 472446402);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.11
     -8715097876569077135289834537
      for bit0 value is -1030792151
      for bit1 value is -1889785611
      for bit2 value is 472446402
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 45: min * 0.99
START_TEST(s21_mul_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 45. Status is %d, Result is \n", status);
  print_decimal_binary(result);

  ck_assert_int_eq((int)result.bits[0], -687194768);
  ck_assert_int_eq((int)result.bits[1], 171798691);
  ck_assert_int_eq((int)result.bits[2], -42949673);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.99
      -78435880889121694217608510832
      for bit0 value is -687194768
      for bit1 value is 171798691
      for bit2 value is -42949673
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 46: almost min * 0.11
START_TEST(s21_mul_almost_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 46. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1030792151);
  ck_assert_int_eq((int)result.bits[1], -1889785611);
  ck_assert_int_eq((int)result.bits[2], 472446402);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.11
      -8715097876569077135289834537
      for bit0 value is -1030792151
      for bit1 value is -1889785611
      for bit2 value is 472446402
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 47: almost min * 0.99
START_TEST(s21_mul_almost_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 47. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -687194769);
  ck_assert_int_eq((int)result.bits[1], 171798691);
  ck_assert_int_eq((int)result.bits[2], -42949673);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.99
     -78435880889121694217608510831
      for bit0 value is -687194769
      for bit1 value is 171798691
      for bit2 value is -42949673
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 48: -0 * 0
START_TEST(s21_mul_neg0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 48. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 49: 0 * (-0)
START_TEST(s21_mul_0_neg0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 49. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 50: (0.2) * (0.5)
START_TEST(s21_mul_02_05_test) {
  s21_decimal left = {{2, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{5, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal result = {{0}};
  int status = s21_mul(left, right, &result);
  printf("Test mul 50. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 10);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test example
      decimal left = new decimal(2, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(5, 0, 0, false, 1);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Multiply(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result example:
      0.2
      0.5
      0.10
      for bit0 value is 10
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}
END_TEST

// div

// Test 0: -0 / (-0)
START_TEST(s21_div_neg_0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 0. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero
   */
}

END_TEST

// Test 1: 0 / 0
START_TEST(s21_div_0_0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 1. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero
   */
}

END_TEST

// Test 2: 0 / 1
START_TEST(s21_div_0_1_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 2. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 3: 1 / 0
START_TEST(s21_div_1_0_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 3. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero
   */
}

END_TEST

// Test 4: 1 / 1
START_TEST(s21_div_1_1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 4. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      1
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 5: 1 / (-1)
START_TEST(s21_div_1_neg1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 5. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      -1
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 6: (-1) / 1
START_TEST(s21_div_neg1_1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 6. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      1
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 7: (-1) / (-1)
START_TEST(s21_div_neg1_neg1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 7. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      -1
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 8: 1 / 1 - second bit
START_TEST(s21_div_second_bit_1_1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 8. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      4294967296
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 9: 1 / (-1) - second bit
START_TEST(s21_div_second_bit_1_neg1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 9. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      -4294967296
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 10: (-1) / 1 - second bit
START_TEST(s21_div_second_bit_neg1_1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 10. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      4294967296
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 11: (-1) / (-1) - second bit
START_TEST(s21_div_second_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 11. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      -4294967296
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 12: 1 / 1 - third bit
START_TEST(s21_div_third_bit_1_1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 12. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      18446744073709551616
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 13: 1 / (-1) - third bit
START_TEST(s21_div_third_bit_1_neg1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 13. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      -18446744073709551616
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 14: (-1) / 1 - third bit
START_TEST(s21_div_third_bit_neg1_1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 14. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      18446744073709551616
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 15: (-1) / (-1) - third bit
START_TEST(s21_div_third_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 15. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      -18446744073709551616
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 16: max / 0
START_TEST(s21_div_max_0_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 16. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero.
   */
}

END_TEST

// Test 17: max / 1
START_TEST(s21_div_max_1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 17. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      1
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 18: max / (-1)
START_TEST(s21_div_max_neg1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 18. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -1
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 19: max / max
START_TEST(s21_div_max_max_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 19. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      79228162514264337593543950335
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 20: min / 0
START_TEST(s21_div_min_0_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 20. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero.
   */
}

END_TEST

// Test 21: min / 1
START_TEST(s21_div_min_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 21. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      1
      -79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 22: min / (-1)
START_TEST(s21_div_min_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 22. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1);
  ck_assert_int_eq((int)result.bits[1], -1);
  ck_assert_int_eq((int)result.bits[2], -1);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      -1
      79228162514264337593543950335
      for bit0 value is -1
      for bit1 value is -1
      for bit2 value is -1
      for bit3 value is 0
   */
}

END_TEST

// Test 23: max / (-min)
START_TEST(s21_div_max_min_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 23. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -79228162514264337593543950335
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 24: 1.23 / 1.45 - common scale
START_TEST(s21_div_common_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 24. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1490279601);
  ck_assert_int_eq((int)result.bits[1], 1121387012);
  ck_assert_int_eq((int)result.bits[2], 459851266);
  ck_assert_int_eq((int)result.bits[3], 1835008);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      1.45
      0.8482758620689655172413793103
      for bit0 value is -1490279601
      for bit1 value is 1121387012
      for bit2 value is 459851266
      for bit3 value is 1835008
   */
}

END_TEST

// Test 25: 1.23 / (-1.45) - common scale
START_TEST(s21_div_common_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 25. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1490279601);
  ck_assert_int_eq((int)result.bits[1], 1121387012);
  ck_assert_int_eq((int)result.bits[2], 459851266);
  ck_assert_int_eq((int)result.bits[3], -2145648640);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      -1.45
      -0.8482758620689655172413793103
      for bit0 value is -1490279601
      for bit1 value is 1121387012
      for bit2 value is 459851266
      for bit3 value is -2145648640
   */
}

END_TEST

// Test 26: (-1.23) / 1.45 - common scale
START_TEST(s21_div_common_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 26. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1490279601);
  ck_assert_int_eq((int)result.bits[1], 1121387012);
  ck_assert_int_eq((int)result.bits[2], 459851266);
  ck_assert_int_eq((int)result.bits[3], -2145648640);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      1.45
      -0.8482758620689655172413793103
      for bit0 value is -1490279601
      for bit1 value is 1121387012
      for bit2 value is 459851266
      for bit3 value is -2145648640
   */
}

END_TEST

// Test 27: (-1.23) / (-1.45) - common scale
START_TEST(s21_div_common_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 27. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1490279601);
  ck_assert_int_eq((int)result.bits[1], 1121387012);
  ck_assert_int_eq((int)result.bits[2], 459851266);
  ck_assert_int_eq((int)result.bits[3], 1835008);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      -1.45
      0.8482758620689655172413793103
      for bit0 value is -1490279601
      for bit1 value is 1121387012
      for bit2 value is 459851266
      for bit3 value is 1835008
   */
}

END_TEST

// Test 28: 12.3 / 1.45 - different scale
START_TEST(s21_div_different_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 28. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1490279601);
  ck_assert_int_eq((int)result.bits[1], 1121387012);
  ck_assert_int_eq((int)result.bits[2], 459851266);
  ck_assert_int_eq((int)result.bits[3], 1769472);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      1.45
      8.482758620689655172413793103
      for bit0 value is -1490279601
      for bit1 value is 1121387012
      for bit2 value is 459851266
      for bit3 value is 1769472
   */
}

END_TEST

// Test 29: 12.3 / (-1.45) - different scale
START_TEST(s21_div_different_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 29. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1490279601);
  ck_assert_int_eq((int)result.bits[1], 1121387012);
  ck_assert_int_eq((int)result.bits[2], 459851266);
  ck_assert_int_eq((int)result.bits[3], -2145714176);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      -1.45
      -8.482758620689655172413793103
      for bit0 value is -1490279601
      for bit1 value is 1121387012
      for bit2 value is 459851266
      for bit3 value is -2145714176
   */
}

END_TEST

// Test 30: (-12.3) / 1.45 - different scale
START_TEST(s21_div_different_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 30. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1490279601);
  ck_assert_int_eq((int)result.bits[1], 1121387012);
  ck_assert_int_eq((int)result.bits[2], 459851266);
  ck_assert_int_eq((int)result.bits[3], -2145714176);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      1.45
      -8.482758620689655172413793103
      for bit0 value is -1490279601
      for bit1 value is 1121387012
      for bit2 value is 459851266
      for bit3 value is -2145714176
   */
}

END_TEST

// Test 31: (-12.3) / (-1.45) - different scale
START_TEST(s21_div_different_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 31. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], -1490279601);
  ck_assert_int_eq((int)result.bits[1], 1121387012);
  ck_assert_int_eq((int)result.bits[2], 459851266);
  ck_assert_int_eq((int)result.bits[3], 1769472);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      -1.45
      8.482758620689655172413793103
      for bit0 value is -1490279601
      for bit1 value is 1121387012
      for bit2 value is 459851266
      for bit3 value is 1769472
   */
}

END_TEST

// Test 32: 7.9228162514264337593543950335 / 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_div_max_scale_1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 32. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      7.9228162514264337593543950335
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 33: 7.9228162514264337593543950335 / (-7.9228162514264337593543950335) -
// max scale
START_TEST(s21_div_max_scale_1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 33. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      7.9228162514264337593543950335
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 34: (-7.9228162514264337593543950335) / 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_div_max_scale_neg1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 34. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      -7.9228162514264337593543950335
      -1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 35: (-7.9228162514264337593543950335) /
// (-7.9228162514264337593543950335) - max scale
START_TEST(s21_div_max_scale_neg1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 35. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 1);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      -7.9228162514264337593543950335
      1
      for bit0 value is 1
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 36: number / number
START_TEST(s21_div_number_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_div(left, right, &result);
      printf("Test div 36. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Divide(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          2
          2
          1
          for bit0 value is 1
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 37: number / (-number)
START_TEST(s21_div_number_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_div(left, right, &result);
      printf("Test div 37. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Divide(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          2
          -2
          -1
          for bit0 value is 1
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 38: (-number) / number
START_TEST(s21_div_negnumber_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_div(left, right, &result);
      printf("Test div 38. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Divide(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          2
          -1
          for bit0 value is 1
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 39: (-number) / (-number)
START_TEST(s21_div_negnumber_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_div(left, right, &result);
      printf("Test div 39. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Divide(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          -2
          1
          for bit0 value is 1
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 40: max / 0.11
START_TEST(s21_div_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 40. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.11
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal.
   */
}

END_TEST

// Test 41: max / 0.99
START_TEST(s21_div_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 41. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.99
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 42: almost max / 0.11
START_TEST(s21_div_almost_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 42. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.11
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 43: almost max / 0.99
START_TEST(s21_div_almost_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 43. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 1);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.99
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 44: min / 0.11
START_TEST(s21_div_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 44. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.11
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 45: min / 0.99
START_TEST(s21_div_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 45. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.99
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 46: almost min / 0.11
START_TEST(s21_div_almost_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 46. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.11
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 47: almost min / 0.99
START_TEST(s21_div_almost_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 47. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 2);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.99
      Unhandled Exception:
      System.OverflowException: Value was either too large or too small for a
  Decimal
   */
}

END_TEST

// Test 48: -0 / 0
START_TEST(s21_div_neg0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 48. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero.
   */
}

END_TEST

// Test 49: 0 / (-0)
START_TEST(s21_div_0_neg0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 49. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero.
   */
}

END_TEST

// Test 50: 79228162514264337593543950335 / 7.9228162514264337593543950335 - max
// scale
START_TEST(s21_div_time_max_scale_1_1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_div(left, right, &result);
  printf("Test div 50. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 268435456);
  ck_assert_int_eq((int)result.bits[1], 1042612833);
  ck_assert_int_eq((int)result.bits[2], 542101086);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Divide(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      7.9228162514264337593543950335
      10000000000000000000000000000
      for bit0 value is 268435456
      for bit1 value is 1042612833
      for bit2 value is 542101086
      for bit3 value is 0
   */
}

END_TEST

// mod

// Test 0: -0 % (-0)
START_TEST(s21_mod_neg_0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 0. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero
   */
}

END_TEST

// Test 1: 0 % 0
START_TEST(s21_mod_0_0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 1. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero
   */
}

END_TEST

// Test 2: 0 % 1
START_TEST(s21_mod_0_1_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 2. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 3: 1 % 0
START_TEST(s21_mod_1_0_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 3. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero
   */
}

END_TEST

// Test 4: 1 % 1
START_TEST(s21_mod_1_1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 4. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 5: 1 % (-1)
START_TEST(s21_mod_1_neg1_test) {
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 5. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1
      -1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 6: (-1) % 1
START_TEST(s21_mod_neg1_1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 6. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 7: (-1) % (-1)
START_TEST(s21_mod_neg1_neg1_test) {
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 7. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1
      -1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 8: 1 % 1 - second bit
START_TEST(s21_mod_second_bit_1_1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 8. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      4294967296
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 9: 1 % (-1) - second bit
START_TEST(s21_mod_second_bit_1_neg1_test) {
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 9. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      4294967296
      -4294967296
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 10: (-1) % 1 - second bit
START_TEST(s21_mod_second_bit_neg1_1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 10. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      4294967296
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 11: (-1) % (-1) - second bit
START_TEST(s21_mod_second_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 11. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -4294967296
      -4294967296
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 12: 1 % 1 - third bit
START_TEST(s21_mod_third_bit_1_1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 12. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      18446744073709551616
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 13: 1 % (-1) - third bit
START_TEST(s21_mod_third_bit_1_neg1_test) {
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 13. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      18446744073709551616
      -18446744073709551616
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 14: (-1) % 1 - third bit
START_TEST(s21_mod_third_bit_neg1_1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 14. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      18446744073709551616
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 15: (-1) % (-1) - third bit
START_TEST(s21_mod_third_bit_neg1_neg1_test) {
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 15. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -18446744073709551616
      -18446744073709551616
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 16: max % 0
START_TEST(s21_mod_max_0_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 16. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero.
   */
}

END_TEST

// Test 17: max % 1
START_TEST(s21_mod_max_1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 17. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 18: max % (-1)
START_TEST(s21_mod_max_neg1_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 18. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -1
      -0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 19: max % max
START_TEST(s21_mod_max_max_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 19. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      79228162514264337593543950335
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 20: min % 0
START_TEST(s21_mod_min_0_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 20. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero.
   */
}

END_TEST

// Test 21: min % 1
START_TEST(s21_mod_min_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 21. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 22: min % (-1)
START_TEST(s21_mod_min_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 22. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      -1
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147483648
   */
}

END_TEST

// Test 23: max % (-min)
START_TEST(s21_mod_max_min_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 23. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      -79228162514264337593543950335
      0
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 0
   */
}

END_TEST

// Test 24: 1.23 % 1.45 - common scale
START_TEST(s21_mod_common_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 24. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 123);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      1.45
      1.23
      for bit0 value is 123
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 25: 1.23 % (-1.45) - common scale
START_TEST(s21_mod_common_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 25. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 123);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      1.23
      -1.45
      1.23
      for bit0 value is 123
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 26: (-1.23) % 1.45 - common scale
START_TEST(s21_mod_common_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 26. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 123);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      1.45
      -1.23
      for bit0 value is 123
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 27: (-1.23) % (-1.45) - common scale
START_TEST(s21_mod_common_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 27. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 123);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -1.23
      -1.45
      -1.23
      for bit0 value is 123
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 28: 12.3 % 1.45 - different scale
START_TEST(s21_mod_different_scale_1_1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 28. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 70);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      1.45
      0.70
      for bit0 value is 70
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 29: 12.3 % (-1.45) - different scale
START_TEST(s21_mod_different_scale_1_neg1_test) {
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 29. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 70);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      12.3
      -1.45
      0.70
      for bit0 value is 70
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 30: (-12.3) % 1.45 - different scale
START_TEST(s21_mod_different_scale_neg1_1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 30. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 70);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      1.45
      -0.70
      for bit0 value is 70
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 31: (-12.3) % (-1.45) - different scale
START_TEST(s21_mod_different_scale_neg1_neg1_test) {
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 31. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 70);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -12.3
      -1.45
      -0.70
      for bit0 value is 70
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 32: 7.9228162514264337593543950335 % 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_mod_max_scale_1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 32. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_28);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      7.9228162514264337593543950335
      0.0000000000000000000000000000
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 1835008
   */
}

END_TEST

// Test 33: 7.9228162514264337593543950335 % (-7.9228162514264337593543950335) -
// max scale
START_TEST(s21_mod_max_scale_1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 33. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_28);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      7.9228162514264337593543950335
      0.0000000000000000000000000000
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 1835008
   */
}

END_TEST

// Test 34: (-7.9228162514264337593543950335) % 7.9228162514264337593543950335 -
// max scale
START_TEST(s21_mod_max_scale_neg1_1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 34. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], -2145648640);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      7.9228162514264337593543950335
      -7.9228162514264337593543950335
      0.0000000000000000000000000000
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2145648640
   */
}

END_TEST

// Test 35: (-7.9228162514264337593543950335) %
// (-7.9228162514264337593543950335) - max scale
START_TEST(s21_mod_max_scale_neg1_neg1_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 35. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], -2145648640);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -7.9228162514264337593543950335
      -7.9228162514264337593543950335
      0.0000000000000000000000000000
      for bit0 value is 0
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2145648640
   */
}

END_TEST

// Test 36: number % number
START_TEST(s21_mod_number_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_mod(left, right, &result);
      printf("Test mod 36. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(3, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(5, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Remainder(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          3
          5
          3
          for bit0 value is 3
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 37: number % (-number)
START_TEST(s21_mod_number_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_mod(left, right, &result);
      printf("Test mod 37. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(3, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(5, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Remainder(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          3
          -5
          3
          for bit0 value is 3
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is 0
       */
    }
  }
}

END_TEST

// Test 38: (-number) % number
START_TEST(s21_mod_negnumber_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, 0}};
      s21_decimal result = {{0}};
      int status = s21_mod(left, right, &result);
      printf("Test mod 38. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Remainder(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          2
          0
          for bit0 value is 0
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 39: (-number) % (-number)
START_TEST(s21_mod_negnumber_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal result = {{0}};
      int status = s21_mod(left, right, &result);
      printf("Test mod 39. Status is %d, Result is \n", status);
      print_decimal_binary(result);
      ck_assert_int_eq(status, 0);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          decimal answer = Decimal.Remainder(left, right);
          Console.WriteLine(answer.ToString());
          int[] bits = decimal.GetBits(answer);
          for(int i = 0; i < 4; i++) {
              Console.WriteLine("for bit" + i + " value is " +
      bits[i].ToString());
          }
      c# result example:
          -2
          -2
          0
          for bit0 value is 0
          for bit1 value is 0
          for bit2 value is 0
          for bit3 value is -2147483648
       */
    }
  }
}

END_TEST

// Test 40: max % 0.11
START_TEST(s21_mod_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 40. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 8);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.11
      0.08
      for bit0 value is 8
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 41: max % 0.99
START_TEST(s21_mod_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 41. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 63);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950335
      0.99
      0.63
      for bit0 value is 63
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 42: almost max % 0.11
START_TEST(s21_mod_almost_max_small_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 42. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 7);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.11
      0.07
      for bit0 value is 7
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 43: almost max % 0.99
START_TEST(s21_mod_almost_max_small_bigger_test) {
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 43. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 62);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], POS_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      79228162514264337593543950334
      0.99
      0.62
      for bit0 value is 62
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is 131072
   */
}

END_TEST

// Test 44: min % 0.11
START_TEST(s21_mod_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 44. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 8);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.11
      -0.08
      for bit0 value is 8
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 45: min % 0.99
START_TEST(s21_mod_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 45. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 63);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950335
      0.99
      -0.63
      for bit0 value is 63
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 46: almost min % 0.11
START_TEST(s21_mod_almost_min_small_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 46. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 7);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.11
      -0.07
      for bit0 value is 7
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 47: almost min % 0.99
START_TEST(s21_mod_almost_min_small_bigger_test) {
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 47. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 62);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], INT_NEG_SIGN_SCALE_2);
  ck_assert_int_eq(status, 0);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      -79228162514264337593543950334
      0.99
      -0.62
      for bit0 value is 62
      for bit1 value is 0
      for bit2 value is 0
      for bit3 value is -2147352576
   */
}

END_TEST

// Test 48: -0 % 0
START_TEST(s21_mod_neg0_0_test) {
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 48. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero.
   */
}

END_TEST

// Test 49: 0 % (-0)
START_TEST(s21_mod_0_neg0_test) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal result = {{0}};
  int status = s21_mod(left, right, &result);
  printf("Test mod 49. Status is %d, Result is \n", status);
  print_decimal_binary(result);
  ck_assert_int_eq((int)result.bits[0], 0);
  ck_assert_int_eq((int)result.bits[1], 0);
  ck_assert_int_eq((int)result.bits[2], 0);
  ck_assert_int_eq((int)result.bits[3], 0);
  ck_assert_int_eq(status, 3);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      decimal answer = Decimal.Remainder(left, right);
      Console.WriteLine(answer.ToString());
      int[] bits = decimal.GetBits(answer);
      for(int i = 0; i < 4; i++) {
          Console.WriteLine("for bit" + i + " value is " + bits[i].ToString());
      }
  c# result:
      0
      0
      0
      Unhandled Exception:
      System.DivideByZeroException: Attempted to divide by zero.
   */
}

END_TEST

// Comparison Operators
// 0 - FALSE
// 1 - TRUE
// c# compare: Меньше нуля - Значение d1 меньше d2, 0 - Значения параметров d1 и
// d2 равны, Больше нуля - Значение d1 больше значения d2

// Test 0: -0 compare (-0)
START_TEST(s21_comparison_neg_0_0_test) {
  printf("Compare test 0\n");
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      0
      0
      equal status is: 0
   */
}

END_TEST

// Test 1: 0 compare 0
START_TEST(s21_comparison_0_0_test) {
  printf("Compare test 1\n");
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      0
      0
      status is: 0
   */
}

END_TEST

// Test 2: 0 compare 1
START_TEST(s21_comparison_0_1_test) {
  printf("Compare test 2\n");
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      0
      1
      status is: -1
   */
}

END_TEST

// Test 3: 1 compare 0
START_TEST(s21_comparison_1_0_test) {
  printf("Compare test 3\n");
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      1
      0
      status is: 1
   */
}

END_TEST

// Test 4: 1 compare 1
START_TEST(s21_comparison_1_1_test) {
  printf("Compare test 4\n");
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      1
      1
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
   */
}

END_TEST

// Test 5: 1 compare (-1)
START_TEST(s21_comparison_1_neg1_test) {
  printf("Compare test 5\n");
  s21_decimal left = {{1, 0, 0, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      1
      -1
      status is: 1
   */
}

END_TEST

// Test 6: (-1) compare 1
START_TEST(s21_comparison_neg1_1_test) {
  printf("Compare test 6\n");
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -1
      1
      status is: -1
   */
}

END_TEST

// Test 7: (-1) compare (-1)
START_TEST(s21_comparison_neg1_neg1_test) {
  printf("Compare test 7\n");
  s21_decimal left = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -1
      -1
      status is: 0
   */
}

END_TEST

// Test 8: 1 compare 1 - second bit
START_TEST(s21_comparison_second_bit_1_1_test) {
  printf("Compare test 8\n");
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      4294967296
      4294967296
      status is: 0
   */
}

END_TEST

// Test 9: 1 compare (-1) - second bit
START_TEST(s21_comparison_second_bit_1_neg1_test) {
  printf("Compare test 9\n");
  s21_decimal left = {{0, 1, 0, 0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      4294967296
      -4294967296
      status is: 1
   */
}

END_TEST

// Test 10: (-1) compare 1 - second bit
START_TEST(s21_comparison_second_bit_neg1_1_test) {
  printf("Compare test 10\n");
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -4294967296
      4294967296
      status is: -1
   */
}

END_TEST

// Test 11: (-1) compare (-1) - second bit
START_TEST(s21_comparison_second_bit_neg1_neg1_test) {
  printf("Compare test 11\n");
  s21_decimal left = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 1, 0, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 1, 0, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -4294967296
      -4294967296
      status is: 0
   */
}

END_TEST

// Test 12: 1 compare 1 - third bit
START_TEST(s21_comparison_third_bit_1_1_test) {
  printf("Compare test 12\n");
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      18446744073709551616
      18446744073709551616
      status is: 0
   */
}

END_TEST

// Test 13: 1 compare (-1) - third bit
START_TEST(s21_comparison_third_bit_1_neg1_test) {
  printf("Compare test 13\n");
  s21_decimal left = {{0, 0, 1, 0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      18446744073709551616
      -18446744073709551616
      status is: 1
   */
}

END_TEST

// Test 14: (-1) compare 1 - third bit
START_TEST(s21_comparison_third_bit_neg1_1_test) {
  printf("Compare test 14\n");
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -18446744073709551616
      18446744073709551616
      status is: -1
   */
}

END_TEST

// Test 15: (-1) compare (-1) - third bit
START_TEST(s21_comparison_third_bit_neg1_neg1_test) {
  printf("Compare test 15\n");
  s21_decimal left = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 1, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 1, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -18446744073709551616
      -18446744073709551616
      status is: 0
   */
}

END_TEST

// Test 16: max compare 0
START_TEST(s21_comparison_max_0_test) {
  printf("Compare test 16\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950335
      0
      status is: 1
   */
}

END_TEST

// Test 17: max compare 1
START_TEST(s21_comparison_max_1_test) {
  printf("Compare test 17\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950335
      1
      status is: 1
   */
}

END_TEST

// Test 18: max compare (-1)
START_TEST(s21_comparison_max_neg1_test) {
  printf("Compare test 18\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950335
      -1
      status is: 1
   */
}

END_TEST

// Test 19: max compare max
START_TEST(s21_comparison_max_max_test) {
  printf("Compare test 19\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950335
      79228162514264337593543950335
      status is: 0
   */
}

END_TEST

// Test 20: min compare 0
START_TEST(s21_comparison_min_0_test) {
  printf("Compare test 20\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -79228162514264337593543950335
      0
      status is: -1
   */
}

END_TEST

// Test 21: min compare 1
START_TEST(s21_comparison_min_1_test) {
  printf("Compare test 21\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -79228162514264337593543950335
      1
      status is: -1
   */
}

END_TEST

// Test 22: min compare (-1)
START_TEST(s21_comparison_min_neg1_test) {
  printf("Compare test 22\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{1, 0, 0, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(1, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -79228162514264337593543950335
      -1
      status is: -1
   */
}

END_TEST

// Test 23: max compare (-min)
START_TEST(s21_comparison_max_min_test) {
  printf("Compare test 23\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950335
      -79228162514264337593543950335
      status is: 1
   */
}

END_TEST

// Test 24: 1.23 compare 1.45 - common scale
START_TEST(s21_comparison_common_scale_1_1_test) {
  printf("Compare test 24\n");
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      1.23
      1.45
      status is: -1
   */
}

END_TEST

// Test 25: 1.23 compare (-1.45) - common scale
START_TEST(s21_comparison_common_scale_1_neg1_test) {
  printf("Compare test 25\n");
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      1.23
      -1.45
      status is: 1
   */
}

END_TEST

// Test 26: (-1.23) compare 1.45 - common scale
START_TEST(s21_comparison_common_scale_neg1_1_test) {
  printf("Compare test 26\n");
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -1.23
      1.45
      status is: -1
   */
}

END_TEST

// Test 27: (-1.23) compare (-1.45) - common scale
START_TEST(s21_comparison_common_scale_neg1_neg1_test) {
  printf("Compare test 27\n");
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 2);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -1.23
      -1.45
      status is: 1
   */
}

END_TEST

// Test 28: 12.3 compare 1.45 - different scale
START_TEST(s21_comparison_different_scale_1_1_test) {
  printf("Compare test 28\n");
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      12.3
      1.45
      status is: 1
   */
}

END_TEST

// Test 29: 12.3 compare (-1.45) - different scale
START_TEST(s21_comparison_different_scale_1_neg1_test) {
  printf("Compare test 29\n");
  s21_decimal left = {{123, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, false, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      12.3
      -1.45
      status is: 1
   */
}

END_TEST

// Test 30: (-12.3) compare 1.45 - different scale
START_TEST(s21_comparison_different_scale_neg1_1_test) {
  printf("Compare test 30\n");
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -12.3
      1.45
      status is: -1
   */
}

END_TEST

// Test 31: (-12.3) compare (-1.45) - different scale
START_TEST(s21_comparison_different_scale_neg1_neg1_test) {
  printf("Compare test 31\n");
  s21_decimal left = {{123, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal right = {{145, 0, 0, NEG_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(123, 0, 0, true, 1);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(145, 0, 0, true, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -12.3
      -1.45
      status is: -1
   */
}

END_TEST

// Test 32: 7.9228162514264337593543950335
// compare 7.9228162514264337593543950335 - max scale
START_TEST(s21_comparison_max_scale_1_1_test) {
  printf("Compare test 32\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      7.9228162514264337593543950335
      7.9228162514264337593543950335
      status is: 0
   */
}

END_TEST

// Test 33: 7.9228162514264337593543950335 compare
// (-7.9228162514264337593543950335) - max scale
START_TEST(s21_comparison_max_scale_1_neg1_test) {
  printf("Compare test 33\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       POS_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -7.9228162514264337593543950335
      7.9228162514264337593543950335
      status is: 1
   */
}

END_TEST

// Test 34: (-7.9228162514264337593543950335)
// compare 7.9228162514264337593543950335 - max scale
START_TEST(s21_comparison_max_scale_neg1_1_test) {
  printf("Compare test 34\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        POS_SIGN_SCALE_28}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, false, 28);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      7.9228162514264337593543950335
      -7.9228162514264337593543950335
      status is: -1
   */
}

END_TEST

// Test 35: (-7.9228162514264337593543950335) compare
// (-7.9228162514264337593543950335) - max scale
START_TEST(s21_comparison_max_scale_neg1_neg1_test) {
  printf("Compare test 35\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_28}};
  s21_decimal right = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                        NEG_SIGN_SCALE_28}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(-1, -1, -1, true, 28);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -7.9228162514264337593543950335
      -7.9228162514264337593543950335
      status is: 0
   */
}

END_TEST

// Test 36: number compare number
START_TEST(s21_comparison_number_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      printf("Compare test 36\n");
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, 0}};
      int result = s21_is_equal(left, right);
      printf("Equal status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] == right.bits[0]);

      result = s21_is_greater(left, right);
      printf("Greater status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] > right.bits[0]);

      result = s21_is_greater_or_equal(left, right);
      printf("Greater or equal status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] >= right.bits[0]);

      result = s21_is_less(left, right);
      printf("Less status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] < right.bits[0]);

      result = s21_is_less_or_equal(left, right);
      printf("Less or equal status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] <= right.bits[0]);

      result = s21_is_not_equal(left, right);
      printf("Not equal status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] != right.bits[0]);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          int answer = Decimal.Compare(left, right);
          Console.WriteLine("status is: " + answer);
      c# result example:
          2
          2
          status is: 0
       */
    }
  }
}

END_TEST

// Test 37: number compare (-number)
START_TEST(s21_comparison_number_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      printf("Compare test 37\n");
      s21_decimal left = {{i, 0, 0, 0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      int result = s21_is_equal(left, right);
      printf("Equal status is %d\n", result);
      ck_assert_int_eq(result, 0);

      result = s21_is_greater(left, right);
      printf("Greater status is %d\n", result);
      ck_assert_int_eq(result, 1);

      result = s21_is_greater_or_equal(left, right);
      printf("Greater or equal status is %d\n", result);
      ck_assert_int_eq(result, 1);

      result = s21_is_less(left, right);
      printf("Less status is %d\n", result);
      ck_assert_int_eq(result, 0);

      result = s21_is_less_or_equal(left, right);
      printf("Less or equal status is %d\n", result);
      ck_assert_int_eq(result, 0);

      result = s21_is_not_equal(left, right);
      printf("Not equal status is %d\n", result);
      ck_assert_int_eq(result, 1);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          int answer = Decimal.Compare(left, right);
          Console.WriteLine("status is: " + answer);
      c# result example:
          2
          -2
          status is: 1
       */
    }
  }
}

END_TEST

// Test 38: (-number) compare number
START_TEST(s21_comparison_negnumber_number_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      printf("Compare test 38\n");
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, 0}};
      int result = s21_is_equal(left, right);
      printf("Equal status is %d\n", result);
      ck_assert_int_eq(result, 0);

      result = s21_is_greater(left, right);
      printf("Greater status is %d\n", result);
      ck_assert_int_eq(result, 0);

      result = s21_is_greater_or_equal(left, right);
      printf("Greater or equal status is %d\n", result);
      ck_assert_int_eq(result, 0);

      result = s21_is_less(left, right);
      printf("Less status is %d\n", result);
      ck_assert_int_eq(result, 1);

      result = s21_is_less_or_equal(left, right);
      printf("Less or equal status is %d\n", result);
      ck_assert_int_eq(result, 1);

      result = s21_is_not_equal(left, right);
      printf("Not equal status is %d\n", result);
      ck_assert_int_eq(result, 1);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, false, 0);
          Console.WriteLine(right.ToString());
          int answer = Decimal.Compare(left, right);
          Console.WriteLine("status is: " + answer);
      c# result example:
          -2
          2
          status is: -1
       */
    }
  }
}

END_TEST

// Test 39: (-number) compare (-number)
START_TEST(s21_comparison_negnumber_negnumber_test) {
  for (int i = 2; i < 10; i++) {
    for (int j = 2; j < 10; j++) {
      printf("Compare test 39\n");
      s21_decimal left = {{i, 0, 0, NEG_SIGN_SCALE_0}};
      s21_decimal right = {{j, 0, 0, NEG_SIGN_SCALE_0}};
      int result = s21_is_equal(left, right);
      printf("Equal status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] == right.bits[0]);

      result = s21_is_greater(left, right);
      printf("Greater status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] < right.bits[0]);

      result = s21_is_greater_or_equal(left, right);
      printf("Greater or equal status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] <= right.bits[0]);

      result = s21_is_less(left, right);
      printf("Less status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] > right.bits[0]);

      result = s21_is_less_or_equal(left, right);
      printf("Less or equal status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] >= right.bits[0]);

      result = s21_is_not_equal(left, right);
      printf("Not equal status is %d\n", result);
      ck_assert_int_eq(result, left.bits[0] != right.bits[0]);
      /*
       c# test example
          decimal left = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(left.ToString());
          decimal right = new decimal(2, 0, 0, true, 0);
          Console.WriteLine(right.ToString());
          int answer = Decimal.Compare(left, right);
          Console.WriteLine("status is: " + answer);
      c# result example:
          -2
          -2
          status is: 0
       */
    }
  }
}

END_TEST

// Test 40: max compare 0.11
START_TEST(s21_comparison_max_small_test) {
  printf("Compare test 40\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950335
      0.11
      status is: 1
   */
}

END_TEST

// Test 41: max compare 0.99
START_TEST(s21_comparison_max_small_bigger_test) {
  printf("Compare test 41\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950335
      0.99
      status is: 1
   */
}

END_TEST

// Test 42: almost max compare 0.11
START_TEST(s21_comparison_almost_max_small_test) {
  printf("Compare test 42\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950334
      0.11
      status is: 1
   */
}

END_TEST

// Test 43: almost max compare 0.99
START_TEST(s21_comparison_almost_max_small_bigger_test) {
  printf("Compare test 43\n");
  s21_decimal left = {
      {MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, 0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      79228162514264337593543950334
      0.99
      status is: 1
   */
}

END_TEST

// Test 44: min compare 0.11
START_TEST(s21_comparison_min_small_test) {
  printf("Compare test 44\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -79228162514264337593543950335
      0.11
      status is: -1
   */
}

END_TEST

// Test 45: min compare 0.99
START_TEST(s21_comparison_min_small_bigger_test) {
  printf("Compare test 45\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT, MAX_AT_NUMBER_BIT,
                       NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-1, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -79228162514264337593543950335
      0.99
      status is: -1
   */
}

END_TEST

// Test 46: almost min compare 0.11
START_TEST(s21_comparison_almost_min_small_test) {
  printf("Compare test 46\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{11, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(11, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -79228162514264337593543950334
      0.11
      status is: -1
   */
}

END_TEST

// Test 47: almost min compare 0.99
START_TEST(s21_comparison_almost_min_small_bigger_test) {
  printf("Compare test 47\n");
  s21_decimal left = {{MAX_AT_NUMBER_BIT - 1, MAX_AT_NUMBER_BIT,
                       MAX_AT_NUMBER_BIT, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{99, 0, 0, POS_SIGN_SCALE_2}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 1);
  /*
   c# test
      decimal left = new decimal(-2, -1, -1, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(99, 0, 0, false, 2);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      -79228162514264337593543950334
      0.99
     status is: -1
   */
}

END_TEST

// Test 48: -0 compare 0
START_TEST(s21_comparison_neg0_0_test) {
  printf("Compare test 48\n");
  s21_decimal left = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal right = {{0, 0, 0, 0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      0
      0
      status is: 0
   */
}

END_TEST

// Test 49: 0 compare (-0)
START_TEST(s21_comparison_0_neg0_test) {
  printf("Compare test 49\n");
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, NEG_SIGN_SCALE_0}};
  int result = s21_is_equal(left, right);
  printf("Equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(left, right);
  printf("Greater status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_greater_or_equal(left, right);
  printf("Greater or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_less(left, right);
  printf("Less status is %d\n", result);
  ck_assert_int_eq(result, 0);

  result = s21_is_less_or_equal(left, right);
  printf("Less or equal status is %d\n", result);
  ck_assert_int_eq(result, 1);

  result = s21_is_not_equal(left, right);
  printf("Not equal status is %d\n", result);
  ck_assert_int_eq(result, 0);
  /*
   c# test
      decimal left = new decimal(0, 0, 0, false, 0);
      Console.WriteLine(left.ToString());
      decimal right = new decimal(0, 0, 0, true, 0);
      Console.WriteLine(right.ToString());
      int answer = Decimal.Compare(left, right);
      Console.WriteLine("status is: " + answer);
  c# result:
      0
      0
      status is: 0
   */
}

END_TEST

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal x = {{150, 13658, 155, NEG_SIGN_SCALE_28}};  //
  int y = 0;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal x = {{150, 13658, 155, POS_SIGN_SCALE_28}};  //
  int y = 0;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  s21_decimal x = {{150, 13658, 155, POS_SIGN_SCALE_1}};  //
  int y = 0;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal x = {{2100000000, 0, 0, 0}};
  int y;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 2100000000);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal x = {{21000000, 0, 0, NEG_SIGN_SCALE_1}};
  int y;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -2100000);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_6) {
  s21_decimal x = {{483647, 0, 0, POS_SIGN_SCALE_2}};  // scale 2
  int y = 0;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 4836);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_7) {
  s21_decimal x = {{483647, 0, 0, NEG_SIGN_SCALE_2}};  // scale 2
  int y = 0;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -4836);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_8) {
  s21_decimal x = {{3345465, 0, 0, NEG_SIGN_SCALE_2}};  // scale 2
  int y = 0;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -33454);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_9) {
  s21_decimal x = {{3345465, 0, 0, POS_SIGN_SCALE_2}};  // scale 2
  int y = 0;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 33454);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_10) {
  s21_decimal x = {{153432434, 0, 0, POS_SIGN_SCALE_1}};  //
  int y = 0;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 15343243);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal x = {{15008, 0, 0, 196608}};
  float res1;
  int return_1 = s21_from_decimal_to_float(x, &res1);
  float res2 = 15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(return_1, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  s21_decimal x = {{15008, 0, 0, 2147680256}};
  float res1;
  int return_1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(return_1, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  s21_decimal x = {{15008, 0, 0, NEG_SIGN_SCALE_28}};
  float res1;
  int return_1 = s21_from_decimal_to_float(x, &res1);
  ck_assert_int_eq(return_1, 1);
}

END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal x = {{15008, 0, 0, POS_SIGN_SCALE_28}};
  float res1;
  int return_1 = s21_from_decimal_to_float(x, &res1);
  ck_assert_int_eq(return_1, 1);
}

END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal x = {{15008, 0, 0, POS_SIGN_SCALE_1}};
  float res1;
  int return_1 = s21_from_decimal_to_float(x, &res1);
  float res2 = 1500.8;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(return_1, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_float_6) {
  s21_decimal x = {{15008, 0, 0, NEG_SIGN_SCALE_1}};
  float res1;
  int return_1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -1500.8;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(return_1, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_float_7) {
  s21_decimal x = {{15008234, 0, 0, NEG_SIGN_SCALE_2}};
  float res1;
  int return_1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -150082.34;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(return_1, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_float_8) {
  s21_decimal x = {{15008234, 0, 0, POS_SIGN_SCALE_2}};
  float res1;
  int return_1 = s21_from_decimal_to_float(x, &res1);
  float res2 = 150082.34;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(return_1, 0);
}

END_TEST

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = 11.2646;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = 1145834519.2646327;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = 0.1;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = -0.000003;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = -10.2646327;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = 0;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = -0.6139;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_8) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = 1145834519.0345;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_9) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = -7922332.5;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_float_to_decimal_10) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0;
  float tmp = 7922332.5;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}

END_TEST

START_TEST(s21_from_int_to_decimal_1) {
  int src = 49135648;
  s21_decimal check = {{49135648, 0, 0, 0}};
  s21_decimal result = {{0}};
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(return_value, 0);
}

END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  int src = -4;
  s21_decimal check = {{4, 0, 0, 0}};
  s21_decimal result = {{0}};
  set_sign_1_norm_dec(&check);
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}

END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  int src = -23454656;
  s21_decimal check = {{23454656, 0, 0, 0}};
  set_sign_1_norm_dec(&check);
  s21_decimal result = {{0}};
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}

END_TEST

START_TEST(s21_from_int_to_decimal_4) {
  int src = -25435345;
  s21_decimal check = {{25435345, 0, 0, 0}};
  set_sign_1_norm_dec(&check);
  s21_decimal result = {{0}};
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}

END_TEST

START_TEST(s21_from_int_to_decimal_5) {
  int src = 1432342;
  s21_decimal check = {{1432342, 0, 0, 0}};
  s21_decimal result = {{0}};
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(return_value, 0);
}

END_TEST

START_TEST(s21_from_int_to_decimal_6) {
  int src = 3324345;
  s21_decimal check = {{3324345, 0, 0, 0}};
  s21_decimal result = {{0}};
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(return_value, 0);
}

END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal val = {{128564325, 0, 0, 491520}};
  s21_decimal or = {{12, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal val = {{128564325, 0, 0, 2147975168}};
  s21_decimal or = {{12, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_truncate_3) {
  s21_decimal val = {{245345, 0, 0, 0}};
  s21_decimal or = {{245345, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_truncate_4) {
  s21_decimal val = {{400000, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal or = {{4000, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_truncate_5) {
  s21_decimal val = {{400000, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal or = {{40000, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_truncate_6) {
  s21_decimal val = {{400353454, 0, 0, POS_SIGN_SCALE_28}};
  s21_decimal or = {{0, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_truncate_7) {
  s21_decimal val = {{400353454, 0, 0, 1900544}};
  s21_decimal or = {{0, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 1);
}

END_TEST

START_TEST(s21_truncate_8) {
  s21_decimal val = {{400353454, 0, 0, 2149384192}};
  s21_decimal or = {{0, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 1);
}

END_TEST

START_TEST(s21_truncate_10) {
  s21_decimal val = {{0, 1, 0, POS_SIGN_SCALE_1}};
  s21_decimal or = {{429496729, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

// NEG_SIGN_SCALE_0 2147483648   // 0x80000000(hex) -
// 10000000000000000000000000000000 #define POS_SIGN_SCALE_1 65536         //
// 0x10000 (hex)  - 00000000000000010000000000000000 #define POS_SIGN_SCALE_2
// 131072        // 0x20000 (hex)  - 00000000000000100000000000000000 #define
// POS_SIGN_SCALE_28 1835008      // 0x1C0000(hex)  -
// 00000000000111000000000000000000 #define NEG_SIGN_SCALE_1 2147549184  //
// 0x80010000 (hex) - 10000000000000010000000000000000 #define NEG_SIGN_SCALE_2
// 2147614720  // 0x80020000 (hex) - 10000000000000100000000000000000 #define
// NEG_SIGN_SCALE_28 2149318656

START_TEST(s21_floor_1) {
  s21_decimal val = {{128564325, 0, 0, 491520}};
  s21_decimal or = {{12, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_floor_2) {
  s21_decimal val = {{128564325, 0, 0, 2147975168}};
  s21_decimal or = {{13, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_floor_3) {
  s21_decimal val = {{245345, 0, 0, 0}};
  s21_decimal or = {{245345, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_floor_4) {
  s21_decimal val = {{400000, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal or = {{4000, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_floor_5) {
  s21_decimal val = {{400000, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal or = {{40000, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_floor_6) {
  s21_decimal val = {{400353454, 0, 0, POS_SIGN_SCALE_28}};
  s21_decimal or = {{0, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_floor_7) {
  s21_decimal val = {{400353454, 0, 0, 1900544}};
  s21_decimal or = {{0, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 1);
}

END_TEST

START_TEST(s21_truncate_9) {
  s21_decimal val = {{574354, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal or = {{574354, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal res = {0};
  int x = s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_floor_8) {
  s21_decimal val = {{400353454, 0, 0, 2149384192}};
  s21_decimal or = {{0, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 1);
}

END_TEST

START_TEST(s21_floor_9) {
  s21_decimal val = {{574354, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal or = {{574354, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_floor_10) {
  s21_decimal val = {{0, 1, 0, POS_SIGN_SCALE_1}};
  s21_decimal or = {{429496729, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_floor(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_round_1) {
  s21_decimal val = {{128564325, 0, 0, 491520}};
  s21_decimal or = {{13, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST
START_TEST(s21_round_2) {
  s21_decimal val = {{128564325, 0, 0, 2147975168}};
  s21_decimal or = {{13, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST
START_TEST(s21_round_3) {
  s21_decimal val = {{245345, 0, 0, 0}};
  s21_decimal or = {{245345, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST
START_TEST(s21_round_4) {
  s21_decimal val = {{400000, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal or = {{4000, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST
START_TEST(s21_round_5) {
  s21_decimal val = {{400000, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal or = {{40000, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_round_6) {
  s21_decimal val = {{574354, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal or = {{574354, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_round_7) {
  s21_decimal val = {{400353454, 0, 0, POS_SIGN_SCALE_28}};
  s21_decimal or = {{0, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_round_8) {
  s21_decimal val = {{4234234, 0, 0, 1900544}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(x, 1);
}

END_TEST

START_TEST(s21_round_9) {
  s21_decimal val = {{0, 1, 0, POS_SIGN_SCALE_1}};
  s21_decimal or = {{429496730, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_round_10) {
  s21_decimal val = {{400000, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal or = {{40000, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal res = {0};
  int x = s21_round(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_negate_1) {
  s21_decimal val = {{128564325, 0, 0, 491520}};
  s21_decimal or = {{128564325, 0, 0, 2147975168}};
  s21_decimal res = {0};
  int x = s21_negate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_negate_2) {
  s21_decimal val = {{128564325, 0, 0, 2147975168}};
  s21_decimal or = {{128564325, 0, 0, 491520}};
  s21_decimal res = {0};
  int x = s21_negate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_negate_3) {
  s21_decimal val = {{245345, 0, 0, 0}};
  s21_decimal or = {{245345, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_negate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_negate_4) {
  s21_decimal val = {{400000, 0, 0, POS_SIGN_SCALE_2}};
  s21_decimal or = {{400000, 0, 0, NEG_SIGN_SCALE_2}};
  s21_decimal res = {0};
  int x = s21_negate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_negate_5) {
  s21_decimal val = {{400000, 0, 0, POS_SIGN_SCALE_1}};
  s21_decimal or = {{400000, 0, 0, NEG_SIGN_SCALE_1}};
  s21_decimal res = {0};
  int x = s21_negate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_negate_6) {
  s21_decimal val = {{400000, 0, 0, NEG_SIGN_SCALE_0}};
  s21_decimal or = {{400000, 0, 0, 0}};
  s21_decimal res = {0};
  int x = s21_negate(val, &res);
  ck_assert_int_eq(res.bits[3], or.bits[3]);
  ck_assert_int_eq(res.bits[2], or.bits[2]);
  ck_assert_int_eq(res.bits[1], or.bits[1]);
  ck_assert_int_eq(res.bits[0], or.bits[0]);
  ck_assert_int_eq(x, 0);
}

END_TEST

START_TEST(s21_negate_7) {
  s21_decimal val = {{1, 1, 1, 3932160}};
  s21_decimal res = {0};
  int x = s21_negate(val, &res);
  ck_assert_int_eq(x, 1);
}

END_TEST

int main(void) {
  setlocale(LC_ALL, "");
  int number_failed;
  Suite *s = suite_create("s21_decimal");

  TCase *s21_decimal_h = tcase_create("s21_decimal_h");
  SRunner *sr = srunner_create(s);

  suite_add_tcase(s, s21_decimal_h);

  //     add
  tcase_add_test(s21_decimal_h, s21_add_neg_0_0_test);
  tcase_add_test(s21_decimal_h, s21_add_0_0_test);
  tcase_add_test(s21_decimal_h, s21_add_0_1_test);
  tcase_add_test(s21_decimal_h, s21_add_1_0_test);
  tcase_add_test(s21_decimal_h, s21_add_1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_second_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_second_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_second_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_second_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_third_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_third_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_third_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_third_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_max_0_test);
  tcase_add_test(s21_decimal_h, s21_add_max_1_test);
  tcase_add_test(s21_decimal_h, s21_add_max_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_max_max_test);
  tcase_add_test(s21_decimal_h, s21_add_min_0_test);
  tcase_add_test(s21_decimal_h, s21_add_min_1_test);
  tcase_add_test(s21_decimal_h, s21_add_min_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_max_min_test);
  tcase_add_test(s21_decimal_h, s21_add_common_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_common_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_common_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_common_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_different_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_different_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_different_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_different_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_max_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_max_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_max_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_add_max_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_add_number_number_test);
  tcase_add_test(s21_decimal_h, s21_add_number_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_add_negnumber_number_test);
  tcase_add_test(s21_decimal_h, s21_add_negnumber_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_add_max_small_test);
  tcase_add_test(s21_decimal_h, s21_add_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_add_almost_max_small_test);
  tcase_add_test(s21_decimal_h, s21_add_almost_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_add_min_small_test);
  tcase_add_test(s21_decimal_h, s21_add_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_add_almost_min_small_test);
  tcase_add_test(s21_decimal_h, s21_add_almost_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_add_neg0_0_test);
  tcase_add_test(s21_decimal_h, s21_add_0_neg0_test);
  tcase_add_test(s21_decimal_h, s21_div_time_max_scale_1_1_test);

  // sub
  tcase_add_test(s21_decimal_h, s21_sub_neg_0_0_test);
  tcase_add_test(s21_decimal_h, s21_sub_0_0_test);
  tcase_add_test(s21_decimal_h, s21_sub_0_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_1_0_test);
  tcase_add_test(s21_decimal_h, s21_sub_1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_second_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_second_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_second_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_second_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_third_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_third_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_third_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_third_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_0_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_max_test);
  tcase_add_test(s21_decimal_h, s21_sub_min_0_test);
  tcase_add_test(s21_decimal_h, s21_sub_min_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_min_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_min_test);
  tcase_add_test(s21_decimal_h, s21_sub_common_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_common_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_common_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_common_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_different_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_different_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_different_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_different_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_sub_number_number_test);
  tcase_add_test(s21_decimal_h, s21_sub_number_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_sub_negnumber_number_test);
  tcase_add_test(s21_decimal_h, s21_sub_negnumber_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_small_test);
  tcase_add_test(s21_decimal_h, s21_sub_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_sub_almost_max_small_test);
  tcase_add_test(s21_decimal_h, s21_sub_almost_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_sub_min_small_test);
  tcase_add_test(s21_decimal_h, s21_sub_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_sub_almost_min_small_test);
  tcase_add_test(s21_decimal_h, s21_sub_almost_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_sub_neg0_0_test);
  tcase_add_test(s21_decimal_h, s21_sub_0_neg0_test);
  tcase_add_test(s21_decimal_h, s21_sub_15_113_test);

  // mul
  tcase_add_test(s21_decimal_h, s21_mul_neg_0_0_test);
  tcase_add_test(s21_decimal_h, s21_mul_0_0_test);
  tcase_add_test(s21_decimal_h, s21_mul_0_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_1_0_test);
  tcase_add_test(s21_decimal_h, s21_mul_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_second_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_second_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_second_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_second_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_third_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_third_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_third_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_third_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_0_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_max_test);
  tcase_add_test(s21_decimal_h, s21_mul_min_0_test);
  tcase_add_test(s21_decimal_h, s21_mul_min_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_min_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_min_test);
  tcase_add_test(s21_decimal_h, s21_mul_common_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_common_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_common_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_common_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_different_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_different_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_different_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_different_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mul_number_number_test);
  tcase_add_test(s21_decimal_h, s21_mul_number_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_mul_negnumber_number_test);
  tcase_add_test(s21_decimal_h, s21_mul_negnumber_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_small_test);
  tcase_add_test(s21_decimal_h, s21_mul_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_mul_almost_max_small_test);
  tcase_add_test(s21_decimal_h, s21_mul_almost_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_mul_min_small_test);
  tcase_add_test(s21_decimal_h, s21_mul_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_mul_almost_min_small_test);
  tcase_add_test(s21_decimal_h, s21_mul_almost_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_mul_neg0_0_test);
  tcase_add_test(s21_decimal_h, s21_mul_0_neg0_test);
  tcase_add_test(s21_decimal_h, s21_mul_02_05_test);

  //    div
  tcase_add_test(s21_decimal_h, s21_div_neg_0_0_test);
  tcase_add_test(s21_decimal_h, s21_div_0_0_test);
  tcase_add_test(s21_decimal_h, s21_div_0_1_test);
  tcase_add_test(s21_decimal_h, s21_div_1_0_test);
  tcase_add_test(s21_decimal_h, s21_div_1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_second_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_second_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_second_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_second_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_third_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_third_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_third_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_third_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_max_0_test);
  tcase_add_test(s21_decimal_h, s21_div_max_1_test);
  tcase_add_test(s21_decimal_h, s21_div_max_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_max_max_test);
  tcase_add_test(s21_decimal_h, s21_div_min_0_test);
  tcase_add_test(s21_decimal_h, s21_div_min_1_test);
  tcase_add_test(s21_decimal_h, s21_div_min_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_max_min_test);
  tcase_add_test(s21_decimal_h, s21_div_common_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_common_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_common_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_common_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_different_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_different_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_different_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_different_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_max_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_max_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_max_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_div_max_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_div_number_number_test);
  tcase_add_test(s21_decimal_h, s21_div_number_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_div_negnumber_number_test);
  tcase_add_test(s21_decimal_h, s21_div_negnumber_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_div_max_small_test);
  tcase_add_test(s21_decimal_h, s21_div_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_div_almost_max_small_test);
  tcase_add_test(s21_decimal_h, s21_div_almost_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_div_min_small_test);
  tcase_add_test(s21_decimal_h, s21_div_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_div_almost_min_small_test);
  tcase_add_test(s21_decimal_h, s21_div_almost_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_div_neg0_0_test);
  tcase_add_test(s21_decimal_h, s21_div_0_neg0_test);

  //    mod
  tcase_add_test(s21_decimal_h, s21_mod_neg_0_0_test);
  tcase_add_test(s21_decimal_h, s21_mod_0_0_test);
  tcase_add_test(s21_decimal_h, s21_mod_0_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_1_0_test);
  tcase_add_test(s21_decimal_h, s21_mod_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_second_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_second_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_second_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_second_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_third_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_third_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_third_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_third_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_0_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_max_test);
  tcase_add_test(s21_decimal_h, s21_mod_min_0_test);
  tcase_add_test(s21_decimal_h, s21_mod_min_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_min_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_min_test);
  tcase_add_test(s21_decimal_h, s21_mod_common_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_common_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_common_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_common_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_different_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_different_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_different_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_different_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_mod_number_number_test);
  tcase_add_test(s21_decimal_h, s21_mod_number_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_mod_negnumber_number_test);
  tcase_add_test(s21_decimal_h, s21_mod_negnumber_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_small_test);
  tcase_add_test(s21_decimal_h, s21_mod_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_mod_almost_max_small_test);
  tcase_add_test(s21_decimal_h, s21_mod_almost_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_mod_min_small_test);
  tcase_add_test(s21_decimal_h, s21_mod_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_mod_almost_min_small_test);
  tcase_add_test(s21_decimal_h, s21_mod_almost_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_mod_neg0_0_test);
  tcase_add_test(s21_decimal_h, s21_mod_0_neg0_test);

  // comparison
  tcase_add_test(s21_decimal_h, s21_comparison_neg_0_0_test);
  tcase_add_test(s21_decimal_h, s21_comparison_0_0_test);
  tcase_add_test(s21_decimal_h, s21_comparison_0_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_1_0_test);
  tcase_add_test(s21_decimal_h, s21_comparison_1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_second_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_second_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_second_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_second_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_third_bit_1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_third_bit_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_third_bit_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_third_bit_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_0_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_max_test);
  tcase_add_test(s21_decimal_h, s21_comparison_min_0_test);
  tcase_add_test(s21_decimal_h, s21_comparison_min_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_min_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_min_test);
  tcase_add_test(s21_decimal_h, s21_comparison_common_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_common_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_common_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_common_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_different_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_different_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_different_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_different_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_scale_1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_scale_1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_scale_neg1_1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_scale_neg1_neg1_test);
  tcase_add_test(s21_decimal_h, s21_comparison_number_number_test);
  tcase_add_test(s21_decimal_h, s21_comparison_number_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_comparison_negnumber_number_test);
  tcase_add_test(s21_decimal_h, s21_comparison_negnumber_negnumber_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_small_test);
  tcase_add_test(s21_decimal_h, s21_comparison_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_comparison_almost_max_small_test);
  tcase_add_test(s21_decimal_h, s21_comparison_almost_max_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_comparison_min_small_test);
  tcase_add_test(s21_decimal_h, s21_comparison_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_comparison_almost_min_small_test);
  tcase_add_test(s21_decimal_h, s21_comparison_almost_min_small_bigger_test);
  tcase_add_test(s21_decimal_h, s21_comparison_neg0_0_test);
  tcase_add_test(s21_decimal_h, s21_comparison_0_neg0_test);

  tcase_add_test(s21_decimal_h, s21_truncate_1);
  tcase_add_test(s21_decimal_h, s21_truncate_2);
  tcase_add_test(s21_decimal_h, s21_truncate_3);
  tcase_add_test(s21_decimal_h, s21_truncate_4);
  tcase_add_test(s21_decimal_h, s21_truncate_5);
  tcase_add_test(s21_decimal_h, s21_truncate_6);
  tcase_add_test(s21_decimal_h, s21_truncate_7);
  tcase_add_test(s21_decimal_h, s21_truncate_8);
  tcase_add_test(s21_decimal_h, s21_truncate_9);
  tcase_add_test(s21_decimal_h, s21_truncate_10);

  tcase_add_test(s21_decimal_h, s21_floor_1);
  tcase_add_test(s21_decimal_h, s21_floor_2);
  tcase_add_test(s21_decimal_h, s21_floor_3);
  tcase_add_test(s21_decimal_h, s21_floor_4);
  tcase_add_test(s21_decimal_h, s21_floor_5);
  tcase_add_test(s21_decimal_h, s21_floor_6);
  tcase_add_test(s21_decimal_h, s21_floor_7);
  tcase_add_test(s21_decimal_h, s21_floor_8);
  tcase_add_test(s21_decimal_h, s21_floor_9);
  tcase_add_test(s21_decimal_h, s21_floor_10);

  tcase_add_test(s21_decimal_h, s21_round_1);
  tcase_add_test(s21_decimal_h, s21_round_2);
  tcase_add_test(s21_decimal_h, s21_round_3);
  tcase_add_test(s21_decimal_h, s21_round_4);
  tcase_add_test(s21_decimal_h, s21_round_5);
  tcase_add_test(s21_decimal_h, s21_round_6);
  tcase_add_test(s21_decimal_h, s21_round_7);
  tcase_add_test(s21_decimal_h, s21_round_8);
  tcase_add_test(s21_decimal_h, s21_round_9);
  tcase_add_test(s21_decimal_h, s21_round_10);

  tcase_add_test(s21_decimal_h, s21_negate_1);
  tcase_add_test(s21_decimal_h, s21_negate_2);
  tcase_add_test(s21_decimal_h, s21_negate_3);
  tcase_add_test(s21_decimal_h, s21_negate_4);
  tcase_add_test(s21_decimal_h, s21_negate_5);
  tcase_add_test(s21_decimal_h, s21_negate_6);
  tcase_add_test(s21_decimal_h, s21_negate_7);

  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_1);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_2);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_3);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_4);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_5);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_6);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_7);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_8);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_9);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_int_10);

  tcase_add_test(s21_decimal_h, s21_from_decimal_to_float_1);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_float_2);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_float_3);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_float_4);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_float_5);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_float_6);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_float_7);
  tcase_add_test(s21_decimal_h, s21_from_decimal_to_float_8);

  tcase_add_test(s21_decimal_h, s21_from_int_to_decimal_1);
  tcase_add_test(s21_decimal_h, s21_from_int_to_decimal_2);
  tcase_add_test(s21_decimal_h, s21_from_int_to_decimal_3);
  tcase_add_test(s21_decimal_h, s21_from_int_to_decimal_4);
  tcase_add_test(s21_decimal_h, s21_from_int_to_decimal_5);
  tcase_add_test(s21_decimal_h, s21_from_int_to_decimal_6);

  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_1);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_2);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_3);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_4);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_5);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_6);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_7);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_8);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_9);
  tcase_add_test(s21_decimal_h, s21_from_float_to_decimal_10);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
