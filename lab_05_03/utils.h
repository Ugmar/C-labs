#ifndef UTILS_H__
#define UTILS_H__

#include <stdio.h>
#include <stdbool.h>

#define ERRROR_IO_FILE 3
#define ERROR_BIN_WRITE 4
#define ERROR_SEEK_FILE 5
#define ERROR_READ_FILE 6
#define OK 0

int get_number_by_pos(FILE *f, int position, int *number);
int put_number_by_pos(FILE *f, int position, int *number);
int swap_el(FILE *f, size_t i, size_t j);
size_t get_size_file(FILE *f, size_t *n);
bool check_arg(char *arg, char *expected_arg, int len_arg);

#endif
