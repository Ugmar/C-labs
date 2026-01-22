#include <check.h>
#include <stdlib.h>

Suite *list_suite(void);
Suite *matrix_suite(void);
Suite *io_suite(void);

int main(void)
{
    int failed = 0;
    SRunner *runner;

    Suite *matrix = list_suite();
    runner = srunner_create(matrix);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *list = matrix_suite();
    runner = srunner_create(list);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *io = io_suite();
    runner = srunner_create(io);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
