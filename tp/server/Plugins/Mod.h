#ifndef _MOD_H_
#define _MOD_H_
#include "../RaceModInterface.h"
#include "../CarModInterface.h"
#include <vector>

class Mod {
  
  public:
    virtual void execute(RaceModInterface* race, std::vector<CarModInterface*> cars) = 0;
    virtual ~Mod();  
};

#endif