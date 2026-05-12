#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "book.h"
#include "utils.h"

using namespace std;

// Dinh nghia mang toan cuc
char   book_isbn[MAX_BOOK][MAX_ID];
char   book_title[MAX_BOOK][MAX_NAME];
char   book_author[MAX_BOOK][MAX_NAME];
char   book_publisher[MAX_BOOK][MAX_NAME];
int    book_year[MAX_BOOK];
char   book_genre[MAX_BOOK][MAX_NAME];
double book_cost[MAX_BOOK];
double book_price[MAX_BOOK];
int    book_stock[MAX_BOOK];
int    numBooks = 0;

/*
 * Ham: findBookByISBN
 * Mo ta: Tim sach theo ma ISBN
 * Tham so: isbn - ma can tim
 * Tra ve: vi tri trong mang hoac -1
 */
int findBookByISBN(const char* isbn) {
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(book_isbn[i], isbn) == 0) return i;
    }
    return -1;
}

/*
 * Ham: displayAllBooks
 * Mo ta: Hien thi danh sach tat ca sach dang bang
 * Tham so: khong
 * Tra ve: khong
 */
void displayAllBooks() {
    clearScreen();
    cout << "\n";
    printLine(130);
    cout << left << setw(10) << "ISBN"
                 << setw(28) << "Ten sach"
                 << setw(20) << "Tac gia"
                 << setw(16) << "Nha xuat ban"
                 << setw(14) << "Nam xuat ban"
                 << setw(12) << "The loai"
         << right << setw(10) << "Gia nhap"
                  << setw(10) << "Gia ban"
                  << setw(10) << "Ton kho" << "\n";
    printLine(130);
    if (numBooks == 0) {
        cout << "  (Chua co sach nao)\n";
    }
    for (int i = 0; i < numBooks; i++) {
        cout << left  << setw(10) << book_isbn[i]
                      << setw(28) << book_title[i]
                      << setw(20) << book_author[i]
                      << setw(16) << book_publisher[i]
                      << setw(14) << book_year[i]
                      << setw(12) << book_genre[i]
             << right << fixed << setprecision(0)
                      << setw(10) << book_cost[i]
                      << setw(10) << book_price[i]
                      << setw(10) << book_stock[i] << "\n";
    }
    printLine(130);
}

/*
 * Ham: addBook
 * Mo ta: Them sach moi, tu sinh ISBN neu nguoi dung khong nhap, kiem tra trung ISBN
 * Tham so: khong
 * Tra ve: khong
 */
void addBook() {
    if (numBooks >= MAX_BOOK) {
        cout << "Danh sach sach da day!\n";
        pauseScreen();
        return;
    }

    int idx = numBooks;
    char tmpIsbn[MAX_ID];

    inputString(tmpIsbn, MAX_ID, "Nhap ISBN (Enter de tu dong sinh): ");
    if (strlen(tmpIsbn) == 0) {
        int idNum = numBooks + 1;
        do {
            snprintf(tmpIsbn, MAX_ID, "ISBN%03d", idNum++);
        } while (findBookByISBN(tmpIsbn) != -1);
    }
    if (findBookByISBN(tmpIsbn) != -1) {
        cout << "ISBN da ton tai trong he thong!\n";
        pauseScreen();
        return;
    }
    strcpy(book_isbn[idx], tmpIsbn);

    inputString(book_title[idx], MAX_NAME, "Tua sach: ");
    if (strlen(book_title[idx]) == 0) {
        cout << "Tua sach khong duoc de trong!\n";
        pauseScreen();
        return;
    }
    inputString(book_author[idx],    MAX_NAME, "Tac gia: ");
    inputString(book_publisher[idx], MAX_NAME, "Nha xuat ban: ");

    cout << "Nam xuat ban: ";
    cin >> book_year[idx];
    cin.ignore(1000, '\n');

    inputString(book_genre[idx], MAX_NAME, "The loai: ");

    cout << "Gia nhap (VND): ";
    cin >> book_cost[idx];
    cin.ignore(1000, '\n');

    cout << "Gia ban (VND): ";
    cin >> book_price[idx];
    cin.ignore(1000, '\n');

    cout << "So luong ton kho: ";
    cin >> book_stock[idx];
    cin.ignore(1000, '\n');

    numBooks++;
    cout << "Da them sach \"" << book_title[idx] << "\" (ISBN: " << book_isbn[idx] << ") thanh cong!\n";
    pauseScreen();
}

