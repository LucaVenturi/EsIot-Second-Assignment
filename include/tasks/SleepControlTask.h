#if !defined(__SLEEP_TASK__)
#define __SLEEP_TASK__

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#include "tasks/Task.h"
#include "Observer.h"

#define MAX_TASKS 50

class SleepControlTask : public Task, public Observer
{
private:
    int interruptPin;
    int nTasks;
    bool eventReady = false;
    Event lastEvent;
    Task* tasksToControl[MAX_TASKS];
    enum {
        RUNNING,
        SLEEPING
    } state;

    //void sleep();

public:
    SleepControlTask(int interruptPin, Task* tasks[], int n);
    ~SleepControlTask();

    void init(int period);
    void tick();

    void update(Event e);
};


#endif // __SLEEP_TASK__
