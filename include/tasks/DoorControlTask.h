#if !defined(__DOORCONTROLTASK__)
#define __DOORCONTROLTASK__

#include "devices/Door.h"
#include "tasks/Task.h"
#include "Observer.h"

class DoorControlTask : public Task, public Observer
{
private:
    Door* door;
    Event lastEvent;
    bool eventReady;
    long timeInState;
    const long timeout;
    enum {
        OPENING,
        OPEN,
        CLOSING,
        CLOSE,
        TO_EMPTYING,
        EMPTYING
    } state;
public:
    DoorControlTask(Door* d, const long timeout);
    ~DoorControlTask();
    void init(int period);
    void tick();
    void update(Event event);
};


#endif // __DOORCONTROLTASK__
