# Bookstore Management System

A C++ console application for managing a bookstore: customers, books, invoices, inventory, and sales statistics.

---

## Prerequisites (macOS)

Only **g++** (GCC C++11) is required — no external libraries.

Install the compiler via Xcode Command Line Tools:

```bash
xcode-select --install
```

Verify the installation:

```bash
g++ --version   # must show version ≥ 7
make --version
```

---

## Build

### Option 1 — Makefile (recommended)

```bash
cd /path/to/25880243
make
```

This compiles all source files and produces the `25880243` binary in the same directory.

To remove the compiled binary:

```bash
make clean
```

### Option 2 — Manual g++ command

```bash
g++ -std=c++11 -Wall -o 25880243 \
    main.cpp utils.cpp customer.cpp book.cpp \
    invoice.cpp warehouse.cpp statistics.cpp
```

### Option 3 — VS Code

1. Open the project folder via **File → Open Folder**.
2. Install these extensions if not already present:
   - **C/C++** (`ms-vscode.cpptools`)
   - **CodeLLDB** (`vadimcn.vscode-lldb`)
3. Press **F5** and select the **RUN BOOKSTORE** configuration — VS Code builds and runs the program in the integrated terminal.

> Do not use the C/C++ Runner extension's play button — it only compiles the currently open file.

---

## Run

```bash
./25880243
```

On startup, the program automatically loads sample data: **5 customers, 10 books, 20 invoices**, so you can test all features immediately.

---

## Test

There is no automated test suite. Use the interactive menu to verify each module manually.

### Suggested test flow

**1. Customer management** (Menu → 1)

| Step | Action | Expected result |
|------|--------|-----------------|
| View list | Option 1 | 5 pre-loaded customers displayed |
| Add customer | Option 2 | New customer appears in the list |
| Edit customer | Option 3 | Updated fields reflected immediately |
| Delete customer with invoices | Option 4 | Blocked: "Khong the xoa! Khach hang con hoa don trong he thong." |
| Delete customer without invoices | Option 4 | Confirmation prompt (y/n); deleted on "y" |
| Search by phone (exact) | Option 5 | Returns customer only on 100% phone match |
| Search by name (exact) | Option 6 | Returns customer only on 100% name match (case-insensitive) |

**2. Book management** (Menu → 2)

| Step | Action | Expected result |
|------|--------|-----------------|
| View list | Option 1 | 10 pre-loaded books displayed |
| Add book | Option 2 | New book appears in the list |
| Edit book | Option 3 | Updated fields reflected immediately |
| Delete book linked to invoice | Option 4 | Blocked: "Khong the xoa! Sach co hoa don trong he thong." |
| Delete book with stock > 0 (no invoice) | Option 4 | Blocked: stock remaining warning |
| Delete book with stock = 0 and no invoice | Option 4 | Confirmation prompt (y/n); deleted on "y" |
| Search by ISBN | Option 5 | Matching book detail returned |
| Search by title | Option 6 | Matching books returned |

**3. Invoice / sales** (Menu → 3)

| Scenario | What to enter | Expected result |
|----------|--------------|-----------------|
| Bulk discount | Same-genre qty > 5 | 5% line discount applied |
| VIP discount | VIP customer | Additional 10% off subtotal |
| VAT | Any invoice | 10% VAT added to final total |

**4. Inventory** (Menu → 4)

- Option 1: verify low-stock items are highlighted.
- Option 2: enter ISBN then quantity; system updates stock immediately with no confirmation prompt (e.g. "Da nhap them 2 quyen. Ton kho moi: 20").

**5. Statistics** (Menu → 5)

- Check total stock count, breakdown by genre, customer type counts, and daily/monthly revenue reports.

---

## Project structure

```
25880243/
├── Makefile          # Build script
├── constants.h       # Array sizes, VAT rate, discount constants
├── utils.h/cpp       # Safe string input, date/phone validation, clearScreen/pauseScreen
├── customer.h/cpp    # Customer management
├── book.h/cpp        # Book management
├── invoice.h/cpp     # Invoice creation and pricing
├── warehouse.h/cpp   # Inventory management
├── statistics.h/cpp  # Revenue and stock statistics
└── main.cpp          # Main menu and sample data loader
```

---

## Business rules

| Rule | Detail |
|------|--------|
| Bulk discount | Buying > 5 copies of same-genre books → 5% off that line (`BULK_THRESHOLD=5`, `BULK_DISCOUNT=0.05`) |
| VIP discount | VIP customers get an additional 10% off the post-bulk subtotal (`VIP_DISCOUNT=0.10`) |
| VAT | 10% VAT applied to the total after all discounts (`VAT_RATE=0.10`) |
