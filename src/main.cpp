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


Scheduler sched;

void setup() {
    //Serial.begin(9600);
    sched.init(100);

    /* Create task for the user detection, needs a user detector, in this case a PIR */
    PIR* userDetector = new PIRImpl(2 /*pin*/, 5000 /* calibration time*/);
    Task* userDetection = new UserDetectionTask(userDetector, 2, 10000);
    userDetection->init(100);

    /* Create task for waste level monitoring. */
    Sonar* wasteDetector = new SonarImpl(8, 9, 22);
    WasteLevelDetectionTask* wasteLvlDetection = new WasteLevelDetectionTask(wasteDetector);
    wasteLvlDetection->init(200);

    /* Create task for user input via buttons */
    Button* btnOpen = new ButtonImpl(4);
    Button* btnClose = new ButtonImpl(3);
    ButtonControlTask* buttonControl = new ButtonControlTask(btnOpen, btnClose);
    buttonControl->init(100);

    // /* Create task for temperature monitoring */
    TempSensor* tempSensor = new TempSensorImpl(A0);
    TemperatureMonitoringTask* tempMonitor = new TemperatureMonitoringTask(tempSensor);
    tempMonitor->init(200);

    /* Create task for controlling the door, implemented via a servo simulating a door*/
    Door* door = new DoorImpl(10);
    DoorControlTask* doorControl = new DoorControlTask(door, 10000);
    buttonControl->attach(doorControl);
    doorControl->init(500);

    /* Create task for the control of lights */
    Light* l1 = new Led(5);
    Light* l2 = new Led(6);
    LightsControlTask* lightsControl = new LightsControlTask(l1, l2);
    buttonControl->attach(lightsControl);
    tempMonitor->attach(lightsControl);
    wasteLvlDetection->attach(lightsControl);
    lightsControl->init(200);

    /* Create task for the communication with the operator */
    OperatorCommunicationTask* commTask = new OperatorCommunicationTask();
    commTask->attach(tempMonitor);
    commTask->attach(doorControl);
    commTask->init(500);

    sched.addTask(userDetection);
    sched.addTask(wasteLvlDetection);
    sched.addTask(tempMonitor);
    sched.addTask(buttonControl);
    sched.addTask(doorControl);
    sched.addTask(lightsControl);
    sched.addTask(commTask);
}

void loop() {
    sched.schedule();
}