#include "tasks/DoorControlTask.h"
#include <Arduino.h>

DoorControlTask::DoorControlTask(Door* d, long t) : door(d), timeout(t)
{
}

void DoorControlTask::init(int period)
{
    Task::init(period);
    this->state = CLOSE;
    this->timeInState = millis();
}

void DoorControlTask::tick()
{
    Serial.println("door state: " + String(this->state));
    switch (this->state)
    {
    case OPEN:
        // se segnale di chiudere o timeout passa a closing.
        if ( (eventReady && lastEvent == Event::BTN_CLOSE_PRESSED) || (this->timeInState >= this->timeout) )
        {
            this->state = CLOSING;
            this->timeInState = millis();
            eventReady = false;
        }
        break;

    case OPENING:
        Serial.println("Start opening...");
        // this->door->open();
        Serial.println("opening done");
        this->state = OPEN;
        Serial.println("cambiato stato");
        this->timeInState = millis();
        Serial.println("Memorizzato il tempo");
        break;

    case CLOSE:
        // se segnale di open o empty passa allo stato corretto.
        if (this->eventReady)
        {
            if (this->lastEvent == BTN_OPEN_PRESSED)
            {
                this->state = OPENING;
                this->timeInState = millis();
            }
            else if (this->lastEvent == Event::EMPTYING)
            {
                this->state = TO_EMPTYING;
                this->timeInState = millis();
            }
            eventReady = false;
        }
        
        break;

    case CLOSING:
        this->door->close();
        this->state = CLOSE;
        this->timeInState = millis();
        break;

    case TO_EMPTYING:
        this->door->reverse();
        this->state = EMPTYING;
        this->timeInState = millis();
        break;

    case EMPTYING:
        if (this->timeInState >= this->timeout)
        {
            this->state = CLOSING;
            this->timeInState = millis();
        }
        break;
    }
}

void DoorControlTask::update(Event event) {
    this->lastEvent = event; // Memorizza l'ultimo evento
    this->eventReady = true; // Segnala che c'è un evento da gestire
}
