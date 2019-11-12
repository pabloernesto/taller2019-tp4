#include "RaceProxy.h"
#define BQSIZE 100

RaceProxy::RaceProxy(std::string track, Connection& connection) : 
  track(track), connection(connection), bq(BQSIZE), ec(std::move(connection), bq),
  cars(){
    std::string out;
    ec.GetIncomingQueue().trypop(&out);
  }

void RaceProxy::Step() {


  for (auto& car : cars) {
    car->Step(this->track);
  }
  if (this->modifiers_reset == 0){
    this->placeModifiers();
    modifiers_reset = MODIFIER_RESET_SEC*60;
  } else {
    modifiers_reset -= 1;
  }
  this->removeUsedModifiers();
  this->world.Step(timestep, velocityIterations, positionIterations);
}