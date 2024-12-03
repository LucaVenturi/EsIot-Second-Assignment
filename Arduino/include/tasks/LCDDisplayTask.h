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
    bool eventReady;
    Event lastEvent;
    unsigned long timeWasteReceived;
    enum LCDState{
        NONE,
        USER_NEAR,
        USER_INPUTTING,
        ACK_WASTE_RECEIVED,
        TEMP_PROBLEM,
        CONTAINER_FULL
    } state;

    void changeState(LCDState newState, const char* message);

public:
    LCDDisplayTask(UserLCD* lcd);
    ~LCDDisplayTask();

    void init(int period);
    void tick();
    
    // Metodo dell'interfaccia Observer
    void update(Event event);
};

#endif // __LCDTASK__
