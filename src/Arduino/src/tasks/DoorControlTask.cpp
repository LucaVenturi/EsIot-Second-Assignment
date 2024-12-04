#include "tasks/DoorControlTask.h"
#include <Arduino.h>

DoorControlTask::DoorControlTask(Door* d, const unsigned long t1, const unsigned long t3) : door(d), timeoutAccepting(t1), timeoutEmptying(t3)
{
}

void DoorControlTask::init(int period)
{
    Task::init(period);
    //this->setActive(false);
    // TODO: VERIFICARE CHE VADA SU CLOSED.
    this->door->on();
    this->door->close();
    while (this->door->isMoving()) {}
    this->door->off();
    this->state = CLOSED;
    this->timeInState = millis();
}

void DoorControlTask::tick()
{
    //Serial.println("door state: " + String(this->state));

    switch (this->state)
    {
    case OPEN:
        // se segnale di chiudere o timeout passa a closing. 
        if ((
                eventReady && 
                (lastEvent == Event::BTN_CLOSE_PRESSED || 
                lastEvent == Event::CONTAINER_FULL || 
                lastEvent == Event::TEMP_HIGH)
            )
            || millis() - this->timeInState >= this->timeoutAccepting)
        {
            this->door->on();
            this->door->close();
            this->state = CLOSING;

            if (lastEvent == Event::BTN_CLOSE_PRESSED || millis() - this->timeInState >= this->timeoutAccepting)
                this->notify(Event::WASTE_RECEIVED);
            
            this->timeInState = millis();
            eventReady = false;
        }
        break;

    case OPENING:

        if (!this->door->isMoving())
        {
            this->door->off();
            this->state = OPEN;
            this->timeInState = millis();
        }
        break;

    case CLOSED:
        // se segnale di open o empty passa allo stato corretto.
        
        if (this->eventReady)
        {
            if (this->lastEvent == BTN_OPEN_PRESSED)
            {
                this->door->on();
                this->door->open();
                this->state = OPENING;
                this->timeInState = millis();
            }
            else if (this->lastEvent == Event::EMPTY_MSG)
            {
                this->state = TO_EMPTYING;
                this->door->on();
                this->door->reverse();
                this->timeInState = millis();
            }
            eventReady = false;
        }
        
        break;

    case CLOSING:
        if (!this->door->isMoving())
        {
            this->door->off();
            this->state = CLOSED;
            this->timeInState = millis();
        }
        break;

    case TO_EMPTYING:
        if (!this->door->isMoving())
        {
            this->door->off();
            this->state = EMPTYING;
            this->timeInState = millis();
        }
        break;

    case EMPTYING:
        if (millis() - this->timeInState >= this->timeoutEmptying)
        {
            this->door->on();
            this->door->close();
            this->notify(Event::DONE_EMPTYING);
            this->state = CLOSING;
            this->timeInState = millis();
        }
        break;
    }

    //Serial.println("uscito da switch.");
}

void DoorControlTask::update(Event event) {
    this->lastEvent = event; // Memorizza l'ultimo evento
    this->eventReady = true; // Segnala che c'è un evento da gestire
}
