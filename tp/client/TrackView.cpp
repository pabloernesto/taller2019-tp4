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

TrackView::TrackView(ImageCache& i, Track& t)
  : track(t), imagecache(i)
{}

void TrackView::render(Camara& camara, std::vector<std::unique_ptr<TrackPiece>>& track_pieces) {
  for (auto it = track_pieces.begin(); it != track_pieces.end(); it++){
    b2Vec2 pos;
    std::vector<float> pos_vec = (*it)->GetPosition();
    pos.x = pos_vec[0];
    pos.y = pos_vec[1];
    b2Vec2 size;
    size.x = ((*it)->GetSize())[0];
    size.y = ((*it)->GetSize())[1];

    auto trackcode = (*it)->getTrackType();
    if (trackcode > 1 && trackcode < 6){
      auto& trackimage = imagecache.getImage("Imagenes/gray.jpg");
      camara.renderMe(pos, size, trackimage, 0, 0);
    }
    auto& trackimage = imagecache.getImage(image_paths[trackcode]);
    camara.renderMe(pos, size, trackimage, 0, 0);
  }
}
