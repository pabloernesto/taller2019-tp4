#ifndef CAR_H_
#define CAR_H_

#include <Box2D/Box2D.h>

class Car {
  b2Body* body;
  bool gas;
  bool break_;
  // char steer;   // one of l/r/c, for left/right/center
  int life;
  float32 angular_velocity;

  static const b2Vec2 CAR_SIZE;
  static const float32 WEIGHT_KG;
  static const float32 ENGINE_POWER;
  static const float MAX_SPEED;
  static const float32 ANGULAR_VEL_MULT;

  public:
  Car();
  virtual void Place(b2World& world, b2Vec2 position);

  void GasOn();
  void GasOff();
  void BreakOn();
  void BreakOff();
  void SteerLeft();
  void SteerRight();
  void SteerCenter();

  // Calculate the car's forward speed
  float GetSpeed();

  const b2Vec2& GetPosition();
  virtual const b2Vec2& GetPositionToRenderize();
  float GetAngle();
  const b2Vec2& GetSize();

  // Called on every step of the simulation to apply external (user) forces
  void Step();
};

#endif  // CAR_H_
