#include "tasks/TemperatureMonitoringTask.h"
#include <Arduino.h>


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
    this->temperatureSensor->sync();
    // Serial.println("temp: " + String(this->temperatureSensor->getTemperature()));
    // Serial.println("temp monitor state: " + String(this->state));
    switch (this->state)
    {
    case TEMP_OK:
        this->temperatureSensor->sync();
        if (this->temperatureSensor->getTemperature() >= this->DANGER_TEMP)
        {
            this->state = OVERHEATING;
            this->startTimeOverheat = millis();
        }
        break;

    case OVERHEATING:
        this->temperatureSensor->sync();
        if ( ! (this->temperatureSensor->getTemperature() >= DANGER_TEMP) )
        {
            this->state = TEMP_OK;
        } 
        else if (millis() - this->startTimeOverheat >= this->OVERHEAT_TIME)
        {
            this->state = ALARM;
            this->notify(TEMP_HIGH);
            this->disableAllTasks();
        }
        break;

    case ALARM:
        // se temp sotto la soglia o se l'operatore fa quel che deve fare.
        if (this->eventReceived && this->lastEvent == Event::RESTORE_MSG)
        {
            this->state = TEMP_OK;
            this->notify(TEMP_LOW);
            this->enableAllTasks();
        }
        break;
    }
}

void TemperatureMonitoringTask::update(Event event)
{
    this->eventReceived = true;
    this->lastEvent = event;
}
