#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project_lib.h"
#include "author.h"
#include "book.h"

int main(int argc, char *argv[])
{   
    books_array_t b;
    authors_array_t au;
    int choice;


    init_author(&au, 5);  // provlima me to init_author kai to init_book. den trexoun mazi. mono mona tous
    init_book(&b, 5);
    load_book_logs(&b);
    load_author_logs(&au);

    choice = menu();    
    while (choice)
    {
        if (choice == 1)
        {
            add_author(&au);
            print_authors(&au);
        }   
        else if(choice == 2)
        {
            add_book(&b);
            print_books(&b);
        }
        else if(choice == 3){}
        else if(choice == 4){}
        else if(choice == 5){}
        else if(choice == 6){}
        else if(choice == 7) 
            {
                save_book_logs(&b);
                save_author_logs(&au);
                free_books_array(&b);
                free_authors_array(&au);
                return 0;
            }
        choice = menu();
    }
    
    return 0;
}
