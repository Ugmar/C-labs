#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "utils.h"

bool is_exp_digit(char *str)
{
    while (isspace(*str))
    {
        str++;
    }

    char *end = str + strlen(str);

    while (isspace(*(end - 1)) && end > str)
    {
        end--;
    }

    if (end - str <= 0)
    {
        return false;
    }

    *end = '\0';

    if (*str == '+' || *str == '-')
    {
        str++;
    }

    bool digits_before_dot = false;
    bool dot = false;
    bool digits_after_dot = false;
    bool digits_after_exp = false;

    while (isdigit(*str))
    {
        str++;
        digits_before_dot = true;
    }

    if (*str == '.')
    {
        dot = true;
        str++;

        while (isdigit(*str))
        {
            str++;
            digits_after_dot = true;
        }
    }

    if (*str == 'e' || *str == 'E')
    {
        str++;

        if (*str == '+' || *str == '-') 
        {
            str++;
        }

        while (isdigit(*str))
        {
            digits_after_exp = true;
            str++;
        }

        if (!digits_after_exp) 
        {
            return false;
        }
    }

    if (*str != '\0') 
    {
        return false;
    }

    if (digits_before_dot)
    {
        return true;
    }

    if (!digits_before_dot && dot && digits_after_dot)
    {
        return true;
    }

    return false;
}
