#ifndef RACE_H_
#define RACE_H_

//#include "CarProxy.h"
//#include "ModifierProxy.h"
//#include "Track.h"
//#include <vector>
//#include <memory>   // unique_ptr
//#include "ContactListener.h"
#include "../common/socket.h"
#include <string>
// #include "TrackProxy.h"

class RaceProxy {
private:
  Connection& connection;
  // TrackProxy track;

public:
  RaceProxy(std::string track, Connection& connection);
  void AddCar();
};

#endif 
