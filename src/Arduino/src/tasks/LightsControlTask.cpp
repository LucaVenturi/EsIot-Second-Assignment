#include "tasks/LightsControlTask.h"


LightsControlTask::LightsControlTask(Light *l1, Light *l2) : L1(l1), L2(l2), eventReady(false)
{
}


void LightsControlTask::init(int period)
{
    Task::init(period);
    //this->setActive(false);
    this->state = OK;
    this->L1->switchOn();
    this->L2->switchOff();
}


void LightsControlTask::tick()
{
// Verifica se l'evento è pronto prima di entrare nello stato
    if (!eventReady) {
        return;
    }

    // Elabora l'evento in base allo stato
    switch (this->state)
    {
    case OK:
        if (lastEvent == TEMP_HIGH || lastEvent == CONTAINER_FULL)
        {
            this->state = lastEvent==TEMP_HIGH ? ALARM : FULL;  // Passa allo stato di allarme o pieno
            this->L1->switchOff();
            this->L2->switchOn();
        }
        break;

    // MAGARI POSSO FARE UN SOLO STATO DI ALLARME VISTO CHE NON CAMBIA NULLA CREDO.
    case FULL:
        if (lastEvent == CONTAINER_EMPTY)
        {
            this->state = OK;  // Torna allo stato OK
            this->L1->switchOn();
            this->L2->switchOff();
        }
        break;

    case ALARM:
        if (lastEvent == TEMP_LOW)
        {
            this->state = OK;  // Torna allo stato OK
            this->L1->switchOn();
            this->L2->switchOff();
        }
        break;
    }

    // Dopo aver elaborato l'evento, resettiamo eventReady
    eventReady = false;
}

void LightsControlTask::update(Event event)
{
    this->lastEvent = event;
    this->eventReady = true;
}
