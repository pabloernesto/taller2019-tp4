#include "RaceView.h"
#include <SDL2/SDL_ttf.h>
#include "ModifierView.h"
#include <iostream>

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, CarProxy& car)
  : race(race), window(w), renderer(r), cars(),
  camara(0, 0, 600, 400, car), imagecache(w, r),
  track(imagecache), car(car)
{
  imagecache.LoadAnimation("Imagenes/pitstop_car_1.png", 3, 1, 10);
  imagecache.LoadAnimation("Imagenes/explosion.png", 12, 1, 10);
  auto& base_cars = race->GetCars();

  for (auto it = base_cars.begin(); it != base_cars.end(); it++){
    cars.emplace_back(
      imagecache.getImage("Imagenes/pitstop_car_1.png"),
      imagecache.getImage("Imagenes/explosion.png"),
      **it, camara);
  }
  TTF_Init();
}

RaceView::~RaceView(){
  TTF_Quit();
}

void RaceView::render(int tick) {
  camara.Update();
  SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
  track.render(camara, this->race->getTrackPieces());

  //Actualizo CarViews
  auto& carProxies = race->GetCars();
  if (carProxies.size() > cars.size()){
    for (auto it = carProxies.begin() + cars.size(); it != carProxies.end(); it++){
    //Image& img = imagecache.getImage("Imagenes/pitstop_car_1.png");
    //if ((*it)->GetId() != car.GetId()){
      //img.ChangeColor();
    //}
    cars.emplace_back(
      imagecache.getImage("Imagenes/pitstop_car_1.png"),
      imagecache.getImage("Imagenes/explosion.png"),
      **it, camara);
    }
  }

  // Modifiers may be added or removed at any time. Re-get this every tick.
  auto&& modifiers = this->race->getModifiers();
  for (auto& modifier : modifiers) {
    std::string path = "Imagenes/" + modifier.getType() + ".bmp";
    ModifierView view(imagecache.getImage(path), modifier, camara);
    view.render(tick);
  }

  for (auto& car : cars){
    car.render(tick);
  }
  
  if (race->Ended()){
    if (race->GetWinnerId() == car.GetId()){
      showMessage("GANASTE");
    } else {
      showMessage("PERDISTE");
    }
  }
}

void RaceView::showMessage(std::string message){
  TTF_Font* font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);
  SDL_Color color = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect Message_rect = {0, 0, 70*7, 70};

  SDL_RenderCopyEx(renderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceMessage);
  TTF_CloseFont(font);
}