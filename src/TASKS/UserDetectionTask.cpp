#include "tasks/UserDetectionTask.h"

UserDetectionTask::UserDetectionTask(PIR *userDetector) : userDetector(userDetector)
{
}

void UserDetectionTask::init(int period)
{
    Task::init(period);
    if (!this->userDetector->isReady())
    {
        this->userDetector->startCalibrating();
        this->state = CALIBRATING;
    } else
    {
        this->state = DETECTING;
    }
    
}

void UserDetectionTask::tick()
{
    switch (this->state)
    {
        case CALIBRATING:
            this->userDetector->waitCalibrationDone();
            this->state = DETECTING;
            break;

        case DETECTING:
            this->userDetector->sync();
            if (this->userDetector->userDetected())
                this->state = DETECTED;
                // Notify that user is near.
                // Activate other tasks.
            break;
            
        case DETECTED:
            // se nn rileva movim per t secondi torna a DETECTING.
            break;
    }
}