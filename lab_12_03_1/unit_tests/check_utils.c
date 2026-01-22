#include <stdlib.h>
#include <dlfcn.h>

#include "check_utils.h"
#include "errors.h"
#include "sort.h"
#include "io.h"
#include "filter.h"

START_TEST(test_count_all_elems_empty_file)
{
    int rc;
    size_t len = 0;

    rc = count_all_elems(NULL, &len);

    ck_assert_int_eq(rc, ERROR_IO_FILE);
}
END_TEST

START_TEST(test_count_all_elems_empty_len)
{
    int rc;
    FILE *f = tmpfile();

    rc = count_all_elems(f, NULL);

    ck_assert_int_eq(rc, ERROR_EMPTY_POINT_LEN);
    fclose(f);
}
END_TEST

START_TEST(test_count_all_elems_str_in_file)
{
    int rc;
    FILE *f = tmpfile();
    size_t len = 0;

    fprintf(f, "1 2 dfgd 3");
    rewind(f);

    rc = count_all_elems(f, &len);

    ck_assert_int_eq(rc, ERROR_INVALID_DIGIT);
    fclose(f);
}
END_TEST

START_TEST(test_count_all_elems_correct)
{
    int rc;
    FILE *f = tmpfile();
    size_t len = 0;

    fprintf(f, "1 2 4 3");
    rewind(f);

    rc = count_all_elems(f, &len);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(len, 4);
    fclose(f);
}
END_TEST

Suite *count_all_elems_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("count_all_elems");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_count_all_elems_empty_file);
    tcase_add_test(tc_neg, test_count_all_elems_empty_len);
    tcase_add_test(tc_neg, test_count_all_elems_str_in_file);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_count_all_elems_correct);

    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(test_count_filter_elems_null_point)
{
    int rc;
    size_t len = 0;

    rc = count_filter_elems(NULL, NULL, &len);

    ck_assert_int_eq(rc, ERROR_EMPTY_POINT_ARR);
}
END_TEST

START_TEST(test_count_filter_elems_len_null)
{
    int rc;
    size_t len = 3;
    int start[] = {1, 2, 3};

    rc = count_filter_elems(start, start + len, NULL);

    ck_assert_int_eq(rc, ERROR_EMPTY_POINT_LEN);
}
END_TEST

START_TEST(test_count_filter_elems_invalid_point)
{
    int rc;
    size_t len = 3;
    int start[] = {1, 2, 3};

    rc = count_filter_elems(start + len, start, &len);

    ck_assert_int_eq(rc, ERROR_INVALID_POINT);
}
END_TEST

START_TEST(test_count_filter_elems_eq_point)
{
    int rc;
    size_t len = 3;
    int start[] = {1, 2, 3};

    rc = count_filter_elems(start, start, &len);

    ck_assert_int_eq(rc, ERROR_EMPTY_ARR);
}
END_TEST

START_TEST(test_count_filter_elems_correct)
{
    int rc;
    size_t len = 6;
    int start[] = {1, 2, 3, -4, -5, 10};

    rc = count_filter_elems(start, start + len, &len);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(len, 4);
}
END_TEST

Suite *count_filter_elems_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("count_filter_elems");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_count_filter_elems_null_point);
    tcase_add_test(tc_neg, test_count_filter_elems_len_null);
    tcase_add_test(tc_neg, test_count_filter_elems_invalid_point);
    tcase_add_test(tc_neg, test_count_filter_elems_eq_point);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_count_filter_elems_correct);

    suite_add_tcase(s, tc_pos);

    return s;
}

int compare_int(const void *first, const void *second)
{
    return *(int *)first - *(int *)second;
}

START_TEST(test_mysort_one_el)
{
    void *hlib = dlopen("./out/libsort.so", RTLD_NOW);
    void (*mysort)(void *, size_t, size_t, compare_t) = dlsym(hlib, "mysort");

    int start[] = {1};

    mysort(start, 1, sizeof(int), compare_int);

    dlclose(hlib);
    ck_assert_int_eq(start[0], 1);
}
END_TEST

START_TEST(test_mysort_sort_el)
{
    void *hlib = dlopen("./out/libsort.so", RTLD_NOW);
    void (*mysort)(void *, size_t, size_t, compare_t) = dlsym(hlib, "mysort");

    int res[] = {1, 2, 3, 4, 5};
    int start[] = {1, 2, 3, 4, 5};

    mysort(start, 5, sizeof(int), compare_int);
    dlclose(hlib);

    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(start[i], res[i]);
    
}
END_TEST

START_TEST(test_mysort_reverse_el)
{
    void *hlib = dlopen("./out/libsort.so", RTLD_NOW);
    void (*mysort)(void *, size_t, size_t, compare_t) = dlsym(hlib, "mysort");

    int res[] = {1, 2, 3, 4, 5};
    int start[] = {5, 4, 3, 2, 1};

    mysort(start, 5, sizeof(int), compare_int);

    dlclose(hlib);
    for (size_t i = 0; i < 5; i++)
    {
        ck_assert_int_eq(start[i], res[i]);
    }
}
END_TEST

START_TEST(test_mysort_random_el)
{
    void *hlib = dlopen("./out/libsort.so", RTLD_NOW);
    void (*mysort)(void *, size_t, size_t, compare_t) = dlsym(hlib, "mysort");

    int res[] = {1, 2, 3, 4, 5};
    int start[] = {5, 2, 1, 3, 4};

    mysort(start, 5, sizeof(int), compare_int);
    dlclose(hlib);
    
    for (size_t i = 0; i < 5; i++)
    {
        ck_assert_int_eq(start[i], res[i]);
    }
}
END_TEST

Suite *mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("mysort");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_mysort_random_el);
    tcase_add_test(tc_pos, test_mysort_reverse_el);
    tcase_add_test(tc_pos, test_mysort_sort_el);
    tcase_add_test(tc_pos, test_mysort_one_el);

    suite_add_tcase(s, tc_pos);

    return s;
}
