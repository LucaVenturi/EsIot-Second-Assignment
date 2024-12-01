#include "tasks/UserDetectionTask.h"
#include <Arduino.h>

UserDetectionTask::UserDetectionTask(PIR *userDetector, unsigned long t) : userDetector(userDetector), timeout(t)
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
    Task::init(period);
}

void UserDetectionTask::tick()
{
    //Serial.println(String(this->state));
    switch (this->state)
    {
        case CALIBRATING:
            this->userDetector->waitCalibrationDone();
            this->state = DETECTING;
            // Activate other tasks.
            break;

        case DETECTING:
            this->userDetector->sync();
            if (this->userDetector->userDetected()){
                this->state = DETECTED;
                // Notify that user is near.
                this->notify(MOTION_DETECTED);
                // Abilita la task per il controllo input utente e porta.
                // ...
            }
            break;
            
        case DETECTED:
            // se nn rileva movim per t secondi torna a DETECTING.
            this->userDetector->sync();
            if (!this->userDetector->userDetected())
            {
                this->state = WAIT_UNDETECTED;
                this->timeUndetected = millis();
            }
            
            break;

        case WAIT_UNDETECTED:
            // se nn rileva movim per t secondi torna a DETECTING.
            this->userDetector->sync();
            if (this->userDetector->userDetected())
            {
                this->state = DETECTED;
            }
            
            if (millis() - timeUndetected >= timeout)
            {
                this->state = DETECTING;
                this->notify(NO_MOTION);
            }
            
            break;
    }
}