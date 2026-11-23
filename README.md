# STM32 LCD 16x2 trên Proteus

Dự án thử nghiệm điều khiển màn hình LCD 16x2 bằng vi điều khiển **STM32F103C6** trong môi trường mô phỏng **Proteus**. Chương trình sử dụng giao diện 4-bit để gửi dữ liệu đến LCD và hiển thị dòng chữ cùng bộ đếm chạy từ 0 đến 9.

## Chức năng

- Khởi tạo và điều khiển LCD 16x2 ở chế độ 4-bit.
- Hiển thị dòng:
  - Hàng 1: `Hello STM32!`
  - Hàng 2: `Count: `
- Tăng giá trị đếm từ `0` đến `9`, sau đó quay lại `0` sau mỗi giây.
- Thêm đèn LED PA5 có tác dụng nhấp nháy bằng ngắt Timer 2.

## Linh kiện mô phỏng

- STM32F103C6
- LCD 16x2
- LED nối PA5
- STM32Cube HAL
- Proteus ISIS

## Sơ đồ nối chân

| Chức năng LCD | STM32 |
|---|---|
| RS | PA9 |
| EN/E | PA10 |
| D4 | PB4 |
| D5 | PB5 |
| D6 | PB6 |
| D7 | PB7 |
| LED | PA5 |

> Nhớ nối nguồn `VCC`, `GND` và chân điều chỉnh độ tương phản `VEE` của LCD.

## Cấu trúc thư mục

```text
LCD/
├── Core/
│   ├── Inc/
│   │   ├── lcd.h
│   │   └── main.h
│   └── Src/
│       ├── lcd.c
│       └── main.c
├── LCD.ioc
└── STM32F103C6UX_FLASH.ld
```

## API điều khiển LCD

Các hàm điều khiển LCD được khai báo trong `lcd.h`:

```c
void lcd_init(uint8_t rows, uint8_t cols);
void lcd_clear(void);
void lcd_goto(uint8_t x, uint8_t y);
void lcd_print(const char *s);
```

Ví dụ:

```c
lcd_init(16, 2);
lcd_clear();
lcd_goto(0, 0);
lcd_print("Hello STM32!");
```

## Mô phỏng trên Proteus

1. Mở file `.pdsprj` trong Proteus.
2. Nạp file HEX đã build cho vi điều khiển STM32.
3. Chạy mô phỏng.
4. Quan sát LCD hiển thị hai dòng và số đếm thay đổi mỗi giây.

Lưu ý: phải chọn đúng file firmware HEX tương ứng trong phần thuộc tính của STM32 trong Proteus.

## Build chương trình

Project được tạo và cấu hình bằng STM32CubeIDE với bộ vi xử lý **STM32F103C6**. Có thể mở thư mục `LCD/` trong STM32CubeIDE, build project và nạp file HEX đầu ra vào mô phỏng Proteus.
