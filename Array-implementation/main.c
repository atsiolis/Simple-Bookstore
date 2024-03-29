#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writes.h"
#include "author.h"
#include "book.h"
#include "project.h"

int main(int argc, char *argv[])
{
    books_array_t b;
    authors_array_t au;
    writes_array_t wr;
    int choice;

    init_author(&au, 5);        
    init_book(&b, 5);           
    init_writes(&wr, 5);        
    load_author_logs(&au);      
    load_book_logs(&b);         
    load_writes_logs(&wr);      

    choice = menu();
    while (choice)
    {
        if (choice == 1)
        {
            add_author(&au);
            //print_authors(&au);
        }
        else if (choice == 2)
        {
            add_book(&b, &au, &wr);
            //print_books(&b);
        }
        else if (choice == 3)
        {
            search_surname_and_print_author(&au, &b, &wr);
        }
        else if (choice == 4)
        {
            seach_title_and_print_book(&b, &au, &wr);
        }
        else if (choice == 5)
        {
            search_id_and_delete_author(&au, &b, &wr);
        }
        else if (choice == 6)
        {
            search_title_and_delete_book(&b, &au, &wr);
        }
        else if (choice == 7)
        {
            save_book_logs(&b);
            save_author_logs(&au);
            save_writes_logs(&wr);
            free_books_array(&b);
            free_authors_array(&au);
            free_writes_array(&wr);
            return 0;
        }
        else
        {
            printf("Invalid input. Please choose an operation from [1,7].\n");
        }
        choice = menu();
    }
}