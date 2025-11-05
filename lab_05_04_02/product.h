#ifndef PRODUCT_H__
#define PRODUCT_H__

#include <stdint.h>

#define ERROR_INVALID_PARAM 53
#define ERROR_IO_FILE 1
#define ERROR_READ_FILE 2
#define ERROR_INVALID_STRING 3
#define ERROR_EMPTY_FILE 4
#define OK 0

#define LEN_NAME (30 + 1)
#define LEN_MAKER (15 + 1)
#define COUNT_PRODUCT 100

struct product
{
    uint32_t price;
    uint32_t count;
    char name[LEN_NAME + 1];
    char maker[LEN_MAKER + 1];   
};

int sort_product(char *name_input, char *output);
int print_product(char *name, char *str);
int add_product(char *name_file);

#endif
