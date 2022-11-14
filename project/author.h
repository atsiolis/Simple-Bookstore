#ifndef AUTHOR_H
#define AUTHOR_H

typedef struct author
{
    int writer_id;
    char *surname;
    char *name;
    int num_of_books;
}author_t;

typedef struct authors_array
{
    author_t *array;
    int capacity;
    int size;
}authors_array_t;

void load_author_logs(authors_array_t *au); //dk if placed correctly- based on students from codes_2019
void init_author(authors_array_t *au, int cap);
void add_author(authors_array_t *au);
void print_authors(authors_array_t *au);
void save_author_logs(authors_array_t *au);

#endif