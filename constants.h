#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_CUSTOMER 100
#define MAX_BOOK     200
#define MAX_INVOICE  500
#define MAX_ITEMS    10

#define MAX_ID    20
#define MAX_NAME  100
#define MAX_PHONE 15
#define MAX_EMAIL 50
#define MAX_ADDR  150
#define MAX_DATE  12   // "DD/MM/YYYY\n\0" — extra byte lets fgets capture the newline

#define VAT_RATE        0.10
#define VIP_DISCOUNT    0.10
#define BULK_DISCOUNT   0.05
#define BULK_THRESHOLD  5

#endif
