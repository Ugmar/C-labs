#include <stdlib.h>

#include "utils.h"

#define COUNT_DIGITS 10
#define NUMBER_DIGITS 100

int import_file(char *name_input, char *name_output)
{
    FILE *input, *output;

    input = fopen(name_input, "r");

    if (input == NULL)
    {
        return ERRROR_IO_FILE;
    }

    output = fopen(name_output, "wb");

    if (output == NULL)
    {
        fclose(input);

        return ERRROR_IO_FILE;
    }

    int el;

    while (fscanf(input, "%d", &el) == 1)
    {
        if (fwrite(&el, sizeof(el), 1, output) != 1)
        {
            fclose(input);
            fclose(output);

            return ERROR_BIN_WRITE;
        }
    }

    fclose(input);
    fclose(output);

    return OK;
}

int export_file(char *name_input, char *name_output)
{
    FILE *input, *output;

    input = fopen(name_input, "rb");

    if (input == NULL)
    {
        return ERRROR_IO_FILE;
    }

    output = fopen(name_output, "w");

    if (output == NULL)
    {
        fclose(input);
        return ERRROR_IO_FILE;
    }

    int el;

    while (fread(&el, sizeof(el), 1, input) == 1)
    {
        fprintf(output, "%d ", el);
    }

    fclose(input);
    fclose(output);

    return OK;
}

int create_file(char *name_file)
{
    FILE *f = fopen(name_file, "wb");

    if (f == NULL)
    {
        return ERRROR_IO_FILE;
    }

    int el = rand() % NUMBER_DIGITS;
    
    for (int i = 0; i < COUNT_DIGITS; i++)
    {
        if (fwrite(&el, sizeof(el), 1, f) != 1)
        {
            fclose(f);
            return ERROR_BIN_WRITE;
        }

        el = rand() % NUMBER_DIGITS;
    }

    fclose(f);

    return OK;
}

int print_file(char *name_file)
{
    FILE *f = fopen(name_file, "rb");
    
    if (f == NULL)
    {
        return ERRROR_IO_FILE;
    }

    size_t n;
    size_t rc = get_size_file(f, &n);

    if (rc != OK)
    {
        fclose(f);
        return rc;
    }

    int el;

    for (size_t i = 0; i < n; i++)
    {
        if (fread(&el, sizeof(el), 1, f) == 1)
        {
            fprintf(stdout, "%d ", el);
        }
        else
        {
            return ERROR_READ_FILE;
        }
    }
    
    fclose(f);

    return OK;
}

int sort_file(char *name_file)
{
    FILE *f = fopen(name_file, "rb+");

    if (f == NULL)
    {
        return ERRROR_IO_FILE;
    }

    size_t n;
    size_t rc = get_size_file(f, &n);

    if (rc != OK)
    {
        fclose(f);
        return rc;
    }

    int number_j, number_min;

    for (size_t i = 0; i < n; i++)
    {
        size_t min_index = i;

        for (size_t j = i + 1; j < n; j++)
        {
            rc = get_number_by_pos(f, j, &number_j);
            rc |= get_number_by_pos(f, min_index, &number_min);

            if (rc != OK)
            {
                fclose(f);
                return rc;
            }

            if (number_j < number_min)
            {
                min_index = j;
            }
        }

        rc = swap_el(f, i, min_index);

        if (rc != OK)
        {
            fclose(f);
            return rc;
        }
    }

    return OK;
}
