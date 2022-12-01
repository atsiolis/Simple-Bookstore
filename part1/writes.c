#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writes.h"

//initialize the writes struct- same as init_book function and init_author function
void init_writes(writes_array_t *wr, int cap)
{
    wr->array = malloc(cap * sizeof(writes_t));
    wr->capacity = cap;
    wr->size = 0;
}

//load the writes from the file- same as load_book_logs function and load_author_logs function
void load_writes_logs(writes_array_t *wr)
{
    int i;
    char line[100];
    char *token;
    FILE *fp;

    if ((fp = fopen("writes_logs.txt", "r")) == NULL)
    {
        printf("Author-book info (writes) not found. Created file.\n");
        fp = fopen("writes_logs.txt", "w");
        fclose(fp);
        return;
    }

    fgets(line, 100, fp);
    token = strtok(line, "\n\0");
    wr->size = atoi(token);
    token = NULL;

    for (i = 0; i < wr->size; i++)
    {
        if (i == wr->capacity)
        {
            wr->capacity *= 2;
            wr->array = realloc(wr->array, wr->capacity * sizeof(writes_t));
        }

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

//add new author-book info to the writes array
void add_writes(writes_array_t *wr, char *title, int writer_id) 
{
    int i;

    if (wr->size == wr->capacity)
    {
        wr->capacity *= 2;
        wr->array = realloc(wr->array, wr->capacity * sizeof(writes_t));
    }

    wr->array[wr->size].title = malloc(strlen(title) + 1);
    strcpy(wr->array[wr->size].title, title);
    wr->array[wr->size].writer_id = writer_id;
    wr->size++;

    int temp = wr->size;

    for (i = wr->size - 1; i > 0 && wr->array[i].writer_id < wr->array[i - 1].writer_id; i--)
    {
        swap_writes(&wr->array[i], &wr->array[i - 1]);  //sort based on the id 
        temp = i - 1;                                   //save the position of the new element
    }

    for (i = temp; i > 0; i--)                          //sort based on the title starting from the position of the new element
    {
        if (wr->array[i].writer_id == wr->array[i - 1].writer_id)           
        {
            if (strcmp(wr->array[i].title, wr->array[i - 1].title) < 0)
            {
                swap_writes(&wr->array[i], &wr->array[i - 1]);
            }
        }
    }
}

//swap two writes elements
void swap_writes(writes_t *a, writes_t *b)
{
    writes_t temp = *a;
    *a = *b;
    *b = temp;
}

//search for the position of the author-book info in the array based on the id and return the position
int bin_search_writes(writes_array_t *wr, int writer_id)
{
    int low = 0;
    int high = wr->size - 1;
    int mid;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (wr->array[mid].writer_id == writer_id)
            return mid;
        else if (wr->array[mid].writer_id < writer_id)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

//search for the position of the author-book info in the array based on the title and return the position
int search_writes(writes_array_t *wr, char *title)
{
    int i;

    for (i = 0; i < wr->size; i++)
    {
        if (strcmp(wr->array[i].title, title) == 0)
            return i;
    }
    return -1;
}

//save the writes array to the file- same as save_book_logs function and save_author_logs function
void save_writes_logs(writes_array_t *wr)
{
    int i;
    FILE *fp;

    if ((fp = fopen("writes_logs.txt", "w")) == NULL)
    {
        printf("Error logging writes information.\n");
        return;
    }
    fprintf(fp, "%d\n", wr->size);

    for (i = 0; i < wr->size; i++)
    {
        fprintf(fp, "%s\n", wr->array[i].title);
        fprintf(fp, "%d\n", wr->array[i].writer_id);
    }
    fclose(fp);
}

//free the writes array- same as free_book function and free_author function
void free_writes_array(writes_array_t *wr)
{
    int i;
    for (i = 0; i < wr->size; i++)
        free(wr->array[i].title);
    free(wr->array);
}
