#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define LEN_COMMAND 100

#define ADD "ADD"
#define NEXT "NEXT"
#define STATUS "STATUS"
#define STATS "STATS"
#define QUIT "QUIT"

int main()
{
    queue q;
    init_queue(&q);

    int is_run = 1;
    int rc = 0;

    char command[LEN_COMMAND];

    document_t doc;
    int steps;

    int priority;
    char title[LEN_TITLE + 1];

    while (is_run)
    {
        fprintf(stderr, "Введите команду: ");

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            is_run = 0;
            break;
        }

        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';

        if (strncmp(command, ADD, strlen(ADD)) == 0)
        {
            if (sscanf(command + strlen(ADD) + 1, "%d %63s", &priority, title) == 2)
            {
                rc = add_document(&q, priority, title);

                if (rc < 0)
                    fprintf(stderr, "Произошла ошибка при добавлении документа\n");
            }
            else
                fprintf(stderr, "Ошибка формата команды ADD\n");
        }
        else if (strncmp(command, NEXT, strlen(NEXT)) == 0)
        {
            if (get_next_document(&q, &doc, &steps) != 0)
                fprintf(stderr, "Пустая очередь\n");
        }
        else if (strncmp(command, STATUS, strlen(STATUS)) == 0)
        {
            get_status(&q);
        }
        else if (strncmp(command, STATS, strlen(STATS)) == 0)
        {
            get_stats(&q);
        }
        else if (strncmp(command, QUIT, strlen(QUIT)) == 0)
        {
            fprintf(stderr, "Завершение программы\n");
            is_run = 0;
        }
        else
            fprintf(stderr, "Неизвестная команда: %s\n", command);
    }

    clean_queue(&q);
    return 0;
}
