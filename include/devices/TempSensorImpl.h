#ifndef __TEMPSENSIMPL__
#define __TEMPSENSIMPL__

#include "TempSensor.h"

class TempSensorImpl : TempSensor
{
    private:
        const int pin;
        int temp;
    public:
        TempSensorImpl(const int pin);
        void sync();
        int getTemperature();
};

#endif