/*
 * Ham: editBook
 * Mo ta: Sua thong tin sach theo ISBN
 * Tham so: khong
 * Tra ve: khong
 */
void editBook() {
    char isbn[MAX_ID];
    inputString(isbn, MAX_ID, "Nhap ISBN can sua: ");
    int idx = findBookByISBN(isbn);
    if (idx == -1) {
        cout << "Khong tim thay ISBN " << isbn << "!\n";
        pauseScreen();
        return;
    }

    cout << "Dang sua: " << book_isbn[idx] << " - " << book_title[idx] << "\n";
    cout << "(Nhan Enter de giu nguyen tung truong)\n\n";

    char tmp[MAX_NAME];

    // Tua sach
    cout << "Tua sach [" << book_title[idx] << "]: ";
    cin.getline(tmp, MAX_NAME);
    if (strlen(tmp) > 0) strcpy(book_title[idx], tmp);

    // Tac gia
    cout << "Tac gia [" << book_author[idx] << "]: ";
    cin.getline(tmp, MAX_NAME);
    if (strlen(tmp) > 0) strcpy(book_author[idx], tmp);

    // Nha xuat ban
    cout << "Nha xuat ban [" << book_publisher[idx] << "]: ";
    cin.getline(tmp, MAX_NAME);
    if (strlen(tmp) > 0) strcpy(book_publisher[idx], tmp);

    // The loai
    cout << "The loai [" << book_genre[idx] << "]: ";
    cin.getline(tmp, MAX_NAME);
    if (strlen(tmp) > 0) strcpy(book_genre[idx], tmp);

    // Nam xuat ban
    cout << "Nam xuat ban [" << book_year[idx] << "]: ";
    cin.getline(tmp, MAX_NAME);
    if (strlen(tmp) > 0) book_year[idx] = atoi(tmp);

    // Gia nhap
    cout << fixed << setprecision(0);
    cout << "Gia nhap [" << book_cost[idx] << "]: ";
    cin.getline(tmp, MAX_NAME);
    if (strlen(tmp) > 0) book_cost[idx] = atof(tmp);

    // Gia ban
    cout << "Gia ban [" << book_price[idx] << "]: ";
    cin.getline(tmp, MAX_NAME);
    if (strlen(tmp) > 0) book_price[idx] = atof(tmp);

    cout << "Cap nhat thanh cong!\n";
    pauseScreen();
}

/*
 * Ham: deleteBook
 * Mo ta: Xoa sach theo ISBN, chi cho phep xoa khi ton kho = 0
 * Tham so: khong
 * Tra ve: khong
 */
void deleteBook() {
    char isbn[MAX_ID];
    inputString(isbn, MAX_ID, "Nhap ISBN can xoa: ");
    int idx = findBookByISBN(isbn);
    if (idx == -1) {
        cout << "Khong tim thay ISBN " << isbn << "!\n";
        pauseScreen();
        return;
    }
    if (book_stock[idx] != 0) {
        cout << "Khong the xoa! Sach con " << book_stock[idx] << " quyen trong kho.\n";
        pauseScreen();
        return;
    }

    cout << "Xac nhan xoa sach \"" << book_title[idx] << "\"? (y/n): ";
    char c;
    cin >> c;
    cin.ignore(1000, '\n');
    if (c != 'y' && c != 'Y') {
        cout << "Huy bo.\n";
        pauseScreen();
        return;
    }

    for (int i = idx; i < numBooks - 1; i++) {
        strcpy(book_isbn[i],      book_isbn[i+1]);
        strcpy(book_title[i],     book_title[i+1]);
        strcpy(book_author[i],    book_author[i+1]);
        strcpy(book_publisher[i], book_publisher[i+1]);
        strcpy(book_genre[i],     book_genre[i+1]);
        book_year[i]  = book_year[i+1];
        book_cost[i]  = book_cost[i+1];
        book_price[i] = book_price[i+1];
        book_stock[i] = book_stock[i+1];
    }
    numBooks--;
    cout << "Da xoa sach " << isbn << "!\n";
    pauseScreen();
}

