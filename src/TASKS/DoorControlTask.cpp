#include "tasks/DoorControlTask.h"

DoorControlTask::DoorControlTask(Door* d) : door(d)
{

}

void DoorControlTask::init(int period)
{
    Task::init(period);
    this->state = CLOSE;
}

void DoorControlTask::tick()
{
    switch (this->state)
    {
    case OPEN:
        // se segnale di chiudere o timeout passa a closing.
        if (eventReady && lastEvent == Event::BTN_CLOSE_PRESSED)
        {
            this->state = CLOSING;
            eventReady = false;
        }
        break;

    case OPENING:
        this->door->open();
        this->state = OPEN;
        break;

    case CLOSE:
        // se segnale di open o empty passa allo stato corretto.
        if (this->eventReady)
        {
            if (this->lastEvent == Event::BTN_OPEN_PRESSED)
                this->state = OPENING;
            else if (this->lastEvent == Event::EMPTYING)
                this->state = TO_EMPTYING;
            eventReady = false;
        }
        
        break;

    case CLOSING:
        this->door->close();
        this->state = CLOSE;
        break;

    case TO_EMPTYING:
        this->door->reverse();
        this->state = EMPTYING;
        break;

    case EMPTYING:
        // DOPO T SECONDI TORNA A CLOSING
        break;
    }
}

void DoorControlTask::update(Event event) {
    this->lastEvent = event; // Memorizza l'ultimo evento
    this->eventReady = true; // Segnala che c'è un evento da gestire
}
