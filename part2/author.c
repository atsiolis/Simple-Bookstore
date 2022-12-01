#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "author.h"
#define SIZE 20

//initialize the author list
void init_author_list(authors_list_t *au)
{
    au->head = NULL;    //set head to NULL
    au->size = 0;       //set size to 0 
}

//load the author list from the file 
void load_author_list(authors_list_t *au)
{
    int i;
    char line[100];
    char *token;
    author_node_t *node;
    FILE *fp;

    if ((fp = fopen("author_logs.txt", "r")) == NULL)
    {
        printf("Author logs not found. Created file.\n");       //if file not found, create file
        fp = fopen("author_logs.txt", "w");
        fclose(fp);
        return;
    }
    node = (author_node_t *)malloc(sizeof(author_node_t));      //allocate memory for the node
    node->info = (author_t *)malloc(sizeof(author_t));          //allocate memory for the author info
    node->info->name = (char *)malloc(SIZE * sizeof(char));     //allocate memory for the name
    node->info->surname = (char *)malloc(SIZE * sizeof(char));  //allocate memory for the surname
    
    fgets(line, 100, fp);
    token = strtok(line, "\n\0");                    //get the first line of the file
    au->size = atoi(token);             //convert the string to int and set it to the size
    token = NULL;               //set token to NULL

    for (i = 0; i < au->size; i++)
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
    free(node->info->surname);      //free the memory of the node used to load the file
    free(node->info->name);
    free(node->info);
    free(node);
}

//add new author to the end of the author list- used in the load_author_list function
void add_author_tail(authors_list_t *au, author_node_t *author)
{
    author_node_t *new_node, *cur;          //create new node and current node
    new_node = (author_node_t *)malloc(sizeof(author_node_t));      
    new_node->info = (author_t *)malloc(sizeof(author_t));
    new_node->info->surname = (char *)malloc(SIZE * sizeof(char));
    new_node->info->name = (char *)malloc(SIZE * sizeof(char));
    new_node->next = NULL;
    strcpy(new_node->info->surname, author->info->surname);         //copy the info to the new node
    strcpy(new_node->info->name, author->info->name);
    new_node->info->writer_id = author->info->writer_id;
    new_node->info->num_of_books = author->info->num_of_books;
    if (au->head == NULL)
    {
        au->head = new_node;                    //if the list is empty, set the new node to the head
        return;
    }
    cur = au->head;
    while (cur->next != NULL)
    {
        cur = cur->next;                    //go to the end of the list
    }
    cur->next = new_node;                   //set the new node to the end of the list
}

//add new author to the author list
void add_author(authors_list_t *au)
{
    author_node_t *prev, *cur, *new_node;
    time_t t;
    char surname[20];
    srand((unsigned)time(&t));
    int id = rand() % 1000 + 1;         //generate random id
    new_node = (author_node_t *)malloc(sizeof(author_node_t));
    new_node->info = (author_t *)malloc(sizeof(author_t));
    new_node->info->surname = (char *)malloc(SIZE * sizeof(char));
    new_node->info->name = (char *)malloc(SIZE * sizeof(char));
    new_node->next = NULL;

    bool a = true;
    while (a == true)
    {
        a = false;
        for (cur = au->head; cur != NULL; cur = cur->next)
        {
            if (cur->info->writer_id == id)
            {
                id = rand() % 1000 + 1;                     //if the id is already used, generate new id
                a = true;
            }
        }
    }

    printf("Enter surname: ");
    scanf("%s", surname);
    if (author_exists(au, surname) != 0)
    {
        printf("Author already exists.\n");             //if the author already exists, return
        return;
    }
    strcpy(new_node->info->surname, surname);

    new_node->info->writer_id = id;
    printf("Enter name: ");
    scanf("%s", new_node->info->name);                 
    new_node->info->num_of_books = 0;
    au->size++;

    prev = NULL;
    cur = au->head;

    if (cur == NULL)
    {
        new_node->next = au->head;              //if the list is empty, set the new node to the head
        au->head = new_node;
        return;
    }

    while ((cur != NULL) && (cur->info->writer_id < new_node->info->writer_id))
    {
        prev = cur;
        cur = cur->next;                //go to the correct position in the list based on the id
    }
    if (cur == au->head)
    {
        new_node->next = au->head;
        au->head = new_node;                //if the new node is the first in the list, set it to the head
        return;
    }
    prev->next = new_node;              //set the new node to the correct position
    new_node->next = cur;
}

