#include <string.h>

#include "utils.h"
#include "product.h"

#define COUNT_PARAM 3
#define MAX_LEN_PARAM_ACTION 2

int main(int argc, char **argv)
{
    int rc = ERROR_INVALID_PARAM;

    if (argc == COUNT_PARAM + 1)
    {
        if (check_arg(argv[1], "st", MAX_LEN_PARAM_ACTION))
        {
            rc = sort_product(argv[2], argv[3]);
        }
        else if (check_arg(argv[1], "ft", MAX_LEN_PARAM_ACTION))
        {
            rc = print_product(argv[2], argv[3]);
        }
    }
    else if (argc == COUNT_PARAM && check_arg(argv[1], "at", MAX_LEN_PARAM_ACTION))
    {    
        rc = add_product(argv[2]);
    }

    return rc;
}
