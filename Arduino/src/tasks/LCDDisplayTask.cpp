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
    this->state = NONE;
}

void LCDDisplayTask::tick()
{
    // TODO: togliere duplicazione codice.
    
    // a prescinedere dallo stato
    if (eventReady && lastEvent == NO_MOTION)
    {
        eventReady = false;
        state = NONE;
        this->lcd->off();
        return;
    }
    

    switch (state)
    {
    
    case NONE:
        if (eventReady && lastEvent == Event::MOTION_DETECTED)
            {
                this->lcd->on();
                changeState(USER_NEAR, "PRESS OPEN TO ENTER WASTE");
            }
        break;

    case USER_NEAR:
        if (eventReady && lastEvent == Event::BTN_OPEN_PRESSED)
            changeState(USER_INPUTTING, "PRESS CLOSE WHEN DONE");
        else if (eventReady && lastEvent == Event::TEMP_HIGH)
            changeState(TEMP_PROBLEM, "PROBLEM DETECTED");
        else if (eventReady && lastEvent == Event::CONTAINER_FULL)
            changeState(CONTAINER_FULL, "CONTAINER FULL");
        break;

    case USER_INPUTTING:
        if (eventReady && lastEvent == Event::WASTE_RECEIVED)
        {
            changeState(ACK_WASTE_RECEIVED, "WASTE RECEIVED");
            timeWasteReceived = millis();
            // forse disabilitare le altre task finche non ha mostrato all'utente waste received per 2 secondi.
        }
        else if (eventReady && lastEvent == Event::TEMP_HIGH)
            changeState(TEMP_PROBLEM, "PROBLEM DETECTED");
        else if (eventReady && lastEvent == Event::CONTAINER_FULL)
            changeState(CONTAINER_FULL, "CONTAINER FULL");
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
            changeState(USER_NEAR, "PRESS OPEN TO ENTER WASTE");
        break;

    case CONTAINER_FULL:
        if (eventReady && lastEvent == Event::DONE_EMPTYING)
            changeState(USER_NEAR, "PRESS OPEN TO ENTER WASTE");
        break;
    }
}

void LCDDisplayTask::update(Event event)
{
    eventReady = true;
    lastEvent = event;
}

void LCDDisplayTask::changeState(LCDState newState, const char* message) {
    state = newState;
    lcd->clear();
    lcd->write(message);
    eventReady = false;
}
