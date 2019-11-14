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

  SCREEN_WIDTH = d["SCREEN_WIDTH"].GetFloat();		//Hay que pasarlo
	SCREEN_HEIGHT = d["SCREEN_HEIGHT"].GetFloat();	//Hay que pasarlo
	CAR_WIDTH = d["CAR_WIDTH"].GetFloat();
	CAR_HEIGHT = d["CAR_HEIGHT"].GetFloat();
	WEIGHT_KG = d["WEIGHT_KG"].GetFloat();
	ENGINE_POWER = d["ENGINE_POWER"].GetFloat();
	MAX_SPEED = d["MAX_SPEED"].GetFloat();
	MAX_SPEED_REV = d["MAX_SPEED_REV"].GetFloat();
	ANGULAR_VEL_MULT0 = d["ANGULAR_VEL_MULT"].GetFloat();
	FRICTION = d["FRICTION"].GetFloat();
	EXPLODING_SEC_LIMIT = d["EXPLODING_SEC_LIMIT"].GetFloat();
	LIFE = d["LIFE"].GetInt();
  FRAME_RATE = d["FRAME_RATE"].GetInt();
}