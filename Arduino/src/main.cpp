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

/* mettere questi in un file sarebbe top */
#define CALIBRATION_TIME 10000
#define SCHED_PERIOD 100
#define TSLEEP 60000
#define PIN_PIR 2
#define PIN_SONAR_ECHO 9
#define PIN_SONAR_TRIG 8
#define ROOM_TEMP 23 /* leggerlo dal sensore sarebbe meglio i know... */
#define PIN_BTN_OPEN 4
#define PIN_BTN_CLOSE 3
#define PIN_TEMP_SENSOR A0
#define PIN_DOOR_SERVO 10
#define T1 10000
#define T3 5000
#define PIN_L1 5
#define PIN_L2 6
#define ADDR_I2C_LCD 0x27
#define LCD_ROWS 4
#define LCD_COLS 20


Scheduler sched;

void setup() {
    
    //sched.init(SCHED_PERIOD);

    /* Create task for the user detection, needs a user detector, in this case a PIR */
    PIR* userDetector = new PIRImpl(PIN_PIR, CALIBRATION_TIME);
    UserDetectionTask* userDetection = new UserDetectionTask(userDetector, PIN_PIR, TSLEEP);

    /* Create task for waste level monitoring, uses a Sonar */
    Sonar* wasteDetector = new SonarImpl(PIN_SONAR_TRIG, PIN_SONAR_ECHO, ROOM_TEMP);
    WasteLevelDetectionTask* wasteLvlDetection = new WasteLevelDetectionTask(wasteDetector);

    /* Create task for user input via buttons */
    Button* btnOpen = new ButtonImpl(PIN_BTN_OPEN);
    Button* btnClose = new ButtonImpl(PIN_BTN_CLOSE);
    ButtonControlTask* buttonControl = new ButtonControlTask(btnOpen, btnClose);

    /* Create task for temperature monitoring*/
    TempSensor* tempSensor = new TempSensorImpl(PIN_TEMP_SENSOR);
    TemperatureMonitoringTask* tempMonitor = new TemperatureMonitoringTask(tempSensor);

    /* Create task for controlling the door, implemented via a servo simulating a door*/
    Door* door = new DoorImpl(PIN_DOOR_SERVO);
    DoorControlTask* doorControl = new DoorControlTask(door, T1, T3);

    /* Create task for the control of lights */
    Light* l1 = new Led(PIN_L1);
    Light* l2 = new Led(PIN_L2);
    LightsControlTask* lightsControl = new LightsControlTask(l1, l2);

    /* Create task for the communication with the operator dashboard*/
    OperatorCommunicationTask* commTask = new OperatorCommunicationTask();

    /* Create task for lcd */
    UserLCD* lcd = new LCDi2c(ADDR_I2C_LCD, LCD_COLS, LCD_ROWS);
    LCDDisplayTask* lcdDisplay = new LCDDisplayTask(lcd);


    /* Attach observers to each task */
    buttonControl->attachObserver(doorControl);
    buttonControl->attachObserver(lcdDisplay);
    buttonControl->attachObserver(lightsControl);

    doorControl->attachObserver(wasteLvlDetection);
    doorControl->attachObserver(lcdDisplay);

    wasteLvlDetection->attachObserver(lightsControl);
    wasteLvlDetection->attachObserver(doorControl);
    wasteLvlDetection->attachObserver(lcdDisplay);

    tempMonitor->attachObserver(doorControl);
    tempMonitor->attachObserver(lightsControl);
    tempMonitor->attachObserver(lcdDisplay);

    userDetection->attachObserver(lcdDisplay);

    commTask->attachObserver(doorControl);
    commTask->attachObserver(lcdDisplay);
    commTask->attachObserver(tempMonitor);

    // Add the tasks that get controlled by other tasks, in this case I only deactivate and reactivate the button task when there is a problem and i want to disable the user input.
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
    userDetection->init(SCHED_PERIOD);
    wasteLvlDetection->init(SCHED_PERIOD * 2);
    tempMonitor->init(SCHED_PERIOD * 2);
    buttonControl->init(SCHED_PERIOD);
    doorControl->init(SCHED_PERIOD * 2);
    lightsControl->init(SCHED_PERIOD * 2);
    commTask->init(SCHED_PERIOD * 2);
    lcdDisplay->init(SCHED_PERIOD * 2);

    sched.init(SCHED_PERIOD);

    /* Add tasks to scheduler */
    sched.addTask(userDetection);
    sched.addTask(wasteLvlDetection);
    sched.addTask(buttonControl);
    sched.addTask(doorControl);
    sched.addTask(tempMonitor);
    sched.addTask(lcdDisplay);
    sched.addTask(lightsControl);
    sched.addTask(commTask);

    /* Beging Serial and msgservice which uses serial */
    Serial.begin(9600);
    MsgService.init();

}

    // TODO: Valutare se disabilitare input utente mentre viene mostrato WASTE RECEIVED sull'lcd. -- PER ORA NO
    // TODO: Valutare cosa succede se il sistema va in sleep (nessun movimento rilevato) mentre la porta è aperta o in reverse. -- rimane aperta.

    // TODO: Controllare se l'operatore puo fare EMPTY e RESTORE mentre non è rilevato movimento.
    // FATTO: impostare il motore a 0 all'avvio.
    // FATTO: regolare i tempi di timeout per ogni cosa.

void loop() {
    sched.schedule();
}