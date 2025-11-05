#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LEN_S (256 + 1)

bool is_reject(const char *s, const char *reject)
{
    for (size_t i = 0; reject[i] != '\0'; i++)
    {
        if (*s == reject[i])
        {
            return true;
        }
    }
    
    return false;
}

size_t my_strcspn(const char *s, const char *reject)
{
    size_t count = 0;

    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (!is_reject(&s[i], reject))
        {
            count++;
        }
        else
        {
            return count;
        }
    }

    return count;
}

char *my_strpbrk(const char *s, const char *accept)
{
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (is_reject(&s[i], accept))
        {
            return (char *)&s[i];
        }
    }

    return NULL;
}

size_t my_strspn(const char *s, const char *accept)
{
    size_t len = 0;
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (is_reject(&s[i], accept))
        {
            len++;
        }
        else
        {
            return len;
        }
    }

    return len;
}


char *my_strchr(const char *s, int c)
{
    if (c == '\0')
    {
        return (char *)&s[strlen(s)];
    }

    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == c)
        {
            return (char *)&s[i];
        }
    }

    return NULL;
}

char *my_strrchr(const char *s, int c)
{
    if (c == '\0')
    {
        return (char *)&s[strlen(s)];
    }

    const char *index = NULL;
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == c)
        {
            index = &s[i];
        }
    }

    return (char *)index;
}
