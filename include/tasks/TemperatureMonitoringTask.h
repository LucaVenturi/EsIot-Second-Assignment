#if !defined(__TEMPMONITORTASK)
#define __TEMPMONITORTASK

#include "tasks/Task.h"
#include "devices/TempSensor.h"
#include "Subject.h"

class TemperatureMonitoringTask : public Task, public Subject
{
private:
    TempSensor* temperatureSensor;
    const float DANGER_TEMP = 25;
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
};

#endif // __TEMPMONITORTASK
