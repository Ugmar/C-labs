#include <stdlib.h>

#include "check_product.h"
#include "product.h"

START_TEST(test_input_product_NULL_pointer)
{
    int rc;
    int c = 10;

    rc = read_product(NULL, NULL, &c);

    ck_assert_int_eq(rc, ERROR_INVALID_POINTER);
}
END_TEST

START_TEST(test_input_product_empty_line)
{
    int rc;
    FILE *f = tmpfile();
    struct product arr[10];
    int c = 1;

    rc = read_product(f, arr, &c);
    free(arr[0].name);

    ck_assert_int_eq(rc, ERROR_EMPTY_PRODUCT);
}
END_TEST

START_TEST(test_input_product_str_price)
{
    int rc;
    FILE *f = tmpfile();
    fprintf(f, "%s\n%s\n", "adsf", "asdfsd");
    rewind(f);
    int c = 1;

    struct product arr[10];

    rc = read_product(f, arr, &c);
    free(arr[0].name);

    ck_assert_int_eq(rc, ERROR_INVALID_PRICE);
}
END_TEST

START_TEST(test_input_product_negative_arr)
{
    int rc;
    FILE *f = tmpfile();
    fprintf(f, "%s\n%d\n", "adsf", -10);
    rewind(f);
    int c = 1;

    struct product arr[10];

    rc = read_product(f, arr, &c);
    free(arr[0].name);

    ck_assert_int_eq(rc, ERROR_NEGATIVE_PRICE);
}
END_TEST

START_TEST(test_input_product_diff_count)
{
    int rc;
    FILE *f = tmpfile();
    fprintf(f, "%s\n%d\n", "adsf", 10);
    fprintf(f, "%s\n%d\n", "adsf", 20);
    fprintf(f, "%s\n%d\n", "adsf", 30);
    rewind(f);
    int c = 2;

    struct product arr[10];

    rc = read_product(f, arr, &c);
    for (int i = 0; i < c; i++)
    {
        free(arr[i].name);
    }

    ck_assert_int_eq(rc, ERROR_INVALID_COUNT);
}
END_TEST

START_TEST(test_input_one_elemet)
{
    int rc;
    FILE *f = tmpfile();
    fprintf(f, "%s\n%d\n", "adsf", 10);
    rewind(f);
    int c = 1;

    struct product arr[10];

    rc = read_product(f, arr, &c);
    free(arr[0].name);

    ck_assert_int_eq(rc, OK);
}

START_TEST(test_input_some_elemet)
{
    int rc;
    FILE *f = tmpfile();
    fprintf(f, "%s\n%d\n", "adsf", 10);
    fprintf(f, "%s\n%d\n", "adsf", 10);
    fprintf(f, "%s\n%d\n", "adsf", 10);
    fprintf(f, "%s\n%d\n", "adsf", 10);
    fprintf(f, "%s\n%d\n", "adsf", 10);
    rewind(f);
    int c = 5;

    struct product *arr = malloc(sizeof(struct product) * c);

    rc = read_product(f, arr, &c);

    free_products(arr, c);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_read_count_product)
{
    FILE *f = tmpfile();
    fprintf(f, "%d\n", 5);
    rewind(f);

    int c = read_count_product(f);

    ck_assert_int_eq(c, 5);
}
END_TEST

START_TEST(test_read_count_product_string)
{
    FILE *f = tmpfile();
    fprintf(f, "%s\n", "asd");
    rewind(f);

    int c = read_count_product(f);

    ck_assert_int_eq(c, ERROR_COUNT_PRODUCT);
}
END_TEST

Suite *input_product_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("input_matrix");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_input_product_NULL_pointer);
    tcase_add_test(tc_neg, test_input_product_empty_line);
    tcase_add_test(tc_neg, test_input_product_str_price);
    tcase_add_test(tc_neg, test_input_product_negative_arr);
    tcase_add_test(tc_neg, test_input_product_diff_count);
    tcase_add_test(tc_neg, test_read_count_product_string);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_input_one_elemet);
    tcase_add_test(tc_pos, test_input_some_elemet);
    tcase_add_test(tc_pos, test_read_count_product);
  
    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(test_print_products_less_price)
{
    FILE *f_expect = tmpfile();
    fprintf(f_expect, "%s\n%d\n", "p1", 5);
    fprintf(f_expect, "%s\n%d\n", "p2", 6);
    rewind(f_expect);

    FILE *f_out = tmpfile();

    struct product arr[3];
    char name1[] = "p1";
    char name2[] = "p2";
    char name3[] = "p3";

    struct product p1 = { name1, 2, 5 };
    struct product p2 = { name2, 2, 6 };
    struct product p3 = { name3, 2, 12 };

    arr[0] = p1;
    arr[1] = p2;
    arr[2] = p3;

    print_products_less_price(arr, 3, 10, f_out);
    rewind(f_out);

    char expect[120];
    char out[120];

    fgets(expect, sizeof(expect), f_expect);
    fgets(out, sizeof(out), f_out);

    ck_assert_str_eq(out, expect);

    fgets(expect, sizeof(expect), f_expect);
    fgets(out, sizeof(out), f_out);

    ck_assert_str_eq(out, expect);

    fgets(expect, sizeof(expect), f_expect);
    fgets(out, sizeof(out), f_out);

    ck_assert_str_eq(out, expect);

    fgets(expect, sizeof(expect), f_expect);
    fgets(out, sizeof(out), f_out);

    ck_assert_str_eq(out, expect);

    fgets(expect, sizeof(expect), f_expect);
    fgets(out, sizeof(out), f_out);

    ck_assert_int_eq(feof(f_out), 1);
    ck_assert_int_eq(feof(f_expect), 1);
}
END_TEST

START_TEST(test_print_none_products_less_price)
{
    FILE *f_expect = tmpfile();
    FILE *f_out = tmpfile();

    struct product arr[3];
    struct product p1 = { "p1", 2, 13 };
    struct product p2 = { "p2", 2, 10 };
    struct product p3 = { "p3", 2, 12 };
    arr[0] = p1;
    arr[1] = p2;
    arr[2] = p3;

    print_products_less_price(arr, 3, 10, f_out);

    char expect[120];
    char out[120];

    fgets(expect, sizeof(expect), f_expect);
    fgets(out, sizeof(out), f_out);

    ck_assert_int_eq(feof(f_expect), 1);
    ck_assert_int_eq(feof(f_out), 1);
}
END_TEST


Suite *utils_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("utils");

    tc_pos = tcase_create("positive");

    tcase_add_test(tc_pos, test_print_products_less_price);
    tcase_add_test(tc_pos, test_print_none_products_less_price);
  
    suite_add_tcase(s, tc_pos);

    return s;
}
