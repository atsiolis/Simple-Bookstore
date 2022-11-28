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
    load_author_list(&au);

    choice = menu();
    while(choice)
    {
        if(choice == 1)
        {
            add_author(&au);
            print_author_list(&au);
        }
        else if(choice == 2)
        {}
        else if(choice == 3)
        {}
        else if(choice == 4)
        {}
        else if(choice == 5)
        {}
        else if(choice == 6)
        {}
        else if(choice == 7)
        {
            save_author_list(&au);
            return 0;
        }
        else
        {
            printf("Invalid input. Please select an operation from [1,7].\n");
        }
        choice = menu();
    }
}
