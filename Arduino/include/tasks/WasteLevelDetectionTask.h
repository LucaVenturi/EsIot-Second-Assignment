#if !defined(__WASTEDETECTIONTASK__)
#define __WASTEDETECTIONTASK__

#include "tasks/ControllingTask.h"
#include "devices/Sonar.h"
#include "Subject.h"

class WasteLevelDetectionTask : public ControllingTask, public Subject, public Observer
{
private:
    Sonar* wasteLvlDetector;
    const float THRESHOLD = 96; /* % above which is considered full */
    const float MAX_DEPTH = 2;
    Event lastEvent;
    bool eventReady = false;
    enum {
        NOT_FULL,
        FULL
    } state;

    float calculatePercentage();

public:
    WasteLevelDetectionTask(Sonar *sonar);
    ~WasteLevelDetectionTask();
    void init(int period);
    void tick();
    void update(Event e);
};

#endif // __WASTEDETECTIONTASK__
