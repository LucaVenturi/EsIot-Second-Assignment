#include "DoorImpl.h"
#include "ServoMotorImpl.h"
#include <Arduino.h>

DoorImpl::DoorImpl(const int pin) : servoMotor(new ServoMotorImpl(pin))
{

}

void DoorImpl::open()
{
    rotateByDegrees(90);
}

void DoorImpl::close()
{
    rotateByDegrees(-this->pos);
}

void DoorImpl::reverse()
{
    rotateByDegrees(-90);
}

void DoorImpl::rotateByDegrees(int deg)
{
    if (deg > 0)
    {
        this->delta = 1;
    }
    else
    {
        this->delta = -1;
    }

    deg = abs(deg);
    
    this->servoMotor->on();
    for (int i = 0; i < deg; i++) {
        this->servoMotor->setPosition(pos);         
        delay(2);
        this->pos += this->delta;
    }
    this->servoMotor->off();
}
