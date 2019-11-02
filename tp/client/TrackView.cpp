#include "TrackView.h"

TrackView::TrackView(SDL_Window* w, SDL_Renderer* r, Track& t)
  : window(w), renderer(r), track(t)
{}

void TrackView::render(Camara& camara) {
  track.render(window, renderer, camara);
}
