#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "my_snprintf.h"

#define HEX 16
#define OCT 8
#define DEC 10

#define MAX_DIGIT ((sizeof(unsigned long) * CHAR_BIT + 2) / 3)

#define PRINT_ERROR -1

void print_signed_base(char *s, int *len, size_t n, long a, int base)
{
    if (!s || !len)
        return;
    
    if (a < 0)
    {
        if (*len < n)
            s[*len] = '-';

        (*len)++;

        print_unsigned_base(s, len, n, (unsigned long)(-(a + 1)) + 1, base);
    }
    else
        print_unsigned_base(s, len, n, (unsigned long)a, base);
}


void print_unsigned_base(char *s, int *len, size_t n, unsigned long a, int base)
{
    if (!s || !len)
        return;

    char digits[] = "0123456789abcdef";
    char tmp[MAX_DIGIT];
    int cur_len = 0;

    if (a == 0)
    {
        tmp[cur_len] = '0';
        cur_len++;
    }

    while (a)
    {
        tmp[cur_len] = digits[a % base];
        cur_len++;
        a /= base;
    }

    for (int i = cur_len - 1; i >= 0; i--)
    {
        if (*len < n)
            s[*len] = tmp[i];

        (*len)++;
    }
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    if (!format)
        return PRINT_ERROR;

    va_list args;

    va_start(args, format);

    int len = 0;

    bool is_long = false;
    bool is_short = false;

    char c;
    char *str;

    if (n > 0)
        s[--n] = '\0';

    while (*format)
    {
        if (*format != '%')
        {
            if (len < n)
                s[len] = *format;

            len++;
        }
        else
        {
            format++;

            switch (*format)
            {
                case 'l':
                    is_long = true;
                    format++;
                    break;
                case 'h':
                    is_short = true;
                    format++;
                    break;
            }

            switch (*format)
            {
                case 'c':
                    c = (char)va_arg(args, int);

                    if (len < n)
                        s[len] = c;

                    len++;
                    break;
                case 's':
                    str = va_arg(args, char *);

                    if (!str)
                        str = "(null)";

                    while (*str != '\0')
                    {
                        if (len < n)
                            s[len] = *str;
                        len++;
                        str++;
                    }
                    break;
                case 'i':
                case 'd':
                    {
                        long digit;
                        
                        if (is_long)
                            digit = va_arg(args, long);
                        else if (is_short)
                            digit = (short)va_arg(args, int);
                        else
                            digit = va_arg(args, int);

                        print_signed_base(s, &len, n, digit, DEC);
                        break;
                    }
                case 'o':
                    {
                        unsigned long digit;

                        if (is_long)
                            digit = va_arg(args, unsigned long);
                        else if (is_short)
                            digit = (unsigned short)va_arg(args, unsigned int);
                        else
                            digit = va_arg(args, unsigned int);

                        print_unsigned_base(s, &len, n, digit, OCT);
                        break;
                    }
                case 'x':
                    {
                        unsigned long digit;

                        if (is_long)
                            digit = va_arg(args, unsigned long);
                        else if (is_short)
                            digit = (unsigned short)va_arg(args, unsigned int);
                        else
                            digit = va_arg(args, unsigned int);

                        print_unsigned_base(s, &len, n, digit, HEX);
                        break;
                    }
            }

            is_long = false;
            is_short = false;
        }

        format++;
    }

    va_end(args);

    if (len < n)
        s[len] = '\0';

    return len;
}
