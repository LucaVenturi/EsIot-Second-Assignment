#include "UserDetectionTask.h"

UserDetectionTask::UserDetectionTask(PIR *userDetector) : userDetector(userDetector)
{

}

void UserDetectionTask::init(int period)
{
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
            break;

        case DETECTING:
            this->userDetector->sync();
            if (this->userDetector->userDetected())
                this->state = DETECTED;
            break;
            
        case DETECTED:
            // se nn rileva movim per t secondi torna a DETECTING.
            break;
    }
}