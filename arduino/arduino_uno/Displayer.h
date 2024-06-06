#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <LiquidCrystal_I2C.h>

class Displayer {
public:
    Displayer(int addr, int col, int rows);
    void begin();
    void display(int col, int row, String data);
private:
    LiquidCrystal_I2C lcd;
};

Displayer::Displayer(int addr, int col, int rows) : lcd(addr, col, rows) {}

void Displayer::begin(){
    lcd.init();
    lcd.backlight();
}

void Displayer::display(int col, int row, String data) {
    lcd.setCursor(col, row);
    lcd.print(data);
}

#endif