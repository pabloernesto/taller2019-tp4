#ifndef ASPHALTTRACKPIECE_H_
#define ASPHALTTRACKPIECE_H_
#include "Car.h"
#include <vector>
#include "TrackPiece.h"

class AsphaltTrackPiece : public TrackPiece{

public:
  AsphaltTrackPiece(float x, float y, int track_type, std::vector<float> size);
  // void Place(b2World& world, b2Vec2 position);
  virtual void updateCarCounter(Car& car) override;
  const bool isCarOverMe(Car& car);
  const std::vector<float> GetPosition();
  const std::vector<float> GetSize();
  const int getTrackType();

};

#endif