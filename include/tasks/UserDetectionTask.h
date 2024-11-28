#ifndef __USER_DETECT__
#define __USER_DETECT__

#include "Task.h"
#include "Subject.h"
#include "devices/Led.h"
#include "devices/PIR.h"

class UserDetectionTask: public Task, public Subject
{
private:
    // const Light* L1;
    // const Light* L2;
    PIR* userDetector;

    enum {
        CALIBRATING,
        DETECTING,
        DETECTED
    } state;

public:
    UserDetectionTask(PIR* userDetector);
    void init(int period);
    void tick();
};

#endif

