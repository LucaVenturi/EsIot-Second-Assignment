#ifndef __TEMPSENS__
#define __TEMPSENS__

#include "Synchronizable.h"

class TempSensor : public Synchronizable
{
    private:
        /* data */
    public:
        virtual int getTemperature() = 0;
};

#endif