#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h> 
#include "author.h"
#define SIZE 20

void init_author_list(authors_list_t *au)
{

    au->head = NULL;
    au->size = 0;
}

void load_author_list(authors_list_t *au)
{
    int i;
    char line[100];
    char *token;
    author_node_t *node;
    FILE *fp;

    if((fp = fopen("author_logs.txt", "r")) == NULL)
    {
        printf("Author logs not found. Created file.\n");
        fp = fopen("author_logs.txt", "w");
        fclose(fp);
        return;
    }
    node= (author_node_t *)malloc(sizeof(author_node_t));
    node->info = (author_t *)malloc(sizeof(author_t));
    node->info->name = (char *)malloc(SIZE * sizeof(char));
    node->info->surname = (char *)malloc(SIZE * sizeof(char));
    fgets(line, 100, fp);
    token = strtok(line, "\n\0");
    au->size = atoi(token);
    token = NULL;

    for(i = 0; i < au->size; i++)
    {
        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        node->info->writer_id = atoi(token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        strcpy(node->info->surname, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        strcpy(node->info->name, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        node->info->num_of_books = atoi(token);
        token = NULL;  

        add_author_tail(au, node);
              
    }
    fclose(fp);
}

void add_author(authors_list_t *au)
{
    author_node_t *prev,*cur, *new_node;
    time_t t;
    char surname[20];
    srand((unsigned) time(&t));
    int id = rand() %1000+1;
    printf("hello");
    new_node = (author_node_t *)malloc(sizeof(author_node_t));
    new_node->info = (author_t *)malloc(sizeof(author_t));
    new_node->info->surname = (char *)malloc(SIZE * sizeof(char));
    new_node->info->name = (char *)malloc(SIZE * sizeof(char));
    new_node->next = NULL;

    bool a = true;
    while(a==true)
    {
        a=false;
        for(cur = au->head; cur != NULL; cur = cur->next)
        {
            if(cur->info->writer_id == id)
            {
                id = rand() %1000+1;
                a=true;
            }
        }
    }

    printf("Enter surname: ");
    scanf("%s", surname);
    if(author_exists(au, surname) != 0)
    {
        printf("Author already exists.\n");
        return;
    }
    strcpy(new_node->info->surname, surname);
    
    new_node->info->writer_id = id;
    printf("Enter name: ");
    scanf("%s", new_node->info->name);
    new_node->info->num_of_books = 0;
    au->size++;

    prev=NULL;
    cur=au->head;

    if (cur == NULL)
    {
        new_node->next=au->head;
        au->head = new_node;
        return;
    }
    
    while((cur != NULL) && (cur->info->writer_id < new_node->info->writer_id))
    {
        prev = cur;
        cur = cur->next;
    }
    if(cur == au->head)
    {
        new_node->next = au->head;
        au->head = new_node;
        return;
    }
    prev->next = new_node;
    new_node->next = cur;
    
}
int author_exists(authors_list_t *au, char *surname)
{
    author_node_t *cur;
    for(cur = au->head; cur != NULL; cur = cur->next)
    {
        if(strcmp(cur->info->surname, surname) == 0)
            return 1;
    }
    return 0;
}
void print_author_list(authors_list_t *au)
{
    author_node_t *cur;
    cur=au->head;
    while(cur != NULL)
    {
        printf("Surname: %s, Name: %s, ID: %d, Number of books: %d\n", cur->info->surname, cur->info->name, cur->info->writer_id, cur->info->num_of_books);
        cur = cur->next;
    }
}


void add_author_tail(authors_list_t *au, author_node_t *author)
{
    author_node_t *new_node, *cur;
    new_node = (author_node_t *)malloc(sizeof(author_node_t));
    new_node->info = (author_t *)malloc(sizeof(author_t));
    new_node->info->surname = (char *)malloc(SIZE * sizeof(char));
    new_node->info->name = (char *)malloc(SIZE * sizeof(char));
    new_node->next = NULL;
    strcpy(new_node->info->surname, author->info->surname);
    strcpy(new_node->info->name, author->info->name);
    new_node->info->writer_id = author->info->writer_id;
    new_node->info->num_of_books = author->info->num_of_books;
    if(au->head == NULL)
    {
        au->head = new_node;
        return;
    }
    cur = au->head;
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new_node;
}

void save_author_list(authors_list_t *au)
{
    FILE *fp;
    author_node_t *cur;
    fp = fopen("author_logs.txt", "w");
    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    cur=au->head;
    fprintf(fp, "%d\n", au->size);

    while(cur != NULL)
    {
        fprintf(fp, "%d\n", cur->info->writer_id);
        fprintf(fp, "%s\n", cur->info->surname);
        fprintf(fp, "%s\n", cur->info->name);
        fprintf(fp, "%d\n", cur->info->num_of_books);
        cur = cur->next;
    }
    fclose(fp);
}