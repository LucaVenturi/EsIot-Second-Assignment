#if !defined(__WASTEDETECTIONTASK__)
#define __WASTEDETECTIONTASK__

#include <tasks/ControllingTask.h>
#include <devices/Sonar.h>
#include "Subject.h"

class WasteLevelDetectionTask : public ControllingTask, public Subject, public Observer
{
private:
    Sonar* wasteLvlDetector;
    const float THRESHOLD = 0.05;
    Event lastEvent;
    bool eventReady = false;
    enum {
        NOT_FULL,
        FULL
    } state;
public:
    WasteLevelDetectionTask(Sonar *sonar);
    ~WasteLevelDetectionTask();
    void init(int period);
    void tick();
    void update(Event e);
};

#endif // __WASTEDETECTIONTASK__
