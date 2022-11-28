#ifndef WRITES_H
#define WRITES_H


typedef struct writes
{
    char *title;
    int writer_id;
}writes_t;

typedef struct wr_node
{
    writes_t *info;
    struct wr_node *next;
}writes_node_t;

typedef struct wr_list
{
    writes_node_t *head;
    int size;
}writes_list_t;

#endif