#ifndef STR_H__

#define STR_H__

#define ERROR_READ_S 1
#define ERROR_LEN_S 2
#define ERROR_LEN_WORD 200
#define ERROR_NO_WORD 4
#define OK 0

#define LEN_S (256 + 1)
#define LEN_WORD (16 + 1)
#define COUNT_WORD ((LEN_S) / 2)

size_t str_split(char (*arr)[LEN_WORD], char *str, size_t len);
size_t str_unique(char (*arr)[LEN_WORD], size_t len);
void str_sort(char (*arr)[LEN_WORD], size_t len);

#endif
