#include "tasks/OperatorCommunicationTask.h"
#include <Arduino.h>

OperatorCommunicationTask::OperatorCommunicationTask() : state(IDLE), receivedCommand("") {}

OperatorCommunicationTask::~OperatorCommunicationTask() {}

void OperatorCommunicationTask::init(int period)
{
    Task::init(period);
    this->state = IDLE;
    this->receivedCommand = "";
    MsgService.init(); // Initialize the MsgService for serial communication
}

void OperatorCommunicationTask::tick()
{
    switch (this->state)
    {
    case IDLE:
        if (MsgService.isMsgAvailable())
        {
            Msg *msg = MsgService.receiveMsg();
            if (msg != nullptr)
            {
                parseCommand(msg->getContent());
                delete msg; // Free memory allocated for the message
            }
        }
        break;

    case EMPTY_COMMAND:
        MsgService.sendMsg("OperatorCommunicationTask: EMPTY command received.");
        this->notify(Event::EMPTY_MSG); // Notify other tasks
        this->state = IDLE;
        break;

    case RESTORE_COMMAND:
        MsgService.sendMsg("OperatorCommunicationTask: RESTORE command received.");
        this->notify(Event::RESTORE_MSG); // Notify other tasks
        this->state = IDLE;
        break;
    }
}

void OperatorCommunicationTask::parseCommand(const String &command)
{
    if (command == "EMPTY")
    {
        this->state = EMPTY_COMMAND;
    }
    else if (command == "RESTORE")
    {
        this->state = RESTORE_COMMAND;
    }
    else
    {
        MsgService.sendMsg("OperatorCommunicationTask: Unknown command received: " + command);
    }
}

// void OperatorCommunicationTask::update(int event)
// {
//     //Example logic to handle events from other tasks
//     switch (event)
//     {
//     case Event::TEMP_HIGH:
//         MsgService.sendMsg("Warning: High temperature detected!");
//         break;

//     case Event::CONTAINER_FULL:
//         MsgService.sendMsg("Alert: Container is full.");
//         break;

//     case Event::SYSTEM_OK:
//         MsgService.sendMsg("System is operating normally.");
//         break;

//     default:
//         MsgService.sendMsg("Unknown event received.");
//         break;
//     }
// }
