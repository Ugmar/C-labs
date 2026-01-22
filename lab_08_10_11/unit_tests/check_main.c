#include <check.h>
#include <stdlib.h>

#include "check_matrix.h"

int main(void)
{
    int failed = 0;
    SRunner *runner;

    Suite *addition_matrix = addition_matrix_suite();
    runner = srunner_create(addition_matrix);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *multiply_matrix = multiply_matrix_suite();
    runner = srunner_create(multiply_matrix);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *solution_gauss_row_matrix = solution_gauss_row_matrix_suite();
    runner = srunner_create(solution_gauss_row_matrix);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);


    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
