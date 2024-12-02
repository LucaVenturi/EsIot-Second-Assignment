#if !defined(__LCDTASK__)
#define __LCDTASK__

#include "tasks/Task.h"
#include "Observer.h"
#include "devices/UserLCD.h"

class LCDDisplayTask : public Task, public Observer
{
private:
    UserLCD* lcd; // Puntatore al display LCD
    String message;        // Messaggio da visualizzare sul display
    bool updated;          // Flag per sapere se il messaggio è stato aggiornato

public:
    LCDDisplayTask(UserLCD* lcd);
    ~LCDDisplayTask();

    void init(int period);
    void tick();
    
    // Metodo dell'interfaccia Observer
    void update(int event);
};

#endif // __LCDTASK__
