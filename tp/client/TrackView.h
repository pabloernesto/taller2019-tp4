#ifndef TRACKVIEW_H_
#define TRACKVIEW_H_

#include <SDL2/SDL.h>
#include "../common/Track.h"

class TrackView {
private:
  Track& track;
  SDL_Window* window;
  SDL_Renderer* renderer;

public:
  TrackView(SDL_Window* w, SDL_Renderer* r, Track& t);
  void render(SDL_Rect& camara);
};

#endif    // TRACKVIEW_H_
