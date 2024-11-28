#include "Subject.h"

Subject::Subject() : numObservers(0) {}

void Subject::attach(Observer *observer)
{
    if (numObservers < 10) {  // Evita di superare la dimensione massima
        observers[numObservers++] = observer;
    }
}

void Subject::detach(Observer *observer)
{
    for (int i = 0; i < numObservers; i++) {
        if (observers[i] == observer) {
            // Sposta gli observer successivi per "rimuovere" quello trovato
            for (int j = i; j < numObservers - 1; j++) {
                observers[j] = observers[j + 1];
            }
            numObservers--;
            break;
        }
    }
}

void Subject::notify(Event event)
{
    for (int i = 0; i < numObservers; i++) {
        observers[i]->update(event);  // Notifica ogni observer con l'evento specificato
    }
}