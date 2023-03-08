#ifndef BOOK_H
#define BOOK_H

typedef struct book
{
    char *title;
    int release_date;
    float price;
} book_t;

typedef struct b_node
{
    book_t *info;
    struct b_node *next;
} book_node_t;

typedef struct b_list
{
    book_node_t *head;
    int size;
} books_list_t;

void init_book_list(books_list_t *b);
void load_book_list(books_list_t *b);
void add_book_tail(books_list_t *b, book_node_t *book);
int book_exists(books_list_t *b, char *title);
void print_book_list(books_list_t *b);
void save_book_list(books_list_t *b);
void free_book_list(books_list_t *b);

#endif