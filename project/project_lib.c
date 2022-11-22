#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writes.h"
#include "author.h"
#include "book.h"
#include "project_lib.h"


int menu()
{
    int choice;

    printf("Choose an operation:\n");
    printf("1. Insert new writer record.\n");
    printf("2. Insert new book record.\n");
    printf("3. Search a writer record.\n");
    printf("4. Search a book record. \n");
    printf("5. Delete a writer record.\n");
    printf("6. Delete a book record. \n");
    printf("7. Exit\n");
    scanf("%d", &choice);

    return choice;
}

void add_book(books_array_t *b, authors_array_t *au, writes_array_t *wr)
{
    int i,num_of_authors;
    char surname[20], name[20],temp;
    int au_ex_id;
    
    if(b->size == b->capacity)
    {
        b->capacity *= 2;
        b->array = realloc(b->array, b->capacity * sizeof(book_t));
    }
    b->array[b->size].title = malloc(50 * sizeof(char));
    printf("Enter release year: ");
    scanf("%d", &b->array[b->size].release_date);
    printf("Enter title: ");
    scanf("%c", &temp);
    scanf("%[^\n]", b->array[b->size].title);
    scanf("%c", &temp);
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

void sort_by_id_then_title(writes_array_t *wr)
{
    int i, j;
    for(i = 0; i < wr->size - 1; i++)
    {
        for(j = 0; j < wr->size - i - 1; j++)
        {
            if(wr->array[j].writer_id > wr->array[j+1].writer_id)
            {
                swap_writes(&wr->array[j], &wr->array[j+1]);
            }
            else if(wr->array[j].writer_id == wr->array[j+1].writer_id)
            {
                if(strcmp(wr->array[j].title, wr->array[j+1].title) > 0)
                {
                    swap_writes(&wr->array[j], &wr->array[j+1]);
                }
            }
        }
    }
}



