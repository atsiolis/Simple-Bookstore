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

void load_book_logs(books_array_t *b); //dk if placed correctly- based on students from codes_2019
void init_book(books_array_t *b, int cap);
void add_book(books_array_t *b);
void print_books(books_array_t *b);
void save_book_logs(books_array_t *b);
#endif