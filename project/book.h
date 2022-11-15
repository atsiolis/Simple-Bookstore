#ifndef BOOK_H
#define BOOK_H

typedef struct book
{
    char *title;
    int release_date;
    float price;
}book_t;

typedef struct books_array
{
    book_t *array;
    int capacity;
    int size;
}books_array_t;

void init_book(books_array_t *b, int cap);
void load_book_logs(books_array_t *b);
void swap_books(book_t *a, book_t *b);
void add_book(books_array_t *b, authors_array_t *au, writes_array_t *wr);
void print_books(books_array_t *b);
void save_book_logs(books_array_t *b);
void free_books_array(books_array_t *b);
#endif