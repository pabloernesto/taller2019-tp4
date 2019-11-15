#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <SDL2/SDL.h>

struct Configuration {
public:
  float SCREEN_WIDTH;
  float SCREEN_HEIGHT;
  float CAR_WIDTH;
  float CAR_HEIGHT;
  float WEIGHT_KG;
  float ENGINE_POWER;
  float MAX_SPEED;
  float MAX_SPEED_REV;
  float ANGULAR_VEL_MULT0;
  float FRICTION;
  float EXPLODING_SEC_LIMIT;
  int LIFE;
  int FRAME_RATE;

public:
  Configuration(const char* name);
};

#endif