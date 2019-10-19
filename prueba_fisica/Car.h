#ifndef CAR_H_
#define CAR_H_

#include <Box2D/Box2D.h>

class Car {
  b2Body* body;
  static const float32 WIDTH_METERS;
  static const float32 LENGTH_METERS;
  static const float32 WEIGHT_KG;

  public:
  void Place(b2World& world, b2Vec2 position);
  void GasOn();
  const b2Vec2& GetPosition();
};

#endif  // CAR_H_
