#ifndef CAR_H_
#define CAR_H_

#include <Box2D/Box2D.h>
#include "Track.h"
#include "Contactable.h"
#include "Posta.h"
#include "Plugins/CarModInterface.h"

class Track;
class Race;

class Car : public Contactable, public CarModInterface{
  int id;
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
  size_t step_counter_max_speed_mult;
  float max_speed_multiplier;
  float speed_reducer;
  size_t step_counter_red_speed;
  float angular_vel_modif;
  size_t step_counter_ang_velocity;

  std::unique_ptr<Posta> lastPosta;
  bool dead;
  Race* race;
  int laps;
  b2Vec2 car_size;

  public:
  Car(int id, Race* race);
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
  float getReducedSpeed(float speed_rcv);
  float GetSpeed();
  const b2Vec2& GetPosition();
  float GetAngle();
  const b2Transform& GetTransform();
  const b2Vec2& GetSize();
  void updateCounter(size_t value);
  void updateMaxSpeed();
  void updateAngularVelocity();
  void setCounter(size_t value);
  bool isGoingForward();
  // Called on every step of the simulation to apply external (user) forces
  void Step(Track& track);

  // Methods for modifiers (and CarModInterface):
  void restoreLife() override;
  void multiplyMaxSpeed(float multiplier, size_t steps) override;
  void incrementAngularVelocity(float amount, size_t steps);
  void updateMaxSpeedMultiplier();
  void reduceLife() override;
  void reduceSpeed(float speed_reduction);
  bool isDamaged() override;

  virtual void Contact(Contactable* contactable);
  virtual void GetContactedBy(Car* car);
  virtual void GetContactedBy(Posta* posta);
  virtual void GetContactedBy(Modifier* modifier);
  bool isDead();
  int GetId();
  bool isBreakOn();
  int GetLife();

private:
  void DieAndRevive(Track& track);
};

#endif  // CAR_H_
