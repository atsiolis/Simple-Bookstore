#ifndef WRITES_H
#define WRITES_H

typedef struct writes
{
    char *title;
    int writer_id;
} writes_t;

typedef struct writes_array
{
    writes_t *array;
    int capacity;
    int size;
} writes_array_t;

void init_writes(writes_array_t *wr, int cap);
void load_writes_logs(writes_array_t *wr);
void add_writes(writes_array_t *wr, char *title, int writer_id);
void swap_writes(writes_t *a, writes_t *b);
int bin_search_writes(writes_array_t *wr, int writer_id);
int search_writes(writes_array_t *wr, char *title);
void save_writes_logs(writes_array_t *wr);
void free_writes_array(writes_array_t *wr);

#endif