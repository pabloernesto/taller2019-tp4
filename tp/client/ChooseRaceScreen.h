#ifndef CHOOSERACESCREEN_H_
#define CHOOSERACESCREEN_H_
#include "GameScreen.h"
#include "Button.h"
#include <vector>
#include <string>
#include <memory>   // unique_ptr
#include "../common/socket.h"
#include "rapidjson/document.h"

class ChooseRaceScreen : public GameScreen{
private:
  std::unique_ptr<Button> button_chain;
  TTF_Font* font;

public:
  GameScreen* next_screen;
  Connection connection;

  ChooseRaceScreen(SDL_Window *w, SDL_Renderer *r);
  ~ChooseRaceScreen();
  GameScreen* start();

private:
  void GetGames(Connection& connection, rapidjson::Document* race_list);
  void DrawWindow();
};

#endif