#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "author.h"
#define SIZE 20

//intialize the author struct
void init_author(authors_array_t *au, int cap)      
{
    au->array = malloc(cap * sizeof(author_t)); //allocate memory for the author struct
    au->capacity = cap;                         //set capacity to given value
    au->size = 0;                               //set size to 0
}

//load the authors from the file
void load_author_logs(authors_array_t *au)
{
    int i;
    char line[100];
    char *token;
    FILE *fp;

    if ((fp = fopen("author_logs.txt", "r")) == NULL)       //open the file
    {                                                
        printf("Author logs not found. Created file.\n");   //if file not found, create it
        fp = fopen("author_logs.txt", "w");                 
        fclose(fp);
        return;
    }
    fgets(line, 100, fp);                   //read first line to get the number of authors
    token = strtok(line, "\n\0");           //tokenize the line            
    au->size = atoi(token);                 //set the size to the number of authors
    token = NULL;                           //set token to NULL to reset it

    for (i = 0; i < au->size; i++)
    {
        if (i == au->capacity)
        {
            au->capacity *= 2;        //if the array is full, double the capacity
            au->array = realloc(au->array, au->capacity * sizeof(author_t)); //reallocate memory
        }

        fgets(line, 100, fp);                   //read the next line
        token = strtok(line, "\n\0");           //tokenize the line
        au->array[i].writer_id = atoi(token);   //set the writer id to the token
        token = NULL;                           //set token to NULL to reset it

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");                       //same as above
        au->array[i].surname = malloc(strlen(token) + 1);   //allocate enough memory for the surname plus 1 for the null terminator 
        strcpy(au->array[i].surname, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        au->array[i].name = malloc(strlen(token) + 1);      //same as above
        strcpy(au->array[i].name, token);
        token = NULL;

        fgets(line, 100, fp);
        token = strtok(line, "\n\0");
        au->array[i].num_of_books = atof(token);        //same as above
        token = NULL;
    }
    fclose(fp);
}


//manually add a new author to the array
void add_author(authors_array_t *au)
{
    int i;
    char surname[SIZE];
    time_t t;
    srand((unsigned)time(&t));              //seed the random number generator
    int id = rand() % 1000 + 1;             //generate a random number between 1 and 1001

    if (au->size == au->capacity)
    {
        au->capacity *= 2;              //if the array is full, double the capacity
        au->array = realloc(au->array, au->capacity * sizeof(author_t));        //reallocate memory
    }

    au->array[au->size].surname = malloc(SIZE * sizeof(char));      //allocate memory for the surname
    au->array[au->size].name = malloc(SIZE * sizeof(char));         //allocate memory for the name

    bool a = true;
    while (a == true)
    {
        a = false;
        for (i = 0; i < au->size; i++)
        {
            if (id == au->array[i].writer_id)       //if the id is already in use, generate a new one
            {
                id = rand() % 1000 + 1;            //generate a new id
                a = true;                        //set a to true to repeat the loop
            }
        }
    }

    printf("Enter surname: ");       //get the surname from the user 
    scanf("%s", surname);                       
    if (author_exists(au, surname) != 0)                
    {
        printf("Author already exists.\n");             //if the author already exists, notify the user and return
        return;
    }
    strcpy(au->array[au->size].surname, surname);       
    au->array[au->size].writer_id = id;                 
    printf("Writer id: %d \n", id);                     
    printf("Enter name: ");                             
    scanf("%s", au->array[au->size].name);              
    au->array[au->size].num_of_books = 0;               
    au->size++;                                         

    for (i = au->size - 1; i > 0 && au->array[i].writer_id < au->array[i - 1].writer_id; i--)   //sort the array by id
        swap_author(&au->array[i], &au->array[i - 1]);                                          //swap the elements until the array is sorted
}

//checks if the author exists and returns the id of the author
int author_exists(authors_array_t *au, char *surname)
{
    int i;
    for (i = 0; i < au->size; i++)
    {
        if (strcmp(au->array[i].surname, surname) == 0)
            return au->array[i].writer_id;
    }
    return 0;
}

//swap two authors
void swap_author(author_t *a, author_t *b)
{
    author_t temp = *a;         
    *a = *b;                
    *b = temp;      
}

//print the authors
void print_authors(authors_array_t *au)
{
    int i;
    for (i = 0; i < au->size; i++)
        printf("Writer id: %d, Surname: %s, Name: %s, Number of books: %d\n", au->array[i].writer_id, au->array[i].surname, au->array[i].name, au->array[i].num_of_books);
}

//binary search for the author position in the array by id
int bin_search_author(authors_array_t *au, int id)
{
    int left = 0;               
    int right = au->size - 1;               
    int mid;      

    while (left <= right)               
    {
        mid = (left + right) / 2;               //get the middle element
        if (au->array[mid].writer_id == id)     //if the id is found, return the position  
            return mid;
        else if (au->array[mid].writer_id < id) //if the id is smaller than the middle element, search the right half
            left = mid + 1;
        else                                    //if the id is bigger than the middle element, search the left half
            right = mid - 1;
    }
    return -1;                                  //if the id is not found, return -1
}

//add author to the array automatically- used in add_book function to add the author if he doesn't exist
void auto_add_author(authors_array_t *au, char *surname, char *name)   
{
    int i;
    time_t t;
    srand((unsigned)time(&t));
    int id = rand() % 1000 + 1;

    if (au->size == au->capacity)
    {
        au->capacity *= 2;
        au->array = realloc(au->array, au->capacity * sizeof(author_t));
    }
    au->array[au->size].surname = malloc(SIZE * sizeof(char));
    au->array[au->size].name = malloc(SIZE * sizeof(char));

    bool a = true;
    while (a == true)
    {
        a = false;
        for (i = 0; i < au->size; i++)
        {
            if (id == au->array[i].writer_id)
            {
                id = rand() % 1000 + 1;
                a = true;
            }
        }
    }

    printf("Writer id: %d \n", id);         //same as add_author function but without the user input
    au->array[au->size].writer_id = id;
    strcpy(au->array[au->size].surname, surname);
    strcpy(au->array[au->size].name, name);
    au->array[au->size].num_of_books = 1;

    au->size++;

    for (i = au->size - 1; i > 0 && au->array[i].writer_id < au->array[i - 1].writer_id; i--)
        swap_author(&au->array[i], &au->array[i - 1]);
}

//save the authors to a file
void save_author_logs(authors_array_t *au)
{
    int i;
    FILE *fp;

    if ((fp = fopen("author_logs.txt", "w")) == NULL)     //open the file in write mode
    {
        printf("Error logging authors.\n");         //if the file can't be opened, notify the user
        return;
    }

    fprintf(fp, "%d\n", au->size);      //write the size of the array to the file
    for (i = 0; i < au->size; i++)
    {
        fprintf(fp, "%d\n", au->array[i].writer_id);            //write the id to the file
        fprintf(fp, "%s\n", au->array[i].surname);              //write the surname to the file
        fprintf(fp, "%s\n", au->array[i].name);                 //write the name to the file
        fprintf(fp, "%d\n", au->array[i].num_of_books);         //write the number of books to the file
    }
    fclose(fp);
}

//free the memory of the authors array
void free_authors_array(authors_array_t *au)
{
    int i;

    for (i = 0; i < au->size; i++)     
    {
        free(au->array[i].name);        //free the name
        free(au->array[i].surname);     //free the surname
    }
    free(au->array);                    //free the array
}