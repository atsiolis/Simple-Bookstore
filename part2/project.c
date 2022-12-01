#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "writes.h"
#include "author.h"
#include "book.h"
#include "project.h"
#define SIZE 20

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

//add a new book to the list
void add_book(books_list_t *b, authors_list_t *au, writes_list_t *wr)
{
    int i, num_of_authors, au_ex_id;
    char surname[SIZE], name[SIZE], temp, title[50];
    book_node_t *book, *book_prev, *book_cur;
    author_node_t *author_cur;
    book = malloc(sizeof(book_node_t));
    book->info = malloc(sizeof(book_t));
    book->info->title = malloc(50 * sizeof(char));
    printf("Enter title: ");
    scanf("%c", &temp);         //clear the buffer, so that we can scan the title correctly with spaces included
    scanf("%[^\n]", title);     //read the title
    scanf("%c", &temp);         //clear the buffer again
    if (book_exists(b, title) == 1)
    {
        printf("Book already exists.\n");
        return;
    }
    strcpy(book->info->title, title);
    printf("Enter release year: ");
    scanf("%d", &book->info->release_date);
    printf("Enter price: ");
    scanf("%f", &book->info->price);
    printf("Number of authors: ");
    scanf("%d", &num_of_authors);

    for (i = 0; i < num_of_authors; i++)
    {
        printf("Enter author's surname: ");
        scanf("%s", surname);
        au_ex_id = author_exists(au, surname);          //check if the author exists, if so, get the id of the author
        if (au_ex_id != 0)
        {
            add_writes(wr, book->info->title, au_ex_id);    //if the author exists, add the book to the writes list
            author_cur = au->head;
            while (author_cur != NULL)
            {
                if (author_cur->info->writer_id == au_ex_id)        
                {                                           //if the author exists, increase the number of books
                    author_cur->info->num_of_books++;
                }
                author_cur = author_cur->next;
            }
        }
        else
        {
            printf("Author doesn't exist.\n");          //if the author doesn't exist scan the name and add the author to the author list automatically
            printf("Enter author's name: ");            //and add the book to the writes list
            scanf("%s", name);
            auto_add_author(au, surname, name);
            add_writes(wr, book->info->title, author_exists(au, surname));
        }
    }
    b->size++;
    book_cur = b->head;
    book_prev = NULL;
    while (book_cur != NULL && strcmp(book_cur->info->title, book->info->title) < 0)
    {
        book_prev = book_cur;
        book_cur = book_cur->next;                              //get the correct position to insert the book alphabetically 
    }

    if (book_prev == NULL)
    {
        book->next = b->head;                   //if the book is the first in the list or the list is empty add it to the head
        b->head = book;
    }
    else
    {
        book_prev->next = book;                 //else add it to the next node
        book->next = book_cur;
    }
}

//search for surname in the author list and print their books 
void search_surname_and_print_author(authors_list_t *au, books_list_t *b, writes_list_t *wr)
{
    int id;
    char surname[20];
    author_node_t *au_cur = au->head;
    writes_node_t *wr_cur = wr->head;
    book_node_t *b_cur = b->head;

    printf("Enter author's surname: ");
    scanf("%s", surname);

    id = author_exists(au, surname);
    if (id == 0)
    {
        printf("Author does not exist.\n");         //if the author doesn't exist, notify the user and return
        return;
    }

    while (au_cur != NULL)
    {
        if (au_cur->info->writer_id == id)
        {
            printf("Author's id: %d\n", au_cur->info->writer_id);
            printf("Author's surname: %s\n", au_cur->info->surname);                //print the author's info
            printf("Author's name: %s\n", au_cur->info->name);
            printf("Number of books: %d\n", au_cur->info->num_of_books);
        }
        au_cur = au_cur->next;
    }

    while (wr_cur != NULL)
    {
        if (wr_cur->info->writer_id == id)
        {                                   //if the author wrote a book, print the book's info
            printf("\n");
            printf("Title: %s\n", wr_cur->info->title);
            b_cur = b->head;
            while (b_cur != NULL)
            {
                if (!strcmp(b_cur->info->title, wr_cur->info->title))
                {
                    printf("Release date: %d\n", b_cur->info->release_date);
                    printf("Price: %.2f\n", b_cur->info->price);
                    printf("\n");
                }
                b_cur = b_cur->next;
            }
        }
        wr_cur = wr_cur->next;
    }
    return;
}

