#include "tasks/LCDDisplayTask.h"
#include <Arduino.h>

LCDDisplayTask::LCDDisplayTask(UserLCD* lcd) : lcd(lcd), message(""), updated(false)
{
}

LCDDisplayTask::~LCDDisplayTask()
{
}

void LCDDisplayTask::init(int period)
{
    Task::init(period);
    //lcd->on() or init()
}

void LCDDisplayTask::tick()
{
    if (this->updated) // Aggiorna il display solo se il messaggio è stato modificato
    {
        lcd->clear();
        lcd->write(this->message);
        this->updated = false;      // Resetta il flag
    }
}

void LCDDisplayTask::update(int eventCode)
{
    // Aggiorna il messaggio in base all'evento ricevuto
    switch (eventCode)
    {
        case MOTION_DETECTED:
            message = "PRESS OPEN TO ENTER WASTE";
            break;

        case BTN_OPEN_PRESSED:
            message = "PRESS CLOSE WHEN DONE";
            break;

        case WASTE_RECEIVED:
            message = "WASTE RECEIVED";
            break;

        case TEMP_HIGH:
            message = "PROBLEM DETECTED";
            break;

        case CONTAINER_FULL:
            message = "CONTAINER FULL";
            break;

    }

    updated = true; // Imposta il flag per indicare che il messaggio è stato aggiornato
}
