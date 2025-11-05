#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "str.h"

void print_words(char (*arr_words)[LEN_WORD], size_t len)
{
    printf("Result:");
    for (size_t i = 0; i < len; i++)
    {
        printf(" %s", arr_words[i]);
    }
    printf("\n");
}

bool is_separator(char symbol, char *separators, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (separators[i] == symbol)
        {
            return true;
        }
    }

    return false;
}
