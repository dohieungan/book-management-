#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "customer.h"
#include "invoice.h"
#include "utils.h"

using namespace std;

// Dinh nghia mang toan cuc
char   cus_id[MAX_CUSTOMER][MAX_ID];
char   cus_name[MAX_CUSTOMER][MAX_NAME];
char   cus_phone[MAX_CUSTOMER][MAX_PHONE];
char   cus_email[MAX_CUSTOMER][MAX_EMAIL];
char   cus_address[MAX_CUSTOMER][MAX_ADDR];
char   cus_regdate[MAX_CUSTOMER][MAX_DATE];
int    cus_type[MAX_CUSTOMER];
int    numCustomers = 0;

/*
 * Ham: findCustomerById
 * Mo ta: Tim khach hang theo ma KH
 * Tham so: id - ma can tim
 * Tra ve: vi tri trong mang hoac -1 neu khong tim thay
 */
int findCustomerById(const char* id) {
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(cus_id[i], id) == 0) return i;
    }
    return -1;
}

/*
 * Ham: findCustomerByPhone
 * Mo ta: Tim khach hang theo so dien thoai
 * Tham so: phone - so dien thoai can tim
 * Tra ve: vi tri trong mang hoac -1
 */
int findCustomerByPhone(const char* phone) {
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(cus_phone[i], phone) == 0) return i;
    }
    return -1;
}

/*
 * Ham: displayAllCustomers
 * Mo ta: Hien thi danh sach toan bo khach hang dang bang
 * Tham so: khong
 * Tra ve: khong
 */
void displayAllCustomers() {
    clearScreen();
    cout << "\n";
    printLine(115);
    cout << left << setw(8)  << "Ma KH"
                 << setw(22) << "Ho ten"
                 << setw(12) << "Dien thoai"
                 << setw(22) << "Email"
                 << setw(22) << "Dia chi"
                 << setw(12) << "Ngay DK"
                 << setw(8)  << "Loai" << "\n";
    printLine(115);
    if (numCustomers == 0) {
        cout << "  (Chua co khach hang nao)\n";
    }
    for (int i = 0; i < numCustomers; i++) {
        cout << left << setw(8)  << cus_id[i]
                     << setw(22) << cus_name[i]
                     << setw(12) << cus_phone[i]
                     << setw(22) << cus_email[i]
                     << setw(22) << cus_address[i]
                     << setw(12) << cus_regdate[i]
                     << setw(8)  << (cus_type[i] == 1 ? "VIP" : "Thuong") << "\n";
    }
    printLine(115);
}

/*
 * Ham: addCustomer
 * Mo ta: Them khach hang moi, tu sinh ma KH###, kiem tra trung so dien thoai
 * Tham so: khong
 * Tra ve: khong
 */
void addCustomer() {
    if (numCustomers >= MAX_CUSTOMER) {
        cout << "Danh sach khach hang da day!\n";
        pauseScreen();
        return;
    }

    int idx = numCustomers;
    char tmp[MAX_PHONE];

    int idNum = numCustomers + 1;
    do {
        snprintf(cus_id[idx], MAX_ID, "KH%03d", idNum++);
    } while (findCustomerById(cus_id[idx]) != -1);

    inputString(cus_name[idx], MAX_NAME, "Ho ten: ");
    if (strlen(cus_name[idx]) == 0) {
        cout << "Ten khong duoc de trong!\n";
        pauseScreen();
        return;
    }

    int phoneDone = 0;
    while (!phoneDone) {
        inputString(tmp, MAX_PHONE, "So dien thoai: ");
        if (!isValidPhone(tmp)) {
            cout << "SDT khong hop le (9-11 chu so). Nhap lai!\n";
        } else if (findCustomerByPhone(tmp) != -1) {
            cout << "SDT da ton tai trong he thong. Nhap lai!\n";
        } else {
            strcpy(cus_phone[idx], tmp);
            phoneDone = 1;
        }
    }

    inputString(cus_email[idx],   MAX_EMAIL, "Email: ");
    inputString(cus_address[idx], MAX_ADDR,  "Dia chi: ");

    int dateDone = 0;
    while (!dateDone) {
        inputString(cus_regdate[idx], MAX_DATE, "Ngay dang ky (DD/MM/YYYY): ");
        if (!isValidDate(cus_regdate[idx])) {
            cout << "Ngay khong hop le. Nhap lai!\n";
        } else {
            dateDone = 1;
        }
    }

    cout << "Loai khach (0=Thuong, 1=VIP): ";
    int t = 0;
    cin >> t;
    cin.ignore(1000, '\n');
    cus_type[idx] = (t == 1) ? 1 : 0;

    numCustomers++;
    cout << "Da them khach hang " << cus_id[idx] << " thanh cong!\n";
    pauseScreen();
}

