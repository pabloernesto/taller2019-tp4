#ifndef BUTTONSTART_H_
#define BUTTONSTART_H_
#include "Button.h"

class ButtonStart : public Button{
  private: 
    std::string name;
    SDL_Rect button;
    int index;

  public:
    ButtonStart(std::string name, int width, int height);
    virtual RaceProxy* ReactToClick(int* id_player, int x, int y, Connection& connection);
};

#endif