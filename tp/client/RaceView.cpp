#include "RaceView.h"
#include <SDL2/SDL_ttf.h>
#include "ModifierView.h"

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, Race& race, Car& car)
  : window(w), renderer(r), race(race), cars(),
  camara(0, 0, 600, 400, car),
  imagecache(w, r),
  track(imagecache, race.GetTrack())
{
  imagecache.LoadAnimation("Imagenes/pitstop_car_1.png", 3, 1, 10);
  imagecache.LoadAnimation("Imagenes/explosion.png", 12, 1, 10);
  auto& base_cars = race.GetCars();
  for (auto it = base_cars.begin() + cars.size(); it != base_cars.end(); it++)
    cars.emplace_back(
      imagecache.getImage("Imagenes/pitstop_car_1.png"),
      imagecache.getImage("Imagenes/explosion.png"),
      **it, camara);
  TTF_Init();
}

RaceView::~RaceView(){
	TTF_Quit();
}

void RaceView::render(int tick) {
  camara.Update();
  SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
  track.render(camara, this->race.getTrackPieces());
  std::vector<std::unique_ptr<Modifier>>& modifiers = this->race.getModifiers();
  for (auto it = modifiers.begin(); it != modifiers.end(); it++){
    Modifier& current_mod = **(it);
    std::string mod_type = (*it)->getType();
    std::string image_path = "Imagenes/" + mod_type + ".png"; 
    ModifierView current_mod_view(imagecache.getImage(image_path), current_mod, camara);
    current_mod_view.render(tick);
  }

  for (auto& car : cars)
    car.render(tick);

  if (race.Ended()){
    showMessage("GANASTE");
  }
}

void RaceView::showMessage(std::string message){
  TTF_Font* font = TTF_OpenFont("lazy.ttf", 50);
  SDL_Color color = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect Message_rect = {0, 0, 500, 500};

  SDL_RenderCopyEx(renderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);
	TTF_CloseFont(font);
}