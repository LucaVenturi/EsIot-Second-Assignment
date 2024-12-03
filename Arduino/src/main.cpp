#include <Arduino.h>

/* mettere questi include in un file apposito e includere solo quello sarebbe meglio */
#include "scheduler/Scheduler.h"
#include "devices/PIR.h"
#include "devices/PIRImpl.h"
#include "tasks/UserDetectionTask.h"
#include "devices/Button.h"
#include "devices/ButtonImpl.h"
#include "tasks/ButtonControlTask.h"
#include "devices/TempSensor.h"
#include "devices/TempSensorImpl.h"
#include "tasks/TemperatureMonitoringTask.h"
#include "devices/Door.h"
#include "devices/DoorImpl.h"
#include "tasks/DoorControlTask.h"
#include "devices/Light.h"
#include "devices/Led.h"
#include "tasks/LightsControlTask.h"
#include "devices/SonarImpl.h"
#include "tasks/WasteLevelDetectionTask.h"
#include "tasks/OperatorCommunicationTask.h"
#include "tasks/LCDDisplayTask.h"
#include "devices/UserLCD.h"
#include "devices/LCDi2c.h"


Scheduler sched;

void setup() {

    Serial.begin(9600);
    
    sched.init(100);

    /* Create task for the user detection, needs a user detector, in this case a PIR */
    PIR* userDetector = new PIRImpl(2 /*pin*/, 10000 /* calibration time*/);
    UserDetectionTask* userDetection = new UserDetectionTask(userDetector, 2, 10000);

    /* Create task for waste level monitoring. */
    Sonar* wasteDetector = new SonarImpl(8, 9, 22);
    WasteLevelDetectionTask* wasteLvlDetection = new WasteLevelDetectionTask(wasteDetector);

    /* Create task for user input via buttons */
    Button* btnOpen = new ButtonImpl(4);
    Button* btnClose = new ButtonImpl(3);
    ButtonControlTask* buttonControl = new ButtonControlTask(btnOpen, btnClose);

    /* Create task for temperature monitoring */
    TempSensor* tempSensor = new TempSensorImpl(A0);
    TemperatureMonitoringTask* tempMonitor = new TemperatureMonitoringTask(tempSensor);

    /* Create task for controlling the door, implemented via a servo simulating a door*/
    Door* door = new DoorImpl(10);
    DoorControlTask* doorControl = new DoorControlTask(door, 10000);

    /* Create task for the control of lights */
    Light* l1 = new Led(5);
    Light* l2 = new Led(6);
    LightsControlTask* lightsControl = new LightsControlTask(l1, l2);

    /* Create task for the communication with the operator */
    OperatorCommunicationTask* commTask = new OperatorCommunicationTask();

    /* Create task for lcd */
    UserLCD* lcd = new LCDi2c(0x27, 20, 4);
    LCDDisplayTask* lcdDisplay = new LCDDisplayTask(lcd);

    /* Attach tasks to each other */
    buttonControl->attach(doorControl);
    buttonControl->attach(lcdDisplay);
    buttonControl->attach(lightsControl);

    doorControl->attach(wasteLvlDetection);
    doorControl->attach(lcdDisplay);

    wasteLvlDetection->attach(lightsControl);
    wasteLvlDetection->attach(doorControl);
    wasteLvlDetection->attach(lcdDisplay);

    tempMonitor->attach(doorControl);
    tempMonitor->attach(lightsControl);
    tempMonitor->attach(lcdDisplay);

    userDetection->attach(lcdDisplay);

    commTask->attach(doorControl);
    commTask->attach(lcdDisplay);
    commTask->attach(tempMonitor);

    // se ci sono problemi disattivano l'input utente.
    wasteLvlDetection->addTaskToBeControlled(buttonControl);
    tempMonitor->addTaskToBeControlled(buttonControl);

    // Quando calibrato il pir attiva tutte le task.
    // userDetection->addTaskToBeControlled(wasteLvlDetection);
    // userDetection->addTaskToBeControlled(tempMonitor);
    // userDetection->addTaskToBeControlled(buttonControl);
    // userDetection->addTaskToBeControlled(doorControl);
    // userDetection->addTaskToBeControlled(lightsControl);
    // userDetection->addTaskToBeControlled(commTask);
    // userDetection->addTaskToBeControlled(lcdDisplay);

    /* Initialize tasks */
    userDetection->init(100);
    wasteLvlDetection->init(200);
    tempMonitor->init(200);
    buttonControl->init(100);
    doorControl->init(200);
    lightsControl->init(200);
    commTask->init(200);
    lcdDisplay->init(200);

    /* Add tasks to scheduler */
    sched.addTask(userDetection);
    sched.addTask(wasteLvlDetection);
    sched.addTask(tempMonitor);
    sched.addTask(buttonControl);
    sched.addTask(doorControl);
    sched.addTask(lightsControl);
    sched.addTask(commTask);
    sched.addTask(lcdDisplay);

    MsgService.init(); // Initialize the MsgService for serial communication
}


    // TODO: Verificare bene cosa succede all'avvio. -- FATTO
    // TODO: quando va in sleep l'lcd memorizza lo stato. -- FATTO
    // TODO: Valutare se disabilitare input utente mentre viene mostrato WASTE RECEIVED sull'lcd. -- PER ORA NO
    // TODO: Comunicare all'Operator Dashboard la temperatura e il livello corrente. -- FATTO

    // TODO: Valutare cosa succede se il sistema va in sleep (nessun movimento rilevato) mentre la porta è aperta o in reverse. -- rimane aperta, controllare ordine di esecuzione.



    
    // TODO: Controllare se l'operatore puo fare EMPTY e RESTORE mentre non è rilevato movimento.
    // TODO: Verificare i led.
    // TODO: impostare il motore a 0 all'avvio.
    // TODO: regolare i tempi di timeout per ogni cosa.
    // TODO: aggiungere stringa di messagio mentre sta svuotando.
    // TODO: dopo un paio di minuti segna waste received e non cambia piu. forse si addormenta mentre c'è waste received e bugga tutto.
    // TODO: a volte dopo aver svuotato non si aggiornano le luci e credo non si aggiorni lo stato di wastelvl monitoring.


void loop() {
    sched.schedule();
}