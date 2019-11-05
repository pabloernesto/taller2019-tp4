#ifndef RACE_H_
#define RACE_H_

#include <Box2D/Box2D.h>
#include "Car.h"
#include "Track.h"
#include <vector>
#include <memory>   // unique_ptr
#include "ContactListener.h"
#include "Posta.h"

class Race {
  b2World world;
  std::vector<std::unique_ptr<Car>> cars;
  std::vector<std::unique_ptr<Posta>> postas;
  Track track;
  ContactListener listener;

public:
  Race(std::string track);
  void Step();
  Car& AddCar(float x, float y);
  void AddPosta(float x, float y, int id, float32 angle);
  std::vector<std::unique_ptr<Car>>& GetCars();
  Track& GetTrack();
  std::vector<std::unique_ptr<TrackPiece>>& getTrackPieces();

  Race();
};

#endif    // RACE_H_
