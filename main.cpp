#include <iostream>
#include <cstring>
#include <cstdlib>
#include "constants.h"
#include "utils.h"
#include "customer.h"
#include "book.h"
#include "invoice.h"
#include "warehouse.h"
#include "statistics.h"

using namespace std;

/*
 * Ham: loadSampleData
 * Mo ta: Nap du lieu mau (5 khach hang, 10 cuon sach, 20 hoa don)
 *        Ton kho la gia tri HIEN TAI sau tat ca hoa don mau.
 *        Tong tien hoa don duoc tinh truoc theo dung quy tac nghiep vu.
 * Tham so: khong
 * Tra ve: khong
 */
void loadSampleData() {
    // =========================================================
    // KHACH HANG (5 ban ghi)
    // =========================================================
    strcpy(cus_id[0],      "KH001");
    strcpy(cus_name[0],    "Nguyen Van An");
    strcpy(cus_phone[0],   "0901234567");
    strcpy(cus_email[0],   "an@gmail.com");
    strcpy(cus_address[0], "Q1 HCM");
    strcpy(cus_regdate[0], "01/01/2024");
    cus_type[0] = 0;

    strcpy(cus_id[1],      "KH002");
    strcpy(cus_name[1],    "Tran Thi Binh");
    strcpy(cus_phone[1],   "0912345678");
    strcpy(cus_email[1],   "binh@gmail.com");
    strcpy(cus_address[1], "Q3 HCM");
    strcpy(cus_regdate[1], "15/03/2024");
    cus_type[1] = 1; // VIP

    strcpy(cus_id[2],      "KH003");
    strcpy(cus_name[2],    "Le Minh Chau");
    strcpy(cus_phone[2],   "0923456789");
    strcpy(cus_email[2],   "chau@gmail.com");
    strcpy(cus_address[2], "Binh Thanh HCM");
    strcpy(cus_regdate[2], "20/06/2024");
    cus_type[2] = 0;

    strcpy(cus_id[3],      "KH004");
    strcpy(cus_name[3],    "Pham Thi Dung");
    strcpy(cus_phone[3],   "0934567890");
    strcpy(cus_email[3],   "dung@gmail.com");
    strcpy(cus_address[3], "Q7 HCM");
    strcpy(cus_regdate[3], "10/08/2024");
    cus_type[3] = 1; // VIP

    strcpy(cus_id[4],      "KH005");
    strcpy(cus_name[4],    "Hoang Van Em");
    strcpy(cus_phone[4],   "0945678901");
    strcpy(cus_email[4],   "em@gmail.com");
    strcpy(cus_address[4], "Thu Duc HCM");
    strcpy(cus_regdate[4], "05/09/2024");
    cus_type[4] = 0;

    numCustomers = 5;

    // =========================================================
    // SACH (10 dau sach)
    // book_stock la ton kho HIEN TAI sau tat ca 20 hoa don mau
    // =========================================================

    // --- Cong nghe ---
    strcpy(book_isbn[0],      "ISBN001");
    strcpy(book_title[0],     "Lap trinh C++");
    strcpy(book_author[0],    "Bjarne Stroustrup");
    strcpy(book_publisher[0], "NXB Tre");
    book_year[0]  = 2020;
    strcpy(book_genre[0],     "Cong nghe");
    book_cost[0]  = 80000;
    book_price[0] = 120000;
    book_stock[0] = 37;

    strcpy(book_isbn[1],      "ISBN002");
    strcpy(book_title[1],     "Cau truc du lieu");
    strcpy(book_author[1],    "Nguyen Thanh Hai");
    strcpy(book_publisher[1], "NXB DHQG");
    book_year[1]  = 2019;
    strcpy(book_genre[1],     "Cong nghe");
    book_cost[1]  = 60000;
    book_price[1] = 95000;
    book_stock[1] = 18;

    strcpy(book_isbn[4],      "ISBN005");
    strcpy(book_title[4],     "Python co ban");
    strcpy(book_author[4],    "Guido van Rossum");
    strcpy(book_publisher[4], "NXB Tre");
    book_year[4]  = 2022;
    strcpy(book_genre[4],     "Cong nghe");
    book_cost[4]  = 70000;
    book_price[4] = 110000;
    book_stock[4] = 11;

    strcpy(book_isbn[7],      "ISBN008");
    strcpy(book_title[7],     "Lap trinh Java");
    strcpy(book_author[7],    "Nguyen Manh Hung");
    strcpy(book_publisher[7], "NXB DHQG");
    book_year[7]  = 2021;
    strcpy(book_genre[7],     "Cong nghe");
    book_cost[7]  = 75000;
    book_price[7] = 115000;
    book_stock[7] = 16;

    // --- Ky nang ---
    strcpy(book_isbn[2],      "ISBN003");
    strcpy(book_title[2],     "Dac nhan tam");
    strcpy(book_author[2],    "Dale Carnegie");
    strcpy(book_publisher[2], "NXB Tong hop");
    book_year[2]  = 2018;
    strcpy(book_genre[2],     "Ky nang");
    book_cost[2]  = 45000;
    book_price[2] = 75000;
    book_stock[2] = 83;

    strcpy(book_isbn[6],      "ISBN007");
    strcpy(book_title[6],     "Atomic Habits");
    strcpy(book_author[6],    "James Clear");
    strcpy(book_publisher[6], "NXB Lao Dong");
    book_year[6]  = 2021;
    strcpy(book_genre[6],     "Ky nang");
    book_cost[6]  = 65000;
    book_price[6] = 105000;
    book_stock[6] = 45;

    strcpy(book_isbn[9],      "ISBN010");
    strcpy(book_title[9],     "Tu duy nhanh va cham");
    strcpy(book_author[9],    "Daniel Kahneman");
    strcpy(book_publisher[9], "NXB Tre");
    book_year[9]  = 2022;
    strcpy(book_genre[9],     "Ky nang");
    book_cost[9]  = 90000;
    book_price[9] = 145000;
    book_stock[9] = 21;

    // --- Van hoc ---
    strcpy(book_isbn[3],      "ISBN004");
    strcpy(book_title[3],     "Nha gia kim");
    strcpy(book_author[3],    "Paulo Coelho");
    strcpy(book_publisher[3], "NXB Van hoc");
    book_year[3]  = 2015;
    strcpy(book_genre[3],     "Van hoc");
    book_cost[3]  = 50000;
    book_price[3] = 80000;
    book_stock[3] = 0; // het hang

    strcpy(book_isbn[5],      "ISBN006");
    strcpy(book_title[5],     "So Do");
    strcpy(book_author[5],    "Vu Trong Phung");
    strcpy(book_publisher[5], "NXB Van hoc");
    book_year[5]  = 2019;
    strcpy(book_genre[5],     "Van hoc");
    book_cost[5]  = 45000;
    book_price[5] = 75000;
    book_stock[5] = 30;

    strcpy(book_isbn[8],      "ISBN009");
    strcpy(book_title[8],     "Mat Biec");
    strcpy(book_author[8],    "Nguyen Nhat Anh");
    strcpy(book_publisher[8], "NXB Tre");
    book_year[8]  = 2020;
    strcpy(book_genre[8],     "Van hoc");
    book_cost[8]  = 35000;
    book_price[8] = 55000;
    book_stock[8] = 67;

    numBooks = 10;

    // =========================================================
    // HOA DON (20 hoa don — thang 01 va 02/2025)
    // Quy tac tinh tien: giam 5% neu qty cung the loai > 5,
    // giam them 10% VIP, cong VAT 10%.
    // =========================================================

    strcpy(inv_id[0], "HD001"); strcpy(inv_cus_id[0], "KH001"); strcpy(inv_date[0], "05/01/2025");
    strcpy(inv_isbn[0][0], "ISBN001"); inv_qty[0][0] = 2;
    strcpy(inv_isbn[0][1], "ISBN003"); inv_qty[0][1] = 1;
    inv_item_count[0] = 2; inv_total[0] = 346500.0;

    strcpy(inv_id[1], "HD002"); strcpy(inv_cus_id[1], "KH002"); strcpy(inv_date[1], "08/01/2025");
    strcpy(inv_isbn[1][0], "ISBN002"); inv_qty[1][0] = 2;
    strcpy(inv_isbn[1][1], "ISBN005"); inv_qty[1][1] = 2;
    inv_item_count[1] = 2; inv_total[1] = 405900.0;

    strcpy(inv_id[2], "HD003"); strcpy(inv_cus_id[2], "KH003"); strcpy(inv_date[2], "10/01/2025");
    strcpy(inv_isbn[2][0], "ISBN006"); inv_qty[2][0] = 3;
    strcpy(inv_isbn[2][1], "ISBN009"); inv_qty[2][1] = 2;
    inv_item_count[2] = 2; inv_total[2] = 583000.0;

    strcpy(inv_id[3], "HD004"); strcpy(inv_cus_id[3], "KH004"); strcpy(inv_date[3], "12/01/2025");
    strcpy(inv_isbn[3][0], "ISBN007"); inv_qty[3][0] = 3;
    strcpy(inv_isbn[3][1], "ISBN010"); inv_qty[3][1] = 2;
    inv_item_count[3] = 2; inv_total[3] = 598950.0;

    strcpy(inv_id[4], "HD005"); strcpy(inv_cus_id[4], "KH005"); strcpy(inv_date[4], "15/01/2025");
    strcpy(inv_isbn[4][0], "ISBN001"); inv_qty[4][0] = 3;
    strcpy(inv_isbn[4][1], "ISBN008"); inv_qty[4][1] = 2;
    inv_item_count[4] = 2; inv_total[4] = 649000.0;

    strcpy(inv_id[5], "HD006"); strcpy(inv_cus_id[5], "KH001"); strcpy(inv_date[5], "18/01/2025");
    strcpy(inv_isbn[5][0], "ISBN003"); inv_qty[5][0] = 6;
    inv_item_count[5] = 1; inv_total[5] = 470250.0;

    strcpy(inv_id[6], "HD007"); strcpy(inv_cus_id[6], "KH002"); strcpy(inv_date[6], "20/01/2025");
    strcpy(inv_isbn[6][0], "ISBN007"); inv_qty[6][0] = 4;
    strcpy(inv_isbn[6][1], "ISBN010"); inv_qty[6][1] = 3;
    inv_item_count[6] = 2; inv_total[6] = 804127.5;

    strcpy(inv_id[7], "HD008"); strcpy(inv_cus_id[7], "KH003"); strcpy(inv_date[7], "22/01/2025");
    strcpy(inv_isbn[7][0], "ISBN001"); inv_qty[7][0] = 2;
    strcpy(inv_isbn[7][1], "ISBN002"); inv_qty[7][1] = 2;
    strcpy(inv_isbn[7][2], "ISBN005"); inv_qty[7][2] = 2;
    inv_item_count[7] = 3; inv_total[7] = 679250.0;

    strcpy(inv_id[8], "HD009"); strcpy(inv_cus_id[8], "KH004"); strcpy(inv_date[8], "25/01/2025");
    strcpy(inv_isbn[8][0], "ISBN009"); inv_qty[8][0] = 4;
    inv_item_count[8] = 1; inv_total[8] = 217800.0;

    strcpy(inv_id[9], "HD010"); strcpy(inv_cus_id[9], "KH005"); strcpy(inv_date[9], "28/01/2025");
    strcpy(inv_isbn[9][0], "ISBN006"); inv_qty[9][0] = 2;
    strcpy(inv_isbn[9][1], "ISBN003"); inv_qty[9][1] = 3;
    inv_item_count[9] = 2; inv_total[9] = 555500.0;

    strcpy(inv_id[10], "HD011"); strcpy(inv_cus_id[10], "KH001"); strcpy(inv_date[10], "02/02/2025");
    strcpy(inv_isbn[10][0], "ISBN007"); inv_qty[10][0] = 2;
    strcpy(inv_isbn[10][1], "ISBN010"); inv_qty[10][1] = 4;
    inv_item_count[10] = 2; inv_total[10] = 825550.0;

    strcpy(inv_id[11], "HD012"); strcpy(inv_cus_id[11], "KH002"); strcpy(inv_date[11], "05/02/2025");
    strcpy(inv_isbn[11][0], "ISBN001"); inv_qty[11][0] = 3;
    strcpy(inv_isbn[11][1], "ISBN008"); inv_qty[11][1] = 3;
    inv_item_count[11] = 2; inv_total[11] = 663052.5;

    strcpy(inv_id[12], "HD013"); strcpy(inv_cus_id[12], "KH003"); strcpy(inv_date[12], "08/02/2025");
    strcpy(inv_isbn[12][0], "ISBN006"); inv_qty[12][0] = 3;
    strcpy(inv_isbn[12][1], "ISBN009"); inv_qty[12][1] = 3;
    inv_item_count[12] = 2; inv_total[12] = 611325.0;

    strcpy(inv_id[13], "HD014"); strcpy(inv_cus_id[13], "KH004"); strcpy(inv_date[13], "10/02/2025");
    strcpy(inv_isbn[13][0], "ISBN002"); inv_qty[13][0] = 3;
    strcpy(inv_isbn[13][1], "ISBN005"); inv_qty[13][1] = 3;
    inv_item_count[13] = 2; inv_total[13] = 578407.5;

    strcpy(inv_id[14], "HD015"); strcpy(inv_cus_id[14], "KH005"); strcpy(inv_date[14], "12/02/2025");
    strcpy(inv_isbn[14][0], "ISBN003"); inv_qty[14][0] = 5;
    strcpy(inv_isbn[14][1], "ISBN007"); inv_qty[14][1] = 3;
    inv_item_count[14] = 2; inv_total[14] = 721050.0;

    strcpy(inv_id[15], "HD016"); strcpy(inv_cus_id[15], "KH001"); strcpy(inv_date[15], "15/02/2025");
    strcpy(inv_isbn[15][0], "ISBN009"); inv_qty[15][0] = 4;
    strcpy(inv_isbn[15][1], "ISBN006"); inv_qty[15][1] = 2;
    inv_item_count[15] = 2; inv_total[15] = 522500.0;

    strcpy(inv_id[16], "HD017"); strcpy(inv_cus_id[16], "KH002"); strcpy(inv_date[16], "18/02/2025");
    strcpy(inv_isbn[16][0], "ISBN010"); inv_qty[16][0] = 5;
    inv_item_count[16] = 1; inv_total[16] = 717750.0;

    strcpy(inv_id[17], "HD018"); strcpy(inv_cus_id[17], "KH003"); strcpy(inv_date[17], "20/02/2025");
    strcpy(inv_isbn[17][0], "ISBN001"); inv_qty[17][0] = 3;
    strcpy(inv_isbn[17][1], "ISBN002"); inv_qty[17][1] = 2;
    inv_item_count[17] = 2; inv_total[17] = 605000.0;

    strcpy(inv_id[18], "HD019"); strcpy(inv_cus_id[18], "KH004"); strcpy(inv_date[18], "22/02/2025");
    strcpy(inv_isbn[18][0], "ISBN007"); inv_qty[18][0] = 3;
    strcpy(inv_isbn[18][1], "ISBN003"); inv_qty[18][1] = 2;
    inv_item_count[18] = 2; inv_total[18] = 460350.0;

    strcpy(inv_id[19], "HD020"); strcpy(inv_cus_id[19], "KH005"); strcpy(inv_date[19], "25/02/2025");
    strcpy(inv_isbn[19][0], "ISBN008"); inv_qty[19][0] = 4;
    strcpy(inv_isbn[19][1], "ISBN002"); inv_qty[19][1] = 3;
    inv_item_count[19] = 2; inv_total[19] = 778525.0;

    numInvoices = 20;
}

int main() {
    loadSampleData();
    cout << "Du lieu mau da duoc nap: 5 khach hang, 10 dau sach, 20 hoa don.\n";
    pauseScreen();

    int choice;
    do {
        clearScreen();
        printLine(40);
        cout << "   ===== QUAN LY NHA SACH =====\n";
        printLine(40);
        cout << "1. Quan ly khach hang\n"
             << "2. Quan ly sach\n"
             << "3. Lap hoa don ban hang\n"
             << "4. Quan ly kho\n"
             << "5. Thong ke\n"
             << "0. Thoat\n";
        printLine(40);
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
            case 1: customerMenu();   break;
            case 2: bookMenu();       break;
            case 3: invoiceMenu();    break;
            case 4: warehouseMenu();  break;
            case 5: statisticsMenu(); break;
            case 0:
                cout << "Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                pauseScreen();
        }
    } while (choice != 0);

    return 0;
}