/*
 * Ham: searchBookByISBN
 * Mo ta: Tim va hien thi chi tiet mot cuon sach theo ma ISBN chinh xac
 * Tham so: isbn - ma ISBN can tim
 * Tra ve: khong
 */
void searchBookByISBN(const char* isbn) {
    int idx = findBookByISBN(isbn);
    printLine(65);
    cout << "Ket qua tim kiem ISBN: \"" << isbn << "\"\n";
    printLine(65);
    if (idx == -1) {
        cout << "  Khong tim thay sach voi ISBN nay.\n";
    } else {
        cout << "ISBN          : " << book_isbn[idx]      << "\n"
             << "Tua sach      : " << book_title[idx]     << "\n"
             << "Tac gia       : " << book_author[idx]    << "\n"
             << "Nha xuat ban  : " << book_publisher[idx] << "\n"
             << "Nam xuat ban  : " << book_year[idx]      << "\n"
             << "The loai      : " << book_genre[idx]     << "\n"
             << "Gia ban       : " << fixed << setprecision(0) << book_price[idx] << " VND\n"
             << "Ton kho       : " << book_stock[idx]     << " quyen\n";
    }
    printLine(65);
}

/*
 * Ham: searchBookByTitle
 * Mo ta: Tim sach theo tua de (tim mo, khong phan biet hoa thuong)
 * Tham so: title - tu khoa tim kiem
 * Tra ve: khong
 */
void searchBookByTitle(const char* title) {
    int found = 0;
    printLine(100);
    cout << "Ket qua tim kiem theo tua de: \"" << title << "\"\n";
    printLine(100);
    cout << left << setw(10) << "ISBN"
                 << setw(30) << "Tua sach"
                 << setw(20) << "Tac gia"
                 << setw(12) << "The loai"
         << right << setw(8) << "Gia ban"
                  << setw(6) << "Kho" << "\n";
    printLine(100);
    for (int i = 0; i < numBooks; i++) {
        if (strContainsCaseInsensitive(book_title[i], title)) {
            cout << left  << setw(10) << book_isbn[i]
                          << setw(30) << book_title[i]
                          << setw(20) << book_author[i]
                          << setw(12) << book_genre[i]
                 << right << fixed << setprecision(0)
                          << setw(8) << book_price[i]
                          << setw(6) << book_stock[i] << "\n";
            found++;
        }
    }
    if (!found) cout << "  Khong tim thay sach nao.\n";
    printLine(100);
}

/*
 * Ham: bookMenu
 * Mo ta: Menu con quan ly sach
 * Tham so: khong
 * Tra ve: khong
 */
void bookMenu() {
    int choice;
    do {
        clearScreen();
        printLine(40);
        cout << "       QUAN LY SACH\n";
        printLine(40);
        cout << "1. Xem danh sach sach\n"
             << "2. Them sach moi\n"
             << "3. Sua thong tin sach\n"
             << "4. Xoa sach\n"
             << "5. Tim kiem theo ISBN\n"
             << "6. Tim kiem theo tua sach\n"
             << "0. Quay lai\n";
        printLine(40);
        cout << "Chon: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
            case 1:
                displayAllBooks();
                pauseScreen();
                break;
            case 2:
                addBook();
                break;
            case 3:
                editBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5: {
                char isbn[MAX_ID];
                inputString(isbn, MAX_ID, "Nhap ISBN can tim: ");
                searchBookByISBN(isbn);
                pauseScreen();
                break;
            }
            case 6: {
                char title[MAX_NAME];
                inputString(title, MAX_NAME, "Nhap tua sach can tim: ");
                searchBookByTitle(title);
                pauseScreen();
                break;
            }
            case 0: break;
            default: cout << "Lua chon khong hop le!\n"; pauseScreen();
        }
    } while (choice != 0);
}
