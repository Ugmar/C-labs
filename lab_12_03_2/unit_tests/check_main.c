#include <check.h>
#include <stdlib.h>

#include "check_arr.h"

int main(void)
{
    int failed = 0;
    SRunner *runner;

    Suite *s_arr = arr_suite();
    runner = srunner_create(s_arr);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
