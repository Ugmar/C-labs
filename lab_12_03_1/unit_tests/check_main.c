#include <check.h>
#include <stdlib.h>

#include "check_arr.h"
#include "check_utils.h"

int main(void)
{
    int failed = 0;
    SRunner *runner;

    Suite *s_creat_arr = create_arr_suite();
    runner = srunner_create(s_creat_arr);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *s_key = key_suite();
    runner = srunner_create(s_key);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *s_fprint_arr = fprint_arr_suite();
    runner = srunner_create(s_fprint_arr);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *s_count_all_elems = count_all_elems_suite();
    runner = srunner_create(s_count_all_elems);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *s_count_filter_elems = count_filter_elems_suite();
    runner = srunner_create(s_count_filter_elems);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *s_mysort = mysort_suite();
    runner = srunner_create(s_mysort);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *s_fill_arr = fill_arr_suite();
    runner = srunner_create(s_fill_arr);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
