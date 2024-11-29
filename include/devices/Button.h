#ifndef __BUTTON__
#define __BUTTON__

#include "Synchronizable.h"

class Button : public Synchronizable {
 
public:
  virtual bool isPressed() = 0;
};

#endif
