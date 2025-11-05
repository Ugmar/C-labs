#ifndef BOOK_H__
#define BOOK_H__

#define LEN_NAME (128 + 1)
#define LEN_DATE (7 + 1)
#define COUNT_BOOK 100

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

#define ERROR_IO_FILE 1
#define ERROR_READ 2
#define OK 0

#include <stdint.h>

struct book
{
    uint64_t id;
    char name[LEN_NAME + 1];
    double avg_time;
    char date[LEN_DATE + 1];
};

int input_books(struct book *books, size_t *len);
size_t books_delete_max_id(struct book *books, size_t len);
size_t books_leave_only_may(struct book *books, size_t len);
int print_book(struct book *books, size_t len);
size_t books_unique_name(struct book *books, size_t len);

#endif
