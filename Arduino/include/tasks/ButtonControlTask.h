#ifndef __BUTTON_CONTROL_TASK_H__
#define __BUTTON_CONTROL_TASK_H__

#include "Task.h"
#include "Subject.h" // Per notificare altre task
#include "devices/Button.h"

class ButtonControlTask : public Task, public Subject {
private:
    Button* bOpen;
    Button* bClose;
    enum {
        OPEN_PRESSED,
        CLOSE_PRESSED,
        IDLE
    } state;

public:
    ButtonControlTask(Button* open, Button* close);
    void init(int period);
    void tick();
};

#endif
