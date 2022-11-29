#ifndef AUTHOR_H
#define AUTHOR_H

typedef struct author
{
    int writer_id;
    char *surname;
    char *name;
    int num_of_books;
} author_t;

typedef struct authors_array
{
    author_t *array;
    int capacity;
    int size;
} authors_array_t;

void init_author(authors_array_t *au, int cap);
void load_author_logs(authors_array_t *au);
void add_author(authors_array_t *au);
int author_exists(authors_array_t *au, char *surname);
void swap_author(author_t *a, author_t *b);
void print_authors(authors_array_t *au);
int bin_search_author(authors_array_t *au, int id);
void auto_add_author(authors_array_t *au, char *surname, char *name);
void save_author_logs(authors_array_t *au);
int compare_author(const void *a, const void *b);
void free_authors_array(authors_array_t *au);
#endif