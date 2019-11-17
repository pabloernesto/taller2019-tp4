#ifndef _MOD_H_
#define _MOD_H_
#include "../Race.h"
#include "../Car.h"


class Mod {
  
  public:
    Mod();
    virtual void execute(Race& race, Car& car) = 0;
    virtual ~Mod();  
};

#endif