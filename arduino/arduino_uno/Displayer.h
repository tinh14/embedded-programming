#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <LiquidCrystal_I2C.h>

// Lớp Displayer dùng để hiển thị dữ liệu lên màn hình
class Displayer {
public:
    Displayer(int addr, int col, int rows);
    void begin();
    void display(int col, int row, String data);
private:
    LiquidCrystal_I2C lcd;
};

Displayer::Displayer(int addr, int col, int rows) : lcd(addr, col, rows) {}

// Khởi tạo màn hình hiển thị
void Displayer::begin(){
    // Khởi tạo màn hình hiển thị
    lcd.init();
    // Bật đèn nền cho màn hình
    lcd.backlight();
}

// Hiển thị dữ liệu lên màn hình
void Displayer::display(int col, int row, String data) {
    // Di chuyển con trỏ đến vị trí cần hiển thị
    lcd.setCursor(col, row);
    // Hiển thị dữ liệu
    lcd.print(data);
}

#endif