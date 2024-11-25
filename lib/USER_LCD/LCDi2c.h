#if !defined(__LCDI2C__)
#define __LCDI2C__

#include "UserLCD.h"
#include <LiquidCrystal_I2C.h>

class LCDi2c : public UserLCD
{
    private:
        LiquidCrystal_I2C lcd;
        const int rows, cols;
    public:
        LCDi2c(int address, int columns, int rows);
        void write(const String msg);
        void clear();
};


#endif // __LCDI2C__