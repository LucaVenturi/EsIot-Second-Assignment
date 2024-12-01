#if !defined(__LCDTASK__)
#define __LCDTASK__

#include "tasks/Task.h"
#include "Observer.h"
#include <LiquidCrystal_I2C.h>

class LCDDisplayTask : public Task, public Observer
{
private:
    LiquidCrystal_I2C* lcd; // Puntatore al display LCD
    String message;        // Messaggio da visualizzare sul display
    bool updated;          // Flag per sapere se il messaggio è stato aggiornato

public:
    LCDDisplayTask(LiquidCrystal_I2C* lcd);
    ~LCDDisplayTask();

    void init(int period);
    void tick();
    
    // Metodo dell'interfaccia Observer
    void update(int event);
};

#endif // __LCDTASK__
