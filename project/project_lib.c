#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "writes.h"
#include "author.h"
#include "book.h"
#include "project_lib.h"
#define SIZE 50

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
    char surname[20], name[20],temp,title[50];
    int au_ex_id;
    
    if(b->size == b->capacity)

    {
        b->capacity *= 2;
        b->array = realloc(b->array, b->capacity * sizeof(book_t));
    }
    b->array[b->size].title = malloc(50 * sizeof(char));
    printf("Enter title: ");
    scanf("%c", &temp);
    scanf("%[^\n]", title);
    scanf("%c", &temp);
    if(book_exists(b, title) == 1)
    {
        printf("Book already exists.\n");
        return;
    }
    strcpy(b->array[b->size].title, title);
    printf("Enter release year: ");
    scanf("%d", &b->array[b->size].release_date);
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
        swap_book(&b->array[i], &b->array[i-1]);
    }
}

void search_surname_and_print_author(authors_array_t *au, books_array_t *b,  writes_array_t *wr)
{
    int i, id, au_pos, wr_pos;
    char surname[20];
    printf("Enter author's surname: ");
    scanf("%s", surname);

    id = author_exists(au, surname);
    if(id == 0)
    {
        printf("Author does not exist.\n");
        return;
    }
    
    au_pos = bin_search_author(au, id);
    wr_pos = binary_search_writes(wr, id);
    
    int temp = wr_pos;

    for(i=wr_pos; i>=0 && wr->array[i].writer_id == id; i--)
        temp=i;
    
    
    
    printf("Author's id: %d\n", au->array[au_pos].writer_id);
    printf("Author's surname: %s\n", au->array[au_pos].surname);
    printf("Author's name: %s\n", au->array[au_pos].name);
    printf("Number of books: %d\n", au->array[au_pos].num_of_books);
    
    
    for(i=temp; i<wr->size && wr->array[i].writer_id == id; i++)
    {
        printf("\n");
        printf("Title: %s\n", wr->array[i].title);
        printf("Release date: %d\n", b->array[search_book(b, wr->array[i].title)].release_date);
        printf("Price: %.2f\n", b->array[search_book(b, wr->array[i].title)].price);
    }

    return;   
}

void seach_title_and_print_book(books_array_t *b, authors_array_t *au, writes_array_t *wr)
{
    int i, j;
    int book_au_id, au_pos;
    char title[SIZE];
    bool flag = false;

    printf("\n Book title: ");
    scanf("%s", title);

    for (i = 0; i < b->size; i++)
    {
        if (!strcmp(title, b->array[i].title))
        {
            printf("Book info:\n");
            printf("Book's title: %s\n", b->array[i].title);
            printf("Book's release date: %d\n", b->array[i].release_date);
            printf("Book's price: %.2f\n", b->array[i].price);

            for (j = 0; j < wr->size; j++)
            {
                if (strcmp(wr->array[j].title, title) == 0)
                {
                    book_au_id = wr->array[j].writer_id;
                    au_pos = bin_search_author(au, book_au_id);

                    printf("Author's id: %d\n", au->array[au_pos].writer_id);
                    printf("Author's surname: %s\n", au->array[au_pos].surname);
                    printf("Author's name: %s\n", au->array[au_pos].name);
                    printf("Author's number of books: %d\n", au->array[au_pos].num_of_books);
                    printf("\n");
                }
            }
            flag = true;
        }
    }
    if (flag == false)
        printf("No books with this title were found.\n");
}

void search_id_and_delete_author(authors_array_t *au, books_array_t *b, writes_array_t *wr)
{
    int i, j, k, l, id, num_of_books, au_pos, wr_pos, wr_counter = 0;
    printf("Enter author's id: ");
    scanf("%d", &id);

    au_pos = bin_search_author(au, id);

    num_of_books=au->array[au_pos].num_of_books;
    if (au_pos == -1)
    {
        printf("Author does not exist.\n");
        return;
    }

    for (i = au_pos; i < au->size - 1; i++)
    {
        swap_author(&au->array[i], &au->array[i + 1]);
    }
    au->size--;

    for(l=0; l<num_of_books; l++)
    {
        int temp = binary_search_writes(wr, id);
        for (i = wr_pos; i >= 0 && wr->array[i].writer_id == id; i--)
            temp = i;

        wr_counter=0;
        for (i = 0; i < wr->size; i++)
        {
            if (strcmp(wr->array[i].title, wr->array[temp].title) == 0)
                wr_counter++;
        }

        if (wr_counter == 1)
        {
            for (i = temp; i < wr->size && wr->array[i].writer_id == id; i++)
            {
                for (j = i; j < wr->size - 1; j++)
                {
                    swap_writes(&wr->array[j], &wr->array[j + 1]);
                }
                wr->size--;
                for (k = 0; k < b->size; k++)
                {
                    if (strcmp(wr->array[i].title, b->array[k].title) == 0)
                    {
                        for (j = k; j < b->size - 1; j++)
                        {
                            swap_book(&b->array[j], &b->array[j + 1]);
                        }
                    }
                }
                b->size--;
            }
        }
        else if(wr_counter>1)
        {
            for (i = temp; i < wr->size && wr->array[i].writer_id == id; i++)
            {
                for (j = i; j < wr->size - 1; j++)
                {
                    swap_writes(&wr->array[j], &wr->array[j + 1]);
                }
            }
            wr->size--;
        }
    }
}

void search_and_delete_book(books_array_t *b, authors_array_t *au,  writes_array_t *wr)
{
    int i, j;
    int b_pos, wr_pos, b_reg = 0;
    char title[SIZE];

    printf("\n Book title: ");
    scanf("%s", title);

    b_pos = search_book(b, title);
    if(b_pos >= 0)
    {
        for( i = b_pos; i < b->size - 1; i++)
            swap_book(&b->array[i], &b->array[i+1]);
        b->size--;

        while(search_writes(wr, title) >= 0)
        {
            wr_pos = search_writes(wr, title);
            au->array[bin_search_author(au, wr->array[wr_pos].writer_id)].num_of_books--;
            for( i = wr_pos; i < wr->size - 1 ; i++)
                swap_writes(&wr->array[i], &wr->array[i+1]);
            wr->size--;
        }
        printf("\nBook logs with title %s deleted successfully. \n", &title);
    }
    else
        printf("\nNo books with that title were found.\n");

}
