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
        /* code */
        // se segnale di chiudere o timeout passa a closing.
        break;
    case OPENING:
        this->door->open();
        this->state = OPEN;
        break;
    case CLOSE:
        /* code */
        // se segnale di open o empty passa allo stato corretto.
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
    default:
        break;
    }
}


