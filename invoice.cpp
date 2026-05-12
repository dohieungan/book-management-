#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "invoice.h"
#include "customer.h"
#include "book.h"
#include "utils.h"

using namespace std;

// Dinh nghia mang toan cuc
char   inv_id[MAX_INVOICE][MAX_ID];
char   inv_cus_id[MAX_INVOICE][MAX_ID];
char   inv_date[MAX_INVOICE][MAX_DATE];
char   inv_isbn[MAX_INVOICE][MAX_ITEMS][MAX_ID];
int    inv_qty[MAX_INVOICE][MAX_ITEMS];
int    inv_item_count[MAX_INVOICE];
double inv_total[MAX_INVOICE];
int    numInvoices = 0;

/*
 * Ham: generateInvoiceId
 * Mo ta: Tu dong sinh ma hoa don HD### dam bao khong trung
 * Tham so: buffer - vung nho luu ma sinh ra
 * Tra ve: khong
 */
void generateInvoiceId(char* buffer) {
    int idNum = numInvoices + 1;
    do {
        snprintf(buffer, MAX_ID, "HD%03d", idNum++);
        int dup = 0;
        for (int i = 0; i < numInvoices; i++) {
            if (strcmp(inv_id[i], buffer) == 0) { dup = 1; break; }
        }
        if (!dup) break;
    } while (1);
}

/*
 * Ham: calculateTotal
 * Mo ta: Tinh tong tien hoa don theo quy tac nghiep vu:
 *        1. Giam 5% neu tong qty cung the loai trong hoa don > 5
 *        2. Giam them 10% neu khach VIP
 *        3. Cong thue VAT 10%
 * Tham so: invoiceIndex - vi tri hoa don, cusIndex - vi tri khach hang
 * Tra ve: tong tien cuoi cung
 */
double calculateTotal(int invoiceIndex, int cusIndex) {
    int inv = invoiceIndex;
    int nc  = inv_item_count[inv];
    double lineTotal[MAX_ITEMS] = {0};

    for (int i = 0; i < nc; i++) {
        int bi = findBookByISBN(inv_isbn[inv][i]);
        if (bi == -1) continue;

        int genreQty = 0;
        for (int j = 0; j < nc; j++) {
            int bj = findBookByISBN(inv_isbn[inv][j]);
            if (bj != -1 && strcmp(book_genre[bj], book_genre[bi]) == 0) {
                genreQty += inv_qty[inv][j];
            }
        }

        lineTotal[i] = book_price[bi] * inv_qty[inv][i];
        if (genreQty > BULK_THRESHOLD) {
            lineTotal[i] *= (1.0 - BULK_DISCOUNT);
        }
    }

    double subtotal = 0;
    for (int i = 0; i < nc; i++) subtotal += lineTotal[i];

    if (cusIndex >= 0 && cus_type[cusIndex] == 1) {
        subtotal *= (1.0 - VIP_DISCOUNT);
    }

    return subtotal * (1.0 + VAT_RATE);
}

/*
 * Ham: createInvoice
 * Mo ta: Tao hoa don moi: nhap ma KH, danh sach ISBN + so luong, tinh tien, tru kho
 * Tham so: khong
 * Tra ve: khong
 */
