#include "tasks/DoorControlTask.h"
#include <Arduino.h>

DoorControlTask::DoorControlTask(Door* d, long t) : door(d), timeout(t)
{
}

void DoorControlTask::init(int period)
{
    Task::init(period);
    this->state = CLOSED;
    this->timeInState = millis();
}

void DoorControlTask::tick()
{
    //Serial.println("door state: " + String(this->state));
    //long a = millis();

    switch (this->state)
    {
    case OPEN:
        // se segnale di chiudere o timeout passa a closing.
        if ( ( eventReady && lastEvent == Event::BTN_CLOSE_PRESSED ) || ( millis() - this->timeInState >= this->timeout ) )
        {
            this->door->on();
            this->door->close();
            this->state = CLOSING;
            this->timeInState = millis();
            eventReady = false;
        }
        break;

    case OPENING:

        // this->door->open();
        // this->state = OPEN;
        // this->timeInState = millis();

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
                //Serial.println("accendo porta");
                this->door->on();
                //Serial.println("apro porta");
                this->door->open();
                //Serial.println("cambio stato");
                this->state = OPENING;
                this->timeInState = millis();
            }
            else if (this->lastEvent == Event::EMPTYING)
            {
                this->state = TO_EMPTYING;
                this->door->on();
                this->door->reverse();
                this->timeInState = millis();
            }
            //Serial.println("tolgo evento da coda");
            eventReady = false;
            //Serial.println("Tempo impiegato: " + String(millis() - a));
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
        if (millis() - this->timeInState >= this->timeout)
        {
            this->door->on();
            this->door->close();
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
