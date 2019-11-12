#ifndef RACE_H_
#define RACE_H_

#include "CarProxy.h"
//#include "ModifierProxy.h"
//#include "Track.h"
//#include <vector>
#include <memory>   // unique_ptr
//#include "ContactListener.h"
#include "../common/socket.h"
#include <string>
#include "TrackProxy.h"
#include "../common/EnqueuedConnection.h"
#include "../common/blockingqueue.h"

class RaceProxy {
private:
  Connection& connection;
  TrackProxy track;
  BlockingQueue<std::string> bq;
  EnqueuedConnection ec;
  std::vector<std::unique_ptr<CarProxy>> cars;

public:
  RaceProxy(std::string track, Connection& connection);
};

#endif 
