#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "writes.h"
#include "author.h"
#include "book.h"
#include "project.h"
#define SIZE 50

//print the menu and scan the choice from the user and return it
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

//add a new book to the books array, update the writes array and update the authors array  
void add_book(books_array_t *b, authors_array_t *au, writes_array_t *wr)
{
    int i, num_of_authors;
    char surname[20], name[20], temp, title[50];    
    int au_ex_id;   

    if (b->size == b->capacity)
    {
        b->capacity *= 2;
        b->array = realloc(b->array, b->capacity * sizeof(book_t));
    }
    b->array[b->size].title = malloc(50 * sizeof(char));

    printf("Enter title: ");
    scanf("%c", &temp);         //to clear the buffer, so that we can scan the title correctly with spaces included
    scanf("%[^\n]", title);     //scan the title
    scanf("%c", &temp);         //to clear the buffer again

    if (book_exists(b, title) == 1)
    {
        printf("Book already exists.\n");    //if the book already exists, return
        return;
    }

    strcpy(b->array[b->size].title, title);
    printf("Enter release year: ");
    scanf("%d", &b->array[b->size].release_date);
    printf("Enter price: ");
    scanf("%f", &b->array[b->size].price);
    printf("Number of authors: ");          
    scanf("%d", &num_of_authors);

    for (i = 0; i < num_of_authors; i++)        //for each author scan name and surname  
    {

        printf("Enter author's surname: ");
        scanf("%s", surname);
        au_ex_id = author_exists(au, surname);      //check if the author exists

        if (au_ex_id != 0)
        {
            add_writes(wr, b->array[b->size].title, au_ex_id);          //if the author exists, add the writes struct
            au->array[bin_search_author(au, au_ex_id)].num_of_books++;  //and update the number of books of the author
        }
        else
        {
            printf("Author does not exist.\n");
            printf("Enter author's name: ");                    
            scanf("%s", name);
            auto_add_author(au, surname, name);                 //if the author does not exist, add him to the authors array     
            add_writes(wr, b->array[b->size].title, author_exists(au, surname));    //and add the writes struct
        }
    }

    b->size++;
    
    for (i = b->size - 1; i > 0 && strcmp(b->array[i].title, b->array[i - 1].title) < 0; i--) 
    {
        swap_book(&b->array[i], &b->array[i - 1]);    //sort the books array by title
    }
}

//search an author by surname and print their books
void search_surname_and_print_author(authors_array_t *au, books_array_t *b, writes_array_t *wr)
{
    int i, id, au_pos, wr_pos;
    char surname[20];

    printf("Enter author's surname: ");
    scanf("%s", surname);

    id = author_exists(au, surname);
    if (id == 0)
    {
        printf("Author does not exist.\n");             //if the author does not exist, return
        return;
    }

    au_pos = bin_search_author(au, id);     //find the position of the author in the authors array
    wr_pos = bin_search_writes(wr, id);     //find the position of the author in the writes array

    int temp = wr_pos;
    for (i = wr_pos; i >= 0 && wr->array[i].writer_id == id; i--)           //find the first position of the author in the writes array
        temp = i;

    printf("Author's id: %d\n", au->array[au_pos].writer_id);
    printf("Author's surname: %s\n", au->array[au_pos].surname);
    printf("Author's name: %s\n", au->array[au_pos].name);
    printf("Number of books: %d\n", au->array[au_pos].num_of_books);

    for (i = temp; i < wr->size && wr->array[i].writer_id == id; i++)
    {
        printf("\n");               //print all the books of the author
        printf("Title: %s\n", wr->array[i].title);          
        printf("Release date: %d\n", b->array[search_book(b, wr->array[i].title)].release_date);
        printf("Price: %.2f\n", b->array[search_book(b, wr->array[i].title)].price);
        printf("\n");
    }
    return;
}

