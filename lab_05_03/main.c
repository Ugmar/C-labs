/*
тип int
сортировка выбором
сортировка по возрастанию
*/

#include <string.h>

#include "file.h"
#include "utils.h"

#define COUNT_PARAM 3
#define MAX_LEN_PARAM_IMP_EXP 6
#define MAX_LEN_PARAM_ACTION 1

int main(int argc, char **argv)
{
    int rc;

    if (argc == COUNT_PARAM + 1)
    {
        if (check_arg(argv[1], "import", MAX_LEN_PARAM_IMP_EXP))
        { 
            rc = import_file(argv[2], argv[3]);
        }
        else if (check_arg(argv[1], "export", MAX_LEN_PARAM_IMP_EXP))
        {
            rc = export_file(argv[2], argv[3]);
        }
    }
    else if (argc == COUNT_PARAM)
    {
        if (check_arg(argv[1], "c", MAX_LEN_PARAM_ACTION))
        {
            rc = create_file(argv[2]);
        }
        else if (check_arg(argv[1], "p", MAX_LEN_PARAM_ACTION))
        {
            rc = print_file(argv[2]);
        }
        else if (check_arg(argv[1], "s", MAX_LEN_PARAM_ACTION))
        {
            rc = sort_file(argv[2]);
        }
        else
        {
            rc = ERROR_INVALID_PARAM;
        }
    }
    else
    {
        rc = ERROR_INVALID_COUNT_PARAM;
    }

    return rc;
}
