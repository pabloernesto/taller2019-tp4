#ifndef CAR_H_
#define CAR_H_

#include <Box2D/Box2D.h>
#include "Track.h"
#include "Contactable.h"
#include "Posta.h"

class Track;

class Car : public Contactable{
  b2Body* body;
  bool gas;
  bool break_;
  bool reverse;
  // char steer;   // one of l/r/c, for left/right/center
  int life;
  float max_speed;
  float32 angular_velocity;
  size_t step_counter;
  size_t step_counter_death;
  std::unique_ptr<Posta> lastPosta;
  bool dead;

  static const b2Vec2 CAR_SIZE;
  static const float32 WEIGHT_KG;
  static const float32 ENGINE_POWER;
  static const float MAX_SPEED;
  static const float MAX_SPEED_REV;
  static const float32 ANGULAR_VEL_MULT;
  static const float32 FRICTION;
  static const size_t EXPLODING_SEC_LIMIT;
  static const size_t LIFE;

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
  void reverseOn();
  void reverseOff();
  bool isGoingReverse();
  bool stopped();

  // Calculate the car's forward speed
  float GetSpeed();
  const b2Vec2& GetPosition();
  float GetAngle();
  const b2Vec2& GetSize();
  void updateCounter(size_t value);
  void updateMaxSpeed();
  void setCounter(size_t value);
  bool isGoingForward();
  // Called on every step of the simulation to apply external (user) forces
  void Step(Track& track);
  virtual void Contact(Contactable* contactable);
  virtual void GetContactedBy(Car* car);
  virtual void GetContactedBy(Posta* posta);
  bool isDead();

private:
  void DieAndRevive(Track& track);
};

#endif  // CAR_H_
