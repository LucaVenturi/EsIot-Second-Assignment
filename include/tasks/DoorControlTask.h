#if !defined(__DOORCONTROLTASK__)
#define __DOORCONTROLTASK__

#include <devices/Door.h>
#include <tasks/Task.h>

class DoorControlTask : public Task
{
private:
    Door* door;
    enum {
        OPENING,
        OPEN,
        CLOSING,
        CLOSE,
        TO_EMPTYING,
        EMPTYING
    } state;
public:
    DoorControlTask(Door* d);
    ~DoorControlTask();
    void init(int period);
    void tick();
};


#endif // __DOORCONTROLTASK__
