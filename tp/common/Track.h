#ifndef TRACK_H_
#define TRACK_H_

// #include "Event.h"
// #include "image.h"
#include "TrackPiece.h"
// #include <SDL2/SDL.h>
// #include "Camara.h
// #include "Event.h"
// #include "image.h"
#include "TrackPiece.h"
// #include "Camara.h"
// #include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>   // unique_ptr
// #include <Box2D/Box2D.h>
#include "Car.h"

class TrackPiece;
class Car;

enum trackTypes {
  HORIZONTAL,
  VERTICAL,
  GIRO_ARRIBADER,
  GIRO_ABAJODER,
  GIRO_ARRIBAIZQ,
  GIRO_ABAJOIZQ,
  PASTO
};

class Track{
private:
  static const std::vector<size_t> PIECE_SIZE;
  size_t num_rows;
  size_t num_cols;
  std::vector<std::vector<int>> blocks;
  std::vector<std::unique_ptr<TrackPiece>> tracks;
  
public:
  // Track(uint16_t height, uint16_t width, std::vector<int> blocks);
  // Track(std::string event, b2World& world);
  // std::string ToStr();
  // void render(SDL_Window* w, SDL_Renderer* r, SDL_Rect& camara);
  Track(std::string race_specs);
  void updateCarCounter(Car& car);
  std::vector<std::unique_ptr<TrackPiece>>& getTrackPieces();
  // Track(uint16_t height, uint16_t width, std::vector<int> blocks);
  // Track(std::string event, b2World& world);
  // std::string ToStr();
  // void render(SDL_Window* w, SDL_Renderer* r, Camara& camara);

/*private:
  // The TrackImages function ensures that assets are loaded exactly once
  std::vector<std::unique_ptr<Image>>& TrackImages(
    SDL_Window* w, SDL_Renderer* r);
  void initializeTrackPieces();*/
};

#endif