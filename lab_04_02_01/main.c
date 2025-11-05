#include <stdio.h>
#include <string.h>

#include "str.h"
#include "utils.h"

int main(void)
{
    char str[LEN_S + 1];
    char arr_words[COUNT_WORD][LEN_WORD];

    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        return ERROR_READ_S;
    }

    if (strlen(str) > LEN_S - 1)
    {
        return ERROR_LEN_S;
    }

    size_t len = str_split(arr_words, str, strlen(str));

    if (len > COUNT_WORD)
    {
        return ERROR_LEN_WORD;
    }

    if (len == 0)
    {
        return ERROR_NO_WORD;
    }

    len = str_unique(arr_words, len);
    str_sort(arr_words, len);
    print_words(arr_words, len);

    return OK;
}