//search a book by title and print its info
void seach_title_and_print_book(books_array_t *b, authors_array_t *au, writes_array_t *wr)
{
    int i, j;
    int book_au_id, au_pos;
    char title[SIZE];
    bool flag = false;      //flag to check if the book exists

    printf("\n Book title: ");
    scanf("%s", title);             //scan for the title

    for (i = 0; i < b->size; i++)
    {
        if (!strcmp(title, b->array[i].title))
        {
            printf("\nBook info:\n");                                       //if the book exists, print its info
            printf("Book's title: %s\n", b->array[i].title);
            printf("Book's release date: %d\n", b->array[i].release_date);
            printf("Book's price: %.2f\n", b->array[i].price);

            for (j = 0; j < wr->size; j++)
            {
                if (strcmp(wr->array[j].title, title) == 0)             //find the entry with the title given in the writes array
                {
                    book_au_id = wr->array[j].writer_id;                //get the id of the author from the writes array
                    au_pos = bin_search_author(au, book_au_id);         //search and return the position of the author in the authors array

                    printf("\n");
                    printf("Author's id: %d\n", au->array[au_pos].writer_id);
                    printf("Author's surname: %s\n", au->array[au_pos].surname);
                    printf("Author's name: %s\n", au->array[au_pos].name);
                    printf("Author's number of books: %d\n", au->array[au_pos].num_of_books);
                    printf("\n");
                }
            }
            flag = true;                                                //set the flag to true if the book exists
        }
    }
    if (flag == false)
        printf("No books with this title were found.\n");           //if the book does not exist notify the user
}

//search an author by id and delete them
void search_id_and_delete_author(authors_array_t *au, books_array_t *b, writes_array_t *wr)
{
    int i, j, k, l, id, temp, num_of_books, au_pos, wr_pos, wr_counter = 0;
    char title[50];
    printf("Enter author's id: ");
    scanf("%d", &id);                   //scan for the id

    au_pos = bin_search_author(au, id);     //find the position of the author in the authors array

    num_of_books = au->array[au_pos].num_of_books;      //get the number of books of the author
    if (au_pos == -1)
    {
        printf("Author does not exist.\n");        //if the author does not exist, notify the user and return
        return;
    }

    for (i = au_pos; i < au->size - 1; i++)
    {
        swap_author(&au->array[i], &au->array[i + 1]);
    }
    au->size--;                 //delete the author from the authors array by swapping their struct to the end of the array and decreasing the size

    for (l = 0; l < num_of_books; l++)
    {                   
        wr_pos = bin_search_writes(wr, id);         //find the position of the author in the writes array
        temp = wr_pos;                              //save the position of the author in the writes array
        for (i = wr_pos; i >= 0 && wr->array[i].writer_id == id; i--)
            temp = i;                           //find the first position of the author in the writes array

        wr_counter = 0;                         //counter to count the number of instances of the title in the writes array
        strcpy(title, wr->array[temp].title);

        for (i = 0; i < wr->size; i++)
        {
            if (strcmp(wr->array[i].title, wr->array[temp].title) == 0)
                wr_counter++;                   //count the number of instances of the title in the writes array   
        }

        if (wr_counter == 1)
        {                    //if the number of instances is 1, the book has only one author so we delete the book from the books array
            for (k = 0; k < b->size; k++)
            {
                if (strcmp(wr->array[temp].title, b->array[k].title) == 0)
                {
                    for (j = k; j < b->size - 1; j++)
                    {
                        swap_book(&b->array[j], &b->array[j + 1]);
                    }
                }
            }
            for (j = temp; j < wr->size - 1; j++)
            {
                swap_writes(&wr->array[j], &wr->array[j + 1]);
            }
            b->size--;              //decrease the size of the books array
            wr->size--;             //decrease the size of the writes array
        }
        else if (wr_counter > 1)
        {                   //if the number of instances is greater than 1, the book has more than one author so we only delete the entry from the writes array
            for (j = temp; j < wr->size - 1; j++)
            {
                swap_writes(&wr->array[j], &wr->array[j + 1]);
            }
            wr->size--;
        }
    }
}

//search a book by title and delete it
void search_title_and_delete_book(books_array_t *b, authors_array_t *au, writes_array_t *wr)
{
    int i;
    int b_pos, wr_pos;
    char title[SIZE];

    printf("\n Book title: ");
    scanf("%s", title);         //scan for the title

    b_pos = search_book(b, title);      //find the position of the book in the books array
    if (b_pos >= 0)
    {
        for (i = b_pos; i < b->size - 1; i++)
            swap_book(&b->array[i], &b->array[i + 1]);
        b->size--;                  //delete the book from the books array by swapping their struct to the end of the array and decreasing the size

        while (search_writes(wr, title) >= 0)
        {
            wr_pos = search_writes(wr, title);              //find the position of the book in the writes array
            au->array[bin_search_author(au, wr->array[wr_pos].writer_id)].num_of_books--;       //decrease the number of books of the author by 1
            for (i = wr_pos; i < wr->size - 1; i++)
                swap_writes(&wr->array[i], &wr->array[i + 1]);          //delete the entry from the writes array by swapping their struct to the end of the array and decreasing the size
            wr->size--;
        }
        printf("\nBook logs with title %s deleted successfully. \n", title);
    }
    else
        printf("\nNo books with that title were found.\n");
}