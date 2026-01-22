#ifndef MY_SNPRINTF_H__
#define MY_SNPRINTF_H__

#include <stdlib.h>

int my_snprintf(char *s, size_t n, const char *format, ...);
void print_unsigned_base(char *s, int *len, size_t n, unsigned long a, int base);
void print_signed_base(char *s, int *len, size_t n, long a, int base);

#endif
