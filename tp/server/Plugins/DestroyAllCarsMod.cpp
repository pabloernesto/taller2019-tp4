#include "DestroyAllCarsMod.h"
#include <iostream>

extern "C" Mod* create(){
  return new DestroyAllCarsMod;
}

DestroyAllCarsMod::DestroyAllCarsMod(){}

void DestroyAllCarsMod::execute(RaceModInterface* race, std::vector<CarModInterface*> cars){
  std::cout << "Inside execute\n";
  for (auto it = cars.begin(); it != cars.end(); it ++){
    for (size_t i = 0; i < 10 ; i ++){
      (*it)->reduceLife();
    }
  }
}

DestroyAllCarsMod::~DestroyAllCarsMod(){}