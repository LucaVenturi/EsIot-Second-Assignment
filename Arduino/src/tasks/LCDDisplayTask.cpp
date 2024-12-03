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
    //this->setActive(false);
    this->lcd->init();
    this->lcd->on();
    changeState(USER_NEAR, "PRESS OPEN TO ENTER WASTE");
    this->lcd->off();
}

void LCDDisplayTask::tick()
{
    // a prescinedere dallo stato. 
    // TODO: ho scoperto che esiste la funzione noDisplay() che spegne lo schermo ma salva il contenuto, mi risparmio di memorizzare lo stato precedente quando va in sleep.
    // if (eventReady && lastEvent == Event::MOTION_DETECTED)
    // {
    //     lcd->on();
    //     eventReady = false;
    //     return;
    // }
    // if (eventReady && lastEvent == Event::NO_MOTION)
    // {
    //     lcd->off();
    //     eventReady = false;
    //     return;
    // }
    
    switch (this->state)
    {
    // case NONE:
    //     if (eventReady && lastEvent == Event::MOTION_DETECTED)
    //         {
    //             this->lcd->on();
    //             changeState(lastState, lastMessage);
    //         }
    //     break;

    case USER_NEAR:
        if (eventReady && lastEvent == Event::BTN_OPEN_PRESSED)
            changeState(USER_INPUTTING, "PRESS CLOSE WHEN DONE");
        else if (eventReady && lastEvent == Event::EMPTY_MSG)
            changeState(USER_INPUTTING, "CONTAINER IS BEING EMPTIED");
        else if (eventReady && lastEvent == Event::TEMP_HIGH)
            changeState(TEMP_PROBLEM, "PROBLEM DETECTED");
        else if (eventReady && lastEvent == Event::CONTAINER_FULL)
            changeState(FULL, "CONTAINER FULL");
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
            changeState(FULL, "CONTAINER FULL");
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

    case EMPTYING:
        if ( eventReady && ( lastEvent == Event::CONTAINER_EMPTY || lastEvent == Event::DONE_EMPTYING ) )
            changeState(USER_NEAR, "PRESS OPEN TO ENTER WASTE");
        else if (eventReady && lastEvent == Event::TEMP_HIGH)
            changeState(TEMP_PROBLEM, "PROBLEM DETECTED");
        else if (eventReady && lastEvent == Event::CONTAINER_FULL)
            changeState(FULL, "CONTAINER FULL");
        break;

    case TEMP_PROBLEM:
        if (eventReady && lastEvent == Event::RESTORE_MSG)
            changeState(USER_NEAR, "PRESS OPEN TO ENTER WASTE");
        break;

    case FULL:
        if (eventReady && lastEvent == Event::EMPTY_MSG)
            changeState(EMPTYING, "CONTAINER IS BEING EMPTIED");
        break;
    }
}

void LCDDisplayTask::update(Event event)
{   
    if (event == Event::MOTION_DETECTED)
    {
        lcd->on();
        eventReady = false;
        return;
    }
    if (event == Event::NO_MOTION)
    {
        lcd->off();
        eventReady = false;
        return;
    }
    eventReady = true;
    lastEvent = event;
}

void LCDDisplayTask::changeState(LCDState newState, const String message) {
    state = newState;
    lcd->clear();
    lcd->write(message);
    eventReady = false;
}
