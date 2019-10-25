#ifndef CAR_H_
#define CAR_H_

#include <Box2D/Box2D.h>

class Car {
  b2Body* body;
  bool gas;   // gas pedal. Is the car accelerating?

public:
  void GasOn();
  void GasOff();

  void Place(b2World& world, b2Vec2 position);
  const b2Vec2& GetPosition();
  const b2Vec2& GetSize();

  // width and length, in meters
  static const b2Vec2 CAR_SIZE;
  static const float32 WEIGHT_KG;
};

#endif    // CAR_H_
