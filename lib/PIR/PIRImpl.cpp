#include "PIRImpl.h"
#include <Arduino.h>

PIRImpl::PIRImpl(const int pin, const int calibrationTime)
{
    this->pin = pin;
    this->calibrationTime = calibrationTime;
    this->detected = false;
    this->isReady = true;

    pinMode(pin, INPUT);

    startCalibrating();

    waitCalibrationDone();

    sync();
};

bool PIRImpl::userDetected()
{
    if (!this->isReady)
        return false;
    
    return this->detected;
}

void PIRImpl::sync()
{
    if (!this->isReady)
        return;
    
    this->detected = digitalRead(pin);
    this->updateSyncTime();
}

void PIRImpl::startCalibrating()
{
    this->calibrationStartTime = millis();
    // millis() - this->calibrationStartTime >= calibrationTime

}

void PIRImpl::waitCalibrationDone()
{
    delay(calibrationTime);
    this->isReady = true;
    
}