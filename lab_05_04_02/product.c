#include <stdio.h>
#include <string.h>

#include "product.h"

int input_product(char *name, struct product *arr_product, size_t *n)
{
    FILE *f = fopen(name, "r");

    if (f == NULL)
    {
        return ERROR_IO_FILE;
    }

    size_t i = 0;
    int rc = 0;
    struct product current;

    while (!feof(f))
    {
        if (fgets(current.name, LEN_NAME + 1, f) == NULL)
        {
            if (feof(f))
            {
                break;
            }
            
            rc = ERROR_READ_FILE;
        }

        if (strlen(current.name) > LEN_NAME - 1)
        {
            rc = ERROR_INVALID_STRING;
        }

        current.name[strlen(current.name) - 1] = '\0';

        if (fgets(current.maker, LEN_MAKER + 1, f) == NULL)
        {
            rc = ERROR_READ_FILE;
        }

        if (strlen(current.maker) > LEN_MAKER - 1)
        {
            rc = ERROR_INVALID_STRING;
        }

        current.maker[strlen(current.maker) - 1] = '\0';

        if (fscanf(f, "%u %u", &current.price, &current.count) != 2)
        {
            rc = ERROR_READ_FILE;
        }

        if (rc)
        {
            fclose(f);
            return rc;
        }

        arr_product[i] = current;
        i++;

        fgetc(f);
    }

    fclose(f);

    if (!i)
    {
        return ERROR_EMPTY_FILE;
    }

    *n = i;

    return OK;
}

void selection_sort(struct product *arr_product, size_t n)
{
    struct product tmp, el_j, el_max;

    for (size_t i = 0; i < n; i++)
    {
        size_t max_index = i;

        for (size_t j = i + 1; j < n; j++)
        {
            el_j = arr_product[j];
            el_max = arr_product[max_index];

            if (el_j.price > el_max.price || (el_j.price == el_max.price && el_j.count > el_max.count))
            {
                max_index = j;
            }
        }

        tmp = arr_product[i];
        arr_product[i] = arr_product[max_index];
        arr_product[max_index] = tmp;       
    }
}

int sort_product(char *name_input, char *name_output)
{
    struct product arr_product[COUNT_PRODUCT];
    size_t n;

    int rc = input_product(name_input, arr_product, &n);

    if (rc != OK)
    {
        return rc;
    }

    selection_sort(arr_product, n);
    
    FILE *f_output = fopen(name_output, "w");

    if (f_output == NULL)
    {
        return ERROR_IO_FILE;
    }

    for (size_t i = 0; i < n; i++)
    {
        fprintf(f_output, "%s\n%s\n%u\n%u\n", arr_product[i].name, arr_product[i].maker, arr_product[i].price, arr_product[i].count);
    }
    
    return OK;
}

int print_product(char *name, char *str)
{
    int len_str = strlen(str);

    if (len_str > LEN_NAME - 1)
    {
        return ERROR_INVALID_STRING;
    }

    struct product arr_product[COUNT_PRODUCT];
    size_t n;

    int rc = input_product(name, arr_product, &n);

    if (rc != OK)
    {
        return rc;
    }

    int len_name;
    size_t index_compare;
    rc = ERROR_INVALID_STRING;
    
    for (size_t i = 0; i < n; i++)
    {
        len_name = strlen(arr_product[i].name);
        index_compare = len_name - len_str;

        if (index_compare > len_name)
        {
            continue;
        }

        if (strncmp(&arr_product[i].name[index_compare], str, len_str) == 0)
        {
            rc = OK;
            fprintf(stdout, "%s\n%s\n%u\n%u\n", arr_product[i].name, arr_product[i].maker, arr_product[i].price, arr_product[i].count);
        }
    }

    return rc;
}

int insert_product_in_file(char *name_file, struct product *arr_product, size_t n, struct product current, size_t index)
{
    FILE *f = fopen(name_file, "w");
    
    if (f == NULL)
    {
        return ERROR_IO_FILE;
    }

    for (size_t i = 0; i < n + 1; i++)
    {
        if (i == index)
        {
            fprintf(f, "%s\n%s\n%u\n%u\n", current.name, current.maker, current.price, current.count);
        }

        if (i < n)
        {
            fprintf(f, "%s\n%s\n%u\n%u\n", arr_product[i].name, arr_product[i].maker, arr_product[i].price, arr_product[i].count);
        }
    }

    return OK;
}

size_t search_index_product(struct product *arr_product, size_t n, struct product current)
{
    size_t l = 0;
    size_t r = n;
    size_t index = n;
    struct product el_m;

    while (l < r)
    {
        size_t m = l + (r - l) / 2;
        el_m = arr_product[m];

        if (current.price == el_m.price)
        {
            if (current.count == el_m.count)
            {
                return m;
            }
            else if (el_m.count > current.count)
            {
                l = m + 1;
            }
            else
            {
                index = m;
                r = m;
            }
        }
        else if (el_m.price > current.price)
        {
            l = m + 1;
        }
        else
        {
            index = m;
            r = m;
        }
    }

    return index;
}

int add_product(char *name_file)
{
    struct product arr_product[COUNT_PRODUCT];
    size_t n;

    int rc = input_product(name_file, arr_product, &n);

    if (rc != OK)
    {
        return rc;
    }

    struct product current;

    if (fgets(current.name, LEN_NAME + 1, stdin) == NULL)
    {
        return ERROR_READ_FILE;
    }

    if (strlen(current.name) > LEN_NAME - 1)
    {
        return ERROR_INVALID_STRING;
    }
    
    current.name[strlen(current.name) - 1] = '\0';

    if (fgets(current.maker, LEN_MAKER, stdin) == NULL)
    {
        return ERROR_READ_FILE;
    }

    if (strlen(current.maker) > LEN_MAKER - 1)
    {
        return ERROR_INVALID_STRING;
    }

    current.maker[strlen(current.maker) - 1] = '\0';
    
    if (fscanf(stdin, "%u %u", &current.price, &current.count) != 2)
    {
        return ERROR_READ_FILE;
    }

    size_t index = search_index_product(arr_product, n, current);

    rc = insert_product_in_file(name_file, arr_product, n, current, index);

    if (rc != OK)
    {
        return rc;
    }

    return OK;
}
