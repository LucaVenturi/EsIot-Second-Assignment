#if !defined(__WASTEDETECTIONTASK__)
#define __WASTEDETECTIONTASK__

#include <tasks/Task.h>
#include <devices/Sonar.h>

class WasteLevelDetectionTask : public Task
{
private:
    Sonar* wasteLvlDetector;
    const float THRESHOLD = 0.1;
    enum {
        NOT_FULL,
        FULL
    } state;
public:
    WasteLevelDetectionTask(Sonar *sonar);
    ~WasteLevelDetectionTask();
    void init(int period);
    void tick();
};

#endif // __WASTEDETECTIONTASK__
