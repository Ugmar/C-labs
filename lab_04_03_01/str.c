#include <string.h>
#include <stdlib.h>

#include "symbol.h"
#include "str.h"

size_t str_to_arr(char (*arr_words)[LEN_WORD], char *str)
{
    char separators[] = " ,;:-.!?\n";
    char *pword = strtok(str, separators);

    size_t i = 0;

    while (pword)
    {
        if (strlen(pword) > LEN_WORD - 1)
        {
            return ERROR_LEN_WORD;
        }

        strncpy(arr_words[i], pword, strlen(pword));
        arr_words[i][strlen(pword)] = '\0';

        pword = strtok(NULL, separators);
        i++;
    }

    return i;
}

void create_new_string(char (*arr_words)[LEN_WORD], size_t len, char *last_word, char *new_str)
{
    size_t len_last_word = strlen(last_word);

    for (size_t i = len - 1; i >= 0 && i < len; i--)
    {
        if (strncmp(arr_words[i], last_word, len_last_word) != 0 || strlen(arr_words[i]) != len_last_word)
        {
            size_t len_word = strlen(arr_words[i]);

            len_word = unique_symbol(arr_words[i], len_word);

            if (strlen(new_str) > 0)
            {
                strncat(new_str, " ", MIN_LEN_STR);
            }
            
            strncat(new_str, arr_words[i], len_word);
        }
    }
}
