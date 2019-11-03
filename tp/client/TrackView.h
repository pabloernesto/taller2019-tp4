#ifndef TRACKVIEW_H_
#define TRACKVIEW_H_

#include <SDL2/SDL.h>
#include "../common/TrackPiece.h"
#include "../common/Track.h"
#include "../common/Camara.h"
#include "../common/ImageCache.h"
#include <memory>

class TrackView {
private:
  Track& track;
  ImageCache& imagecache;

public:
  TrackView(ImageCache& i, Track& t);
  void render(Camara& camara, std::vector<std::unique_ptr<TrackPiece>>& track_pieces);
};

#endif    // TRACKVIEW_H_
