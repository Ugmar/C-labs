#ifndef FILE_H__
#define FILE_H__

#define ERROR_INVALID_COUNT_PARAM 1
#define ERROR_INVALID_PARAM 2

int import_file(char *name_input, char *name_output);
int export_file(char *name_input, char *name_output);
int create_file(char *name_file);
int print_file(char *name_file);
int sort_file(char *name_file);

#endif
