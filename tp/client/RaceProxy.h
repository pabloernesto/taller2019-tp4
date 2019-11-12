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
#include <mutex>
#include "rapidjson/document.h"

class RaceProxy {
private:
  BlockingQueue<std::string> bq;
  EnqueuedConnection ec;
  std::vector<std::unique_ptr<CarProxy>> cars;

  std::vector<std::unique_ptr<ModifierProxy>> modifiers;
  std::mutex modifiers_mtx;

  std::thread t;
  std::vector<std::unique_ptr<TrackPieceProxy>> tracks;

  void UpdateLoop();
  CarProxy* GetCarWithId(int id);

public:
  RaceProxy(std::string track, Connection&& connection);
  void Start();
  std::vector<std::unique_ptr<TrackPieceProxy>>& getTrackPieces(); 
  CarProxy* GetCar(int id);
  std::vector<std::unique_ptr<CarProxy>>& GetCars();
  std::vector<ModifierProxy> getModifiers();
};

#endif 
