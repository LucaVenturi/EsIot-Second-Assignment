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
    this->state = NONE;
}

void LCDDisplayTask::tick()
{
    switch (state)
    {
    
    case NONE:
        if (eventReady && lastEvent == Event::MOTION_DETECTED)
            {
                eventReady = false;
                state = USER_NEAR;
                lcd->clear();
                lcd->write("PRESS OPEN TO ENTER WASTE");
            }
        break;

    case USER_NEAR:
        if (eventReady && lastEvent == Event::BTN_OPEN_PRESSED)
        {
            eventReady = false;
            state = USER_INPUTTING;
            lcd->clear();
            lcd->write("PRESS CLOSE WHEN DONE");
        }
        else if (eventReady && lastEvent == Event::TEMP_HIGH)
        {
            eventReady = false;
            state = TEMP_PROBLEM;
            lcd->clear();
            lcd->write("PROBLEM DETECTED");
        }
        else if (eventReady && lastEvent == Event::CONTAINER_FULL)
        {
            eventReady = false;
            state = CONTAINER_FULL;
            lcd->clear();
            lcd->write("CONTAINER FULL");
        }
        break;
    case USER_INPUTTING:
        if (eventReady && lastEvent == Event::WASTE_RECEIVED)
        {
            eventReady = false;
            state = ACK_WASTE_RECEIVED;
            timeWasteReceived = millis();
            lcd->clear();
            lcd->write("WASTE RECEIVED");
            // forse disabilitare le altre task finche non ha mostrato all'utente waste received per 2 secondi.
        }
        else if (eventReady && lastEvent == Event::TEMP_HIGH)
        {
            eventReady = false;
            state = TEMP_PROBLEM;
            lcd->clear();
            lcd->write("PROBLEM DETECTED");
        }
        else if (eventReady && lastEvent == Event::CONTAINER_FULL)
        {
            eventReady = false;
            state = CONTAINER_FULL;
            lcd->clear();
            lcd->write("CONTAINER FULL");
        }
        break;
    
    case ACK_WASTE_RECEIVED:
        if (millis() - timeWasteReceived >= 2000)
        {
            state = USER_NEAR;
            lcd->clear();
            lcd->write("PRESS OPEN TO ENTER WASTE");
            // forse riabilita
        }
        break;
    case TEMP_PROBLEM:
        if (eventReady && lastEvent == Event::RESTORE_MSG)
        {
            state = USER_NEAR;
            lcd->clear();
            lcd->write("PRESS OPEN TO ENTER WASTE");
        }
        break;
    case CONTAINER_FULL:
        if (eventReady && lastEvent == Event::DONE_EMPTYING)
        {
            state = USER_NEAR;
            lcd->clear();
            lcd->write("PRESS OPEN TO ENTER WASTE");
        }
        break;
    }
}

void LCDDisplayTask::update(Event event)
{
    eventReady = true;
    lastEvent = event;
}
