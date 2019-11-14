#ifndef BUTTONJOINRACE_H_
#define BUTTONJOINRACE_H_
#include "Button.h"

class ButtonJoinRace : public Button{
  private: 
    std::string name;
    SDL_Rect button;
    rapidjson::Value game;
    int index;

  public:
    ButtonJoinRace(std::string name, int width, int height, int index, rapidjson::Value&& game);
    virtual int ReactToClick(int x, int y, Connection& connection);
    rapidjson::Value& GetGame();
    int GetIndex();

};

#endif