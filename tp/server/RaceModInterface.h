#ifndef _RACEMODINTERFACE_H_
#define _RACEMODINTERFACE_H_
#include "CarModInterface.h"

class RaceModInterface {

  public:
    // Modifiers
    virtual void placeRandomModifier(float x, float y) = 0;
    virtual void placeStoneModifier(float x, float y) = 0;
    virtual void placeBoostModifier(float x, float y) = 0;
    virtual void placeHealthModifier(float x, float y) = 0;
    virtual void removeModifiers() = 0;
    virtual void removeStoneModifiers() = 0;
    virtual void removeBoostModifiers() = 0;
    virtual void removeHealthModifiers() = 0;
};

#endif
