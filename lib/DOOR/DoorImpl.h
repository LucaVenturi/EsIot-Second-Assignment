#if !defined(__DOORIMPL__)
#define __DOORIMPL__

#include "Door.h"
#include "ServoMotor.h"

class DoorImpl : public Door
{
    private:
        ServoMotor* servoMotor;
        int pos = 0;
        int delta = 1;

        void rotateByDegrees(int deg);

    public:
        DoorImpl(int servoPin);
        void open();
        void close();
        void reverse();
};



#endif // __DOORIMPL__
