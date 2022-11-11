#include <stdio.h>
#include <stdlib.h>

int menu();
void add_writer();

int main(int argc, char *argv[])
{
    int choice;
    choice = menu();
    while (choice)
    {
     if (choice == 1)
     {

     }   
     else if(choice == 2)
     {

     }
     else if(choice == 3)
     {

     }
     else if(choice == 4)
     {

     }
     else if(choice == 5)
     {

     }
     else if(choice == 6)
     {

     }
     choice = menu();
    }
}

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