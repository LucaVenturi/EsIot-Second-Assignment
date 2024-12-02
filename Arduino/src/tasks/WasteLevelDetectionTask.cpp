#include <tasks/WasteLevelDetectionTask.h>


WasteLevelDetectionTask::WasteLevelDetectionTask(Sonar *sonar) : wasteLvlDetector(sonar)
{
}

void WasteLevelDetectionTask::init(int period)
{
    Task::init(period);
    this->state = NOT_FULL;
}

void WasteLevelDetectionTask::tick()
{
    switch (this->state)
    {
        case NOT_FULL:
            this->wasteLvlDetector->sync();
            if (this->wasteLvlDetector->getDistance() <= THRESHOLD)
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
