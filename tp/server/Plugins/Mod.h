#ifndef _MOD_H_
#define _MOD_H_
#include "../Race.h"


class Mod {
  
  public:
    virtual void execute(Race* race) = 0;
    virtual ~Mod();  
};

#endif