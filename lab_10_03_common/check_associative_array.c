#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "associative_array.h"

START_TEST(test_assoc_array_create_destroy_success)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);
    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

START_TEST(test_assoc_array_insert_single)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_insert(arr, "key1", 52);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_insert_multiple)
{
    assoc_array_t arr = assoc_array_create();

    ck_assert_int_eq(assoc_array_insert(arr, "key1", 1), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_insert(arr, "key2", 2), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_insert(arr, "key3", 3), ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_insert_duplicate_key)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "key1", 1);
    assoc_array_error_t err = assoc_array_insert(arr, "key1", 2);
    ck_assert_int_eq(err, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_insert_empty_key)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_insert(arr, "", 10);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_insert_null_key)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_insert(arr, NULL, 10);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_insert_null_array)
{
    assoc_array_error_t err = assoc_array_insert(NULL, "key", 1);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_assoc_array_find_existing_key)
{
    assoc_array_t arr = assoc_array_create();
    int *value;
    int test_value = 1;

    assoc_array_insert(arr, "key", test_value);
    assoc_array_error_t err = assoc_array_find(arr, "key", &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, test_value);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_find_not_existing_key)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_insert(arr, "key1", 10);
    assoc_array_error_t err = assoc_array_find(arr, "key2", &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_find_in_empty_array)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_error_t err = assoc_array_find(arr, "key", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_find_null_parameters)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    ck_assert_int_eq(assoc_array_find(NULL, "key", &value), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_find(arr, NULL, &value), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_find(arr, "key", NULL), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_remove_existing_key)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);

    assoc_array_error_t err = assoc_array_remove(arr, "key1");
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    ck_assert_int_eq(assoc_array_find(arr, "key1", &value), ASSOC_ARRAY_NOT_FOUND);
    ck_assert_int_eq(assoc_array_find(arr, "key2", &value), ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_remove_not_existing_key)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "key1", 10);
    assoc_array_error_t err = assoc_array_remove(arr, "key2");

    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_remove_empty_array)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_remove(arr, "key");
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_remove_all_keys)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);

    ck_assert_int_eq(assoc_array_remove(arr, "key1"), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, "key2"), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, "key3"), ASSOC_ARRAY_OK);

    int *value;
    ck_assert_int_eq(assoc_array_find(arr, "key1", &value), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_remove_null_parameters)
{
    assoc_array_t arr = assoc_array_create();

    ck_assert_int_eq(assoc_array_remove(NULL, "key"), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_remove(arr, NULL), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_clear_not_empty_array)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);

    assoc_array_error_t err = assoc_array_clear(arr);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    ck_assert_int_eq(assoc_array_find(arr, "key1", &value), ASSOC_ARRAY_NOT_FOUND);
    ck_assert_int_eq(assoc_array_find(arr, "key2", &value), ASSOC_ARRAY_NOT_FOUND);
    ck_assert_int_eq(assoc_array_find(arr, "key3", &value), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_clear_empty_array)
{
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_clear(arr);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_min_basic)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_insert(arr, "key3", 3);
    assoc_array_insert(arr, "key1", 1);
    assoc_array_insert(arr, "key2", 2);

    assoc_array_error_t err = assoc_array_min(arr, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_max_basic)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_insert(arr, "key3", 3);
    assoc_array_insert(arr, "key1", 1);
    assoc_array_insert(arr, "key2", 2);

    assoc_array_error_t err = assoc_array_max(arr, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 3);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_min_single_element)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_insert(arr, "key", 1);

    assoc_array_error_t err = assoc_array_min(arr, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_max_single_element)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_insert(arr, "key", 2);

    assoc_array_error_t err = assoc_array_max(arr, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 2);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_min_empty_array)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_error_t err = assoc_array_min(arr, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_max_empty_array)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    assoc_array_error_t err = assoc_array_max(arr, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_min_max_null_parameters)
{
    assoc_array_t arr = assoc_array_create();
    int *value;

    ck_assert_int_eq(assoc_array_min(NULL, &value), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_min(arr, NULL), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_max(NULL, &value), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_max(arr, NULL), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

void sum_values(const char *key, int *num, void *param)
{
    (void)key;
    *(int *)param += *num;
}

START_TEST(test_assoc_array_each_values)
{
    assoc_array_t arr = assoc_array_create();
    int sum = 0;

    assoc_array_insert(arr, "key1", 1);
    assoc_array_insert(arr, "key2", 2);
    assoc_array_insert(arr, "key3", 3);

    assoc_array_error_t err = assoc_array_each(arr, sum_values, &sum);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(sum, 6);

    assoc_array_destroy(&arr);
}
END_TEST

void max_key(const char *key, int *num, void *param)
{
    (void)num;

    if (strcmp(key, (char *)param) > 0)
        strncpy((char *)param, key, 99);
}

START_TEST(test_assoc_array_each_keys)
{
    assoc_array_t arr = assoc_array_create();
    char buffer[100] = {0};

    assoc_array_insert(arr, "key1", 1);
    assoc_array_insert(arr, "key2", 2);
    assoc_array_insert(arr, "key3", 3);

    assoc_array_error_t err = assoc_array_each(arr, max_key, &buffer);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    ck_assert_str_eq(buffer, "key3");

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_each_empty_array)
{
    assoc_array_t arr = assoc_array_create();
    int counter = 0;

    assoc_array_error_t err = assoc_array_each(arr, sum_values, &counter);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(counter, 0);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_each_null_parameters)
{
    assoc_array_t arr = assoc_array_create();

    ck_assert_int_eq(assoc_array_each(NULL, NULL, NULL), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_each(arr, NULL, NULL), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc array");

    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_assoc_array_create_destroy_success);
    tcase_add_test(tc_pos, test_assoc_array_clear_not_empty_array);
    tcase_add_test(tc_pos, test_assoc_array_clear_empty_array);
    tcase_add_test(tc_pos, test_assoc_array_insert_single);
    tcase_add_test(tc_pos, test_assoc_array_insert_multiple);
    tcase_add_test(tc_pos, test_assoc_array_find_existing_key);
    tcase_add_test(tc_pos, test_assoc_array_remove_existing_key);
    tcase_add_test(tc_pos, test_assoc_array_remove_all_keys);
    tcase_add_test(tc_pos, test_assoc_array_min_basic);
    tcase_add_test(tc_pos, test_assoc_array_max_basic);
    tcase_add_test(tc_pos, test_assoc_array_min_single_element);
    tcase_add_test(tc_pos, test_assoc_array_max_single_element);
    tcase_add_test(tc_pos, test_assoc_array_each_values);
    tcase_add_test(tc_pos, test_assoc_array_each_keys);
    tcase_add_test(tc_pos, test_assoc_array_each_empty_array);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_assoc_array_insert_empty_key);
    tcase_add_test(tc_neg, test_assoc_array_insert_null_key);
    tcase_add_test(tc_neg, test_assoc_array_insert_duplicate_key);
    tcase_add_test(tc_neg, test_assoc_array_insert_null_array);
    tcase_add_test(tc_neg, test_assoc_array_find_not_existing_key);
    tcase_add_test(tc_neg, test_assoc_array_find_in_empty_array);
    tcase_add_test(tc_neg, test_assoc_array_remove_not_existing_key);
    tcase_add_test(tc_neg, test_assoc_array_remove_empty_array);
    tcase_add_test(tc_neg, test_assoc_array_min_empty_array);
    tcase_add_test(tc_neg, test_assoc_array_max_empty_array);
    tcase_add_test(tc_neg, test_assoc_array_find_null_parameters);
    tcase_add_test(tc_neg, test_assoc_array_remove_null_parameters);
    tcase_add_test(tc_neg, test_assoc_array_each_null_parameters);
    tcase_add_test(tc_neg, test_assoc_array_min_max_null_parameters);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);
    return s;
}
