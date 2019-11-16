#include "Configuration.h"
#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <fstream>

Configuration::Configuration(const char* name){
  std::ifstream ifs(name);
  rapidjson::IStreamWrapper isw(ifs);

  rapidjson::Document d;
  d.ParseStream(isw);

  SCREEN_WIDTH = d["SCREEN_WIDTH"].GetFloat();    //Hay que pasarlo
  SCREEN_HEIGHT = d["SCREEN_HEIGHT"].GetFloat();  //Hay que pasarlo
  CAR_WIDTH = d["CAR_WIDTH"].GetFloat();
  CAR_HEIGHT = d["CAR_HEIGHT"].GetFloat();
  WEIGHT_KG = d["WEIGHT_KG"].GetFloat();
  ENGINE_POWER = d["ENGINE_POWER"].GetFloat();
  MAX_SPEED = d["MAX_SPEED"].GetFloat();
  MAX_SPEED_REV = d["MAX_SPEED_REV"].GetFloat();
  ANGULAR_VEL_MULT = d["ANGULAR_VEL_MULT"].GetFloat();
  FRICTION = d["FRICTION"].GetFloat();
  EXPLODING_SEC_LIMIT = d["EXPLODING_SEC_LIMIT"].GetFloat();
  LIFE = d["LIFE"].GetInt();
  FRAME_RATE = d["FRAME_RATE"].GetUint64();
  SPEED_RED_TIME_SEC = d["SPEED_RED_TIME_SEC"].GetFloat();
  BOOST_MULT = d["BOOST_MULT"].GetFloat();
	BOOST_DURATION_SEC = d["BOOST_DURATION_SEC"].GetFloat();
	PIXELS_PER_METER = d["PIXELS_PER_METER"].GetInt();
	POSTA_WIDTH = d["POSTA_WIDTH"].GetFloat();
	POSTA_HEIGHT = d["POSTA_HEIGHT"].GetFloat();
	TIME_STEP = d["TIME_STEP"].GetFloat();
	VELOCITY_ITERATIONS = d["VELOCITY_ITERATIONS"].GetInt();
	POSITION_ITERATIONS = d["POSITION_ITERATIONS"].GetInt();
	MODIFIERS_AVAILABLE = d["MODIFIERS_AVAILABLE"].GetInt();
	MODIFIER_DIST_DROP = d["MODIFIER_DIST_DROP"].GetFloat();
	MODIFIER_RESET_SEC = d["MODIFIER_RESET_SEC"].GetFloat();
	MODIFIER_WIDTH = d["MODIFIER_WIDTH"].GetFloat();
	MODIFIER_HEIGHT = d["MODIFIER_HEIGHT"].GetFloat();
	STONE_SPEED_REDUCTION = d["STONE_SPEED_REDUCTION"].GetFloat();
	PIECE_WIDTH = d["PIECE_WIDTH"].GetFloat();
	PIECE_HEIGHT = d["PIECE_HEIGHT"].GetFloat();
}

Configuration::~Configuration(){
}