//check if the author already exists and return the id
int author_exists(authors_list_t *au, char *surname)
{
    author_node_t *cur;
    for (cur = au->head; cur != NULL; cur = cur->next)
    {
        if (strcmp(cur->info->surname, surname) == 0)
            return cur->info->writer_id;
    }
    return 0;
}

//print the author list
void print_author_list(authors_list_t *au)
{
    author_node_t *cur;
    cur = au->head;
    while (cur != NULL)
    {
        printf("Surname: %s, Name: %s, ID: %d, Number of books: %d\n", cur->info->surname, cur->info->name, cur->info->writer_id, cur->info->num_of_books);
        cur = cur->next;
    }
}

//add new author automatically- usedin the add_book function
void auto_add_author(authors_list_t *au, char *surname, char *name)
{
    author_node_t *prev, *cur, *new_node;
    time_t t;
    srand((unsigned)time(&t));
    int id = rand() % 1000 + 1;
    new_node = (author_node_t *)malloc(sizeof(author_node_t));
    new_node->info = (author_t *)malloc(sizeof(author_t));
    new_node->info->surname = (char *)malloc(SIZE * sizeof(char));
    new_node->info->name = (char *)malloc(SIZE * sizeof(char));
    new_node->next = NULL;

    bool a = true;
    while (a == true)
    {
        a = false;
        for (cur = au->head; cur != NULL; cur = cur->next)
        {
            if (cur->info->writer_id == id)
            {
                id = rand() % 1000 + 1;                 //if the id is already used, generate new id
                a = true;
            }
        }
    }
    printf("Writer id: %d \n", id);
    strcpy(new_node->info->surname, surname);
    new_node->info->writer_id = id;
    strcpy(new_node->info->name, name);
    new_node->info->num_of_books = 1;
    au->size++;

    prev = NULL;
    cur = au->head;

    if (cur == NULL)
    {
        new_node->next = au->head;
        au->head = new_node;            //if the list is empty, set the new node to the head
        return;
    }

    while ((cur != NULL) && (cur->info->writer_id < new_node->info->writer_id))
    {
        prev = cur;
        cur = cur->next;                //go to the correct position in the list based on the id
    }
    if (cur == au->head)
    {
        new_node->next = au->head;
        au->head = new_node;                //if the new node is the first in the list, set it to the head
        return;
    }
    prev->next = new_node;              //set the new node to the correct position
    new_node->next = cur;
}

//save the author list to a file
void save_author_list(authors_list_t *au)
{
    FILE *fp;
    author_node_t *cur;
    fp = fopen("author_logs.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    cur = au->head;
    fprintf(fp, "%d\n", au->size);

    while (cur != NULL)
    {
        fprintf(fp, "%d\n", cur->info->writer_id);
        fprintf(fp, "%s\n", cur->info->surname);
        fprintf(fp, "%s\n", cur->info->name);
        fprintf(fp, "%d\n", cur->info->num_of_books);
        cur = cur->next;
    }
    fclose(fp);
}

//free the author list
void free_author_list(authors_list_t *au)
{
    author_node_t *cur, *next;
    cur = au->head;
    while( cur != NULL)
    {
        next = cur->next;
        free(cur->info->surname);
        free(cur->info->name);
        free(cur->info);
        free(cur);
        cur = next;
    }
    au->head = NULL;
}