#include "tasks/LightsControlTask.h"

LightsControlTask::LightsControlTask(Light *l1, Light *l2) : L1(l1), L2(l2)
{
}


void LightsControlTask::init(int period)
{
    Task::init(period);
    this->state = OK;
    this->L1->switchOn();
    this->L2->switchOff();
}


void LightsControlTask::tick()
{
    switch (this->state)
    {
    case OK:
        /* code */
        // se riceve un segnale va allo stato giusto.
        break;
    case FULL:
        /* code */
        break;
    case ALARM:
        /* code */
        break;
    }
}
