#ifndef CAR_H_
#define CAR_H_

#include <Box2D/Box2D.h>

class Car {
  b2Body* body;
  bool gas;

  public:
  void Place(b2World& world, b2Vec2 position);
  void GasOn();
  void GasOff();
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  const b2Vec2& GetPosition();
  const b2Vec2& GetSize();

  static const b2Vec2 CAR_SIZE;
  static const float32 WEIGHT_KG;
};

#endif  // CAR_H_
