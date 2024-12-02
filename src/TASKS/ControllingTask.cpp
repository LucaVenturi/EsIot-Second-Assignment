#include "tasks/ControllingTask.h"

bool ControllingTask::addTaskToBeControlled(Task *t)
{
    if (this->nTasks < MAX_TASKS)
    {
        this->tasksToControl[nTasks] = t;
        this->nTasks++;
    }
}

void ControllingTask::enableAllTasks()
{
    for (int i = 0; i < nTasks; i++)
    {
        this->tasksToControl[i]->setActive(true);
    }
}

void ControllingTask::disableAllTasks()
{
        for (int i = 0; i < nTasks; i++)
    {
        this->tasksToControl[i]->setActive(false);
    }
}