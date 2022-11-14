#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "author.h"
#define SIZE 20


void load_author_logs(authors_array_t *au)
{
    int i;
    char line[100];
    char *token;
    FILE *fp;

    if((fp = fopen("author_logs.txt", "r")) == NULL)
    {
        fprintf(stderr, "File not found.\n");
        fp = fopen("author_logs.txt", "w");
        fclose(fp);
        return;
    }
    fgets(line, 100, fp);
    token = strtok(line, "\n\0");
    au->size = atoi(token);
    token = NULL;

    for( i = 0; i < au->size; i++)
    {
        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        au->array[i].writer_id = atoi(token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        au->array[i].surname = malloc(strlen(token) + 1);
        strcpy(au->array[i].surname, token);
        token = NULL;

        
        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        au->array[i].name = malloc(strlen(token) + 1);
        strcpy(au->array[i].name, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        au->array[i].num_of_books = atof(token);
        token = NULL;
    } 
    fclose(fp);
}

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

void save_author_logs(authors_array_t *au)
{
    int i;
    FILE *fp;
    
    if((fp = fopen("author_logs.txt", "w")) == NULL)
    {
        fprintf(stderr, "Error logging authors.\n");
        return;
    }
    fprintf(fp, "%d\n",au->size);
    for(i = 0; i < au->size; i++)
    {
        fprintf(fp, "%d\n", au->array[i].writer_id);
        fprintf(fp, "%s\n", au->array[i].surname);
        fprintf(fp, "%s\n", au->array[i].name);
        fprintf(fp, "%d\n", au->array[i].num_of_books);
    }
    fclose(fp);
}