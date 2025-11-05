#ifndef UTILS_H__

#define UTILS_H__

#include <stdbool.h>

void print_words(char (*arr_words)[], size_t len);
bool is_separator(char symbol, char *separators, size_t len);

#endif
