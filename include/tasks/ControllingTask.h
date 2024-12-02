#if !defined(__CONTROLLING_TASK__)
#define __CONTROLLING_TASK__

#include "Task.h"
#define MAX_TASKS 25

class ControllingTask : public Task
{
protected:
    int nTasks = 0;
    Task* tasksToControl[MAX_TASKS];
public:
    bool addTaskToBeControlled(Task* t);
    void enableAllTasks();
    void disableAllTasks();
};



#endif // __CONTROLLING_TASK__
