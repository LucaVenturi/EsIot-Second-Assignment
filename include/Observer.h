#ifndef OBSERVER_H
#define OBSERVER_H

#include "Event.h"

class Observer {
public:
    virtual void update(Event event) = 0;  // Ogni Observer implementa questo metodo con un evento di tipo enum
};

#endif
