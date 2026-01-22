#ifndef LIST_H__
#define LIST_H__

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

node_t *create_node(void *data);
void free_list(node_t *head);
node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));
void insert(node_t **head, node_t *elem, node_t *before);
node_t *reverse(node_t *head);
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
void front_back_split(node_t *head, node_t **back);
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

#endif
