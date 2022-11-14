#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#define SIZE 50

void load_book_logs(books_array_t *b)
{
    int i;
    char line[100];
    char *token;
    FILE *fp;

    if((fp = fopen("book_logs.txt", "r")) == NULL)
    {
        printf("File not found.\n");
        fp = fopen("book_logs.txt", "w");
        fclose(fp);
        return;
    }
    fgets(line, 100, fp);
    token = strtok(line, "\n\0");
    b->size = atoi(token);
    token = NULL;
    
    for( i = 0; i < b->size; i++)
    {
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

void save_book_logs(books_array_t *b)
{
    int i;
    FILE *fp;

    if ((fp = fopen("book_logs.txt", "w")) == NULL)
    {
        fprintf(stderr, "Error logging books.\n");
        return;
    }
    fprintf(fp, "%d\n",b->size);
    for( i = 0; i < b->size; i++)
    {
        fprintf(fp, "%s\n", b->array[i].title);
        fprintf(fp, "%d\n", b->array[i].release_date);
        fprintf(fp, "%f\n", b->array[i].price);
    }
    fclose(fp);
}

void free_books_array(books_array_t *b)
{
    int i;
    for(i = 0; i < b->size; i++)
    {
        free(b->array[i].title);
    }
    free(b->array);
}