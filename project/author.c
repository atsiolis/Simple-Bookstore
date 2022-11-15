#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h> 
#include <time.h>
#include "author.h"
#define SIZE 20

void init_author(authors_array_t *au, int cap)
{
    au->array = malloc(cap * sizeof(author_t)); 
    au->capacity = cap;
    au->size = 0;
}

void load_author_logs(authors_array_t *au)
{
    int i;
    char line[100];
    char *token;
    FILE *fp;

    if((fp = fopen("author_logs.txt", "r")) == NULL)
    {
        printf("File not found.\n");
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

void swap_author(author_t *a, author_t *b)
{
    author_t temp = *a;
    *a = *b;
    *b = temp;
}

void add_author(authors_array_t *au)
{
    int i;
    time_t t;
    srand((unsigned) time(&t));
    int id = rand() %1000;
    if(au->size == au->capacity)
    {
        au->capacity *= 2;
        au->array = realloc(au->array, au->capacity * sizeof(author_t));
    }
    au->array[au->size].surname= malloc(SIZE * sizeof(char));
    au->array[au->size].name= malloc(SIZE * sizeof(char));

    bool a = true;
    while (a == true)
    {
        a = false;
        for(i = 0; i < au->size; i++)
        {
            if(id == au->array[i].writer_id)
            {    
                id = rand() %1000;
                a = true;
            }
        }
    }
    
    au->array[au->size].writer_id = id;
    printf("Writer id: %d \n", id);
    printf("Enter surname: ");
    scanf("%s", au->array[au->size].surname);
    printf("Enter name: ");
    scanf("%s", au->array[au->size].name);
    au->array[au->size].num_of_books = 0;
    au->size++;
    
    for(i = au->size - 1; i > 0 && au->array[i].writer_id < au->array[i - 1].writer_id; i--)
        swap_author(&au->array[i], &au->array[i - 1]);
}

void auto_add_author(authors_array_t *au,char *surname, char *name)
{
    int i;
    time_t t;
    srand((unsigned) time(&t));
    int id = rand() %1000;
    if(au->size == au->capacity)
    {
        au->capacity *= 2;
        au->array = realloc(au->array, au->capacity * sizeof(author_t));
    }
    au->array[au->size].surname= malloc(SIZE * sizeof(char));
    au->array[au->size].name= malloc(SIZE * sizeof(char));

    bool a = true;
    while (a == true)
    {
        a = false;
        for(i = 0; i < au->size; i++)
        {
            if(id == au->array[i].writer_id)
            {    
                id = rand() %1000;
                a = true;
            }
        }
    }

    printf("Writer id: %d \n", id);
    au->array[au->size].writer_id = id;
    strcpy(au->array[au->size].surname, surname);
    strcpy(au->array[au->size].name, name);
    au->array[au->size].num_of_books = 1;

    au->size++;
    
    for(i = au->size - 1; i > 0 && au->array[i].writer_id < au->array[i - 1].writer_id; i--)
        swap_author(&au->array[i], &au->array[i - 1]);
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
        printf("Error logging authors.\n");
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

void free_authors_array(authors_array_t *au)
{
    int i;
    for(i = 0; i < au->size; i++)
    {
        free(au->array[i].name);
        free(au->array[i].surname);
    }
    free(au->array);
}


int compare_author(const void *a, const void *b)
{
    author_t *x = (author_t *)a;
    author_t *y = (author_t *)b;
    return x->writer_id - y->writer_id;
}

int author_exists(authors_array_t *au, char *surname)
{
    int i;
    for(i = 0; i < au->size; i++)
    {
        if(strcmp(au->array[i].surname, surname) == 0)
            return au->array[i].writer_id;
    }
    return 0;
}

int bin_search_author(authors_array_t *au, int id)
{
    int left = 0;
    int right = au->size - 1;
    int mid;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(au->array[mid].writer_id == id)
            return mid;
        else if(au->array[mid].writer_id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}