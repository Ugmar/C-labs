#ifndef BOOK_H__
#define BOOK_H__

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct book book_t;

struct book
{
    char *name;
    size_t cap_name;
    char *author;
    size_t cap_author;
    int year;
};

void print_book(node_t *node, FILE *file);
void print_books(node_t *head, FILE *file);
void free_book(void *b);
book_t *input_book(FILE *file_read);
node_t *input_books(FILE *file_read);
int reverse_books(node_t **head, FILE *file_write);
int sort_books(node_t **head, FILE *file_write);
int insert_book(node_t **head, FILE *file_write);
void free_books(node_t *books);
int compare_book_sort(const void *book1, const void *book2);
int compare_book_find(const void *book1, const void *book2);

#endif
