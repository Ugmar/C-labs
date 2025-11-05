#include <string.h>
#include <stdio.h>

#include "product.h"

int input_product(char *filename, struct product *arr_product)
{
    FILE *f = fopen(filename, "r");

    if (!f)
        return ERROR_IO_FILE;

    size_t count_product = 0;

    if (fscanf(f, "%zu\n", &count_product) != 1)
    {
        fclose(f);
        return ERROR_COUNT_PRODUCT; 
    }

    if (count_product > COUNT_PRODUCT)
    {
        fclose(f);
        return ERROR_OVERFLOW_COUNT_PRODUCT;
    }
    
    struct product current;
    size_t size_current_name = 0;
    int size = 0;

    for (size_t i = 0; i < count_product; i++)
    {
        if (fgets(current.name, LEN_NAME + 2, f) == NULL)
        {
            fclose(f);
            return ERROR_EMPTY_PRODUCT;
        }

        size_current_name = strlen(current.name);

        if (current.name[size_current_name - 1] == '\n')
            current.name[size_current_name - 1] = '\0';

        if (strlen(current.name) > LEN_NAME - 1)
        {
            fclose(f);
            return ERROR_INVALID_NAME;
        }

        if (fscanf(f, "%ld\n", &current.price) != 1)
        {
            fclose(f);
            return ERROR_INVALID_PRICE;
        }
        
        if (current.price < 0)
        {
            fclose(f);
            return ERROR_NEGATIVE_PRICE;
        }
        
        arr_product[size] = current;
        size++;
    }

    if (!feof(f))
    {
        fclose(f);
        return ERROR_INVALID_COUNT;
    }

    fclose(f);
    return size;
}

void print_product(const struct product *item)
{
    printf("%s\n%ld\n", item->name, item->price);
}

void print_products_less_price(struct product *arr_product, size_t size_arr, double price)
{
    for (size_t i = 0; i < size_arr; i++)
    {
        if (arr_product[i].price < price)
            print_product(&arr_product[i]);
    }
}
