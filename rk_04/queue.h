#ifndef QUEUE_H__
#define QUEUE_H__

#include <sys/time.h>
#include <time.h>

#define COUNT_PRIORITY 5
#define LEN_TITLE 63

typedef struct
{
    int doc_id;                // Уникальный ID (генерируется системой)
    int priority;              // 1-5, где 5 - самый высокий
    char title[LEN_TITLE + 1]; // Название документа
    int processing_time;       // Время обработки в условных единицах
    struct timeval timestamp;  // Время поступления (`man gettimeofday`)
} document_t;

typedef struct node
{
    document_t doc;
    struct node *next;
} node_t;

typedef struct
{
    node_t *lists[COUNT_PRIORITY];
    int total;
    int sum_id;
    int min_priority;
    int max_priority;
    int next_id;
} queue;

void init_queue(queue *q);
int add_document(queue *q, int priority, char *title);
int get_next_document(queue *q, document_t *result, int *steps);
void get_status(queue *q);
void get_stats(queue *q);
void clean_queue(queue *q);

#endif
