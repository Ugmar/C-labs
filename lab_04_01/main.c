#include <stdio.h>
#include <string.h>

#include "my_string.h"

void test_my_strcspn()
{
    int err_cnt = 0;

    if (my_strcspn("hello", "la") != strcspn("hello", "la"))
    {
        err_cnt++;
    }

    if (my_strcspn("gggg", "g") != strcspn("gggg", "g"))
    {
        err_cnt++;
    }

    if (my_strcspn("", "") != strcspn("", ""))
    {
        err_cnt++;
    }

    if (my_strcspn("gggg", "asd") != strcspn("gggg", "asd"))
    {
        err_cnt++;
    }

    if (my_strcspn("world", "world") != strcspn("world", "world"))
    {
        err_cnt++;
    }

    printf("%d\n", err_cnt);
}

void test_my_strpbrk()
{
    int err_cnt = 0;
    const char *p1;
    const char *p2;

    p1 = my_strpbrk("hello", "elo");
    p2 = strpbrk("hello", "elo");

    if (*p1 != *p2)
    {
        err_cnt++;
    }

    p1 = my_strpbrk("gggg", "g");
    p2 = strpbrk("gggg", "g");

    if (*p1 != *p2)
    {
        err_cnt++;
    }
    
    p1 = my_strpbrk("", "");
    p2 = strpbrk("", "");

    if (p1 != p2)
    {
        err_cnt++;
    }

    p1 = my_strpbrk("gggg", "asd");
    p2 = strpbrk("gggg", "asd");

    if (p1 != p2)
    {
        err_cnt++;
    }

    p1 = my_strpbrk("gfds", "s");
    p2 = strpbrk("gfds", "s");

    if (*p1 != *p2)
    {
        err_cnt++;
    }

    printf("%d\n", err_cnt);
}

void test_my_strspn()
{
    int err_cnt = 0;

    if (my_strspn("hello", "") != strspn("hello", ""))
    {
        err_cnt++;
    }

    if (my_strspn("", "g") != strspn("", "g"))
    {
        err_cnt++;
    }

    if (my_strspn("", "") != strspn("", ""))
    {
        err_cnt++;
    }

    if (my_strspn("gggg", "asd") != strspn("gggg", "asd"))
    {
        err_cnt++;
    }

    if (my_strspn("world", "row") != strspn("world", "row"))
    {
        err_cnt++;
    }

    if (my_strspn("tomorrow", "tom") != strspn("tomorrow", "tom"))
    {
        err_cnt++;
    }

    printf("%d\n", err_cnt);
}

void test_my_strchr()
{
    int err_cnt = 0;
    const char *p1;
    const char *p2;

    p1 = my_strchr("hello", 'o');
    p2 = strchr("hello", 'o');
    
    if (*p1 != *p2)
    {
        err_cnt++;
    }

    p1 = my_strchr("hello", 'l');
    p2 = strchr("hello", 'l');
    
    if (*p1 != *p2)
    {
        err_cnt++;
    }

    p1 = my_strchr("abc", 'l');
    p2 = strchr("abc", 'l');
    
    if (p1 != p2)
    {
        err_cnt++;
    }

    p1 = my_strchr("", 'a');
    p2 = strchr("", 'a');
    
    if (p1 != p2)
    {
        err_cnt++;
    }

    p1 = my_strchr("hello", 'h');
    p2 = strchr("hello", 'h');
    
    if (*p1 != *p2)
    {
        err_cnt++;
    }

    p1 = my_strchr("hello", '\0');
    p2 = strchr("hello", '\0');
    
    if (*p1 != *p2)
    {
        err_cnt++;
    }

    printf("%d\n", err_cnt);
}

void test_my_strrchr()
{
    int err_cnt = 0;
    const char *p1;
    const char *p2;

    p1 = my_strrchr("hello", 'o');
    p2 = strrchr("hello", 'o');
    
    if (*p1 != *p2)
    {
        err_cnt++;
    }

    p1 = my_strrchr("hello", 'l');
    p2 = strrchr("hello", 'l');
    
    if (*p1 != *p2)
    {
        err_cnt++;
    }

    p1 = my_strrchr("abc", 'l');
    p2 = strrchr("abc", 'l');
    
    if (p1 != p2)
    {
        err_cnt++;
    }

    p1 = my_strrchr("", 'a');
    p2 = strrchr("", 'a');
    
    if (p1 != p2)
    {
        err_cnt++;
    }

    p1 = my_strrchr("hello", 'h');
    p2 = strrchr("hello", 'h');
    
    if (*p1 != *p2)
    {
        err_cnt++;
    }

    p1 = my_strchr("hello", '\0');
    p2 = strchr("hello", '\0');
    
    if (*p1 != *p2)
    {
        err_cnt++;
    }

    printf("%d\n", err_cnt);
}

int main(void)
{
    test_my_strcspn();
    test_my_strpbrk();
    test_my_strspn();
    test_my_strchr();
    test_my_strrchr();

    return 0;
}
