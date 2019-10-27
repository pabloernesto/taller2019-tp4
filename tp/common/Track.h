#ifndef TRACK_H_
#define TRACK_H_
#include "Event.h"
#include "image.h"
#include "TrackPiece.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include <Box2D/Box2D.h>

enum trackTypes {
  HORIZONTAL,
  VERTICAL,
  GIRO_ARRIBADER,
  GIRO_ABAJODER,
  GIRO_ARRIBAIZQ,
  GIRO_ABAJOIZQ,
  PASTO
};

class Track : public Event {
private:
  uint16_t height;
  uint16_t width;
  std::vector<int> blocks;
  std::vector<TrackPiece> tracks;
  
public:
  Track(uint16_t height, uint16_t width, std::vector<int> blocks);
  Track(std::string event);
  std::string ToStr();
  void render(SDL_Window* w, SDL_Renderer* r);
private:
  std::map<int,Image*> tracksImages(SDL_Window* w, SDL_Renderer* r);
  void initialiceTrackPieces(b2World& world, std::vector<int> blocks);
};

#endif