void createInvoice() {
    if (numInvoices >= MAX_INVOICE) {
        cout << "Danh sach hoa don da day!\n";
        pauseScreen();
        return;
    }

    int inv = numInvoices;
    generateInvoiceId(inv_id[inv]);

    char cusId[MAX_ID];
    inputString(cusId, MAX_ID, "Nhap ma khach hang: ");
    int ci = findCustomerById(cusId);
    if (ci == -1) {
        cout << "Khong tim thay khach hang " << cusId << "!\n";
        pauseScreen();
        return;
    }
    strcpy(inv_cus_id[inv], cusId);

    int dateDone = 0;
    while (!dateDone) {
        inputString(inv_date[inv], MAX_DATE, "Ngay lap hoa don (DD/MM/YYYY): ");
        if (!isValidDate(inv_date[inv])) {
            cout << "Ngay khong hop le. Nhap lai!\n";
        } else {
            dateDone = 1;
        }
    }

    int itemCount = 0;
    cout << "Nhap danh sach sach (toi da " << MAX_ITEMS << " dong, ISBN trong = ket thuc):\n";

    while (itemCount < MAX_ITEMS) {
        char isbn[MAX_ID];
        cout << "  ISBN sach thu " << (itemCount + 1) << ": ";
        cin.getline(isbn, MAX_ID);

        if (strlen(isbn) == 0) break;

        int bi = findBookByISBN(isbn);
        if (bi == -1) {
            cout << "  Khong tim thay ISBN " << isbn << ". Bo qua.\n";
            continue;
        }

        cout << "  So luong (ton kho: " << book_stock[bi] << "): ";
        int qty;
        cin >> qty;
        cin.ignore(1000, '\n');

        if (qty <= 0) {
            cout << "  So luong khong hop le. Bo qua.\n";
            continue;
        }
        if (qty > book_stock[bi]) {
            cout << "  Khong du hang! Chi con " << book_stock[bi] << " quyen.\n";
            pauseScreen();
            continue;
        }

        int dup = -1;
        for (int k = 0; k < itemCount; k++) {
            if (strcmp(inv_isbn[inv][k], isbn) == 0) { dup = k; break; }
        }
        if (dup != -1) {
            if (inv_qty[inv][dup] + qty > book_stock[bi]) {
                cout << "  Tong so luong vuot qua ton kho!\n";
                continue;
            }
            inv_qty[inv][dup] += qty;
        } else {
            strcpy(inv_isbn[inv][itemCount], isbn);
            inv_qty[inv][itemCount] = qty;
            itemCount++;
        }
    }

    if (itemCount == 0) {
        cout << "Khong co san pham nao. Huy tao hoa don.\n";
        pauseScreen();
        return;
    }

    inv_item_count[inv] = itemCount;
    inv_total[inv] = calculateTotal(inv, ci);

    for (int i = 0; i < itemCount; i++) {
        int bi = findBookByISBN(inv_isbn[inv][i]);
        if (bi != -1) book_stock[bi] -= inv_qty[inv][i];
    }

    numInvoices++;
    cout << "\nDa tao hoa don " << inv_id[inv] << " thanh cong!\n";
    printInvoice(inv);
    pauseScreen();
}

/*
 * Ham: printInvoice
 * Mo ta: In chi tiet mot hoa don dang receipt ra man hinh
 * Tham so: invoiceIndex - vi tri hoa don trong mang
 * Tra ve: khong
 */
void printInvoice(int inv) {
    if (inv < 0 || inv >= numInvoices) {
        cout << "Hoa don khong ton tai!\n";
        return;
    }

    int ci = findCustomerById(inv_cus_id[inv]);

    printLine(60);
    cout << "           HOA DON BAN HANG\n";
    printLine(60);
    cout << "Ma HD    : " << inv_id[inv]   << "\n"
         << "Ngay     : " << inv_date[inv] << "\n"
         << "Khach    : " << inv_cus_id[inv];
    if (ci != -1)
        cout << " - " << cus_name[ci] << " (" << (cus_type[ci] == 1 ? "VIP" : "Thuong") << ")";
    cout << "\n";
    printLine(60);

    cout << left << setw(5)  << "STT"
                 << setw(25) << "Tua sach"
         << right << setw(6)  << "SL"
                  << setw(10) << "Don gia"
                  << setw(12) << "Thanh tien" << "\n";
    printLine(60);

    int nc = inv_item_count[inv];
    double subtotalRaw = 0;

    for (int i = 0; i < nc; i++) {
        int bi = findBookByISBN(inv_isbn[inv][i]);
        if (bi == -1) continue;

        int genreQty = 0;
        for (int j = 0; j < nc; j++) {
            int bj = findBookByISBN(inv_isbn[inv][j]);
            if (bj != -1 && strcmp(book_genre[bj], book_genre[bi]) == 0) {
                genreQty += inv_qty[inv][j];
            }
        }

        double linePrice = book_price[bi];
        int hasDiscount = (genreQty > BULK_THRESHOLD);
        if (hasDiscount) linePrice *= (1.0 - BULK_DISCOUNT);
        double lt = linePrice * inv_qty[inv][i];
        subtotalRaw += lt;

        cout << left  << setw(5)  << (i + 1)
                      << setw(25) << book_title[bi]
             << right << fixed << setprecision(0)
                      << setw(6)  << inv_qty[inv][i]
                      << setw(10) << linePrice
                      << setw(12) << lt;
        if (hasDiscount) cout << " (-5%)";
        cout << "\n";
    }

    printLine(60);
    cout << left  << setw(40) << "Tong cong:"
         << right << fixed << setprecision(0) << setw(18) << subtotalRaw << "\n";

    if (ci != -1 && cus_type[ci] == 1) {
        cout << left  << setw(40) << "Giam VIP (10%):"
             << right << setw(18) << (-subtotalRaw * VIP_DISCOUNT) << "\n";
        subtotalRaw *= (1.0 - VIP_DISCOUNT);
    }
    cout << left  << setw(40) << "Thue VAT (10%):"
         << right << setw(18) << (subtotalRaw * VAT_RATE) << "\n";
    printLine(60);
    cout << left  << setw(40) << "TONG THANH TOAN:"
         << right << setw(18) << inv_total[inv] << "\n";
    printLine(60);
}

