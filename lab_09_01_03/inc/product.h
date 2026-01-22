#ifndef PRODUCT_H__
#define PRODUCT_H__

#include <stdlib.h>
#include <stdio.h>

#define ERROR_IO_FILE -1
#define ERROR_COUNT_PRODUCT -2
#define ERROR_EMPTY_PRODUCT -3
#define ERROR_INVALID_PRICE -5
#define ERROR_INVALID_COUNT -6
#define ERROR_NEGATIVE_PRICE -7
#define ERROR_MEMORY -9
#define ERROR_INVALID_POINTER -10
#define OK 0

struct product
{
    char *name;
    size_t size_name;
    int price;
};

void free_products(struct product *products, size_t count);
int read_count_product(FILE *f);
int read_product(FILE *file, struct product *arr_product, int *count_product);
void print_product(const struct product *item, FILE *f);
void print_products_less_price(struct product *arr_product, size_t size_arr, double price, FILE *f);

#endif
