#include "devices/DoorImpl.h"
#include "devices/ServoMotorImpl.h"
#include <Arduino.h>

DoorImpl::DoorImpl(const int pin) : servoMotor(new ServoMotorImpl(pin))
{
}

void DoorImpl::moveTo(const int deg)
{
    if (!this->isMoving())
    {
        this->movingUntil = millis() + deg * 2;
        this->servoMotor->setPosition( constrain(deg, 0, 180) );
    }
}

void DoorImpl::open()
{
    moveTo(180);
}

void DoorImpl::close()
{
    moveTo(90);
}

void DoorImpl::reverse()
{
    moveTo(0);
}

void DoorImpl::on()
{
    this->servoMotor->on();
}

void DoorImpl::off()
{
    this->servoMotor->off();
}

bool DoorImpl::isMoving()
{
    return ( millis() >= this->movingUntil ) ? false : true;
}
