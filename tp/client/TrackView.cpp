#include "TrackView.h"
#include <iostream>

TrackView::TrackView(SDL_Window* w, SDL_Renderer* r, Track& t)
  : window(w), renderer(r), track(t){
  track_images.emplace_back(new Image("../client/Imagenes/horizontal.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/vertical.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/giro_arribader.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/giro_abajoder.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/giro_arribaizq.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/giro_abajoizq.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/pasto.bmp", w, r));
}

void TrackView::render(Camara& camara, std::vector<std::unique_ptr<TrackPiece>>& track_pieces) { 
  for (auto it = track_pieces.begin(); it != track_pieces.end(); it++){
    b2Vec2 pos;
    std::vector<float> pos_vec = (*it)->GetPosition();
    pos.x = pos_vec[0];
    pos.y = pos_vec[1];
    b2Vec2 size;
    size.x = ((*it)->GetSize())[0];
    size.y = ((*it)->GetSize())[1];
    if ((*it)->getTrackType() != 6){
      std::cout << "Asfalto!" << '\n';
    }
    camara.renderMe(pos, size, *(this->track_images[(*it)->getTrackType()]), 0);
  }
}
