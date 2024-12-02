#ifndef __PIRIMPL__
#define __PIRIMPL__

#include "PIR.h"

class PIRImpl : public PIR
{
    public:
        PIRImpl(const int pin, const int calibrationTime);
        bool userDetected();
        bool isReady();
        void startCalibrating();
        void waitCalibrationDone();

        // Inherited.
        void sync();

    private:
        int pin;
        bool detected;
        bool ready;
        long calibrationTime;
        long calibrationStartTime;

};


#endif