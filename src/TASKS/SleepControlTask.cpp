#include "tasks/SleepControlTask.h"

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#include "tasks/Task.h"
#include "Observer.h"


SleepControlTask::SleepControlTask(int interruptPin, Task *tasks[], int n)
    : interruptPin(interruptPin)
{
    if (n < MAX_TASKS)
    {
        for (int i = 0; i < n; i++)
        {
            this->tasksToControl[i] = tasks[i];
        }
    }
}


void SleepControlTask::init(int period)
{
    Task::init(period);
    this->state = RUNNING;
}

void SleepControlTask::tick()
{
    switch (this->state)
    {
    case RUNNING:
        if (this->eventReady)
        {
            this->state = SLEEPING;
            //sleep();
        }
        
        break;
    case SLEEPING:
        /* code */
        break;
    default:
        break;
    }
}

void SleepControlTask::update(Event e)
{

}


