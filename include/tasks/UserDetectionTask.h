#ifndef __USER_DETECT__
#define __USER_DETECT__

#include "Task.h"
#include "Subject.h"
#include "devices/Led.h"
#include "devices/PIR.h"

class UserDetectionTask: public Task, public Subject
{
private:
    PIR* userDetector;
    unsigned long timeout;
    unsigned long timeUndetected;
    enum {
        CALIBRATING,
        DETECTING,
        DETECTED,
        WAIT_UNDETECTED
    } state;

public:
    UserDetectionTask(PIR* userDetector, unsigned long timeout);
    void init(int period);
    void tick();
};

#endif