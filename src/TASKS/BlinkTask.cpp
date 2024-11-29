#include "tasks/BlinkTask.h"

BlinkTask::BlinkTask(int pin){
  this->pin = pin;
  led = new Led(pin); 
}
  
void BlinkTask::init(int period){
  Task::init(period);
  state = OFF;
}
  
void BlinkTask::tick(){
  switch (state){
    case OFF:
      led->switchOn();
      state = ON; 
      break;
    case ON:
      led->switchOff();
      state = OFF;
      break;
  }
}
