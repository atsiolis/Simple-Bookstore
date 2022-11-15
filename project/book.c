#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writes.h"
#include "author.h"
#include "book.h"
#define SIZE 50

void init_book(books_array_t *b, int cap)
{
    b->array = malloc(cap * sizeof(book_t));
    b->capacity = cap;
    b->size = 0;
}

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

void swap_books(book_t *a, book_t *b)
{
    book_t temp = *a;
    *a = *b;
    *b = temp;
}

void add_book(books_array_t *b, authors_array_t *au, writes_array_t *wr)
{
    int i,num_of_authors;
    char surname[20], name[20];
    int au_ex_id;
    
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
    printf("Number of authors: ");
    scanf("%d", &num_of_authors);

    for(i = 0; i < num_of_authors; i++)
    {
        
        printf("Enter author's surname: ");
        scanf("%s", surname);
        au_ex_id=author_exists(au, surname);
        if(au_ex_id!=0)
        {
            add_writes(wr, b->array[b->size].title, au_ex_id);
            au->array[bin_search_author(au,au_ex_id)].num_of_books++;
        }
        else
        {
            printf("Author does not exist.\n");
            printf("Enter author's name: ");
            scanf("%s", name);
            auto_add_author(au, surname, name);
            add_writes(wr, b->array[b->size].title, author_exists(au, surname));
        }
    }

    b->size++;

    for(i = b->size-1; i > 0 && strcmp(b->array[i].title, b->array[i-1].title) < 0; i--)
    {
        swap_books(&b->array[i], &b->array[i-1]);
    }
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
        printf("Error logging books.\n");
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

