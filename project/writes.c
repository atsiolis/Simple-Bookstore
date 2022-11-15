#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writes.h"

void init_writes(writes_array_t *wr, int cap)
{
    wr->array = malloc(cap * sizeof(writes_t));
    wr->capacity = cap;
    wr->size = 0; 
}

void load_writes_logs(writes_array_t *wr)
{
    int i;
    char line[100];
    char *token;
    FILE *fp;

    if((fp = fopen("writes_logs.txt", "r")) == NULL)
    {
        printf("File not found.\n");
        fp = fopen("writes_logs.txt", "w");
        fclose(fp);
        return;
    }
    fgets(line, 100, fp);
    token = strtok(line, "\n\0");
    wr->size = atoi(token);
    token = NULL;

    for(i = 0; i < wr->size; i++)
    {
        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        wr->array[i].title = malloc(strlen(token) + 1);
        strcpy(wr->array[i].title, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        wr->array[i].writer_id = atoi(token);
        token = NULL;
    }
    fclose(fp);
}

void add_writes(writes_array_t *wr, char *title, int writer_id)
{
    if(wr->size == wr->capacity)
    {
        wr->capacity *= 2;
        wr->array = realloc(wr->array, wr->capacity * sizeof(writes_t));
    }
    wr->array[wr->size].title = malloc(strlen(title) + 1);
    strcpy(wr->array[wr->size].title, title);
    wr->array[wr->size].writer_id = writer_id;
    wr->size++;
}

void print_writes(writes_array_t *wr)
{
    int i;
    for(i = 0; i< wr->size; i++)
        printf("Writer id: %d, Book title: %s", wr->array[i].writer_id, wr->array[i].title);
}

void save_writes_logs(writes_array_t *wr)
{
    int i;
    FILE *fp;

    if((fp = fopen("writes_logs.txt", "w")) == NULL)
    {
        printf("Error logging writes information.\n");
        return;
    }
    fprintf(fp, "%d\n", wr->size);
    for(i = 0; i < wr->size; i++)
    {
        fprintf(fp, "%s\n", wr->array[i].title);
        fprintf(fp, "%d\n", wr->array[i].writer_id);
    }
    fclose(fp);
}

void free_writes_array(writes_array_t *wr)
{
    int i;
    for(i = 0; i< wr->size; i++)
        free(wr->array[i].title);
    free(wr->array);
}