/*
 * Ham: displayAllInvoices
 * Mo ta: Hien thi tat ca hoa don dang danh sach
 * Tham so: khong
 * Tra ve: khong
 */
void displayAllInvoices() {
    clearScreen();
    cout << "\n";
    printLine(67);
    cout << left << setw(8)  << "Ma HD"
                 << setw(8)  << "Ma KH"
                 << setw(12) << "Ngay lap"
                 << setw(24) << "San pham (ISBN x SL)"
         << right << setw(15) << "Tong tien" << "\n";
    printLine(67);
    if (numInvoices == 0) {
        cout << "  (Chua co hoa don nao)\n";
    }
    for (int i = 0; i < numInvoices; i++) {
        // In dong dau: ma HD, ma KH, ngay, san pham thu 1, tong tien
        cout << left << setw(8)  << inv_id[i]
                     << setw(8)  << inv_cus_id[i]
                     << setw(12) << inv_date[i];

        // San pham thu 1
        if (inv_item_count[i] > 0) {
            char item[24];
            snprintf(item, sizeof(item), "%s x%d", inv_isbn[i][0], inv_qty[i][0]);
            cout << left << setw(24) << item;
        }

        cout << right << fixed << setprecision(0) << setw(15) << inv_total[i] << "\n";

        // Cac san pham tiep theo in thut vao duoi dong tren
        for (int j = 1; j < inv_item_count[i]; j++) {
            char item[24];
            snprintf(item, sizeof(item), "%s x%d", inv_isbn[i][j], inv_qty[i][j]);
            cout << left << setw(28) << "" << setw(24) << item << "\n";
        }
    }
    printLine(67);
}

/*
 * Ham: invoiceMenu
 * Mo ta: Menu con quan ly hoa don
 * Tham so: khong
 * Tra ve: khong
 */
void invoiceMenu() {
    int choice;
    do {
        clearScreen();
        printLine(40);
        cout << "     LAP HOA DON BAN HANG\n";
        printLine(40);
        cout << "1. Tao hoa don moi\n"
             << "2. Xem tat ca hoa don\n"
             << "3. Xem chi tiet hoa don\n"
             << "0. Quay lai\n";
        printLine(40);
        cout << "Chon: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
            case 1:
                createInvoice();
                break;
            case 2:
                displayAllInvoices();
                pauseScreen();
                break;
            case 3: {
                char id[MAX_ID];
                inputString(id, MAX_ID, "Nhap ma hoa don: ");
                int found = -1;
                for (int i = 0; i < numInvoices; i++) {
                    if (strcmp(inv_id[i], id) == 0) { found = i; break; }
                }
                if (found == -1) cout << "Khong tim thay hoa don " << id << "!\n";
                else printInvoice(found);
                pauseScreen();
                break;
            }
            case 0: break;
            default: cout << "Lua chon khong hop le!\n"; pauseScreen();
        }
    } while (choice != 0);
}
