#include "TrackView.h"

TrackView::TrackView(SDL_Window* w, SDL_Renderer* r, Track& t)
  : window(w), renderer(r), track(t)
{}

void TrackView::render(SDL_Rect& camara) {
  track.render(window, renderer, camara);
}
