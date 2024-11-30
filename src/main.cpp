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

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(100);

    /* Create task for the user detection, needs a user detector, in this case a PIR */
    PIR* userDetector = new PIRImpl(2 /*pin*/, 5000 /* calibration time*/);
    Task* userDetection = new UserDetectionTask(userDetector, 10000);
    userDetection->init(100);

    /* Create task for user input via buttons */
    Button* btnOpen = new ButtonImpl(4);
    Button* btnClose = new ButtonImpl(3);
    ButtonControlTask* buttonControl = new ButtonControlTask(btnOpen, btnClose);
    buttonControl->init(100);

    // /* Create task for temperature monitoring */
    // TempSensor* tempSensor = new TempSensorImpl(A0);
    // Task* tempMonitor = new TemperatureMonitoringTask(tempSensor);

    /* Create task for controlling the door, implemented via a servo simulating a door*/
    Door* door = new DoorImpl(10);
    DoorControlTask* doorControl = new DoorControlTask(door, 10000);
    buttonControl->attach(doorControl);
    doorControl->init(500);


    sched.addTask(userDetection);
    sched.addTask(buttonControl);
    sched.addTask(doorControl);
}

void loop() {
    sched.schedule();
}