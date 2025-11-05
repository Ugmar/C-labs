#include <stdio.h>
#include <string.h>

#include "book.h"

int input_books(struct book *books, size_t *len)
{
    FILE *f = fopen(INPUT_FILE, "r");

    if (f == NULL)
    {
        return ERROR_IO_FILE;
    }

    struct book current;

    for (size_t i = 0; i < COUNT_BOOK; i++)
    {
        if (fscanf(f, "%lu", &current.id) != 1)
        {
            if (feof(f) && i > 0)
            {
                break;
            }

            fclose(f);
            return ERROR_READ;
        }
        fgetc(f);

        if (fgets(current.name, LEN_NAME + 1, f) == NULL)
        {
            fclose(f);
            return ERROR_READ;
        }

        size_t len_name = strlen(current.name);

        if (strlen(current.name) > LEN_NAME)
        {
            fclose(f);
            return ERROR_READ;
        }

        current.name[len_name - 1] = '\0';

        if (fscanf(f, "%lf", &current.avg_time) != 1)
        {
            fclose(f);
            return ERROR_READ;
        }
        fgetc(f);

        if (fgets(current.date, LEN_DATE + 1, f) == NULL)
        {
            fclose(f);
            return ERROR_READ;
        }

        size_t len_date = strlen(current.date);

        if (strlen(current.date) > LEN_DATE)
        {
            fclose(f);
            return ERROR_READ;
        }

        current.date[len_date - 1] = '\0';

        books[i] = current;
        (*len)++;
    }

    fclose(f);

    return OK;
}

void shift_book(struct book *books, size_t len, size_t index_max)
{
    for (size_t i = index_max; i < len - 1; i++)
    {
        books[i] = books[i + 1];
    }
}


size_t books_delete_max_id(struct book *books, size_t len)
{
    struct book max_book = books[0];
    size_t index_max = 0;

    for (size_t i = 1; i < len; i++)
    {
        if (books[i].id >= max_book.id)
        {
            max_book = books[i];
            index_max = i;

        }
    }

    shift_book(books, len, index_max);

    return len - 1;
}

size_t books_leave_only_may(struct book *books, size_t len)
{
    size_t len_name;

    for (size_t i = 0; i < len; i++)
    {
        len_name = strlen(books[i].date);

        if (strncmp(&books[i].date[len_name - 2], "05", strlen("05")) != 0)
        {
            shift_book(books, len, i);
            len--;
            i--;
        }
    }

    return len;
}

size_t books_unique_name(struct book *books, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = i + 1; j < len; j++)
        {
            if (strncmp(books[i].name, books[j].name, LEN_NAME) == 0 && strlen(books[i].name) == strlen(books[j].name))
            {
                shift_book(books, len, j);
                len--;
                j--;
            }
        }
    }

    return len;
}


int print_book(struct book *books, size_t len)
{
    FILE *f = fopen(OUTPUT_FILE, "w");

    if (f == NULL)
    {
        return ERROR_IO_FILE;
    }

    for (size_t i = 0; i < len; i++)
    {
        fprintf(f, "%lu\n%s\n%lf\n%s\n", books[i].id, books[i].name, books[i].avg_time, books[i].date);
    }

    return OK;
}
