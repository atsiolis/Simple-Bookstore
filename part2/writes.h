#ifndef WRITES_H
#define WRITES_H

typedef struct writes
{
    char *title;
    int writer_id;
} writes_t;

typedef struct wr_node
{
    writes_t *info;
    struct wr_node *next;
} writes_node_t;

typedef struct wr_list
{
    writes_node_t *head;
    int size;
} writes_list_t;

void init_writes_list(writes_list_t *wr);
void load_writes_list(writes_list_t *wr);
void add_writes_tail(writes_list_t *wr, writes_node_t *writes);
void add_writes(writes_list_t *wr, char *title, int writer_id);
void save_writes_list(writes_list_t *wr);
void free_writes_list(writes_list_t *wr);

#endif