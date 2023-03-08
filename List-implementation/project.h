#ifndef PROJECT_H
#define PROJECT_H

int menu();
void add_book(books_list_t *b, authors_list_t *au, writes_list_t *wr);
void search_surname_and_print_author(authors_list_t *au, books_list_t *b, writes_list_t *wr);
void search_title_print_book(books_list_t *b, authors_list_t *au, writes_list_t *wr);
void search_id_and_delete_author(authors_list_t *au, books_list_t *b, writes_list_t *wr);
void search_title_and_delete_book(books_list_t *b, authors_list_t *au, writes_list_t *wr);

#endif