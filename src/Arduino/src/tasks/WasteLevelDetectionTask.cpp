#include "tasks/WasteLevelDetectionTask.h"
#include "SerialComm/MsgService.h"

WasteLevelDetectionTask::WasteLevelDetectionTask(Sonar *sonar) : wasteLvlDetector(sonar) 
{
}

void WasteLevelDetectionTask::init(int period)
{
    Task::init(period);
    //this->setActive(false);
    this->state = NOT_FULL;
}

void WasteLevelDetectionTask::tick()
{
    this->wasteLvlDetector->sync();
    const float fillPercent = calculatePercentage();
    // MsgService.sendMsg("LEVEL: " + String(fillPercent));
    Serial.print("LEVEL: ");
    Serial.println(fillPercent);
    switch (this->state)
    {
        case NOT_FULL:
            if (fillPercent >= THRESHOLD)
            {
                this->state = FULL;
                // signal other tasks the container is full;
                this->notify(CONTAINER_FULL);
                // disabilita altre task.
                this->disableAllTasks();
            }
            
            break;
        case FULL:
            // Se riceve che il container è stato svuotato torna a NOT_FULL, se poi era un falso tornerà qui.
            if (eventReady)
            {
                if (this->lastEvent == Event::DONE_EMPTYING)
                {
                    this->state = NOT_FULL;
                    this->notify(Event::CONTAINER_EMPTY);
                    this->enableAllTasks();
                    this->eventReady = false;
                }
            }
            break;
    }
}

void WasteLevelDetectionTask::update(Event e)
{
    this->eventReady = true;
    this->lastEvent = e;
}

float WasteLevelDetectionTask::calculatePercentage()
{
    float d = constrain(this->wasteLvlDetector->getDistance(), 0, this->MAX_DEPTH);
    
    return  100 - ( (d * 100) / this->MAX_DEPTH );
}
