#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"

int main(void)
{
    char str[LEN_S + 1];

    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        return ERROR_READ_S;
    }

    if (strlen(str) > LEN_S - 1)
    {
        return ERROR_LEN_S;
    }

    bool result = is_exp_digit(str);

    if (result)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

    return OK;
}
