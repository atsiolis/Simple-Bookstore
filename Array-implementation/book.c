#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#define SIZE 50

//initialize the book struct
void init_book(books_array_t *b, int cap)
{
    b->array = malloc(cap * sizeof(book_t));        //allocate memory for the book struct
    b->capacity = cap;                              //set capacity to given value
    b->size = 0;                                    //set size to 0
}

//load the books from the file- same as load_author_logs function
void load_book_logs(books_array_t *b)
{
    int i;
    char line[100];
    char *token;
    FILE *fp;

    if ((fp = fopen("book_logs.txt", "r")) == NULL) 
    {
        printf("Book logs not found. Created file.\n");
        fp = fopen("book_logs.txt", "w");
        fclose(fp);
        return;
    }

    fgets(line, 100, fp);
    token = strtok(line, "\n\0");
    b->size = atoi(token);
    token = NULL;

    for (i = 0; i < b->size; i++)
    {
        if (i == b->capacity)
        {
            b->capacity *= 2;
            b->array = realloc(b->array, b->capacity * sizeof(book_t));
        }

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        b->array[i].title = malloc(strlen(token) + 1);
        strcpy(b->array[i].title, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        b->array[i].release_date = atoi(token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        b->array[i].price = atof(token);
        token = NULL;
    }
    fclose(fp);
}

//checks if the book is already in the array
int book_exists(books_array_t *b, char *title)
{
    int i;
    for (i = 0; i < b->size; i++)
    {
        if (strcmp(b->array[i].title, title) == 0)
            return 1;
    }
    return 0;
}

//swap two books
void swap_book(book_t *a, book_t *b)
{
    book_t temp = *a;
    *a = *b;
    *b = temp;
}

//print the books
void print_books(books_array_t *b)
{
    int i;

    for (i = 0; i < b->size; i++)
        printf("Release year: %d, Title: %s, Price: %f\n", b->array[i].release_date, b->array[i].title, b->array[i].price);
}

//search for a book by title and return the position in the array
int search_book(books_array_t *b, char *title)
{
    int i;

    for (i = 0; i < b->size; i++)
    {
        if (strcmp(b->array[i].title, title) == 0)
            return i;
    }
    return -1;
}

//save the books to the file- same as save_author_logs function
void save_book_logs(books_array_t *b)
{
    int i;
    FILE *fp;

    if ((fp = fopen("book_logs.txt", "w")) == NULL)
    {
        printf("Error logging books.\n");
        return;
    }
    fprintf(fp, "%d\n", b->size);

    for (i = 0; i < b->size; i++)
    {
        fprintf(fp, "%s\n", b->array[i].title);
        fprintf(fp, "%d\n", b->array[i].release_date);
        fprintf(fp, "%f\n", b->array[i].price);
    }
    fclose(fp);
}

//free the memory allocated for the books array
void free_books_array(books_array_t *b)
{
    int i;
    for (i = 0; i < b->size; i++)
    {
        free(b->array[i].title);
    }
    free(b->array);
}