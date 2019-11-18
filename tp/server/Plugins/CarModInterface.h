#ifndef _CARMODINTERFACE_H_
#define _CARMODINTERFACE_H_
#include <stdlib.h>

class CarModInterface {
  
  public:
    // Life
    virtual void restoreLife() = 0;
    virtual void reduceLife() = 0;
    virtual bool isDamaged() = 0;
    
    // Speed
    virtual void multiplyMaxSpeed(float multiplier, size_t steps) = 0;
};

#endif