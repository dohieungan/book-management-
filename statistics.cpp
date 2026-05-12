#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "statistics.h"
#include "book.h"
#include "customer.h"
#include "invoice.h"
#include "utils.h"

using namespace std;

/*
 * Ham: statTotalStock
 * Mo ta: Tinh va hien thi tong so luong tat ca sach dang co trong kho
 * Tham so: khong
 * Tra ve: khong
 */
void statTotalStock() {
    int total = 0;
    for (int i = 0; i < numBooks; i++) total += book_stock[i];
    printLine(50);
    cout << "THONG KE TON KHO\n";
    printLine(50);
    cout << "Tong so dau sach        : " << numBooks << "\n"
         << "Tong so quyen trong kho : " << total    << "\n";
    printLine(50);
}

/*
 * Ham: statBooksByGenre
 * Mo ta: Dem so dau sach va tong ton kho theo tung the loai
 * Tham so: khong
 * Tra ve: khong
 */
void statBooksByGenre() {
    char genres[50][MAX_NAME];
    int  gCount[50] = {0};
    int  gStock[50] = {0};
    int  numGenres = 0;

    for (int i = 0; i < numBooks; i++) {
        int gi = -1;
        for (int j = 0; j < numGenres; j++) {
            if (strcmp(genres[j], book_genre[i]) == 0) { gi = j; break; }
        }
        if (gi == -1) {
            if (numGenres >= 50) continue;
            strcpy(genres[numGenres], book_genre[i]);
            gi = numGenres++;
        }
        gCount[gi]++;
        gStock[gi] += book_stock[i];
    }

    printLine(55);
    cout << "THONG KE SACH THEO THE LOAI\n";
    printLine(55);
    cout << left << setw(20) << "The loai"
         << right << setw(10) << "So dau sach"
                  << setw(10) << "Ton kho" << "\n";
    printLine(55);
    for (int j = 0; j < numGenres; j++) {
        cout << left  << setw(20) << genres[j]
             << right << setw(10) << gCount[j]
                      << setw(10) << gStock[j] << "\n";
    }
    if (numGenres == 0) cout << "  (Chua co du lieu)\n";
    printLine(55);
}

/*
 * Ham: statCustomersByType
 * Mo ta: Dem so khach hang theo loai the (Thuong / VIP)
 * Tham so: khong
 * Tra ve: khong
 */
void statCustomersByType() {
    int thuong = 0, vip = 0;
    for (int i = 0; i < numCustomers; i++) {
        if (cus_type[i] == 1) vip++;
        else thuong++;
    }
    printLine(40);
    cout << "THONG KE KHACH HANG THEO LOAI\n";
    printLine(40);
    cout << "Khach hang Thuong : " << thuong      << "\n"
         << "Khach hang VIP    : " << vip          << "\n"
         << "Tong cong         : " << numCustomers << "\n";
    printLine(40);
}

/*
 * Ham: statRevenueByDate
 * Mo ta: Tong doanh thu theo ngay cu the hoac theo thang (nguoi dung chon)
 * Tham so: khong
 * Tra ve: khong
 */
void statRevenueByDate() {
    cout << "Thong ke theo:\n"
         << "1. Ngay cu the\n"
         << "2. Thang\n"
         << "Chon: ";
    int opt;
    cin >> opt;
    cin.ignore(1000, '\n');

    if (opt == 1) {
        char date[MAX_DATE];
        int dateDone = 0;
        while (!dateDone) {
            inputString(date, MAX_DATE, "Nhap ngay (DD/MM/YYYY): ");
            if (!isValidDate(date)) cout << "Ngay khong hop le. Nhap lai!\n";
            else dateDone = 1;
        }
        double total = 0;
        int cnt = 0;
        for (int i = 0; i < numInvoices; i++) {
            if (strcmp(inv_date[i], date) == 0) {
                total += inv_total[i];
                cnt++;
            }
        }
        printLine(50);
        cout << "Doanh thu ngay " << date << "\n";
        printLine(50);
        cout << "So hoa don     : " << cnt << "\n"
             << "Tong doanh thu : " << fixed << setprecision(0) << total << " VND\n";
        printLine(50);

    } else if (opt == 2) {
        int mm, yyyy;
        cout << "Nhap thang (1-12): ";
        cin >> mm;
        cout << "Nhap nam (VD: 2024): ";
        cin >> yyyy;
        cin.ignore(1000, '\n');

        if (mm < 1 || mm > 12) {
            cout << "Thang khong hop le!\n";
            pauseScreen();
            return;
        }

        double total = 0;
        int cnt = 0;
        for (int i = 0; i < numInvoices; i++) {
            int d_mm = (inv_date[i][3]-'0')*10 + (inv_date[i][4]-'0');
            int d_yy = (inv_date[i][6]-'0')*1000 + (inv_date[i][7]-'0')*100
                     + (inv_date[i][8]-'0')*10   + (inv_date[i][9]-'0');
            if (d_mm == mm && d_yy == yyyy) {
                total += inv_total[i];
                cnt++;
            }
        }
        printLine(50);
        cout << "Doanh thu thang " << setfill('0') << setw(2) << mm
             << "/" << setw(4) << yyyy << setfill(' ') << "\n";
        printLine(50);
        cout << "So hoa don     : " << cnt << "\n"
             << "Tong doanh thu : " << fixed << setprecision(0) << total << " VND\n";
        printLine(50);

    } else {
        cout << "Lua chon khong hop le!\n";
    }
}

/*
 * Ham: statOutOfStock
 * Mo ta: Liet ke sach da het hang (ton kho = 0)
 * Tham so: khong
 * Tra ve: khong
 */
void statOutOfStock() {
    printLine(65);
    cout << "DANH SACH SACH HET HANG\n";
    printLine(65);
    cout << left << setw(10) << "ISBN"
                 << setw(35) << "Tua sach"
                 << setw(12) << "The loai" << "\n";
    printLine(65);
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (book_stock[i] == 0) {
            cout << left << setw(10) << book_isbn[i]
                         << setw(35) << book_title[i]
                         << setw(12) << book_genre[i] << "\n";
            found++;
        }
    }
    if (!found) cout << "  (Khong co sach nao het hang)\n";
    printLine(65);
    cout << "Tong: " << found << " sach het hang\n";
}

/*
 * Ham: statisticsMenu
 * Mo ta: Menu con thong ke doanh thu va ton kho
 * Tham so: khong
 * Tra ve: khong
 */
void statisticsMenu() {
    int choice;
    do {
        clearScreen();
        printLine(45);
        cout << "            THONG KE\n";
        printLine(45);
        cout << "1. Tong so luong sach trong kho\n"
             << "2. So sach theo the loai\n"
             << "3. So khach hang theo loai the\n"
             << "4. Doanh thu theo ngay / thang\n"
             << "5. Danh sach sach het hang\n"
             << "0. Quay lai\n";
        printLine(45);
        cout << "Chon: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
            case 1: statTotalStock();      pauseScreen(); break;
            case 2: statBooksByGenre();    pauseScreen(); break;
            case 3: statCustomersByType(); pauseScreen(); break;
            case 4: statRevenueByDate();   pauseScreen(); break;
            case 5: statOutOfStock();      pauseScreen(); break;
            case 0: break;
            default: cout << "Lua chon khong hop le!\n"; pauseScreen();
        }
    } while (choice != 0);
}
