#include <check.h>
#include <stdlib.h>

#include "check_product.h"

int main(void)
{
    int failed = 0;
    SRunner *runner;

    Suite *read_product = input_product_suite();
    runner = srunner_create(read_product);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *utils = utils_suite();
    runner = srunner_create(utils);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
