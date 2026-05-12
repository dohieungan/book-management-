#ifndef INVOICE_H
#define INVOICE_H

#include "constants.h"

// Mang song song luu hoa don
extern char   inv_id[MAX_INVOICE][MAX_ID];
extern char   inv_cus_id[MAX_INVOICE][MAX_ID];
extern char   inv_date[MAX_INVOICE][MAX_DATE];
extern char   inv_isbn[MAX_INVOICE][MAX_ITEMS][MAX_ID];
extern int    inv_qty[MAX_INVOICE][MAX_ITEMS];
extern int    inv_item_count[MAX_INVOICE];
extern double inv_total[MAX_INVOICE];
extern int    numInvoices;

// Prototype
void createInvoice();
void printInvoice(int invoiceIndex);
void displayAllInvoices();
void generateInvoiceId(char* buffer);
double calculateTotal(int invoiceIndex, int cusIndex);
void invoiceMenu();

#endif
