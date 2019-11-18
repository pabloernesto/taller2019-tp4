#ifndef _DESTROYALLCARSMOD_H_
#define _DESTROYALLCARSMOD_H_
#include "Mod.h"

class DestroyAllCarsMod : public Mod{

  public:
    DestroyAllCarsMod();
    virtual void execute(RaceModInterface* race, std::vector<CarModInterface*> cars) override;
    virtual ~DestroyAllCarsMod();

};

#endif