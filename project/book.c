#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#define SIZE 50

void init_book(books_array_t *b, int cap)
{
    b->array = malloc(cap * sizeof(book_t));
    b->capacity = cap;
    b->size = 0;
}

void add_book(books_array_t *b)
{
    if(b->size == b->capacity)
    {
        b->capacity *= 2;
        b->array = realloc(b->array, b->capacity * sizeof(book_t));
    }
    b->array[b->size].title = malloc(SIZE * sizeof(char));
    printf("Enter release year: ");
    scanf("%d", &b->array[b->size].release_date);
    printf("Enter title: ");
    scanf("%s", b->array[b->size].title);
    printf("Enter price: ");
    scanf("%f", &b->array[b->size].price);

    b->size++;
}

void print_books(books_array_t *b)
{
    int i;
    for(i = 0; i < b->size; i++)
        printf("Release year: %d, Title: %s, Price: %f\n", b->array[i].release_date, b->array[i].title, b->array[i].price);
}