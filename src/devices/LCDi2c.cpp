#include "devices/LCDi2c.h"

LCDi2c::LCDi2c(int address, int columns, int rows) : lcd(address, columns, rows), rows(rows), cols(columns)
{
    this->lcd.init();
    this->lcd.backlight();
    this->lcd.clear();
}

void LCDi2c::write(const String msg)
{
    const int length = msg.length();
    for (int i = 0; ( i < this->rows ) && ( i * this->cols < length ); i++) {
        String line = msg.substring(i * this->cols, (i + 1) * this->cols);
        lcd.setCursor(0, i);
        lcd.print(line);
    }
};

void LCDi2c::clear()
{
    this->lcd.clear();
}