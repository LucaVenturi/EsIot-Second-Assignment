#include "devices/LCDi2c.h"

LCDi2c::LCDi2c(uint8_t address, int columns, int rows) : lcd(address, columns, rows), rows(rows), cols(columns)
{
    this->lcd.init();
    this->off();
    this->clear();
}

void LCDi2c::write(const String& msg) {
    if (lcdOn)
    {
        lcd.setCursor(0,0);
        lcd.print(msg);
    }

}


void LCDi2c::clear()
{
    this->lcd.clear();
}


void LCDi2c::on()
{
    this->lcd.on();
    this->lcd.backlight();
    //this->lcd.display();
    this->lcdOn = true;
}


void LCDi2c::off()
{
    this->lcd.noBacklight();
    this->lcd.off();
    //this->lcd.noDisplay();
    this->lcdOn = false;
}

void LCDi2c::init()
{
    this->lcd.init();
}