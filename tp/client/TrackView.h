#ifndef TRACKVIEW_H_
#define TRACKVIEW_H_

#include <SDL2/SDL.h>
#include "TrackPieceProxy.h"
#include "Camara.h"
#include "ImageCache.h"
#include <memory>

class TrackView {
private:
  ImageCache& imagecache;

public:
  TrackView(ImageCache& i);
  void render(Camara& camara, std::vector<std::unique_ptr<TrackPieceProxy>>& track_pieces);

private:
  void renderBackGroundForPiece(Camara& camara, int trackcode,
      std::vector<float> position, std::vector<float> size);
};

#endif    // TRACKVIEW_H_
