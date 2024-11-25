#ifndef __BUTTON__
#define __BUTTON__

#include "Synchronizable.h"

class Button : public Synchronizable {
 
public:
  Button();
  virtual bool isPressed() = 0;
};

#endif
