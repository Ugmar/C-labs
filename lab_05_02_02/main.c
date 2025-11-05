#include <stdio.h>

#include "utils.h"

#define COUNT_PARAM 2

int main(int argc, char **argv)
{
    if (argc != COUNT_PARAM)
    {
        return ERROR_INVALID_PARAM;
    }

    FILE *f = fopen(argv[argc - 1], "r");

    if (f == NULL)
    {
        return ERROR_IO_FILE;
    }

    int n = 0;
    double avg = calc_avg(f, &n);

    if (n == 0 || n == 1)
    {
        fclose(f);
        return ERROR_NO_DATA;
    }

    rewind(f);

    double variance = calc_variance(f, avg);

    fclose(f);
    
    printf("%lf\n", variance);

    return OK;
}
