#include "devices/SonarImpl.h"
#include <Arduino.h>

SonarImpl::SonarImpl(const int trig_pin, const int echo_pin, const float temperature)
{
    this->trig_pin = trig_pin;
    this->echo_pin = echo_pin;
    this->temperature = temperature;
    this->sound_speed = 331.45 + 0.62 * temperature;

    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
}

void SonarImpl::sync()
{
    /* Triggering stage: sending the impulse */

    digitalWrite(this->trig_pin, LOW);
    delayMicroseconds(3);
    digitalWrite(this->trig_pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trig_pin, LOW);
    
    /* Receiving the echo */

    float tUS = pulseIn(this->echo_pin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * this->sound_speed;

    this->distance = d;
    this->updateSyncTime();
}

float SonarImpl::getDistance()
{
    return this->distance;
}
