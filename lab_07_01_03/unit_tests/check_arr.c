#include <stdlib.h>

#include "check_arr.h"
#include "arr.h"
#include "errors.h"

START_TEST(test_create_arr_invalid_ptr_file)
{
    int *arr = NULL, *end_arr = NULL;
    int rc;

    rc = create_arr(NULL, &arr, &end_arr);

    ck_assert_int_eq(rc, ERROR_IO_FILE);
}
END_TEST

START_TEST(test_create_arr_empty_file)
{
    int *arr = NULL, *end_arr = NULL;
    int rc;

    FILE *f = tmpfile();

    rc = create_arr(f, &arr, &end_arr);

    fclose(f);

    ck_assert_int_eq(rc, ERRPR_EMPTY_FILE);
}
END_TEST

START_TEST(test_create_arr_str_in_file)
{
    int *arr = NULL, *end_arr = NULL;
    int rc;

    FILE *f = tmpfile();
    fprintf(f, "1 2 3 dsfg 3 4");
    rewind(f);

    rc = create_arr(f, &arr, &end_arr);

    fclose(f);

    ck_assert_int_eq(rc, ERROR_INVALID_DIGIT);
}
END_TEST

START_TEST(test_create_usual_arr)
{
    int *arr = NULL, *end_arr = NULL;
    int arr_res[7] = {4, 3, 2, 5, -1, 0, 3};
    int rc;

    FILE *f = tmpfile();
    fprintf(f, "4 3 2 5 -1 0 3");
    rewind(f);

    rc = create_arr(f, &arr, &end_arr);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < 7; i++)
        ck_assert_int_eq(arr[i], arr_res[i]);

    fclose(f);
    free(arr);
}
END_TEST

START_TEST(test_create_arr_len_one)
{
    int *arr = NULL, *end_arr = NULL;
    int arr_res[1] = {12};
    int rc;

    FILE *f = tmpfile();
    fprintf(f, "12");
    rewind(f);

    rc = create_arr(f, &arr, &end_arr);

    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(arr[0], arr_res[0]);

    fclose(f);
    free(arr);
}
END_TEST

Suite *create_arr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("create_arr");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_create_arr_invalid_ptr_file);
    tcase_add_test(tc_neg, test_create_arr_empty_file);
    tcase_add_test(tc_neg, test_create_arr_str_in_file);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_create_arr_len_one);
    tcase_add_test(tc_pos, test_create_usual_arr);

    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(test_key_null_point)
{
    int *start_filter_arr = NULL, *end_filter_arr = NULL;
    int rc;

    rc = key(NULL, NULL, &start_filter_arr, &end_filter_arr);

    ck_assert_int_eq(rc, ERROR_EMPTY_POINT_ARR);
}
END_TEST

START_TEST(test_key_eq_point)
{
    int start_arr[] = {1, 2, 3}, *start_filter_arr = NULL, *end_filter_arr = NULL;
    int rc;

    rc = key(start_arr, start_arr, &start_filter_arr, &end_filter_arr);

    ck_assert_int_eq(rc, ERROR_EMPTY_ARR);
}
END_TEST

START_TEST(test_key_gt_point)
{
    int start_arr[] = {1, 2}, *start_filter_arr = NULL, *end_filter_arr = NULL;
    int rc;

    rc = key(start_arr + 3, start_arr, &start_filter_arr, &end_filter_arr);

    ck_assert_int_eq(rc, ERROR_INVALID_POINT);
}
END_TEST

START_TEST(test_key_last_neg_el)
{
    int *start_filter_arr = NULL, *end_filter_arr = NULL;
    int arr_res[] = {1, 2, 3};
    int rc;

    int start_arr[] = {1, 2, 3, -5};

    rc = key(start_arr, start_arr + 4, &start_filter_arr, &end_filter_arr);

    for (size_t i = 0; i < sizeof(arr_res) / sizeof(arr_res[0]); i++)
    {
        ck_assert_int_eq(arr_res[i], start_filter_arr[i]);
    }

    free(start_filter_arr);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_key_no_neg_el)
{
    int *start_filter_arr = NULL, *end_filter_arr = NULL;
    int rc;
    int arr_res[] = {1, 2, 3, 4};

    int start_arr[] = {1, 2, 3, 4};

    rc = key(start_arr, start_arr + 4, &start_filter_arr, &end_filter_arr);

    for (size_t i = 0; i < sizeof(arr_res) / sizeof(arr_res[0]); i++)
    {
        ck_assert_int_eq(arr_res[i], start_filter_arr[i]);
    }

    free(start_filter_arr);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_key_neg_in_ceneter_el)
{
    int *start_filter_arr = NULL, *end_filter_arr = NULL;
    int rc;
    int arr_res[] = {1, 2};

    int start_arr[] = {1, 2, -1, 3, 4};

    rc = key(start_arr, start_arr + 5, &start_filter_arr, &end_filter_arr);

    for (size_t i = 0; i < sizeof(arr_res) / sizeof(arr_res[0]); i++)
    {
        ck_assert_int_eq(arr_res[i], start_filter_arr[i]);
    }

    free(start_filter_arr);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_key_firtst_neg_el)
{
    int *start_filter_arr = NULL, *end_filter_arr = NULL;
    int rc;

    int start_arr[] = {-1, 2, 1, 3, 4};

    rc = key(start_arr, start_arr + 5, &start_filter_arr, &end_filter_arr);

    free(start_filter_arr);

    ck_assert_int_eq(rc, ERROR_EMPTY_ARR);
}
END_TEST