//search for a book in the book list and print its info
void search_title_print_book(books_list_t *b, authors_list_t *au, writes_list_t *wr)
{
    char title[50];
    book_node_t *b_cur = b->head;
    writes_node_t *wr_cur = wr->head;
    author_node_t *au_cur = au->head;

    printf("Enter title: ");
    scanf("%s", title);

    if (book_exists(b, title) == 0)
    {
        printf("Book does not exist.\n");
        return;
    }

    while (b_cur != NULL)
    {                                       //print the book's info
        if (!strcmp(b_cur->info->title, title))
        {
            printf("Title: %s\n", b_cur->info->title);
            printf("Release date: %d\n", b_cur->info->release_date);
            printf("Price: %.2f\n", b_cur->info->price);
        }
        b_cur = b_cur->next;
    }

    while (wr_cur != NULL)
    {                                           //print the authors info
        if (!strcmp(wr_cur->info->title, title))
        {
            printf("\n");
            printf("Author's id: %d\n", wr_cur->info->writer_id);
            au_cur = au->head;
            while (au_cur != NULL)
            {
                if (au_cur->info->writer_id == wr_cur->info->writer_id)
                {
                    printf("Author's surname: %s\n", au_cur->info->surname);
                    printf("Author's name: %s\n", au_cur->info->name);
                    printf("Number of books: %d\n", au_cur->info->num_of_books);
                }
                au_cur = au_cur->next;
            }
        }
        wr_cur = wr_cur->next;
    }
    return;
}

//search an author by id and delete them
void search_id_and_delete_author(authors_list_t *au, books_list_t *b, writes_list_t *wr)
{
    int i, id, nob, title_counter = 0;
    char title[50];
    author_node_t *au_cur = au->head, *au_prev = NULL;
    writes_node_t *wr_cur = wr->head, *wr_prev = NULL;
    book_node_t *b_cur = b->head, *b_prev = NULL;
    bool flag = true;                   //flag to check if the author exists
    printf("Enter author's id: ");
    scanf("%d", &id);

    while ((au_cur != NULL) && (au_cur->info->writer_id != id))
    {
        au_prev = au_cur;                       //search for the author
        au_cur = au_cur->next;
    }

    if (au_cur == au->head)
    {                                       //if the author is the first in the list, delete and update the head
        au_cur = au->head;
        au->head = au->head->next;
        nob = au_cur->info->num_of_books;   //get the number of books the author wrote
        free(au_cur->info->surname);
        free(au_cur->info->name);
        free(au_cur->info);
        free(au_cur);
        au->size--;
        flag = false;                       //set the flag to false to notify that the author exists
    }
    else
    {                                       //else find the author and delete their node
        au_prev->next = au_cur->next;
        nob = au_cur->info->num_of_books;   //get the number of books the author wrote
        free(au_cur->info->surname);
        free(au_cur->info->name);
        free(au_cur->info);
        free(au_cur);
        flag = false;                       //set the flag to false to notify that the author exists
        au->size--;
    }
    if (flag == true)
    {
        printf("Author doesn't exist.\n");
    }

    for (i = 0; i < nob; i++)
    {                               //for each book the author wrote
        wr_cur = wr->head;
        while ((wr_cur != NULL) && wr_cur->info->writer_id != id)
        {
            wr_prev = wr_cur;
            wr_cur = wr_cur->next;              //search for the author in the writes list
        }
        strcpy(title, wr_cur->info->title);     //get the title of the book

        wr_cur = wr->head;
        title_counter = 0;                      //counter to count the number of instances of the title in the writes array
        while (wr_cur != NULL)
        {
            if (!strcmp(title, wr_cur->info->title))
                title_counter++;                //count the number of instances of the title in the writes array
            wr_cur = wr_cur->next;
        }

        if (title_counter == 1)
        {                                           //if the title is only in the writes array once, delete it from the books array
            while ((b_cur != NULL) && (strcmp(title, b_cur->info->title) != 0))
            {
                b_prev = b_cur;
                b_cur = b_cur->next;                //search for the book in the books array    
            }
            if (b_cur == b->head)
            {
                b_cur = b->head;
                b->head = b->head->next;
                free(b_cur->info->title);           //if the book is the first in the list, delete and update the head
                free(b_cur->info);
                free(b_cur);
                b->size--;
            }
            else
            {
                b_prev->next = b_cur->next;
                free(b_cur->info->title);           //else find the book and delete its node
                free(b_cur->info);
                free(b_cur);
                b->size--;
            }
        }

        wr_cur = wr->head;
        while ((wr_cur != NULL) && wr_cur->info->writer_id != id)
        {                                           //search for the author's entries in the writes array
            wr_prev = wr_cur;
            wr_cur = wr_cur->next;                  
        }
        if (wr_cur == wr->head)
        {
            wr_cur = wr->head;
            wr->head = wr->head->next;              
            free(wr_cur->info->title);              //if the entry is the first in the list, delete and update the head
            free(wr_cur->info);
            free(wr_cur);
            wr->size--;
        }
        else
        {
            wr_prev->next = wr_cur->next;
            free(wr_cur->info->title);
            free(wr_cur->info);                     //else find the entry and delete its node
            free(wr_cur);
            wr->size--;
        }
    }
}

