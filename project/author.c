#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "author.h"
#define SIZE 20


void init_author(authors_array_t *au, int cap)
{
    au->array = malloc(cap * sizeof(author_t)); 
    au->capacity = cap;
    au->size = 0;
}

void add_author(authors_array_t *au)
{
    if(au->size == au->capacity)
    {
        au->capacity *= 2;
        au->array = realloc(au->array, au->capacity * sizeof(author_t));
    }
    au->array[au->size].surname= malloc(SIZE * sizeof(char));
    au->array[au->size].name= malloc(SIZE * sizeof(char));
    printf("Enter writer id: ");
    scanf("%d", &au->array[au->size].writer_id);
    printf("Enter surname: ");
    scanf("%s", au->array[au->size].surname);
    printf("Enter name: ");
    scanf("%s", au->array[au->size].name);
    au->array[au->size].num_of_books = 0;
    au->size++;
}

void print_authors(authors_array_t *au)
{
    int i;
    for(i = 0; i < au->size; i++)
        printf("Writer id: %d, Surname: %s, Name: %s, Number of books: %d\n", au->array[i].writer_id,  au->array[i].surname, au->array[i].name, au->array[i].num_of_books);
        
}