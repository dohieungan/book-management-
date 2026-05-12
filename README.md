# Quản Lý Nhà Sách

Chương trình C++ console quản lý nhà sách: Khách hàng, Sách, Hóa đơn, Kho, Thống kê.

## Yêu cầu

Chỉ cần trình biên dịch **g++** (GCC C++) hỗ trợ C++11 — không cần cài thêm thư viện ngoài.

| Hệ điều hành | Cách cài g++ |
|---|---|
| **macOS** | `xcode-select --install` |
| **Ubuntu / Debian** | `sudo apt update && sudo apt install g++ make` |
| **Fedora / RHEL** | `sudo dnf install gcc-c++ make` |
| **Windows** | Cài [MSYS2](https://www.msys2.org/) → trong terminal MSYS2 chạy: `pacman -S mingw-w64-ucrt-x86_64-gcc make` |

> Kiểm tra đã cài đúng chưa: `g++ --version` — phải hiện phiên bản ≥ 7.

---

## Build

### Cách 1 — dùng Makefile (khuyên dùng)

```bash
# macOS / Linux
cd /path/to/NhaSach
make
./25880243

# Windows (MSYS2 terminal)
cd /path/to/NhaSach
make
./25880243.exe
```

### Cách 2 — lệnh g++ thủ công

```bash
# macOS / Linux
g++ -std=c++11 -Wall -o 25880243 \
    main.cpp utils.cpp customer.cpp book.cpp \
    invoice.cpp warehouse.cpp statistics.cpp
./NhaSach

# Windows (MSYS2 terminal)
g++ -std=c++11 -Wall -o 25880243.exe \
    main.cpp utils.cpp customer.cpp book.cpp \
    invoice.cpp warehouse.cpp statistics.cpp
./NhaSach.exe
```

### Cách 3 — Visual Studio Code

1. Mở thư mục `NhaSach/` bằng **File → Open Folder**.
2. Cài hai extension sau nếu chưa có:
   - **C/C++** — `ms-vscode.cpptools`
   - **CodeLLDB** — `vadimcn.vscode-lldb`
3. Nhấn **F5** → chọn cấu hình **RUN BOOKSTORE** → chương trình tự build và chạy ngay trong terminal tích hợp của VS Code.

> Lưu ý: không dùng nút ▶ của extension C/C++ Runner — nó chỉ biên dịch file đang mở, không đủ cho dự án nhiều file này.

### Cách 4 — Visual Studio 2019+

1. Tạo project **Empty C++ Project**.
2. Thêm tất cả file `.cpp` vào **Source Files** và `.h` vào **Header Files**.
3. Nhấn **Ctrl+F5** để build và chạy.

---

## Lưu ý quan trọng

- **Chỉ biên dịch từ mã nguồn** — các file `25880243`, `25880243.exe` trong thư mục là file đã biên dịch sẵn trên máy khác, **không dùng được** trên máy mới. Hãy tự build bằng lệnh trên.
- Mã nguồn dùng thư viện chuẩn C++ (`iostream`, `iomanip`, `cstring`, `cstdlib`) — không phụ thuộc gì ngoài.
- Hàm xóa màn hình và dừng chương trình đã có guard `#ifdef _WIN32` nên chạy đúng trên cả Windows lẫn macOS/Linux.

---

## Chạy chương trình

```bash
./25880243        # macOS / Linux
./25880243.exe    # Windows
```

Khi khởi động, chương trình tự nạp dữ liệu mẫu gồm **5 khách hàng, 10 đầu sách, 20 hóa đơn** để test ngay.

---

## Cấu trúc file

```
NhaSach/
 Makefile          # Build script (make)
 constants.h       # Hằng số kích thước mảng, VAT, giảm giá
 utils.h/cpp       # Nhập chuỗi an toàn, kiểm tra ngày/SĐT, clearScreen/pauseScreen
 customer.h/cpp    # Quản lý khách hàng
 book.h/cpp        # Quản lý sách
 invoice.h/cpp     # Lập hóa đơn, tính tiền
 warehouse.h/cpp   # Quản lý kho
 statistics.h/cpp  # Thống kê doanh thu, tồn kho
 main.cpp          # Menu chính, loadSampleData()
```

---

## Chức năng

### 1. Quản lý khách hàng
| Tùy chọn | Chức năng |
|----------|-----------|
| 1 | Xem danh sách khách hàng |
| 2 | Thêm khách hàng mới |
| 3 | Chỉnh sửa thông tin khách hàng |
| 4 | Xóa khách hàng (chặn nếu còn hóa đơn liên quan) |
| 5 | Tìm kiếm theo số điện thoại |
| 6 | Tìm kiếm theo họ tên |

### 2. Quản lý sách
| Tùy chọn | Chức năng |
|----------|-----------|
| 1 | Xem danh sách sách |
| 2 | Thêm đầu sách mới |
| 3 | Chỉnh sửa thông tin sách |
| 4 | Xóa sách (chỉ khi tồn kho = 0) |
| 5 | Tìm kiếm theo ISBN |
| 6 | Tìm kiếm theo tên sách |

### 3. Lập hóa đơn bán hàng
Nhập mã KH và danh sách ISBN + số lượng. Tự động tính tổng tiền với các quy tắc:
- Giảm 5% nếu mua > 5 quyển cùng thể loại
- Giảm thêm 10% cho khách VIP
- Cộng thuế VAT 10%

### 4. Quản lý kho
| Tùy chọn | Chức năng |
|----------|-----------|
| 1 | Xem tồn kho toàn bộ (highlight sắp hết / hết hàng) |
| 2 | Nhập hàng — cập nhật số lượng tồn kho |

### 5. Thống kê
| Tùy chọn | Chức năng |
|----------|-----------|
| 1 | Tổng số lượng sách trong kho |
| 2 | Số lượng sách theo thể loại |
| 3 | Số lượng khách hàng theo loại thẻ (Thường / VIP) |
| 4 | Doanh thu theo ngày hoặc theo tháng |
| 5 | Danh sách sách hết hàng (tồn kho = 0) |

---

## Quy định nghiệp vụ

| Quy định | Chi tiết |
|----------|----------|
| Giảm giá số lượng | Mua > 5 quyển cùng thể loại → giảm 5% dòng đó (`BULK_THRESHOLD=5`, `BULK_DISCOUNT=0.05`) |
| Giảm giá VIP | Khách VIP → giảm thêm 10% trên tổng sau bulk (`VIP_DISCOUNT=0.10`) |
| Thuế VAT | Cộng 10% trên tổng sau tất cả giảm giá (`VAT_RATE=0.10`) |
