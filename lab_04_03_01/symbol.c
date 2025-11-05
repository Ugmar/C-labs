#include <stdlib.h>

void delete_symbol(char *word, size_t len, size_t index)
{
    char tmp;

    for (size_t i = index; i < len - 1; i++)
    {
        tmp = word[i];
        word[i] = word[i + 1];
        word[i + 1] = tmp;
    }
}

size_t unique_symbol(char *word, size_t len)
{
    for (size_t i = 1; i < len; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (word[i] == word[j])
            {
                delete_symbol(word, len, i);
                len--;
                i--;
                j = i;
            }
        }
    }

    return len;
}
