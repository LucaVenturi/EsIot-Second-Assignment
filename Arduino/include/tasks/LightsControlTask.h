#if !defined(__LIGHTSCONTROLTASK__)
#define __LIGHTSCONTROLTASK__

#include "tasks/Task.h"
#include "devices/Light.h"
#include "Observer.h"


class LightsControlTask : public Task, public Observer
{
private:
    Light* L1;
    Light* L2;
    Event lastEvent;
    bool eventReady;
    enum {
        OK,
        FULL,
        ALARM
    } state;
public:
    LightsControlTask(Light* l1, Light* l2);
    ~LightsControlTask();
    void init(int period);
    void tick();
    void update(Event event);
};


#endif // __LIGHTSCONTROLTASK__
