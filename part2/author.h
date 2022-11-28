#ifndef AUTHOR_H
#define AUTHOR_H

typedef struct author
{
    int writer_id;
    char *surname;
    char *name;
    int num_of_books;
}author_t;

typedef struct au_node
{
    author_t *info;
    struct au_node *next;
}author_node_t;

typedef struct au_list
{
    author_node_t *head;
    int size;
}authors_list_t;

void init_author_list(authors_list_t *au);
void load_author_list(authors_list_t *au);
void add_author(authors_list_t *au);
void print_author_list(authors_list_t *au);
int author_exists(authors_list_t *au, char *surname);
void add_author_tail(authors_list_t *au, author_node_t *author);
void save_author_list(authors_list_t *au);

#endif