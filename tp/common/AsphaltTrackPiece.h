#ifndef ASPHALTTRACKPIECE_H_
#define ASPHALTTRACKPIECE_H_
// #include <SDL2/SDL.h>
// #include <Box2D/Box2D.h>
#include "Car.h"
#include <vector>

class AsphaltTrackPiece : TrackPiece{
private:
  // b2Body* body;
  // static const b2Vec2 TRACKPIECE_SIZE;
  // static const float32 TRACKPIECE_WEIGHT;
  // static const std::vector<size_t> SIZE;
  // float x;
  // float y;

public:
  AsphaltTrackPiece(float x, float y, std::vector<size_t> size);
  // void Place(b2World& world, b2Vec2 position);
  virtual void updateCarCounter(Car& car) override;
  const bool isCarOverMe(Car& car);
  const std::vector<float> GetPosition();
  const std::vector<size_t> GetSize();

};

#endif