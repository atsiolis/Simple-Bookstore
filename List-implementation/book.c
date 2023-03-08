#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#define SIZE 20

//initialize the book list
void init_book_list(books_list_t *b)
{

    b->head = NULL;
    b->size = 0;
}

//load the book list from the file- same as load_author_list
void load_book_list(books_list_t *b)
{
    int i;
    char line[100];
    char *token;
    book_node_t *node;
    FILE *fp;

    if ((fp = fopen("book_logs.txt", "r")) == NULL)
    {
        printf("Book logs not found. Created file.\n");
        fp = fopen("book_logs.txt", "w");
        fclose(fp);
        return;
    }
    node = (book_node_t *)malloc(sizeof(book_node_t));
    node->info = (book_t *)malloc(sizeof(book_t));
    node->info->title = (char *)malloc(SIZE *sizeof(char));
    
    fgets(line, 100, fp);
    token = strtok(line, "\n\0");
    b->size = atoi(token);
    token = NULL;

    for (i = 0; i < b->size; i++)
    {
        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        strcpy(node->info->title, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        node->info->release_date = atoi(token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        node->info->price = atof(token);
        token = NULL;

        add_book_tail(b, node);
    }
    fclose(fp);
    free(node->info->title);
    free(node->info);
    free(node);
}

//add a book to the tail of the list - same as add_author_tail
void add_book_tail(books_list_t *b, book_node_t *book)
{
    book_node_t *new_node, *cur;
    new_node = (book_node_t *)malloc(sizeof(book_node_t));
    new_node->info = (book_t *)malloc(sizeof(book_t));
    new_node->info->title = (char *)malloc(SIZE * sizeof(char));
    new_node->next = NULL;
    strcpy(new_node->info->title, book->info->title);
    new_node->info->release_date = book->info->release_date;
    new_node->info->price = book->info->price;
    if (b->head == NULL)
    {
        b->head = new_node;
        return;
    }
    cur = b->head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new_node;
}

//check if the book is in the list
int book_exists(books_list_t *b, char *title)
{
    book_node_t *book;
    book = b->head;
    while (book != NULL)
    {
        if (strcmp(book->info->title, title) == 0)
        {
            return 1;
        }
        book = book->next;
    }
    return 0;
}

//print the book list
void print_book_list(books_list_t *b)
{
    book_node_t *cur;
    cur = b->head;
    while (cur != NULL)
    {
        printf("Title: %s, Release Date: %d, Price: %f\n", cur->info->title, cur->info->release_date, cur->info->price);
        cur = cur->next;
    }
}

//save the book list to the file - same as save_author_list
void save_book_list(books_list_t *b)
{
    FILE *fp;
    book_node_t *cur;
    fp = fopen("book_logs.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    cur = b->head;
    fprintf(fp, "%d\n", b->size);

    while (cur != NULL)
    {
        fprintf(fp, "%s\n", cur->info->title);
        fprintf(fp, "%d\n", cur->info->release_date);
        fprintf(fp, "%f\n", cur->info->price);
        cur = cur->next;
    }
    fclose(fp);
}

//free the book list - same as free_author_list
void free_book_list(books_list_t *b)
{
    book_node_t *cur, *next;
    cur = b->head;
    while( cur != NULL)
    {
        next = cur->next;
        free(cur->info->title);
        free(cur->info);
        free(cur);
        cur = next;
    }
    b->head = NULL;
}