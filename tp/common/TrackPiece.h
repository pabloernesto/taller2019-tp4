#ifndef TRACKPIECE_H_
#define TRACKPIECE_H_
// #include <SDL2/SDL.h>
// #include <Box2D/Box2D.h>
#include "Car.h"
#include <vector>

class Car;

class TrackPiece{
private:
  // b2Body* body;
  // static const b2Vec2 TRACKPIECE_SIZE;
  // static const float32 TRACKPIECE_WEIGHT;
  // static const std::vector<size_t> SIZE;
  float x;
  float y;
  std::vector<size_t> size;
  int track_type;

public:
  TrackPiece(float x, float y, int track_type, std::vector<size_t> size);
  // void Place(b2World& world, b2Vec2 position);
  virtual void updateCarCounter(Car& car) = 0;
  const bool isCarOverMe(Car& car);
  const std::vector<float> GetPosition();
  const std::vector<size_t> GetSize();
  const int getTrackType();

};

#endif