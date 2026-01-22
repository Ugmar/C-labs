#include <check.h>
#include <stdlib.h>

Suite *list_suite(void);
Suite *book_suite(void);

int main(void)
{
    int failed = 0;
    SRunner *runner;

    Suite *book = book_suite();
    runner = srunner_create(book);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    Suite *list = list_suite();
    runner = srunner_create(list);
    srunner_run_all(runner, CK_VERBOSE);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
