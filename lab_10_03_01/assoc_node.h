#ifndef ASSOC_NODE_H__
#define ASSOC_NODE_H__

typedef struct assoc_node node_t;

struct assoc_node
{
    char *key;
    int value;
};

int compare_node(const void *a, const void *b);
void free_node(node_t *node);
node_t *create_node(const char *key, int value);

#endif