START_TEST(test_key_two_neg_el)
{
    int *start_filter_arr = NULL, *end_filter_arr = NULL;
    int rc;

    int arr_res[] = {-1, 2, 1};
    int start_arr[] = {-1, 2, 1, -3, 4};

    rc = key(start_arr, start_arr + 5, &start_filter_arr, &end_filter_arr);

    for (size_t i = 0; i < sizeof(arr_res) / sizeof(arr_res[0]); i++)
    {
        ck_assert_int_eq(arr_res[i], start_filter_arr[i]);
    }

    free(start_filter_arr);

    ck_assert_int_eq(rc, OK);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("key");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_key_null_point);
    tcase_add_test(tc_neg, test_key_eq_point);
    tcase_add_test(tc_neg, test_key_gt_point);
    tcase_add_test(tc_neg, test_key_firtst_neg_el);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_key_last_neg_el);
    tcase_add_test(tc_pos, test_key_no_neg_el);
    tcase_add_test(tc_pos, test_key_neg_in_ceneter_el);
    tcase_add_test(tc_pos, test_key_two_neg_el);

    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(test_fprint_arr_empty_point_file)
{
    int *start_arr = NULL, *end_arr = NULL;
    int rc;

    FILE *f = tmpfile();

    rc = fprint_arr(NULL, start_arr, end_arr);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_IO_FILE);
}
END_TEST

START_TEST(test_fprint_arr_eq_point)
{
    int start_arr[] = {1, 2, 3, 4};
    int rc;

    FILE *f = tmpfile();

    rc = fprint_arr(f, start_arr, start_arr);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_EMPTY_ARR);
}
END_TEST

START_TEST(test_fprint_arr_empty_point_arr)
{
    int rc;

    FILE *f = tmpfile();

    rc = fprint_arr(f, NULL, NULL);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_EMPTY_POINT_ARR);
}
END_TEST

START_TEST(test_fprint_arr_gt_point)
{
    int rc;
    int arr[] = {1, 2, 3, 4};

    FILE *f = tmpfile();

    rc = fprint_arr(f, arr + 1, arr);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_INVALID_POINT);
}
END_TEST

START_TEST(test_fprint_arr_usual_arr)
{
    int rc;
    int arr[] = {1, 2, 3, 4};

    FILE *f = tmpfile();

    rc = fprint_arr(f, arr, arr + 4);

    rewind(f);
    int a, b, c, d;

    fscanf(f, "%d%d%d%d", &a, &b, &c, &d);

    ck_assert_int_eq(a, arr[0]);
    ck_assert_int_eq(b, arr[1]);
    ck_assert_int_eq(c, arr[2]);
    ck_assert_int_eq(d, arr[3]);

    ck_assert_int_eq(rc, OK);
    fclose(f);
}
END_TEST

Suite *fprint_arr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("fprint_arr");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_fprint_arr_gt_point);
    tcase_add_test(tc_neg, test_fprint_arr_empty_point_arr);
    tcase_add_test(tc_neg, test_fprint_arr_eq_point);
    tcase_add_test(tc_neg, test_fprint_arr_empty_point_file);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_fprint_arr_usual_arr);

    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(test_fill_arr_null_file)
{
    int rc;
    int *start_arr = NULL, *end_arr = NULL;

    rc = fill_arr(NULL, &start_arr, &end_arr);

    ck_assert_int_eq(rc, ERROR_IO_FILE);
}
END_TEST

START_TEST(test_fill_arr_null_arr)
{
    int rc;

    FILE *f = tmpfile();

    rc = fill_arr(f, NULL, NULL);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_EMPTY_POINT_ARR);
}
END_TEST

START_TEST(test_fill_arr_empty_arr)
{
    int rc;
    int *arr = malloc(sizeof(int));
    FILE *f = tmpfile();

    rc = fill_arr(f, &arr, &arr);
    fclose(f);
    free(arr);

    ck_assert_int_eq(rc, ERROR_EMPTY_ARR);
}
END_TEST

START_TEST(test_fill_arr_invalid_point)
{
    int rc;
    int *arr = malloc(sizeof(int));
    int *end = arr + 1;

    FILE *f = tmpfile();

    rc = fill_arr(f, &end, &arr);
    fclose(f);
    free(arr);

    ck_assert_int_eq(rc, ERROR_INVALID_POINT);
}
END_TEST

START_TEST(test_fill_arr_str_in_file)
{
    int rc;
    int *arr = malloc(sizeof(int) * 3);
    int *end = arr + 3;

    FILE *f = tmpfile();
    fprintf(f, "12 13 sfd 2");
    rewind(f);

    rc = fill_arr(f, &arr,&end);

    ck_assert_int_eq(rc, ERROR_READ_FILE);
    free(arr);
    fclose(f);
}
END_TEST

START_TEST(test_fill_arr_correct)
{
    int rc;
    int *arr = malloc(sizeof(int) * 3);
    int *end = arr + 3;

    FILE *f = tmpfile();
    fprintf(f, "12 13 2");
    rewind(f);

    rc = fill_arr(f, &arr, &end);

    ck_assert_int_eq(rc, OK);
    free(arr);
    fclose(f);
}
END_TEST

Suite *fill_arr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("fill_arr");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_fill_arr_null_file);
    tcase_add_test(tc_neg, test_fill_arr_null_arr);
    tcase_add_test(tc_neg, test_fill_arr_empty_arr);
    tcase_add_test(tc_neg, test_fill_arr_invalid_point);
    tcase_add_test(tc_neg, test_fill_arr_str_in_file);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_fill_arr_correct);

    suite_add_tcase(s, tc_pos);

    return s;
}
