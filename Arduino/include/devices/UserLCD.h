#if !defined(__USERLCD__)
#define __USERLCD__

#include <Arduino.h>

class UserLCD
{
    private:
        
    public:
        virtual void write(const String msg) = 0;
        virtual void clear() = 0;
};

#endif // __USERLCD__