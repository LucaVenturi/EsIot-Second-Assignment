#if !defined(__LIGHTSCONTROLTASK__)
#define __LIGHTSCONTROLTASK__

#include "tasks/Task.h"
#include "devices/Light.h"

class LightsControlTask : public Task
{
private:
    Light* L1;
    Light* L2;
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
};


#endif // __LIGHTSCONTROLTASK__
