#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include "Event.h"

class Subject {
private:
    Observer* observers[10];  // Array statico per contenere fino a 10 observers
    int numObservers;         // Conta il numero di observer registrati

public:
    Subject();

    void attach(Observer* observer);

    void detach(Observer* observer);

    void notify(Event event);
};

#endif
