#include "tasks/ButtonControlTask.h"
#include <Arduino.h>

ButtonControlTask::ButtonControlTask(Button *open, Button *close) : bOpen(open), bClose(close)
{
}

void ButtonControlTask::init(int period)
{
    Task::init(period);
    //this->setActive(false);
    this->state = IDLE;
}

void ButtonControlTask::tick()
{
    this->bOpen->sync();
    this->bClose->sync();

    //Serial.println("button state:" + String(this->state));

    switch (this->state)
    {
    case IDLE:
        if (this->bOpen->isPressed())
        {
            this->state = OPEN_PRESSED;
            this->notify(BTN_OPEN_PRESSED);
        } else if (this->bClose->isPressed())
        {
            this->state = CLOSE_PRESSED;
            this->notify(BTN_CLOSE_PRESSED);
        }
        break;

    case OPEN_PRESSED:
        if (!this->bOpen->isPressed())
            this->state = IDLE;
        break;
    case CLOSE_PRESSED:
        if (!this->bClose->isPressed())
            this->state = IDLE;
        break;
    }
}
