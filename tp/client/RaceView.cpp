#include "RaceView.h"
#include <SDL2/SDL_ttf.h>
#include "ModifierView.h"
#include <iostream>
#include "Filmer.h"

#define MYCARIMAGEROUTE "Imagenes/pitstop_car_1.png"
#define OTHERSCARIMAGEROUTE "Imagenes/pitstop_car_2.png"
#define LIFENUMBERSIZE 20
#define LIFEPOSX 10
#define LIFEPOSY 10

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, CarProxy& car)
  : race(race), window(w), renderer(r), cars(),
  camara(0, 0, 600, 400, car), filmer(w,r), imagecache(w, r),
  track(imagecache), car(car)
{
  imagecache.LoadAnimation("Imagenes/pitstop_car_1.png", 3, 1, 10);
  imagecache.LoadAnimation("Imagenes/explosion.png", 12, 1, 10);
  auto& base_cars = race->GetCars();

  for (auto it = base_cars.begin(); it != base_cars.end(); it++){
    this->AddCarView((**it));
  }
}

RaceView::~RaceView(){}

void RaceView::AddCarView(CarProxy& carProxy){
  std::string img_route;
  if (carProxy.GetId() != car.GetId()){
    img_route = OTHERSCARIMAGEROUTE;
  } else {
    img_route = MYCARIMAGEROUTE;
  }
  cars.emplace_back(new CarView(
    imagecache.getImage(img_route),
    imagecache.getImage("Imagenes/explosion.png"),
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
    std::string path = "Imagenes/" + modifier.getType() + ".bmp";
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
  SDL_SetRenderTarget(renderer, NULL);
  this->RenderView(tick);
  
  //Render on film
  if (filmer.IsFilming()){
    SDL_SetRenderTarget(renderer, filmer.GetTexture());
    this->RenderView(tick);
    filmer.FilmFrame();
  }
}

void RaceView::StartFilming(){
  filmer.StartFilming();
}

void RaceView::showMessage(std::string message, int x, int y, int width, int height){
  TTF_Font* font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);
  SDL_Color color = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect Message_rect = {x, y, width* (int) message.size(), height};

  SDL_RenderCopyEx(renderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceMessage);
  TTF_CloseFont(font);
}