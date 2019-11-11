#ifndef RACEFABRIC_H_
#define RACEFABRIC_H_

#include <Box2D/Box2D.h>
#include <memory>   // unique_ptr
#include <vector>
#include "Race.h"

class RaceFabric {

public:
  RaceFabric();
  static Race* makeRace1();
};

#endif    // RACE_H_
