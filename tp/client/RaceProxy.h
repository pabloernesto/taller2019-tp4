#ifndef RACE_H_
#define RACE_H_

#include "CarProxy.h"
#include "ModifierProxy.h"
#include <vector>
#include <memory>   // unique_ptr
#include "../common/socket.h"
#include <string>
#include "TrackPieceProxy.h"
#include "../common/EnqueuedConnection.h"
#include "../common/blockingqueue.h"
#include <thread>
#include "../rapidjson/document.h"

class RaceProxy {
private:
  Connection& connection;
  BlockingQueue<std::string> bq;
  EnqueuedConnection ec;
  std::vector<std::unique_ptr<CarProxy>> cars;
  std::vector<std::unique_ptr<ModifierProxy>> modifiers;
  std::thread t;
  std::vector<std::unique_ptr<TrackPieceProxy>> tracks;

  void UpdateLoop();
  CarProxy* GetCarWithId(int id);

public:
  RaceProxy(std::string track, Connection& connection);
  void Start();
  CarProxy* GetCar(int id);
  std::vector<std::unique_ptr<CarProxy>>& GetCars();
  std::vector<std::unique_ptr<ModifierProxy>>& getModifiers();
};

#endif 
