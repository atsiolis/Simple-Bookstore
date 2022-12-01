#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writes.h"
#define SIZE 20

//initialize the writes list
void init_writes_list(writes_list_t *wr)
{

    wr->head = NULL;
    wr->size = 0;
}

//load the writes list from the file- same as load_book_list
void load_writes_list(writes_list_t *wr)
{
    int i;
    char line[100];
    char *token;
    writes_node_t *node;
    FILE *fp;

    if ((fp = fopen("writes_logs.txt", "r")) == NULL)
    {
        printf("Author-book info (writes) not found. Created file.\n");
        fp = fopen("writes_logs.txt", "w");
        fclose(fp);
        return;
    }
    node = (writes_node_t *)malloc(sizeof(writes_node_t));
    node->info = (writes_t *)malloc(sizeof(writes_t));
    node->info->title = (char *)malloc(SIZE *sizeof(char));
    
    fgets(line, 100, fp);
    token = strtok(line, "\n\0");
    wr->size = atoi(token);
    token = NULL;

    for (i = 0; i < wr->size; i++)
    {
        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        strcpy(node->info->title, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        node->info->writer_id = atoi(token);
        token = NULL;

        add_writes_tail(wr, node);
    }
    fclose(fp);
    free(node->info->title);
    free(node->info);
    free(node);
}

//add a writes node to the tail of the list - same as add_book_tail
void add_writes_tail(writes_list_t *wr, writes_node_t *writes)
{
    writes_node_t *new_node, *cur;
    new_node = (writes_node_t *)malloc(sizeof(writes_node_t));
    new_node->info = (writes_t *)malloc(sizeof(writes_t));
    new_node->info->title = (char *)malloc(SIZE * sizeof(char));
    new_node->next = NULL;
    strcpy(new_node->info->title, writes->info->title);
    new_node->info->writer_id = writes->info->writer_id;
    if (wr->head == NULL)
    {
        wr->head = new_node;
        return;
    }
    cur = wr->head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new_node;
}

//add a writes node to the list
void add_writes(writes_list_t *wr, char *title, int writer_id)
{
    writes_node_t *new_node, *cur, *prev;
    new_node = (writes_node_t *)malloc(sizeof(writes_node_t));
    new_node->info = (writes_t *)malloc(sizeof(writes_t));
    new_node->info->title = (char *)malloc(SIZE * sizeof(char));
    new_node->next = NULL;
    strcpy(new_node->info->title, title);
    new_node->info->writer_id = writer_id;

    wr->size++;

    cur = wr->head;
    prev = NULL;

    if (cur == NULL)
    {
        new_node->next = wr->head;
        wr->head = new_node;
        return;
    }
    while ((cur != NULL) && (cur->info->writer_id < writer_id))
    {
        prev = cur;                 //sort by writer_id
        cur = cur->next;
    }
    while ((cur != NULL) && (strcmp(new_node->info->title, cur->info->title) > 0) && (cur->info->writer_id == writer_id))
    {
        prev = cur;
        cur = cur->next;            //sort by title until writer_id changes
    }
    if (cur == wr->head)
    {
        new_node->next = wr->head;
        wr->head = new_node;
        return;
    }

    prev->next = new_node;
    new_node->next = cur;
}

//save the writes list to the file - same as save_book_list
void save_writes_list(writes_list_t *wr)
{
    FILE *fp;
    writes_node_t *cur;
    fp = fopen("writes_logs.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    cur = wr->head;
    fprintf(fp, "%d\n", wr->size);

    while (cur != NULL)
    {
        fprintf(fp, "%s\n", cur->info->title);
        fprintf(fp, "%d\n", cur->info->writer_id);
        cur = cur->next;
    }
    fclose(fp);
}

//free the writes list - same as free_book_list
void free_writes_list(writes_list_t *wr)
{
    writes_node_t *cur, *next;
    cur = wr->head;
    while( cur != NULL)
    {
        next = cur->next;
        free(cur->info->title);
        free(cur->info);
        free(cur);
        cur = next;
    }
    wr->head = NULL;
}