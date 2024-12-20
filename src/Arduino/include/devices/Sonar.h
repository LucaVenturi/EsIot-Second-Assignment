#ifndef __SONAR__
#define __SONAR__

#include "Synchronizable.h"

class Sonar : public Synchronizable
{
    public:
        virtual float getDistance() = 0;
};

#endif