#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "str.h"

size_t str_split(char (*arr)[LEN_WORD], char *str, size_t len)
{
    size_t index_word = 0;
    size_t index_symbol = 0;
    char separators[] = " ,;:-.!?\n";

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (is_separator(str[i], separators, sizeof(separators)))
        {
            if (index_symbol > 0)
            {
                arr[index_word][index_symbol] = '\0';

                index_symbol = 0;
                index_word++;
            }
        }
        else if (index_symbol >= LEN_WORD - 1)
        {
            return ERROR_LEN_WORD;
        }
        else
        {
            arr[index_word][index_symbol] = str[i];
            index_symbol++;
        }
    }
    
    return index_word;
}

void str_delete_word(char (*arr)[LEN_WORD], size_t len, size_t index)
{
    char tmp[LEN_WORD];

    for (size_t i = index; i < len - 1; i++)
    {
        strncpy(tmp, arr[i], sizeof(tmp) - 1); 
        tmp[sizeof(tmp) - 1] = '\0';

        strncpy(arr[i], arr[i + 1], sizeof(arr[i + 1]) - 1);
        arr[i][sizeof(arr[i + 1]) - 1] = '\0';

        strncpy(arr[i + 1], tmp, sizeof(tmp) - 1);
        arr[i + 1][sizeof(tmp) - 1] = '\0';
    }
}

size_t str_unique(char (*arr)[LEN_WORD], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        size_t len_word = strlen(arr[i]);
        for (size_t j = i + 1; j < len; j++)
        {
            if (strncmp(arr[i], arr[j], len_word) == 0 && (len_word == strlen(arr[j])))
            {
                str_delete_word(arr, len, j);
                j--;
                len--;
            }
        }
    }

    return len;
}

void str_sort(char (*arr)[LEN_WORD], size_t len)
{
    char tmp[LEN_WORD];

    for (size_t j = 0; j < len; j++)
    {
        for (size_t i = 0; i < len - j - 1; i++)
        {
            if (strncmp(arr[i], arr[i + 1], strlen(arr[i])) > 0)
            {
                strncpy(tmp, arr[i], sizeof(tmp) - 1); 
                tmp[sizeof(tmp) - 1] = '\0';

                strncpy(arr[i], arr[i + 1], sizeof(arr[i + 1]) - 1);
                arr[i][sizeof(arr[i + 1]) - 1] = '\0';

                strncpy(arr[i + 1], tmp, sizeof(tmp) - 1);
                arr[i + 1][sizeof(tmp) - 1] = '\0';
            }
        }
    }
}
