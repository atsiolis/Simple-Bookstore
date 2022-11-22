#ifndef PROJECT_LIB_H
#define PROJECT_LIB_H

int menu();
void add_book(books_array_t *b, authors_array_t *au, writes_array_t *wr);
void sort_by_id_then_title(writes_array_t *wr);


#endif