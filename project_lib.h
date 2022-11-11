// #if project_lib_h
// #define project_list.h

typedef struct book
{
    char *title;
    int release_date;
    float price;
}book_t;

typedef struct author
{
    int writer_id;
    char *surname;
    char *name;
    int num_of_books;
}author_t;

typedef struct writes
{
    char *title;
    int writer_id;
}writes_t;

int menu();

// #endif