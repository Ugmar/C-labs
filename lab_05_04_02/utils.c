#include <string.h>
#include "utils.h"

bool check_arg(char *arg, char *expected_arg, int len_arg)
{
    if (strncmp(arg, expected_arg, len_arg) == 0 && strlen(arg) == len_arg)
    {
        return true;
    }

    return false;
}