/*
 * Ham: editCustomer
 * Mo ta: Sua thong tin khach hang theo ma KH
 * Tham so: khong
 * Tra ve: khong
 */
void editCustomer() {
    char id[MAX_ID];
    inputString(id, MAX_ID, "Nhap ma khach hang can sua: ");
    int idx = findCustomerById(id);
    if (idx == -1) {
        cout << "Khong tim thay khach hang " << id << "!\n";
        pauseScreen();
        return;
    }

    cout << "Dang sua: " << cus_id[idx] << " - " << cus_name[idx] << "\n";
    cout << "(Nhan Enter de giu nguyen tung truong)\n\n";

    char tmp[MAX_ADDR];

    // Ho ten
    cout << "Ho ten [" << cus_name[idx] << "]: ";
    cin.getline(tmp, MAX_NAME);
    if (strlen(tmp) > 0) strcpy(cus_name[idx], tmp);

    // So dien thoai
    char tmpPhone[MAX_PHONE];
    cout << "So dien thoai [" << cus_phone[idx] << "]: ";
    cin.getline(tmpPhone, MAX_PHONE);
    if (strlen(tmpPhone) > 0) {
        int phoneDone = 0;
        while (!phoneDone) {
            if (!isValidPhone(tmpPhone)) {
                cout << "SDT khong hop le. Nhap lai: ";
                cin.getline(tmpPhone, MAX_PHONE);
            } else {
                int found = findCustomerByPhone(tmpPhone);
                if (found != -1 && found != idx) {
                    cout << "SDT da ton tai. Nhap lai: ";
                    cin.getline(tmpPhone, MAX_PHONE);
                } else {
                    strcpy(cus_phone[idx], tmpPhone);
                    phoneDone = 1;
                }
            }
        }
    }

    // Email
    cout << "Email [" << cus_email[idx] << "]: ";
    cin.getline(tmp, MAX_EMAIL);
    if (strlen(tmp) > 0) strcpy(cus_email[idx], tmp);

    // Dia chi
    cout << "Dia chi [" << cus_address[idx] << "]: ";
    cin.getline(tmp, MAX_ADDR);
    if (strlen(tmp) > 0) strcpy(cus_address[idx], tmp);

    // Ngay dang ky
    char tmpDate[MAX_DATE];
    int dateDone = 0;
    while (!dateDone) {
        cout << "Ngay dang ky [" << cus_regdate[idx] << "]: ";
        cin.getline(tmpDate, MAX_DATE);
        if (strlen(tmpDate) == 0) {
            dateDone = 1; // giu nguyen
        } else if (!isValidDate(tmpDate)) {
            cout << "Ngay khong hop le (DD/MM/YYYY). Nhap lai!\n";
        } else {
            strcpy(cus_regdate[idx], tmpDate);
            dateDone = 1;
        }
    }

    // Loai khach
    cout << "Loai khach [" << (cus_type[idx] == 1 ? "VIP=1" : "Thuong=0") << "] (0/1, Enter=giu nguyen): ";
    char tStr[4];
    cin.getline(tStr, sizeof(tStr));
    if (strlen(tStr) > 0) {
        int t = tStr[0] - '0';
        if (t == 0 || t == 1) cus_type[idx] = t;
    }

    cout << "Cap nhat thanh cong!\n";
    pauseScreen();
}

/*
 * Ham: deleteCustomer
 * Mo ta: Xoa khach hang theo ma (chan neu con hoa don lien quan)
 * Tham so: khong
 * Tra ve: khong
 */
