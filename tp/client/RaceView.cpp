#include "RaceView.h"
#include <SDL2/SDL_ttf.h>
#include "ModifierView.h"
#include <iostream>
#include "Filmer.h"
#include "../common/Configuration.h"

extern Configuration configuration;

#define MYCAR "pitstop_car_1.png"
#define OTHERSCAR "pitstop_car_2.png"
#define LIFENUMBERSIZE 20
#define LIFEPOSX 10
#define LIFEPOSY 10
#define FILMBUTTONWIDTH 30
#define FILMBUTTONHEIGHT 10
#define EXPLOTION "explosion.png"
#define FONT "MAKISUPA.TTF"

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, CarProxy& car)
  : race(race), window(w), renderer(r), cars(),
  camara(0, 0, configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT, car),
  filmer(w,r), imagecache(w, r), track(imagecache), car(car),
  font(TTF_OpenFont((configuration.FONTS_ROUTE + FONT).c_str(), 50))
{
  imagecache.LoadAnimation(configuration.IMAGES_ROUTE + MYCAR, 3, 1, 10);
  imagecache.LoadAnimation(configuration.IMAGES_ROUTE + EXPLOTION, 12, 1, 10);
  auto& base_cars = race->GetCars();

  for (auto it = base_cars.begin(); it != base_cars.end(); it++){
    this->AddCarView((**it));
  }
}

RaceView::~RaceView(){
  TTF_CloseFont(font);
}

void RaceView::AddCarView(CarProxy& carProxy){
  std::string img_route;
  if (carProxy.GetId() != car.GetId()){
    img_route = configuration.IMAGES_ROUTE + OTHERSCAR;
  } else {
    img_route = configuration.IMAGES_ROUTE + MYCAR;
  }
  cars.emplace_back(new CarView(
    imagecache.getImage(img_route),
    imagecache.getImage(configuration.IMAGES_ROUTE + EXPLOTION),
    carProxy, camara));
}

void RaceView::renderLife(int life){
  showMessage("LIFE: " + std::to_string(life), LIFEPOSX, LIFEPOSY,
    LIFENUMBERSIZE, LIFENUMBERSIZE);
}

void RaceView::UpdateNewCars(){
  auto& carProxies = race->GetCars();
  if (carProxies.size() > cars.size()){
    for (auto it = carProxies.begin() + cars.size(); it != carProxies.end(); it++){
      this->AddCarView((**it));
    }
  }
}

void RaceView::RenderView(int tick){
  SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
  SDL_RenderClear(renderer);
  track.render(camara, this->race->getTrackPieces());

  // Modifiers may be added or removed at any time. Re-get this every tick.
  auto&& modifiers = this->race->getModifiers();
  for (auto& modifier : modifiers) {
    std::string path = configuration.IMAGES_ROUTE + modifier.getType() + ".bmp";
    ModifierView view(imagecache.getImage(path), modifier, camara);
    view.render(tick);
  }

  for (auto& car : cars){
    car->render(tick);
  }

  this->renderLife(car.GetLife());
}

void RaceView::render(int tick) {
  this->UpdateNewCars();
  camara.Update();

  //Render on user screen
  this->RenderView(tick);
  filmer.FilmFrame();   // Does nothing if filmer hasn't started
}

void RaceView::ChangeFilmingState(){
  if (!filmer.IsFilming()){
    filmer.Join();
    filmer.Start();
  } else {
    filmer.Shutdown();
  }
}

void RaceView::showMessage(std::string message, int x, int y, int width, int height){
  SDL_Color color = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect Message_rect = {x, y, width* (int) message.size(), height};

  SDL_RenderCopyEx(renderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceMessage);
}