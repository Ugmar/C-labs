#ifndef STR_H__
#define STR_H__

#define LEN_S (256 + 1)
#define LEN_WORD (16 + 1)
#define COUNT_WORD ((LEN_S) / 2)
#define MIN_LEN_STR 2

#define ERROR_READ_S 1
#define ERROR_LEN_S 2
#define ERROR_LEN_WORD 200
#define ERROR_NO_WORD 4
#define ERROR_EMPT_LINE 5
#define OK 0

size_t str_to_arr(char (*arr_words)[LEN_WORD], char *str);
void create_new_string(char (*arr_words)[LEN_WORD], size_t len, char *last_word, char *new_str);

#endif
