#ifndef BOOK_H
#define BOOK_H


typedef struct book
{
    char *title;
    int release_date;
    float price;
}book_t;

typedef struct b_node
{
    book_t *info;
    struct b_node *next;
}book_node_t;

typedef struct b_list
{
    book_node_t *head;
    int size;
}books_list_t;


#endif