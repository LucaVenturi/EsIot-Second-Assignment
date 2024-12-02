#ifndef EVENT_H
#define EVENT_H

enum Event {
    TEMP_HIGH,    // Evento di temperatura alta
    TEMP_LOW,     // Evento di temperatura bassa
    MOTION_DETECTED, // Evento di movimento rilevato
    NO_MOTION,
    DOOR_OPEN,    // Evento di porta aperta
    DOOR_CLOSED,   // Evento di porta chiusa
    CONTAINER_FULL,
    CONTAINER_EMPTY,
    BTN_OPEN_PRESSED,
    BTN_CLOSE_PRESSED,
    EMPTY_MSG,
    RESTORE_MSG
};

#endif
