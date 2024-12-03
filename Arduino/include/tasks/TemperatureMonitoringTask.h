#if !defined(__TEMPMONITORTASK)
#define __TEMPMONITORTASK

#include "tasks/ControllingTask.h"
#include "devices/TempSensor.h"
#include "Subject.h"

class TemperatureMonitoringTask : public ControllingTask, public Subject, public Observer
{
private:
    TempSensor* temperatureSensor;
    const float DANGER_TEMP = 28.0f;
    unsigned long startTimeOverheat;
    unsigned const int OVERHEAT_TIME = 5000;
    bool eventReceived = false;
    Event lastEvent;
    enum {
        TEMP_OK,
        OVERHEATING,
        ALARM
    } state;
    
public:
    TemperatureMonitoringTask(TempSensor* TempSensor);
    ~TemperatureMonitoringTask();
    void init(int period);
    void tick();
    void update(Event event);
};

#endif // __TEMPMONITORTASK
