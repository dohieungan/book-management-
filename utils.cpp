#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include "utils.h"

using namespace std;

/*
 * Ham: inputString
 * Mo ta: Doc chuoi tu stdin an toan bang cin.getline, tranh buffer overflow
 * Tham so: buffer - vung nho luu chuoi, maxLen - do dai toi da, prompt - thong bao hien thi
 * Tra ve: khong
 */
void inputString(char* buffer, int maxLen, const char* prompt) {
    cout << prompt;
    cin.getline(buffer, maxLen);
}

/*
 * Ham: printLine
 * Mo ta: In duong ke ngang de phan cach menu
 * Tham so: length - so ky tu '-'
 * Tra ve: khong
 */
void printLine(int length) {
    for (int i = 0; i < length; i++) cout << '-';
    cout << "\n";
}

/*
 * Ham: clearScreen
 * Mo ta: Xoa man hinh console (tuong thich Windows va macOS/Linux)
 * Tham so: khong
 * Tra ve: khong
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H" << flush;
#endif
}

/*
 * Ham: pauseScreen
 * Mo ta: Dung chuong trinh, cho nguoi dung nhan Enter de tiep tuc
 * Tham so: khong
 * Tra ve: khong
 */
void pauseScreen() {
#ifdef _WIN32
    system("pause");
#else
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
#endif
}

/*
 * Ham: isValidDate
 * Mo ta: Kiem tra chuoi ngay theo dinh dang DD/MM/YYYY
 * Tham so: date - chuoi ngay can kiem tra
 * Tra ve: 1 neu hop le, 0 neu khong
 */
int isValidDate(const char* date) {
    if (strlen(date) != 10) return 0;
    if (date[2] != '/' || date[5] != '/') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return 0;
    }
    int dd   = (date[0]-'0')*10 + (date[1]-'0');
    int mm   = (date[3]-'0')*10 + (date[4]-'0');
    int yyyy = (date[6]-'0')*1000 + (date[7]-'0')*100
             + (date[8]-'0')*10  + (date[9]-'0');
    if (mm < 1 || mm > 12) return 0;
    if (dd < 1 || dd > 31) return 0;
    if (yyyy < 1900)        return 0;
    int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if ((yyyy % 4 == 0 && yyyy % 100 != 0) || yyyy % 400 == 0) days[2] = 29;
    if (dd > days[mm]) return 0;
    return 1;
}

/*
 * Ham: isValidPhone
 * Mo ta: Kiem tra so dien thoai chi gom chu so, do dai 9-11 ky tu
 * Tham so: phone - chuoi so dien thoai
 * Tra ve: 1 neu hop le, 0 neu khong
 */
int isValidPhone(const char* phone) {
    int len = strlen(phone);
    if (len < 9 || len > 11) return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

/*
 * Ham: strContainsCaseInsensitive
 * Mo ta: Kiem tra haystack co chua needle khong, khong phan biet hoa thuong
 * Tham so: haystack - chuoi goc, needle - chuoi can tim
 * Tra ve: 1 neu tim thay, 0 neu khong
 */
int strContainsCaseInsensitive(const char* haystack, const char* needle) {
    int hlen = strlen(haystack);
    int nlen = strlen(needle);
    if (nlen == 0) return 1;
    if (nlen > hlen) return 0;
    for (int i = 0; i <= hlen - nlen; i++) {
        int match = 1;
        for (int j = 0; j < nlen; j++) {
            if (tolower((unsigned char)haystack[i+j]) != tolower((unsigned char)needle[j])) {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}
