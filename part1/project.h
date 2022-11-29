#ifndef PROJECT_LIB_H
#define PROJECT_LIB_H

int menu();
void add_book(books_array_t *b, authors_array_t *au, writes_array_t *wr);
void search_surname_and_print_author(authors_array_t *au, books_array_t *b, writes_array_t *wr);
void seach_title_and_print_book(books_array_t *b, authors_array_t *au, writes_array_t *wr);
void search_id_and_delete_author(authors_array_t *au, books_array_t *b, writes_array_t *wr);
void search_title_and_delete_book(books_array_t *b, authors_array_t *au, writes_array_t *wr);

#endif