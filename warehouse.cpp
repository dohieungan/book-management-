#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "warehouse.h"
#include "book.h"
#include "utils.h"

using namespace std;

/*
 * Ham: importStock
 * Mo ta: Cap nhat so luong nhap them vao kho cho mot ISBN
 * Tham so: khong
 * Tra ve: khong
 */
void importStock() {
    char isbn[MAX_ID];
    inputString(isbn, MAX_ID, "Nhap ISBN can nhap hang: ");
    int idx = findBookByISBN(isbn);
    if (idx == -1) {
        cout << "Khong tim thay ISBN " << isbn << "!\n";
        pauseScreen();
        return;
    }

    cout << "Sach: "             << book_title[idx] << "\n"
         << "Ton kho hien tai: " << book_stock[idx] << "\n"
         << "So luong nhap them: ";
    int qty;
    cin >> qty;
    cin.ignore(1000, '\n');

    if (qty <= 0) {
        cout << "So luong khong hop le!\n";
        pauseScreen();
        return;
    }

    book_stock[idx] += qty;
    cout << "Da nhap them " << qty << " quyen. Ton kho moi: " << book_stock[idx] << "\n";
    pauseScreen();
}

/*
 * Ham: viewStock
 * Mo ta: Hien thi ton kho toan bo, danh dau sach sap het (< 5) va het hang (= 0)
 * Tham so: khong
 * Tra ve: khong
 */
void viewStock() {
    cout << "\n";
    printLine(80);
    cout << left << setw(10) << "ISBN"
                 << setw(35) << "Tua sach"
                 << setw(12) << "The loai"
         << right << setw(8) << "Ton kho"
         << left  << " Ghi chu" << "\n";
    printLine(80);
    if (numBooks == 0) {
        cout << "  (Chua co sach nao)\n";
    }
    for (int i = 0; i < numBooks; i++) {
        const char* note = "";
        if (book_stock[i] == 0)     note = "*** HET HANG ***";
        else if (book_stock[i] < 5) note = "! Sap het";

        cout << left  << setw(10) << book_isbn[i]
                      << setw(35) << book_title[i]
                      << setw(12) << book_genre[i]
             << right << setw(8)  << book_stock[i]
             << left  << " " << note << "\n";
    }
    printLine(80);
}

/*
 * Ham: warehouseMenu
 * Mo ta: Menu con quan ly kho hang
 * Tham so: khong
 * Tra ve: khong
 */
void warehouseMenu() {
    int choice;
    do {
        clearScreen();
        printLine(40);
        cout << "        QUAN LY KHO\n";
        printLine(40);
        cout << "1. Xem ton kho toan bo\n"
             << "2. Nhap hang (cap nhat so luong)\n"
             << "0. Quay lai\n";
        printLine(40);
        cout << "Chon: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
            case 1:
                viewStock();
                pauseScreen();
                break;
            case 2:
                importStock();
                break;
            case 0: break;
            default: cout << "Lua chon khong hop le!\n"; pauseScreen();
        }
    } while (choice != 0);
}
