#ifndef TRACKPIECE_H_
#define TRACKPIECE_H_
#include "Car.h"
#include <vector>

class Car;

class TrackPiece{
private:
  float x;
  float y;
  std::vector<float> size;
  int track_type;

public:
  TrackPiece(float x, float y, int track_type, std::vector<float> size);
  virtual void updateCarCounter(Car& car) = 0;
  const bool isCarOverMe(Car& car);
  const std::vector<float> GetPosition();
  const std::vector<float> GetSize();
  const int getTrackType();

};

#endif