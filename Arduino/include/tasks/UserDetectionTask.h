#ifndef __USER_DETECT__
#define __USER_DETECT__

#include "Task.h"
#include "ControllingTask.h"
#include "Subject.h"
#include "devices/Led.h"
#include "devices/PIR.h"


class UserDetectionTask: public ControllingTask, public Subject
{
private:
    PIR* userDetector;
    int interruptPin;
    unsigned long timeout;
    unsigned long timeUndetected;
    enum {
        CALIBRATING,
        DETECTING,
        DETECTED,
        WAIT_UNDETECTED
    } state;

    void sleep();

public:
    UserDetectionTask(PIR* userDetector, int interruptPin, unsigned long timeout);
    void init(int period);
    void tick();
};

#endif