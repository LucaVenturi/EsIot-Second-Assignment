#if !defined(__DOORIMPL__)
#define __DOORIMPL__

#include "Door.h"
#include "ServoMotor.h"

class DoorImpl : public Door
{
    private:
        ServoMotor* servoMotor;
        int pos = 90;
        unsigned long movingUntil = 0;

        void moveTo(const int deg);

    public:
        DoorImpl(int servoPin);
        void open();
        void close();
        void reverse();
        void on();
        void off();
        bool isMoving();
};



#endif // __DOORIMPL__
