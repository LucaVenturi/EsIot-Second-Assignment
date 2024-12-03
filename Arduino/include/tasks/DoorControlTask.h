#if !defined(__DOORCONTROLTASK__)
#define __DOORCONTROLTASK__

#include "devices/Door.h"
#include "tasks/Task.h"
#include "Observer.h"
#include "Subject.h"


class DoorControlTask : public Task, public Observer, public Subject
{
private:
    Door* door;
    Event lastEvent;
    bool eventReady;
    unsigned long timeInState;
    const unsigned long timeoutAccepting;
    const unsigned long timeoutEmptying;
    enum {
        OPENING,
        OPEN,
        CLOSING,
        CLOSED,
        TO_EMPTYING,
        EMPTYING
    } state;
public:
    DoorControlTask(Door* d, const unsigned long timeoutAccepting, const unsigned long timeoutEmptying);
    ~DoorControlTask();
    void init(int period);
    void tick();
    void update(Event event);
};


#endif // __DOORCONTROLTASK__