void deleteCustomer() {
    char id[MAX_ID];
    inputString(id, MAX_ID, "Nhap ma khach hang can xoa: ");
    int idx = findCustomerById(id);
    if (idx == -1) {
        cout << "Khong tim thay khach hang " << id << "!\n";
        pauseScreen();
        return;
    }

    for (int i = 0; i < numInvoices; i++) {
        if (strcmp(inv_cus_id[i], id) == 0) {
            cout << "Khong the xoa! Khach hang con hoa don trong he thong.\n";
            pauseScreen();
            return;
        }
    }

    cout << "Xac nhan xoa khach hang " << cus_id[idx] << " - " << cus_name[idx] << "? (y/n): ";
    char c;
    cin >> c;
    cin.ignore(1000, '\n');
    if (c != 'y' && c != 'Y') {
        cout << "Huy bo.\n";
        pauseScreen();
        return;
    }

    for (int i = idx; i < numCustomers - 1; i++) {
        strcpy(cus_id[i],      cus_id[i+1]);
        strcpy(cus_name[i],    cus_name[i+1]);
        strcpy(cus_phone[i],   cus_phone[i+1]);
        strcpy(cus_email[i],   cus_email[i+1]);
        strcpy(cus_address[i], cus_address[i+1]);
        strcpy(cus_regdate[i], cus_regdate[i+1]);
        cus_type[i] = cus_type[i+1];
    }
    numCustomers--;
    cout << "Da xoa khach hang " << id << "!\n";
    pauseScreen();
}

/*
 * Ham: searchCustomerByName
 * Mo ta: Tim kiem khach hang theo ho ten (tim mo, khong phan biet hoa thuong)
 * Tham so: name - chuoi ten can tim
 * Tra ve: khong
 */
void searchCustomerByName(const char* name) {
    int found = 0;
    printLine(115);
    cout << "Ket qua tim kiem theo ten: \"" << name << "\"\n";
    printLine(115);
    cout << left << setw(8)  << "Ma KH"
                 << setw(22) << "Ho ten"
                 << setw(12) << "Dien thoai"
                 << setw(22) << "Email"
                 << setw(22) << "Dia chi"
                 << setw(12) << "Ngay DK"
                 << setw(8)  << "Loai" << "\n";
    printLine(115);
    for (int i = 0; i < numCustomers; i++) {
        if (strContainsCaseInsensitive(cus_name[i], name)) {
            cout << left << setw(8)  << cus_id[i]
                         << setw(22) << cus_name[i]
                         << setw(12) << cus_phone[i]
                         << setw(22) << cus_email[i]
                         << setw(22) << cus_address[i]
                         << setw(12) << cus_regdate[i]
                         << setw(8)  << (cus_type[i] == 1 ? "VIP" : "Thuong") << "\n";
            found++;
        }
    }
    if (!found) cout << "  Khong tim thay ket qua nao.\n";
    printLine(115);
}

/*
 * Ham: customerMenu
 * Mo ta: Menu con quan ly khach hang
 * Tham so: khong
 * Tra ve: khong
 */
void customerMenu() {
    int choice;
    do {
        clearScreen();
        printLine(40);
        cout << "     QUAN LY KHACH HANG\n";
        printLine(40);
        cout << "1. Xem danh sach khach hang\n"
             << "2. Them khach hang moi\n"
             << "3. Sua thong tin khach hang\n"
             << "4. Xoa khach hang\n"
             << "5. Tim theo so dien thoai\n"
             << "6. Tim theo ho ten\n"
             << "0. Quay lai\n";
        printLine(40);
        cout << "Chon: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
            case 1:
                displayAllCustomers();
                pauseScreen();
                break;
            case 2:
                addCustomer();
                break;
            case 3:
                editCustomer();
                break;
            case 4:
                deleteCustomer();
                break;
            case 5: {
                char phone[MAX_PHONE];
                inputString(phone, MAX_PHONE, "Nhap so dien thoai: ");
                int idx = findCustomerByPhone(phone);
                if (idx == -1) {
                    cout << "Khong tim thay!\n";
                } else {
                    cout << "Ma: "    << cus_id[idx]
                         << " | Ten: " << cus_name[idx]
                         << " | Email: " << cus_email[idx]
                         << " | Loai: " << (cus_type[idx] == 1 ? "VIP" : "Thuong") << "\n";
                }
                pauseScreen();
                break;
            }
            case 6: {
                char name[MAX_NAME];
                inputString(name, MAX_NAME, "Nhap ten can tim: ");
                searchCustomerByName(name);
                pauseScreen();
                break;
            }
            case 0: break;
            default: cout << "Lua chon khong hop le!\n"; pauseScreen();
        }
    } while (choice != 0);
}
