#ifndef CAR_H_
#define CAR_H_

#include <Box2D/Box2D.h>

class Car {
  b2Body* body;
  bool gas;
  bool break_;
  int life;

  static const b2Vec2 CAR_SIZE;
  static const float32 WEIGHT_KG;
  static const float32 ENGINE_POWER;

  public:
  Car();
  void Place(b2World& world, b2Vec2 position);

  void GasOn();
  void GasOff();
  void BreakOn();
  void BreakOff();

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  const b2Vec2& GetPosition();
  const b2Vec2& GetSize();

  // Called on every step of the simulation to apply external (user) forces
  void Step();
};

#endif  // CAR_H_
