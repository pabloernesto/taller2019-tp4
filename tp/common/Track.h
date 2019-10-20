#ifndef TRACK_H_
#define TRACK_H_
#include "Event.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Track : public Event {
private:
  uint16_t height;
  uint16_t width;
  std::vector<int> blocks;
  
public:
  Track(uint16_t height, uint16_t width, std::vector<int> blocks);
  Track::Track(std::string event);
  std::string ToStr();
  void render(SDL_Window* w, SDL_Renderer* r);
private:
  std::map<int,Image> Track::tracks(SDL_Window* w, SDL_Renderer* r);
};

#endif