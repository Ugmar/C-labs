#ifndef PRODUCT_H__
#define PRODUCT_H__

#include <stdlib.h>

#define ERROR_IO_FILE -1
#define ERROR_COUNT_PRODUCT -2
#define ERROR_EMPTY_PRODUCT -3
#define ERROR_INVALID_NAME -4
#define ERROR_INVALID_PRICE -5
#define ERROR_INVALID_COUNT -6
#define ERROR_NEGATIVE_PRICE -7
#define ERROR_OVERFLOW_COUNT_PRODUCT -8

#define COUNT_PRODUCT 15
#define LEN_NAME ((25 + 1))

struct product
{
    char name[LEN_NAME + 2];
    long price;
};

int input_product(char *filename, struct product *arr_product);
void print_products_less_price(struct product *arr_product, size_t size_arr, double price);

#endif
