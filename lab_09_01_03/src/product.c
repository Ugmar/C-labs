#define  _POSIX_C_SOURCE 200809L

#include <string.h>

#include "product.h"

#define GETLINE_FAIL -1

int read_count_product(FILE *f)
{
    int count_product = 0;

    if (fscanf(f, "%d\n", &count_product) != 1)
        return ERROR_COUNT_PRODUCT; 

    return count_product;
}

int read_product(FILE *file, struct product *arr_product, int *count_product)
{
    if (!file || !arr_product)
        return ERROR_INVALID_POINTER;
    
    ssize_t len_name;

    for (size_t i = 0; i < *count_product; i++)
    {
        arr_product[i].name = NULL;
        arr_product[i].size_name = 0;
        arr_product[i].price = 0;

        len_name = getline(&arr_product[i].name, &arr_product[i].size_name, file);

        if (len_name == GETLINE_FAIL)
            return ERROR_EMPTY_PRODUCT;

        if (arr_product[i].name[len_name - 1] == '\n')
            arr_product[i].name[len_name - 1] = '\0';

        if (fscanf(file, "%d\n", &arr_product[i].price) != 1)
        {
            *count_product = i + 1;
            return ERROR_INVALID_PRICE;
        }
        
        if (arr_product[i].price < 0)
        {
            *count_product = i + 1;
            return ERROR_NEGATIVE_PRICE;
        }
    }

    if (!feof(file))
        return ERROR_INVALID_COUNT;

    return OK;
}

void print_product(const struct product *item, FILE *f)
{
    fprintf(f, "%s\n%d\n", item->name, item->price);
}

void print_products_less_price(struct product *arr_product, size_t size_arr, double price, FILE *f)
{
    for (size_t i = 0; i < size_arr; i++)
    {
        if (arr_product[i].price < price)
            print_product(&arr_product[i], f);
    }
}

void free_products(struct product *products, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        free(products[i].name);
        products[i].name = NULL;
    }

    free(products);
}
