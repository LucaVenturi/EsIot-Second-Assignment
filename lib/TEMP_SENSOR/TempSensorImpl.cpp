#include "TempSensorImpl.h"

#include <Arduino.h>

TempSensorImpl::TempSensorImpl(const int pin) : pin(pin)
{
    pinMode(this->pin, INPUT);
}

void TempSensorImpl::sync()
{
    // Get the voltage reading from the TMP36
    int reading = analogRead(this->pin);

    // Convert that reading into voltage on a board with 5V.
    float voltage = reading * (5.0 / 1024.0);

    // Convert the voltage into the temperature in Celsius
    this->temp = (voltage - 0.5) * 100;

    this->updateSyncTime();

}

int TempSensorImpl::getTemperature()
{
    return this->temp;
}
