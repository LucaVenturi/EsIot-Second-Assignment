#ifndef __COMM_TASK__
#define __COMM_TASK__

#include "tasks/Task.h"
#include "Observer.h"
#include "Subject.h"
#include "SerialComm/MsgService.h"

class OperatorCommunicationTask : public Task, /* public Observer, */ public Subject
{
private:
    enum State
    {
        IDLE,
        EMPTY_COMMAND,
        RESTORE_COMMAND
    } state;

    String receivedCommand;

    void parseCommand(const String &command);

public:
    OperatorCommunicationTask();
    ~OperatorCommunicationTask();

    void init(int period) override;
    void tick() override;

    //void update(int event); // React to events from other tasks
};

#endif // __COMM_TASK__
