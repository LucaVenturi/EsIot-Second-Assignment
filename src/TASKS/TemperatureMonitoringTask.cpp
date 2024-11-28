#include "tasks/TemperatureMonitoringTask.h"

TemperatureMonitoringTask::TemperatureMonitoringTask(TempSensor *TempSensor) : temperatureSensor(TempSensor)
{
}

void TemperatureMonitoringTask::init(int period)
{
    Task::init(period);
    this->state = TEMP_OK;
}

void TemperatureMonitoringTask::tick()
{
    switch (this->state)
    {
    case TEMP_OK:
        this->temperatureSensor->sync();
        if (this->temperatureSensor->getTemperature() >= DANGER_TEMP)
            this->state = OVERHEATING;
        break;

    case OVERHEATING:
        this->temperatureSensor->sync();
        if (this->temperatureSensor->getTemperature() >= DANGER_TEMP /* && tempo in overheating >= alarm_time */)
        {
            this->state = ALARM;
        }
        
        break;

    case ALARM:
        // se temp sotto la soglia o se l'operatore fa quel che deve fare.
        this->state = TEMP_OK;
        break;
    }
}
