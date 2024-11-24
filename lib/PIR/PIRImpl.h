#ifndef __PIRIMPL__
#define __PIRIMPL__

#include "PIR.h"

class PIRImpl : public PIR
{
    public:
        PIRImpl(const int pin, const int calibrationTime);
        virtual bool userDetected();
        virtual bool isReady();

        // Inherited.
        virtual void sync();
        virtual long getLastSyncTime();

    protected:
        virtual void updateSyncTime();

    private:
        int pin;
        bool detected;
        bool isReady;
        long calibrationTime;
        long calibrationStartTime;
        long lastTimeSync;

        void startCalibrating();
        void waitCalibrationDone();
};


#endif