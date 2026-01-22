#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "erorrs.h"
#include "queue.h"

void init_queue(queue *q)
{
    for (int i = 0; i < COUNT_PRIORITY; i++)
        q->lists[i] = NULL;

    q->total = 0;
    q->sum_id = 0;
    q->min_priority = 5;
    q->max_priority = 1;
    q->next_id = 1;
}

int add_document(queue *q, int priority, char *title)
{
    if (priority < 1 || priority > 5)
    {
        fprintf(stderr, "Ошибка: приоритет должен быть от 1 до 5\n");
        return ERROR_ADD;
    }

    node_t *new_node = malloc(sizeof(node_t));

    if (!new_node)
    {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return ERROR_MEMORY;
    }

    new_node->doc.doc_id = q->next_id++;
    new_node->doc.priority = priority;

    strncpy(new_node->doc.title, title, LEN_TITLE);
    new_node->doc.title[LEN_TITLE] = '\0';

    new_node->doc.processing_time = priority;
    gettimeofday(&new_node->doc.timestamp, NULL);

    new_node->next = NULL;

    if (q->lists[priority - 1] == NULL)
        q->lists[priority - 1] = new_node;
    else
    {
        node_t *cur = q->lists[priority - 1];

        while (cur->next != NULL)
            cur = cur->next;
        cur->next = new_node;
    }

    fprintf(stderr, "+ %d added with priority %d at %ld.%ld\n", new_node->doc.doc_id, priority,
            new_node->doc.timestamp.tv_sec, new_node->doc.timestamp.tv_usec);

    return new_node->doc.doc_id;
}

int get_next_document(queue *q, document_t *result, int *steps)
{
    *steps = 0;

    for (int p = 5; p >= 1; p--)
    {
        (*steps)++;
        if (q->lists[p - 1] != NULL)
        {
            node_t *node = q->lists[p - 1];
            *result = node->doc;
            q->lists[p - 1] = node->next;

            q->total++;
            q->sum_id += result->doc_id;

            if (result->priority < q->min_priority)
                q->min_priority = result->priority;
            if (result->priority > q->max_priority)
                q->max_priority = result->priority;

            free(node);

            fprintf(stderr, "= %d (%d, %s, %ld.%ld) [processed in %d STEPS]\n", result->doc_id, result->priority,
                    result->title, result->timestamp.tv_sec, result->timestamp.tv_usec, *steps);
            return OK;
        }
    }

    return ERROR_EMPTY_QEUUE;
}

void get_status(queue *q)
{
    for (int p = 5; p >= 1; p--)
    {
        fprintf(stderr, "Priority %d: ", p);

        int count = 0;
        node_t *cur = q->lists[p - 1];

        while (cur != NULL)
        {
            count++;
            cur = cur->next;
        }

        fprintf(stderr, "%d docs", count);

        if (count > 0)
        {
            fprintf(stderr, " [ID:");

            cur = q->lists[p - 1];

            while (cur != NULL)
            {
                fprintf(stderr, " %d", cur->doc.doc_id);

                if (cur->next != NULL)
                    fprintf(stderr, ",");

                cur = cur->next;
            }

            fprintf(stderr, "]");
        }

        fprintf(stderr, "\n");
    }
}

void get_stats(queue *q)
{
    fprintf(stderr, "Всего обработано документов: %d\n", q->total);

    if (q->total > 0)
    {
        double avg_id = (double)q->sum_id / q->total;

        printf("Средний ID: %lf\n", avg_id);
        printf("Минимальный приоритет среди обработанных: %d\n", q->min_priority);
        printf("Максимальный приоритет среди обработанных: %d\n", q->max_priority);
    }
    else
    {
        printf("Средний ID: %lf\n", 0.0);
        printf("Минимальный приоритет среди обработанных: %d\n", 0);
        printf("Максимальный приоритет среди обработанных: %d\n", 0);
    }
}

void clean_queue(queue *q)
{
    for (int i = 0; i < COUNT_PRIORITY; i++)
    {
        node_t *cur = q->lists[i];

        while (cur != NULL)
        {
            node_t *next = cur->next;

            free(cur);

            cur = next;
        }

        q->lists[i] = NULL;
    }
}
