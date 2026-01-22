#include <stdlib.h>

#include "check_arr.h"
#include "arr_lib.h"

START_TEST(test_is_prime_neg)
{
    int rc = is_prime(-1);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_is_prime_zero)
{
    int rc = is_prime(0);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_is_prime_one)
{
    int rc = is_prime(1);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_is_prime_even)
{
    int rc = is_prime(4);
    
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_is_prime_ok)
{
    int rc = is_prime(19);
    
    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(test_fill_null)
{
    int rc = fill_arr_primary(NULL, 5, 5);
    
    ck_assert_int_eq(rc, ERROR_INVALID_ARR);
}
END_TEST

START_TEST(test_fill_invalid_size)
{
    int n = 5;
    int arr[n];

    int rc = fill_arr_primary(arr, n, n + 1);
    
    ck_assert_int_eq(rc, ERROR_ARR_SIZE);
}
END_TEST

START_TEST(test_fill_ok)
{
    int n = 5;
    int arr[n];
    int res[] = {2, 3, 5, 7, 11};

    int rc = fill_arr_primary(arr, n, n);
    
    ck_assert_int_eq(rc, OK);

    for (int i = 0; i < n; i++)
        ck_assert_int_eq(res[i], arr[i]);

}
END_TEST

START_TEST(test_add_number_after_even_ok)
{
    int src[] = {1, 2, 3, 4, 5};
    int dst[10];
    int res[] = {1, 2, 0, 3, 4, 0, 5};
    int digit = 0;
    
    int rc = add_number_after_even(src, 5, dst, 10, digit);

    ck_assert_int_eq(rc, 7);
    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(res[i], dst[i]);
}
END_TEST

START_TEST(test_add_number_after_even_no_even)
{
    int src[] = {1, 3, 5, 7};
    int dst[10];
    int digit = 0;
    
    int rc = add_number_after_even(src, 4, dst, 10, digit);
    
    ck_assert_int_eq(rc, 4);
    for (int i = 0; i < 4; i++)
        ck_assert_int_eq(dst[i], src[i]);
}
END_TEST

START_TEST(test_add_number_after_even_all_even)
{
    int src[] = {2, 4, 6, 8};
    int res[] = {2, 0, 4, 0, 6, 0, 8, 0};
    int dst[10];
    int digit = 0;
    
    int rc = add_number_after_even(src, 4, dst, 10, digit);
    
    ck_assert_int_eq(rc, 8);
    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(dst[i], res[i]);
}
END_TEST

START_TEST(test_add_number_after_even_negative_even)
{
    int src[] = {1, -2, 3, -4};
    int dst[10];
    int digit = 0;
    int res[] = {1, -2, 0, 3, -4, 0};
    
    int rc = add_number_after_even(src, 4, dst, 10, digit);
    
    ck_assert_int_eq(rc, 6);
    for (int i = 0; i < rc; i++)
        ck_assert_int_eq(dst[i], res[i]);
}
END_TEST

START_TEST(test_add_number_after_even_null_dst)
{
    int src[] = {1, 2, 3, 4};
    int digit = 0;
    
    int rc = add_number_after_even(src, 4, NULL, 0, digit);
    ck_assert_int_eq(rc, 6);
}
END_TEST

START_TEST(test_add_number_after_even_null_src)
{
    int dst[10];
    int digit = 0;
    
    int rc = add_number_after_even(NULL, 5, dst, 10, digit);
    ck_assert_int_eq(rc, ERROR_INVALID_ARR);
}
END_TEST

START_TEST(test_add_number_after_even_invalid_size)
{
    int src[] = {1, 2, 3, 4};
    int dst[3];
    int digit = 0;
    
    int rc = add_number_after_even(src, 4, dst, 3, digit);
    ck_assert_int_eq(rc, ERROR_ARR_SIZE);
}
END_TEST

Suite *arr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("arr");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_is_prime_neg);
    tcase_add_test(tc_neg, test_is_prime_zero);
    tcase_add_test(tc_neg, test_is_prime_even);
    tcase_add_test(tc_neg, test_is_prime_one);
    tcase_add_test(tc_neg, test_fill_null);
    tcase_add_test(tc_neg, test_fill_invalid_size);
    tcase_add_test(tc_neg, test_add_number_after_even_invalid_size);
    tcase_add_test(tc_neg, test_add_number_after_even_ok);
    tcase_add_test(tc_neg, test_add_number_after_even_no_even);
    tcase_add_test(tc_neg, test_add_number_after_even_all_even);
    tcase_add_test(tc_neg, test_add_number_after_even_negative_even);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_is_prime_ok);
    tcase_add_test(tc_pos, test_fill_ok);
    tcase_add_test(tc_pos, test_add_number_after_even_null_dst);
    tcase_add_test(tc_pos, test_add_number_after_even_null_src);

    suite_add_tcase(s, tc_pos);

    return s;
}
