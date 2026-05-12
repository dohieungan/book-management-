#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "constants.h"

// Mang song song luu thong tin khach hang
extern char   cus_id[MAX_CUSTOMER][MAX_ID];
extern char   cus_name[MAX_CUSTOMER][MAX_NAME];
extern char   cus_phone[MAX_CUSTOMER][MAX_PHONE];
extern char   cus_email[MAX_CUSTOMER][MAX_EMAIL];
extern char   cus_address[MAX_CUSTOMER][MAX_ADDR];
extern char   cus_regdate[MAX_CUSTOMER][MAX_DATE];
extern int    cus_type[MAX_CUSTOMER];   // 0 = Thuong, 1 = VIP
extern int    numCustomers;

// Prototype
void displayAllCustomers();
void addCustomer();
void editCustomer();
void deleteCustomer();
int  findCustomerByPhone(const char* phone);
void searchCustomerByName(const char* name);
int  findCustomerById(const char* id);
void customerMenu();

#endif
