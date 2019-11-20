#include "TrackView.h"

static const std::vector<std::string> image_paths = {
  "Imagenes/horizontal.bmp",
  "Imagenes/vertical.bmp",
  "Imagenes/giro_arribader.bmp",
  "Imagenes/giro_abajoder.bmp",
  "Imagenes/giro_arribaizq.bmp",
  "Imagenes/giro_abajoizq.bmp",
  "Imagenes/pasto.bmp"
};

TrackView::TrackView(ImageCache& i)
  : imagecache(i)
{}

void TrackView::render(Camara& camara, std::vector<std::unique_ptr<TrackPieceProxy>>& track_pieces) {
  for (auto it = track_pieces.begin(); it != track_pieces.end(); it++){
    std::vector<float> pos = (*it)->GetPosition();
    std::vector<float> size = (*it)->GetSize();


    auto trackcode = (*it)->getTrackType();
    renderBackGroundForPiece(camara, trackcode, pos, size);
    auto& trackimage = imagecache.getImage(image_paths[trackcode]);
    std::vector<Sound*> sounds = {};
    camara.renderMe(pos, size, trackimage, sounds, 0, 0);
  }
}

void TrackView::renderBackGroundForPiece(Camara& camara, int trackcode,
      std::vector<float> position, std::vector<float> size){
    if (trackcode > 1 && trackcode < 6){
      auto& trackimage = imagecache.getImage("Imagenes/gray.jpg");
      std::vector<Sound*> sounds = {};
      camara.renderMe(position, size, trackimage, sounds, 0, 0);
    }
}