#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "str.h"

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

    size_t len = str_to_arr(arr_words, str);

    if (len <= 1)
    {
        return ERROR_NO_WORD;
    }

    if (len > COUNT_WORD)
    {
        return ERROR_LEN_WORD;
    }

    char last_word[LEN_WORD];

    strncpy(last_word, arr_words[len - 1], sizeof(arr_words[len - 1]) - 1);
    last_word[sizeof(arr_words[len - 1]) - 1] = '\0';

    char new_str[LEN_S];
    new_str[0] = '\0';
    
    create_new_string(arr_words, len - 1, last_word, new_str);

    if (strlen(new_str) == 0)
    {
        return ERROR_EMPT_LINE;
    }

    printf("Result: %s\n", new_str);

    return OK;
}
