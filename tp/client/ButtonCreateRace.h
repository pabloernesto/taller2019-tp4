#ifndef BUTTONCREATERACE_H_
#define BUTTONCREATERACE_H_
#include "Button.h"

class ButtonCreateRace : public Button{
  private:
    std::string name;
    SDL_Rect button;

  public:
    ButtonCreateRace(std::string name, int width, int height);
    virtual RaceProxy* ReactToClick(int* id_player, int x, int y, Connection& connection);

};

#endif