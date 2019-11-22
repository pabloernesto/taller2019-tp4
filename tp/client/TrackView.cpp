#include "TrackView.h"
#include "../common/Configuration.h"

extern Configuration configuration;

static std::vector<std::string> image_paths;

TrackView::TrackView(ImageCache& i)
  : imagecache(i)
{
  if (image_paths.size() == 0) image_paths = {
    configuration.IMAGES_ROUTE + "horizontal.bmp",
    configuration.IMAGES_ROUTE + "vertical.bmp",
    configuration.IMAGES_ROUTE + "giro_arribader.bmp",
    configuration.IMAGES_ROUTE + "giro_abajoder.bmp",
    configuration.IMAGES_ROUTE + "giro_arribaizq.bmp",
    configuration.IMAGES_ROUTE + "giro_abajoizq.bmp",
    configuration.IMAGES_ROUTE + "pasto.bmp"
  };
}

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
      auto& trackimage = imagecache.getImage(configuration.IMAGES_ROUTE + "gray.jpg");
      std::vector<Sound*> sounds = {};
      camara.renderMe(position, size, trackimage, sounds, 0, 0);
    }
}