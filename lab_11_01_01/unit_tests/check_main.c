#include <check.h>
#include <stdlib.h>

Suite *my_snprintf_suite(void);

int main(void)
{
    int failed = 0;
    SRunner *runner;

    Suite *print = my_snprintf_suite();
    runner = srunner_create(print);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
