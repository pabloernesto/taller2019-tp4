#ifndef CAR_H_
#define CAR_H_

#include <Box2D/Box2D.h>

class Car {
  b2Body* body;

  public:
  void Place(b2World& world, b2Vec2 position);
  void GasOn();
  const b2Vec2& GetPosition();

  static const float32 WIDTH_METERS;
  static const float32 LENGTH_METERS;
  static const float32 WEIGHT_KG;
};

#endif  // CAR_H_
