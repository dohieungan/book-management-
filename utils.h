#ifndef UTILS_H
#define UTILS_H

// Doc chuoi an toan, tranh buffer overflow
void inputString(char* buffer, int maxLen, const char* prompt);

// In duong ke ngang
void printLine(int length);

// Xoa man hinh
void clearScreen();

// Dung chuong trinh, cho nguoi dung nhan Enter
void pauseScreen();

// Kiem tra ngay hop le DD/MM/YYYY, tra ve 1 neu hop le
int isValidDate(const char* date);

// Kiem tra so dien thoai (chi so, 9-11 ky tu)
int isValidPhone(const char* phone);

// Tim chuoi con khong phan biet hoa thuong, tra ve 1 neu tim thay
int strContainsCaseInsensitive(const char* haystack, const char* needle);

#endif