//search a book by title and delete it
void search_title_and_delete_book(books_list_t *b, authors_list_t *au, writes_list_t *wr)
{
    char title[50];
    int i, counter = 0;                 //counter to count the number of instances of the title in the writes array
    book_node_t *b_cur = b->head;
    book_node_t *b_prev = NULL;
    writes_node_t *wr_cur = wr->head;
    writes_node_t *wr_prev = NULL;
    author_node_t *au_cur = au->head;

    printf("Enter title: ");
    scanf("%s", title);

    if (book_exists(b, title) == 0)
    {
        printf("Book does not exist.\n");
        return;
    }

    while (b_cur != NULL && strcmp(b_cur->info->title, title) != 0)
    {
        b_prev = b_cur;
        b_cur = b_cur->next;                //search for the book in the books array
    }
    if (b_cur == b->head)
    {
        b_cur = b->head;
        b->head = b->head->next;
        free(b_cur->info->title);           //if the book is the first in the list, delete and update the head
        free(b_cur->info);
        free(b_cur);
        b->size--;
    }
    else
    {
        b_prev->next = b_cur->next;
        free(b_cur->info->title);           //else find the book and delete its node
        free(b_cur->info);
        free(b_cur);
        b->size--;
    }

    while (wr_cur != NULL)
    {
        if (strcmp(wr_cur->info->title, title) == 0)
        {
            counter++;                      //count the number of instances of the title in the writes array
        }
        wr_cur = wr_cur->next;
    }

    for (i = 0; i < counter; i++)
    {                               //for each instance of the title in the writes array
        wr_cur = wr->head;
        while (wr_cur != NULL && strcmp(wr_cur->info->title, title) != 0)
        {
            wr_prev = wr_cur;               
            wr_cur = wr_cur->next;              //search for the title in the writes array
        }

        au_cur = au->head;
        while (au_cur != NULL)
        {
            if (au_cur->info->writer_id == wr_cur->info->writer_id)
            {
                au_cur->info->num_of_books--;           //update the number of books the author wrote
            }
            au_cur = au_cur->next;
        }
        if (wr_cur == wr->head)
        {
            wr_cur = wr->head;
            wr->head = wr->head->next;
            free(wr_cur->info->title);                  //if the entry is the first in the list, delete and update the head
            free(wr_cur->info);
            free(wr_cur);
            wr->size--;
        }
        else
        {
            wr_prev->next = wr_cur->next;               //else find the entry and delete its node
            free(wr_cur->info->title);
            free(wr_cur->info);
            free(wr_cur);
            wr->size--;
        }
    }
}