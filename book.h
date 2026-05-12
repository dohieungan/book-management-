#ifndef BOOK_H
#define BOOK_H

#include "constants.h"

// Mang song song luu thong tin sach
extern char   book_isbn[MAX_BOOK][MAX_ID];
extern char   book_title[MAX_BOOK][MAX_NAME];
extern char   book_author[MAX_BOOK][MAX_NAME];
extern char   book_publisher[MAX_BOOK][MAX_NAME];
extern int    book_year[MAX_BOOK];
extern char   book_genre[MAX_BOOK][MAX_NAME];
extern double book_cost[MAX_BOOK];
extern double book_price[MAX_BOOK];
extern int    book_stock[MAX_BOOK];
extern int    numBooks;

// Prototype
void displayAllBooks();
void addBook();
void editBook();
void deleteBook();
int  findBookByISBN(const char* isbn);
void searchBookByISBN(const char* isbn);
void searchBookByTitle(const char* title);
void bookMenu();

#endif
