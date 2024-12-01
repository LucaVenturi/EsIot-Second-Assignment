#include "tasks/LCDDisplayTask.h"
#include <Arduino.h>

LCDDisplayTask::LCDDisplayTask(LiquidCrystal_I2C* lcd) : lcd(lcd), message(""), updated(false)
{
}

LCDDisplayTask::~LCDDisplayTask()
{
}

void LCDDisplayTask::init(int period)
{
    Task::init(period);
    lcd->init();          // Inizializza il display
    lcd->backlight();     // Accendi la retroilluminazione
    lcd->clear();         // Pulisci il display
    lcd->print("Starting...");
}

void LCDDisplayTask::tick()
{
    if (updated) // Aggiorna il display solo se il messaggio è stato modificato
    {
        lcd->clear();
        lcd->setCursor(0, 0); // Imposta il cursore in alto a sinistra
        lcd->print(message);  // Mostra il messaggio
        updated = false;      // Resetta il flag
    }
}

void LCDDisplayTask::update(int eventCode)
{
    // Aggiorna il messaggio in base all'evento ricevuto
    switch (eventCode)
    {
    case TEMP_HIGH:
        message = "Temp: HIGH!";
        break;

    case TEMP_LOW:
        message = "Temp: LOW";
        break;

    // case SYSTEM_OK:
    //     message = "System OK";
    //     break;

    default:
        message = "Unknown event";
        break;
    }

    updated = true; // Imposta il flag per indicare che il messaggio è stato aggiornato
}
