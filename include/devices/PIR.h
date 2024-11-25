#ifndef __PIR__
#define __PIR__

#include "Synchronizable.h"


class PIR : public Synchronizable 
{
    public:
        PIR();
        virtual bool userDetected() = 0;
        virtual bool isReady();
        virtual void startCalibrating() = 0;
        virtual void waitCalibrationDone() = 0;
};


#endif