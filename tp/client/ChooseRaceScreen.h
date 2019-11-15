#ifndef CHOOSERACESCREEN_H_
#define CHOOSERACESCREEN_H_
#include "GameScreen.h"
#include "ButtonJoinRace.h"
#include "Button.h"
#include <vector>
#include <string>
#include <memory>   // unique_ptr

class ChooseRaceScreen : public GameScreen{
private:
  std::vector<std::unique_ptr<Button>> buttons;

public:
  ChooseRaceScreen(SDL_Window *w, SDL_Renderer *r);
  ~ChooseRaceScreen();
  GameScreen* start();

private:
  void showMessage(std::string message, int size, int x, int y);
  void GetGames(Connection& connection, rapidjson::Document* race_list);
  void DrawWindow();
};

#endif