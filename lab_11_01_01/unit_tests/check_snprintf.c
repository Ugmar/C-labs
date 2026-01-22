#include <stdarg.h>
#include <check.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "my_snprintf.h"

START_TEST(test_char)
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "char: %c", 'a');
    int rc2 = snprintf(buf2, sizeof(buf2), "char: %c", 'a');
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_string)
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "string: %s", "qwerty");
    int rc2 = snprintf(buf2, sizeof(buf2), "string: %s", "qwerty");
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_digit_pos)
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "digit: %d", 12345);
    int rc2 = snprintf(buf2, sizeof(buf2), "digit: %d", 12345);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_digit_neg)
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "digit: %d", -12345);
    int rc2 = snprintf(buf2, sizeof(buf2), "digit: %d", -12345);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_int_pos)
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "int: %i", 67890);
    int rc2 = snprintf(buf2, sizeof(buf2), "int: %i", 67890);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_int_neg)
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "int: %i", -67890);
    int rc2 = snprintf(buf2, sizeof(buf2), "int: %i", -67890);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_hex) 
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "hex: %x", 0xABCD);
    int rc2 = snprintf(buf2, sizeof(buf2), "hex: %x", 0xABCD);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_oct)
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "oct: %o", 0777);
    int rc2 = snprintf(buf2, sizeof(buf2), "oct: %o", 0777);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_ld)
{
    char buf1[100];
    char buf2[100];
    
    long digit = 1234567890L;
    int rc1 = my_snprintf(buf1, sizeof(buf1), "long: %ld", digit);
    int rc2 = snprintf(buf2, sizeof(buf2), "long: %ld", digit);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_hd)
{
    char buf1[100];
    char buf2[100];
    
    short digit = 123;
    int rc1 = my_snprintf(buf1, sizeof(buf1), "short: %hd", digit);
    int rc2 = snprintf(buf2, sizeof(buf2), "short: %hd", digit);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_long_hex)
{
    char buf1[100];
    char buf2[100];
    
    unsigned long digit = 0xABCDEFAB;
    int rc1 = my_snprintf(buf1, sizeof(buf1), "long hex: %lx", digit);
    int rc2 = snprintf(buf2, sizeof(buf2), "long hex: %lx", digit);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_short_hex)
{
    char buf1[100];
    char buf2[100];
    
    unsigned short digit = 0xFF;
    int rc1 = my_snprintf(buf1, sizeof(buf1), "short hex: %hx", digit);
    int rc2 = snprintf(buf2, sizeof(buf2), "short hex: %hx", digit);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_long_oct)
{
    char buf1[100];
    char buf2[100];
    
    unsigned long digit = 01234567;
    int rc1 = my_snprintf(buf1, sizeof(buf1), "long oct: %lo", digit);
    int rc2 = snprintf(buf2, sizeof(buf2), "long oct: %lo", digit);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_short_oct)
{
    char buf1[100];
    char buf2[100];
    
    unsigned short digit = 0777;
    int rc1 = my_snprintf(buf1, sizeof(buf1), "short oct: %ho", digit);
    int rc2 = snprintf(buf2, sizeof(buf2), "short oct: %ho", digit);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_zero)
{
    char buf1[100];
    char buf2[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), "%d %x %o", 0, 0, 0);
    int rc2 = snprintf(buf2, sizeof(buf2), "%d %x %o", 0, 0, 0);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_many_specifiers)
{
    char buf1[200];
    char buf2[200];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), 
                              "Many: %c, %s, %d, %i, %x, %o, %ld, %hd",
                              'a', "hello", 123, -456, 0xABC, 0777, 
                              1234567890L, (short)123);
    int rc2 = snprintf(buf2, sizeof(buf2), 
                           "Many: %c, %s, %d, %i, %x, %o, %ld, %hd",
                           'a', "hello", 123, -456, 0xABC, 0777, 
                           1234567890L, (short)123);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_zero_buffer_size)
{
    char buf1[1];
    char buf2[1];
    
    int rc1 = my_snprintf(buf1, 0, 
                              "%s %d", "qwerty", 12345);
    int rc2 = snprintf(buf2, 0, 
                           "%s %d", "qwerty", 12345);
    
    ck_assert_int_eq(rc1, rc2);
}
END_TEST

START_TEST(test_null_string)
{
    char buf1[100];
    char buf2[100];
    
    const char *null_str = NULL;
    int rc1 = my_snprintf(buf1, sizeof(buf1), "%s", null_str);
    int rc2 = snprintf(buf2, sizeof(buf2), "%s", null_str);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_max_int)
{
    char buf1[100];
    char buf2[100];
    
    int max_int = INT_MAX;
    int min_int = INT_MIN;
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), 
                              "%d %d", 
                              max_int, min_int);
    int rc2 = snprintf(buf2, sizeof(buf2), 
                           "%d %d", 
                           max_int, min_int);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_null_format)
{
    char buf1[100];
    
    int rc1 = my_snprintf(buf1, sizeof(buf1), 
                              NULL,
                              0xFFFFFFFF);
    
    ck_assert_int_eq(rc1, -1);
}
END_TEST

START_TEST(test_null_print_base)
{
    int len = 5;
    
    print_signed_base(NULL, &len, 5, 10, 10);
    print_unsigned_base(NULL, &len, 5, 10, 10);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_print;

    s = suite_create("my_snprintf");
    tc_print = tcase_create("print");

    tcase_add_test(tc_print, test_char);
    tcase_add_test(tc_print, test_string);
    tcase_add_test(tc_print, test_digit_pos);
    tcase_add_test(tc_print, test_digit_neg);
    tcase_add_test(tc_print, test_int_pos);
    tcase_add_test(tc_print, test_int_neg);
    tcase_add_test(tc_print, test_oct);
    tcase_add_test(tc_print, test_ld);
    tcase_add_test(tc_print, test_hd);
    tcase_add_test(tc_print, test_long_hex);
    tcase_add_test(tc_print, test_short_hex);
    tcase_add_test(tc_print, test_long_oct);
    tcase_add_test(tc_print, test_short_oct);
    tcase_add_test(tc_print, test_zero);
    tcase_add_test(tc_print, test_many_specifiers);
    tcase_add_test(tc_print, test_zero_buffer_size);
    tcase_add_test(tc_print, test_null_string);
    tcase_add_test(tc_print, test_max_int);
    tcase_add_test(tc_print, test_null_format);
    tcase_add_test(tc_print, test_hex);
    tcase_add_test(tc_print, test_null_print_base);

    suite_add_tcase(s, tc_print);

    return s;
}
