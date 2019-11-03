#ifndef RACE_H_
#define RACE_H_

#include <Box2D/Box2D.h>
#include "Car.h"
#include "Track.h"
#include <vector>
#include <memory>   // unique_ptr

class Race {
  b2World world;
  std::vector<std::unique_ptr<Car>> cars;
  Track track;

public:
  Race(std::string track);
  void Step();
  Car& AddCar(float x, float y);
  std::vector<std::unique_ptr<Car>>& GetCars();
  Track& GetTrack();
  std::vector<std::unique_ptr<TrackPiece>>& getTrackPieces();

  Race();
};

#endif    // RACE_H_
