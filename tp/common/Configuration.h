#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <SDL2/SDL.h>
#include <string>

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
  float ANGULAR_VEL_MULT;
  float FRICTION;
  float EXPLODING_SEC_LIMIT;
  int LIFE;
  uint64_t FRAME_RATE;
  float SPEED_RED_TIME_SEC;
	float BOOST_MULT;
	float BOOST_DURATION_SEC;
	int PIXELS_PER_METER;
	float POSTA_WIDTH;
	float POSTA_HEIGHT;
	float TIME_STEP;
	int VELOCITY_ITERATIONS;
	int POSITION_ITERATIONS;
	int MODIFIERS_AVAILABLE;
	float MODIFIER_DIST_DROP;
	float MODIFIER_RESET_SEC;
	float MODIFIER_WIDTH;
	float MODIFIER_HEIGHT;
	float STONE_SPEED_REDUCTION;
  float OIL_INCREMENT;
  float OIL_DURATION;
	float PIECE_WIDTH;
	float PIECE_HEIGHT;
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
	std::string WINDOW_NAME;
	std::string SOUNDS_ROUTE;
  std::string IMAGES_ROUTE;
	std::string FONTS_ROUTE;
	std::string BACKGROUND_MUSIC;

  Configuration(const char* name);
  ~Configuration();
};

#endif