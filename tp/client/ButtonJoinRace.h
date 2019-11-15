#ifndef BUTTONJOINRACE_H_
#define BUTTONJOINRACE_H_
#include "Button.h"

class ButtonJoinRace : public Button{
  private: 
    std::string name;
    SDL_Rect button;
    int index;

  public:
    ButtonJoinRace(std::string name, int width, int height, int index);
    virtual RaceProxy* ReactToClick(int* id_player, int x, int y, Connection& connection);
    int GetIndex();

};

#endif