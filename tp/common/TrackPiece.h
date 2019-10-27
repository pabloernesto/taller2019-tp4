#ifndef TRACKPIECE_H_
#define TRACKPIECE_H_
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

class TrackPiece{
private:
  b2Body* body;
  static const b2Vec2 TRACKPIECE_SIZE;
  static const float32 TRACKPIECE_WEIGHT;
  
public:
  TrackPiece();
  void Place(b2World& world, b2Vec2 position);
};

#endif