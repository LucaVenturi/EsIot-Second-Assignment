#include "Synchronizable.h"
#include <Arduino.h>
  
void Synchronizable::updateSyncTime(){
	lastTimeSync = millis();
}

long Synchronizable::getLastSyncTime(){
	return lastTimeSync;
}
