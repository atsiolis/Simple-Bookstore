#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "author.h"
#include "writes.h"
#include "book.h"
#include "project.h"

int main(int argc, char *argv[])
{
    authors_list_t au;
    books_list_t b;
    writes_list_t wr;
    int choice;
    init_author_list(&au);
    init_book_list(&b);
    init_writes_list(&wr);
    load_author_list(&au);
    load_book_list(&b);
    load_writes_list(&wr);
    printf("\n");

    choice = menu();
    while (choice)
    {
        if (choice == 1)
        {
            add_author(&au);
            print_author_list(&au);
        }
        else if (choice == 2)
        {
            add_book(&b, &au, &wr);
            print_book_list(&b);
        }
        else if (choice == 3)
        {
            search_surname_and_print_author(&au, &b, &wr);
        }
        else if (choice == 4)
        {
            search_title_print_book(&b, &au, &wr);
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
            save_author_list(&au);
            save_book_list(&b);
            save_writes_list(&wr);
            free_author_list(&au);
            free_book_list(&b);
            free_writes_list(&wr);
            return 0;
        }
        else
        {
            printf("Invalid input. Please select an operation from [1,7].\n");
        }
        choice = menu();
    }
}
