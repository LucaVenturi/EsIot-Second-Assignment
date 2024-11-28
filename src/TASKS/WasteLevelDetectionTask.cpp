#include <tasks/WasteLevelDetectionTask.h>


WasteLevelDetectionTask::WasteLevelDetectionTask(Sonar *sonar) : wasteLvlDetector(sonar)
{
}

void WasteLevelDetectionTask::init(int period)
{
    Task::init(period);
    this->state = NOT_FULL;
}

void WasteLevelDetectionTask::tick()
{
    switch (this->state)
    {
        case NOT_FULL:
            this->wasteLvlDetector->sync();
            if (this->wasteLvlDetector->getDistance() <= THRESHOLD)
            {
                this->state = FULL;
                // signal other tasks the container is full;
            }
            
            break;
        case FULL:
            //quanto segue oppure semplicemente controllo il livello e aspetto che una altra task riattivi questa. questa la spengo al passaggio di stato.
            
            // // Aspetta una notifica dalla task di svuotamento
            // if (isContainerEmpty) // Flag globale settato da un'altra task
            // {
            //     this->state = NOT_FULL;
            //     isContainerEmpty = false; // Resetta il flag
            //     // Puoi anche aggiungere un'azione per re-inizializzare lo stato
            // }
            break;
    }
}

