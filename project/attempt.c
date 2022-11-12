#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project_lib.h"
#include "author.h"
#include "book.h"

int main(int argc, char *argv[])
{
    authors_array_t *au;
    init_author(au, 10);
    books_array_t *b;
    init_book(b, 10);
    
    int choice;
    choice = menu();
    while (choice)
    {
        if (choice == 1)
        {
            add_author(au);
            print_authors(au);
        }   
        else if(choice == 2)
        {
            add_book(b);
            print_books(b);
        }
        else if(choice == 3){}
        else if(choice == 4){}
        else if(choice == 5){}
        else if(choice == 6){}
        else if(choice == 7) return 0;
        choice = menu();
    }
    
    return 0;
}