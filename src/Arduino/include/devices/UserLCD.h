#if !defined(__USERLCD__)
#define __USERLCD__

#include <Arduino.h>

class UserLCD
{
    private:
        
    public:
        virtual void on() = 0;
        virtual void off() = 0;
        virtual void write(const String& msg) = 0;
        virtual void clear() = 0;
        virtual void init() = 0;
};

#endif // __USERLCD__