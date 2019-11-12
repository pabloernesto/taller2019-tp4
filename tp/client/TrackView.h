#ifndef TRACKVIEW_H_
#define TRACKVIEW_H_

#include <SDL2/SDL.h>
#include "../common/TrackPiece.h"
#include "../common/Track.h"
#include "Camara.h"
#include "ImageCache.h"
#include <memory>

class TrackView {
private:
  Track& track;
  ImageCache& imagecache;

public:
  TrackView(ImageCache& i, Track& t);
  void render(Camara& camara, std::vector<std::unique_ptr<TrackPiece>>& track_pieces);

private:
  void renderBackGroundForPiece(Camara& camara, int trackcode, 
      std::vector<float> position, std::vector<float> size);
};

#endif    // TRACKVIEW_H_
