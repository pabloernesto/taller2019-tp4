#ifndef TRACKVIEW_H_
#define TRACKVIEW_H_

#include <SDL2/SDL.h>
#include "../common/TrackPiece.h"
#include "../common/Track.h"
#include "../common/Camara.h"
#include <memory>

class TrackView {
private:
  Track& track;
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::vector<std::unique_ptr<Image>> track_images;

public:
  TrackView(SDL_Window* w, SDL_Renderer* r, Track& t);
  void render(Camara& camara, std::vector<std::unique_ptr<TrackPiece>>& track_pieces);
};

#endif    // TRACKVIEW_H_
